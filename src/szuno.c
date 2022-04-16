#include "szuno.h"

/* for space handling */
result_t
token(evaluator_t evaluator, const char *l, int idx)
{
	int i = idx;
	result_t res;
	while(l[i] == ' ')
		i++;
	res = evaluator(l, i);
	if(res.type != ERROR)
		return res;
	else
		return make_error(idx);
}

result_t
integer(const char *l, int idx)
{
	int i = idx, res = 0;
	while(l[i] >= '0' && l[i] <= '9') {
		res = res * 10 + l[i] - '0';
		i++;
	}
	if(i == idx)
		return make_error(idx);
	return make_int(res, i);
}

result_t
ident(const char *l, int idx)
{
	int i = idx;
	char c = l[i];
	if(is_printable(c) && c != ' ' && c != '\"' && c != '\'' && !is_digit(c))
		i++;
	while(is_printable(l[i]) && l[i] != ' ')
		i++;
	if(i == idx)
		return make_error(idx);
	return make_ident(l, idx, i - idx, i);
}

result_t
expr(const char *l, int idx)
{
	result_t id, i;
	i = token(integer, l, idx);
	if(i.type != ERROR)
		return i;

	id = token(ident, l, idx);
	if(id.type != ERROR) {
		if(streq(&id, "+")) {
			result_t e1 = expr(l, id.idx);
			result_t e2;
			check(e1);
			e2 = expr(l, e1.idx);
			check(e2);
			return make_int(e1.i + e2.i, e2.idx);
		} else if(streq(&id, "*")) {
			result_t e1 = expr(l, id.idx);
			result_t e2;
			check(e1);
			e2 = expr(l, e1.idx);
			check(e2);
			return make_int(e1.i * e2.i, e2.idx);
		} else {
			error("invalid operator\n");
			display(&id);
			return make_error(idx);
		}
	} else {
		error("parse error\n");
		return make_error(idx);
	}
}

result_t
command(const char *l, int idx)
{
	result_t op = ident(l, idx);
	check(op);
	if(streq(&op, "print")) {
		result_t e = expr(l, op.idx);
		check(e);
		display(&e);
		return make_nil(e.idx);
	} else {
		display(&op);
		error("invalid statement\n");
		return make_error(idx);
	}
}

result_t
program(const char *l, int idx)
{
	return command(l, idx);
}

void
eval(const char *l)
{
	program(l, 0);
}
