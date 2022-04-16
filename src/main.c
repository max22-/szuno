#include <stdio.h>
#include <stdarg.h>

#include "szuno.h"

int
main(int argc, char *argv[])
{
	char buffer[1024];
	while(!feof(stdin)) {
		printf("> ");
		fflush(stdout);
		fgets(buffer, sizeof(buffer), stdin);
		eval(buffer);
	}
	return 0;
}

void
error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

void
print(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

result_t
user_builtin(const char *l, int idx)
{
	result_t op = token(ident, l, idx);
	check(op);
	if(streq(&op, "hello")) {
		printf("Hello, World !\n");
		return make_nil(op.idx);
	}
	return make_error(idx);
}