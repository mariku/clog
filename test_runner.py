#------------------------------------------------------------------------------

import subprocess
import click
from pathlib import Path
import re
import json
import logging

#------------------------------------------------------------------------------


@click.group()
def cli():
    pass

#------------------------------------------------------------------------------


@cli.command()
@click.option('--executable', required=True)
@click.option('--list-file', required=True)
@click.option('--enable-logging/--disable-logging', default=False)
@click.argument('test_cases', nargs=-1)
def run(executable, list_file, enable_logging, test_cases):
    if enable_logging:
        logging.getLogger().setLevel(logging.INFO)
    with open(list_file) as f:
        functions = [(i, fn) for i, fn in enumerate(json.load(f), 1)]
    test_functions = []
    for t in test_cases:
        test_functions += [(i, fn) for i, fn in functions
                           if re.match(t, fn)
                           if (i, fn) not in test_functions]
    if not test_cases:
        test_functions = functions
    for i, fn in test_functions:
        run_test(executable, i, fn)

#------------------------------------------------------------------------------


def run_test(executable, test_id, name):
    logging.info("starting test: '%s'", name)
    try:
        subprocess.check_call([executable, "1", str(test_id)])
    except subprocess.CalledProcessError:
        logging.info("test: '%s' failed", name)
    else:
        logging.info("test: '%s' succeeded", name)

#------------------------------------------------------------------------------


if __name__ == '__main__':
    logging.getLogger().setLevel(logging.ERROR)
    cli()

#------------------------------------------------------------------------------
