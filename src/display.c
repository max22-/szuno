#include "szuno.h"

void
display(result_t *r)
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