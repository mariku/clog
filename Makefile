all: component_test unit_tests

component_test: foo.c logging.h logging.c main.c bar.c
	clang -g main.c bar.c foo.c logging.c -o $@ -fsanitize=bounds -DLOGGING=1
clean:
	rm -rf test

unit_tests: logging.c buffer_test.c logging.h
	doxygen
	python3 create_test_runner.py generate --input-file xml/index.xml --output-file test_runner.c
	clang -g test_runner.c logging.c buffer_test.c -DLOGGING=1 -o $@




