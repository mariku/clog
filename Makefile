test: foo.c logging.h logging.c main.c bar.c
	clang -g main.c bar.c foo.c logging.c -o test -fsanitize=bounds -DLOGGING=1
clean:
	rm -rf test
