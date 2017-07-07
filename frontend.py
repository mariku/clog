import json
import logging
import click
import subprocess
import re
from simplestruct import Struct, Field
from pathlib import Path
import jinja2

#------------------------------------------------------------------------------


@click.group()
def cli():
    pass

#------------------------------------------------------------------------------

INTERNAL_ID = 0
LOST_MESSAGE_ID = 0

tlog = logging.getLogger("Target")

#------------------------------------------------------------------------------


class LogLine(Struct):
    level = Field
    channel = Field
    line = Field
    msg = Field
    parameters = Field

#------------------------------------------------------------------------------


class IgnoreLine(Exception):
    pass

#------------------------------------------------------------------------------


@cli.command()
@click.option('-o', '--output-file', required=True, type=Path)
@click.option('-I', '--include-path', multiple=True)
@click.option('-D', '--defines', multiple=True)
@click.argument('files', nargs=-1)
def find_logs(output_file, include_path, defines, files):
    logging.info("find_logs: output_file: %s"
                 " include_path: %s"
                 " defines: %s"
                 " files: %s",
                 output_file, include_path, defines, files)
    result = {'channels': [],
              'messages': []}
    for f in files:
        cpp_result = cpp(f, include_path, defines)
        channels, log_lines = parse_cpp_result(cpp_result)
        for c in channels:
            result['channels'].append({'file': f, 'name': c})
        for l in log_lines:
            result['messages'].append(l._asdict())
    try:
        output_file.parent.mkdir(parents=True)
    except FileExistsError:
        pass
    with output_file.open('w') as f:
        json.dump(result, f, indent=4)

#------------------------------------------------------------------------------


@cli.command()
@click.option('-o', '--output-dir', required=True, type=Path)
@click.option('-i', '--input-file', required=True, type=Path)
def generate(output_dir, input_file):
    d = get_dictionary(input_file)
    channels = d['channels']
    for id_, c in enumerate(channels, 1):
        c['id'] = id_
    h_template = jinja2.Template("""#include <logging.h>

{%for c in channels -%}
extern LogChannel {{c.name}};
{% endfor %}
""")
    c_template = jinja2.Template("""
#include <logging_gen.h>

void Logging_init_all() {
{%- for c in channels %}
    Logging_init(&{{c.name}}, {{c.id}});
{%- endfor %}
}

void Logging_dump_all() {
{%- for c in channels %}
    Logging_dump(&{{c.name}});
{%- endfor %}
}
    """)
    with (output_dir / 'logging_gen.h').open('w') as f:
        f.write(h_template.render(channels=channels))
    with (output_dir / 'logging_gen.c').open('w') as f:
        f.write(c_template.render(channels=channels))


#------------------------------------------------------------------------------


def cpp(filename, include_path, defines):

    return subprocess.check_output(['cpp', '-E', filename]
                                   + ['-I' + i for i in include_path]
                                   + ['-D' + d for d in defines]
                                   + ['-D' 'LOGGING=2']).decode('utf-8')


#------------------------------------------------------------------------------


def parse_cpp_result(cpp_result):
    channels = []
    log_lines = []
    pattern = re.compile('.*--- (.*?:) (.*) ---.*')
    rest_pattern = re.compile('.*"(.*?)"(.*)')  # TODO support \"
    for l in cpp_result.splitlines():
        m = pattern.match(l)
        if m:
            type_ = m.group(1)[:-1]
            data = m.group(2)
            if type_ == "channel":
                channels.append(data)
            elif type_ in ["debug"]:
                channel, line, rest = data.split(',', 2)
                line = int(line)
                parsed_rest = rest_pattern.match(rest)
                if parsed_rest:
                    msg = parsed_rest.group(1)
                    parameters = parsed_rest.group(2).split(',')
                    parameters = [p.strip() for p in parameters if p]
                    log_lines.append(LogLine(type_, channel, line, msg,
                                             parameters))
                else:
                    logging.warn("failed to parse msg! line: %s", l)
            else:
                logging.warn("Invalid log level: %s", type_)
            logging.debug("+%s", l)
        else:
            logging.debug("!%s", l)
    return channels, log_lines

#------------------------------------------------------------------------------


@cli.command()
@click.option('--input-file')
@click.option('--executable')
def convert(input_file, executable):
    # todo use classes
    d = get_dictionary(input_file)
    p = subprocess.Popen(args=executable,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         universal_newlines=True)

    while p.poll() is None:
        line = p.stdout.readline()
        line = line.strip()
        try:
            convert_msg(d, line)
        except IgnoreLine:
            pass
    for line in p.stdout.readlines():
        line = line.strip()
        try:
            convert_msg(d, line)
        except IgnoreLine:
            pass

#------------------------------------------------------------------------------


def get_dictionary(input_file):
    with open(str(input_file)) as f:
        return json.load(f)

#------------------------------------------------------------------------------


def convert_msg(d, line):
    channel_id, line_number, parameter = parse_line(line)
    if channel_id == INTERNAL_ID:
        _convert_internal_msg(d, line_number, parameter)
    else:
        _convert_msg(d, line, channel_id, line_number, parameter)

#------------------------------------------------------------------------------


def _convert_internal_msg(d, id_, parameter):
    if id_ == LOST_MESSAGE_ID:
        channel_id = int(parameter[0])
        channel = d['channels'][channel_id - 1]
        number_of_lost_messages = int(parameter[1])
        tlog.warn("Messages lost: channel: %s, number of messages: %d",
                  channel, number_of_lost_messages)
    else:
        logging.warn("Unknown interal id: %s", id_)

#------------------------------------------------------------------------------


def _convert_msg(d, line, channel_id, line_number, parameter):
    try:
        channel = d['channels'][channel_id - 1]
    except IndexError:
        logging.warn("Unkown channel id: %s", channel_id)
        raise IgnoreLine
    try:
        message = [m for m in d['messages']
                   if m['channel'] == channel['name']
                   if m['line'] == line_number][0]
    except IndexError:
        logging.warn("Unkown msg: channel: %s line: %s",
                     channel, line)
        raise IgnoreLine

    tlog.info(message['msg'].format(*parameter))

#------------------------------------------------------------------------------


def parse_line(line):
    try:
        cid, line, *parameter = line.split(',')
        return int(cid), int(line), parameter
    except Exception as e:
        logging.info("Failed to parse line: '%s' exception: %s",
                     line, e)
        raise IgnoreLine

#------------------------------------------------------------------------------

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    cli()

#------------------------------------------------------------------------------
