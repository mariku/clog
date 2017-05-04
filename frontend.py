import json
import logging
import click

#------------------------------------------------------------------------------


@click.group()
def cli():
    pass

#------------------------------------------------------------------------------


@cli.command()
@click.option('--input-file')
def convert(input_file):
    # todo use classes
    d = get_dictionary(input_file)
    test1 = (0, 10, 3)
    convert_msg(d, test1)
    test2 = (0, 10, 4)
    convert_msg(d, test2)

#------------------------------------------------------------------------------


def get_dictionary(input_file):
    with open(input_file) as f:
        return json.load(f)

#------------------------------------------------------------------------------


def convert_msg(d, data):
    try:
        channel = d['channels'][data[0]]
    except IndexError:
        logging.warn("Unkown channel id: %s", data[0])
    try:
        message = [m for m in d['messages']
                   if m['channel'] == channel['name']
                   if m['line'] == data[1]][0]
    except IndexError:
        logging.warn("Unkown msg: channel: %s line: %s",
                     channel, data[1])

    logging.info(message['msg'].format(*tuple(data[2:])))

#------------------------------------------------------------------------------

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    cli()

#------------------------------------------------------------------------------
