#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRODUCT_CODE		24
#define PRODUCT_NAME		128

typedef struct cellphone
{
	char product_code[PRODUCT_CODE];
	char product_name[PRODUCT_NAME];
	unsigned int price;
	unsigned int inventory_num;
}cellphone_t;
