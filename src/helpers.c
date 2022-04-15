#include "szuno.h"
#include "szuno-data.h"

int
streq(result_t *a, const char *b)
{
	int i;
	if(a->type != IDENT) {
		error("streq : expected string as argument\n");
		return 0;
	}
	for(i = 0; i < a->id.len; i++) {
		if(*b == 0)
			return 0;
		if(a->id.ps[a->id.start + i] != *b)
			return 0;

		b++;
	}
	return 1;
}

int
is_printable(char c)
{
	return c >= 0x20 && c <= 0x7e;
}

int
is_digit(char c)
{
	return c >= '0' && c <= '9';
}