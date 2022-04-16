typedef enum { ERROR,
	NIL,
	INT,
	CHAR,
	IDENT } result_type;

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

typedef result_t (*evaluator_t)(const char *, int);

/* Constructors */

result_t make_error(int);
result_t make_nil(int);
result_t make_int(int i, int idx);
result_t make_char(char c, int idx);
result_t make_ident(const char *l, int start, int len, int idx);

/* Helpers */
#define check(x) \
	{ \
		if((x).type == ERROR) return (x); \
	}

int streq(result_t *a, const char *b);
int is_printable(char c);
int is_digit(char c);

#define szuno_debug print

/* Display */
void display(result_t *r);

/* Evaluation */
result_t token(evaluator_t evaluator, const char *l, int idx);
result_t integer(const char *l, int idx);
result_t ident(const char *l, int idx);
result_t expr(const char *l, int idx);
result_t command(const char *l, int idx);
result_t program(const char *l, int idx);

void eval(const char *);


/* To be provided by the user */
void error(const char *, ...); 
void print(const char *, ...);

result_t user_builtin(const char *l, int idx);
