#include "szuno.h"

result_t
make_error(int idx)
{
	result_t res;
	res.type = ERROR;
	return res;
}

result_t
make_nil(int idx)
{
	result_t res;
	res.type = NIL;
	return res;
}

result_t
make_int(int i, int idx)
{
	result_t res;
	res.type = INT;
	res.i = i;
	res.idx = idx;
	return res;
}

result_t
make_char(char c, int idx)
{
	result_t res;
	res.type = CHAR;
	res.c = c;
	res.idx = idx;
	return res;
}

result_t
make_ident(const char *l, int start, int len, int idx)
{
	result_t res;
	res.type = IDENT;
	res.id.ps = l;
	res.id.start = start;
	res.id.len = len;
	res.idx = idx;
	return res;
}