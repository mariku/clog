from lxml import etree
import logging
import click
import jinja2

#------------------------------------------------------------------------------


@click.group()
def cli():
    pass

#------------------------------------------------------------------------------

template = jinja2.Template("""
#include <stdio.h>
#include "munit.h"

int tests_run = 0;
/* test functions declarations */
{% for i in functions -%}
char* {{i}}(void);
{% endfor %}

/* execute all tests */
static char * all_tests() {
{% for i in functions %}
    printf("starting test {{i}}\\n");
    mu_run_test({{i}});
    printf("finished test {{i}}\\n");
{% endfor %}
    return 0;
}

/* main */
int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\\n", result);
    }
    else {
        printf("ALL TESTS PASSED\\n");
    }
    printf("Tests run: %d\\n", tests_run);
    return result != 0;
}
""")

#------------------------------------------------------------------------------

@cli.command()
@click.option('--input-file')
@click.option('--output-file')
def generate(input_file, output_file):
    logging.info("input_file: %s, output_file: %s", input_file, output_file)
    functions = get_functions(input_file)
    logging.info("Functions: %s", functions)
    with open(output_file, 'w') as f:
        f.write(template.render(functions=functions))

#------------------------------------------------------------------------------


def get_functions(xml):
    with open(xml) as f:
        root = etree.parse(f)
    return [i.find('name').text for i in root.iterfind('.//member')
            if i.get('kind') == 'function']


#------------------------------------------------------------------------------

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    cli()
