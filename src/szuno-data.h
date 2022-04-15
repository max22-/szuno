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

/* Display */
void display(result_t *r);