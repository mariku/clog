all: component_test unit_tests

component_test: foo.c logging.h logging.c main.c bar.c
	clang -g main.c bar.c foo.c logging.c -o $@ -fsanitize=bounds -DLOGGING=1
clean:
	rm -rf test

unit_tests: logging.c buffer_test.c logging.h test_runner.c
	python3 create_test_runner.py generate --output-file test_runner.c --doxygen-dir doxy buffer_test.c --list-file tests.json
	clang -g test_runner.c logging.c buffer_test.c -DLOGGING=1 -o $@

.PHONY: run_component_test
run_component_test: component_test
	python3 frontend.py find_logs -o tests/component_test/logs.json -I . foo.c bar.c main.c
	python3 frontend.py convert --input-file tests/component_test/logs.json --executable ./component_test





