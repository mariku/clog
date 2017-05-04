test: foo.c log.h log.c
	clang -g foo.c log.c -o test -fsanitize=bounds
