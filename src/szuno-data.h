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