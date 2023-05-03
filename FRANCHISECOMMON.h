#ifndef FRANCHISECOMMON_H
#define FRANCHISECOMMON_H
#include "FRANCHISECOMMON.h"
typedef struct DATA{
	char prod_name[10];
	int prod_count;
	int money;
}DATA;
typedef struct PRODUCT{
	DATA d;
	struct PRODUCT *left;
	struct PRODUCT *right;
}PRODUCT;
typedef struct PART{
	char name[10];
	struct PART *link[5];
	PRODUCT  *prod;
	int index;
}PART;
typedef struct STACK{
	struct PART *p;
	struct STACK *link;
}STACK;
STACK *top;
typedef struct SUM{
	int sum_prod_count;
	struct SUM *link;
}SUM;
#endif

