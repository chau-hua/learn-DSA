#include "linkedlist.h"

list_t *cellphone_list = NULL;

int check_null_cellphone_list()
{
	return (cellphone_list == NULL);
}

int cellphone_data_add()
{
	if(check_null_cellphone_list())
	{
		cellphone_list = list_create();
		if(!cellphone_list)
		{
			printf("Cannot create list of cellphone!\n");
			return -1;
		}
	}

	
}

int cellphone_data_delete()
{

}

int cellphone_inventory_edit()
{

}

int cellphone_data_search()
{

}

int cellphone_data_dump()
{

}

int main()
{
	int menu;

	while(1)
	{
		printf("Enter menu: ");
		scanf("%d", &menu);

		switch(menu)
		{
			case 1: /* Add a cellphone information */

				break;

			case 2: /* Delete a cellphone information */

				break;

			case 3: /* Edit inventory number */

				break;

			case 4: /* Search a product by price */

				break;

			case 5: /* Dump all products */

				break;

			case 6: /* Terminate program */

				break;

			default:

				break;
		}
	}

	return 0;
}