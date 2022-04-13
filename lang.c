#include "lang.h"

/* Data structures */

typedef enum {ERROR, NIL, INT, CHAR, IDENT} result_type;

typedef struct {
  const char *ps;
  int start, len;
} substring_t;

typedef struct {
  result_type type;
  union {
    int i;
    char c;
    substring_t id;
  };
  int idx;
} result_t;

typedef result_t (*evaluator_t)(const char*, int);

/* Constructors */

result_t make_error(int idx)
{
  result_t res;
  res.type = ERROR;
  return res;
}

result_t make_nil(int idx)
{
  result_t res;
  res.type = NIL;
  return res;
}

result_t make_int(int i, int idx)
{
  result_t res;
  res.type = INT;
  res.i = i;
  res.idx = idx;
  return res;
}

result_t make_char(char c, int idx)
{
  result_t res;
  res.type = CHAR;
  res.c = c;
  res.idx = idx;
  return res;
}

result_t make_ident(const char *l, int start, int len, int idx)
{
  result_t res;
  res.type = IDENT;
  res.id.ps = l;
  res.id.start = start;
  res.id.len = len;
  res.idx = idx;
  return res;
}

/* Display */

void display(result_t *r)
{
  switch(r->type) {
  case ERROR:
    print("<error>\n");
    break;
  case NIL:
    print("<nil>\n");
    break;
  case INT:
    print("%d\n", r->i);
    break;
  case CHAR:
    print("%c\n", r->c);
    break;
  case IDENT: {
    int i;
    for(i = 0; i < r->id.len; i++)
      print("%c", r->id.ps[r->id.start + i]);
    print("\n");
    break;
  }
  default:
    error("display(): unexpected type\n");
  }
}

/* Helper functions */

#define check(x) { if((x).type == ERROR) return (x); }

int streq(result_t *a, const char *b)
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

#define is_printable(c) ((c) >= 0x20 && (c) <= 0x7e)
#define is_digit(c) ((c) >= '0' && (c) <= '9')

/* Evaluation */

/* for space handling */
result_t token(evaluator_t evaluator, const char *l, int idx)
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

result_t integer(const char *l, int idx)
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

result_t ident(const char *l, int idx)
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

result_t expr(const char *l, int idx)
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
    }
    else if(streq(&id, "*")) {
      result_t e1 = expr(l, id.idx);
      result_t e2;
      check(e1);
      e2 = expr(l, e1.idx);
      check(e2);
      return make_int(e1.i * e2.i, e2.idx);
    }
    else {
      error("invalid operator\n");
      display(&id);
      return make_error(idx);
    }
  } else {
    error("parse error\n");
    return make_error(idx);
  }
    
}

result_t stmt(const char *l, int idx)
{
  result_t command = ident(l, idx);
  check(command);
  if(streq(&command, "print")) {
    result_t e = expr(l, command.idx);
    check(e);
    display(&e);
    return make_nil(e.idx);
  }
  else {
    display(&command);
    error("invalid statement\n");
    return make_error(idx);
  }
  
}



result_t program(const char *l, int idx)
{
  return stmt(l, idx);
}

void eval(const char *l)
{
  program(l, 0);
}

