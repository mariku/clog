test: foo.c log.h log.c
	clang -g main.c bar.c foo.c log.c -o test -fsanitize=bounds LOGGING=LOGGING_ENABLED
