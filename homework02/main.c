#include "linkedlist.h"

list_t *cellphone_list = NULL;

int cellphone_cmp_price(void *data1, void *data2)
{
	cellphone_t *cell1, *cell2;
	cell1 = (cellphone_t *)data1;
	cell2 = (cellphone_t *)data2;
	return (cell1->price >= cell2->price)? 0 : -1;
}

int cellphone_del_data(void *data)
{
	cellphone_t *cell;
	cell = (cellphone_t *)data;
	free(cell);
  	return 0;
}

cellphone_t *cellphone_data_create()
{
	cellphone_t *new;
	new = (cellphone_t *)malloc(sizeof(cellphone_t));
	return new;
}

node_t *cellphone_lookup_by_code(char *code)
{
	int i;
	node_t *node;
	cellphone_t *data;

	if((!cellphone_list) || (!cellphone_list->head) || (!code))
		return NULL;
	
	for(node = cellphone_list->head; node; node = node->next)
	{
		data = (cellphone_t *)node->data;
		if(!data)
			continue;
		
		if(strcmp(data->product_code, code) == 0)
			return node;
		else
			continue;
	}
	
	return NULL;
}

void cellphone_print_data(node_t *node)
{
	cellphone_t *data;
	
	data = (cellphone_t *)node->data;
	if(!data)
		return;
	
	printf("Product code: %s\n", data->product_code);
	printf("Product name: %s\n", data->product_name);
	printf("Price: %u\n", data->price);
	printf("Inventory number: %u\n", data->inventory_num);
	printf("\n");
}

node_t *cellphone_lookup_approximate_price(unsigned int price)
{
	int value, abs_val;
	node_t *best = NULL, *node = NULL;
	cellphone_t *data;
	
	if((!cellphone_list) || (!cellphone_list->head))
		return NULL;
	
	best = cellphone_list->head;
	for(node = cellphone_list->head; node; node = node->next)
	{
		if(node == cellphone_list->head)
		{
			best = node;
			data = (cellphone_t *)best->data;
			if(!data)
				return NULL;
			value = price - data->price;
      		abs_val = abs(value);
			continue;
		}

		data = (cellphone_t *)node->data;
		if(!data)
			continue;

    	value = price - data->price;
		if((abs(value)) < abs_val)
		{
			best = node;
			abs_val = abs(value);
		}
	}
	
	return best;
}

int cellphone_data_add()
{
	cellphone_t *cellphone_new;
	node_t *node;

	if(cellphone_list == NULL)
	{
		cellphone_list = list_create(cellphone_cmp_price, cellphone_del_data);
		if(!cellphone_list)
		{
			printf("Cannot create list of cellphone!\n");
			return -1;
		}
	}

	cellphone_new = cellphone_data_create();
	if(cellphone_new == NULL)
	{
		printf("Cannot create a new cellphone data!\n");
		return -1;
	}

  	fflush(stdin);
	printf("Enter product code for new cellphone: ");
	scanf("%s", cellphone_new->product_code);
  	getchar();
	printf("Enter product name for new cellphone: ");
	scanf("%[^\n]", cellphone_new->product_name);
	printf("Enter price of new cellphone: ");
	scanf("%u", &cellphone_new->price);
	printf("Enter inventory number: ");
	scanf("%u", &cellphone_new->inventory_num);
	
	node = listnode_add(cellphone_list, cellphone_new);
	if(node == NULL)
	{
		printf("Cannot add cellphone data to a node!\n");
		return -1;
	}

  	//printf("count = %d\n", cellphone_list->count);
	
	return 0;
}

void cellphone_data_delete()
{
	char code[PRODUCT_CODE] = {0};
	node_t *node;
	cellphone_t *data;
	
	if((!cellphone_list) || (!cellphone_list->head))
	{
		printf("Don't have any data to delete!\n");
		return;
	}
	
	printf("Enter code of product deleted: ");
	scanf("%s", code);
	
	node = cellphone_lookup_by_code(code);
	if(!node)
	{
		printf("Cannot find product to delete!\n");
		return;
	}
	
	data = (cellphone_t *)node->data;
	listnode_delete(cellphone_list, data);
}

void cellphone_inventory_edit()
{
	char code[PRODUCT_CODE] = {0};
	node_t *node;
	cellphone_t *data;
	unsigned int num;
	
	if((!cellphone_list) || (!cellphone_list->head))
	{
		printf("Don't have any data to edit!\n");
		return;
	}
	
	printf("Enter code of product edited: ");
	scanf("%s", code);
	
	node = cellphone_lookup_by_code(code);
	if(!node)
	{
		printf("Cannot find product to edit!\n");
		return;
	}
	
	cellphone_print_data(node);
	data = (cellphone_t *)node->data;
	printf("Update inventory of product %s\n", data->product_code);
	printf("New inventory number = ");
	scanf("%u", &data->inventory_num);
}

void cellphone_data_search()
{
	node_t *node;
	unsigned int price;
	
	printf("Enter approximate price to search: ");
	scanf("%u", &price);
	
	node = cellphone_lookup_approximate_price(price);
	if(!node)
	{
		printf("Cannot find cellphone with approximate price!\n");
		return;
	}
		
	printf("Cellphone with the most approximate price:\n");
	cellphone_print_data(node);
	
	if(!node->prev)
		printf("Cannot find the product below!\n");
	else
		cellphone_print_data(node->prev);
	
	if(!node->next)
		printf("Cannot find the product above!\n");
	else
		cellphone_print_data(node->next);
}

void cellphone_data_dump()
{
	unsigned int menu;
	node_t *node;

GOTO:	
	printf("Prinr all cellphone data (1: incremental; 2: descending): ");
	scanf("%u", &menu);

	if(menu == 1)
	{
		for(node = cellphone_list->head; node; node = node->next)
			cellphone_print_data(node);
	}
	else if (menu == 2)
	{
		for(node = cellphone_list->tail; node; node = node->prev)
			cellphone_print_data(node);
	}
	else
	{
		printf("Only choose 1 or 2!\n");
		goto GOTO;
	}
}

int main()
{
	int menu, ret, term_prog = 0;
	
	while(1)
	{
	    printf("1: Add a cellphone information\n");
	    printf("2: Delete a cellphone information\n");
	    printf("3: Edit inventory number\n");
	    printf("4: Search a product by approximate price\n");
	    printf("5: Dump all products\n");
	    printf("6: Terminate program\n");
		printf("Enter menu: ");
		scanf("%d", &menu);

		switch(menu)
		{
			case 1: /* Add a cellphone information */
				ret = cellphone_data_add();
				if(ret < 0)
					term_prog = 1;
				break;

			case 2: /* Delete a cellphone information */
				cellphone_data_delete();
				break;

			case 3: /* Edit inventory number */
				cellphone_inventory_edit();
				break;

			case 4: /* Search a product by approximate price */
				cellphone_data_search();
				break;

			case 5: /* Dump all products */
				cellphone_data_dump();
				break;

			case 6: /* Terminate program */
				term_prog = 1;
				break;

			default:
				printf("Please enter menu from 1->6\n");
				break;
		}
		
		if(term_prog)
			break;
		printf("----------------------------------------------------\n");
		printf("\n");
	}

	return 0;
}