
#------------------------------------------------------------------------------

from lxml import etree
import logging
import click
import jinja2
from pathlib import Path
import subprocess
import shutil
import json

#------------------------------------------------------------------------------


@click.group()
def cli():
    pass

#------------------------------------------------------------------------------

doxy_template = jinja2.Template("""

GENERATE_LATEX         = NO
GENERATE_HTML          = NO
GENERATE_XML          = YES
OUTPUT_DIRECTORY       = {{output_dir}}
INPUT= \\
{% for f in files -%}
    {{f}} \\
{% endfor %}
""")


c_template = jinja2.Template("""
#include <stdio.h>
#include "unittest.h"
#include <stdlib.h>

/* test functions declarations */
{% for i in functions -%}
char* {{i}}(void);
{% endfor %}

int test_run = 0;

/* execute single test */

static char * run_test(int test_id) {
    char* msg;
    switch(test_id) {
{% for i in functions %}
    case {{loop.index}}: {
        printf("{{i}} ");
        test_run++;
        msg = {{i}}();
        if(msg) {
            printf("[!!]\\n");
            return msg;
        }
        else{
            printf("[ok]\\n");
        }
        break;
    }
{% endfor %}
    default:
        return "Invalid test id";
    }
    return 0;
}

/* execute all tests */
static char * run_all_tests() {
    char* msg;
{% for i in functions %}
    msg = run_test({{loop.index}});
    if(msg) {
        return msg;
    }
{% endfor %}
    return 0;
}

/* main */
int main(int argc, char **argv) {
    char *result;
    int test_id;
    if(argc > 1) {
        test_id = atoi(argv[1]);
        result = run_test(test_id);
    }
    else{
        result = run_all_tests();
    }
    if (result != 0) {
        printf("%s\\n", result);
    }
    return result != 0;
}
""")

#------------------------------------------------------------------------------


@cli.command()
@click.option('--output-file', required=True)
@click.option('--list-file', required=True)
@click.option('--doxygen-dir', type=Path, required=True)
@click.argument('files', nargs=-1)
def generate(output_file, list_file, doxygen_dir, files):
    logging.info("files: %s, output_file: %s", files, output_file)
    run_doxygen(doxygen_dir, files)
    functions = get_functions(doxygen_dir / 'xml' / 'index.xml')
    logging.info("Functions: %s", functions)
    with open(output_file, 'w') as f:
        f.write(c_template.render(functions=functions))
    with open(list_file, 'w') as f:
        json.dump(functions, f, indent=4)

#------------------------------------------------------------------------------


def run_doxygen(doxygen_dir, input_files):
    doxyfile = doxygen_dir / 'doxyfile'
    doxygen_dir.mkdir(exist_ok=True)
    create_doxyfile(doxyfile, doxygen_dir, input_files)
    try:
        shutil.rmtree(str(doxygen_dir / "xml"))
    except FileNotFoundError:
        pass
    subprocess.check_call(['doxygen', str(doxyfile)])

#------------------------------------------------------------------------------


def create_doxyfile(doxyfile, doxygen_dir, input_files):
    with doxyfile.open('w') as f:
        f.write(doxy_template.render(files=input_files,
                                     output_dir=doxygen_dir))

#------------------------------------------------------------------------------


def get_functions(xml):
    with xml.open() as f:
        root = etree.parse(f)
    return [i.find('name').text for i in root.iterfind('.//member')
            if i.get('kind') == 'function'
            if i.find('name').text.startswith("test")]


#------------------------------------------------------------------------------

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    cli()
