#include "rbt.h"

/* Reads one integer. Returns SUCCESS, or FAILURE on bad input / end of input.
 * Bad input is discarded up to the end of the line so the menu cannot loop forever. */
static int read_int(int *value)
{
	int c;

	if (scanf("%d", value) == 1)
		return SUCCESS;

	if (feof(stdin))
		return FAILURE;

	while ((c = getchar()) != '\n' && c != EOF)
		;
	return FAILURE;
}

/* Frees every node of the tree (post-order). */
static void free_tree(tree_t *root)
{
	if (root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

int main(void)
{
	tree_t *root = NULL;
	data_t data;
	data_t minimum;
	data_t maximum;
	int operation;
	char option = 'n';

	do
	{
		printf("1. Insert\n2. Delete\n3. Find Minimum\n4. Delete Minimum\n5. Find Maximum\n6. Delete Maximum\n7. Search\n");
		printf("Enter your choice: ");
		if (read_int(&operation) == FAILURE)
		{
			if (feof(stdin))
				break;
			printf("Invalid input, please enter a number\n");
			option = 'y';
			continue;
		}

		switch (operation)
		{
			case 1:
				printf("Enter the data to be inserted into the RB Tree: ");
				if (read_int(&data) == FAILURE)
				{
					printf("Invalid input\n");
					break;
				}
				if (insert(&root, data) == FAILURE)
					printf("Insertion failed (duplicate or no memory)\n");
				print_tree(root);
				break;
			case 2:
				printf("Enter the data to be deleted from the RB Tree: ");
				if (read_int(&data) == FAILURE)
				{
					printf("Invalid input\n");
					break;
				}
				if (delete(&root, data) == FAILURE)
					printf("Deletion failed (data not found)\n");
				print_tree(root);
				break;
			case 3:
				if (find_minimum(&root, &minimum) == SUCCESS)
					printf("Minimum data: %d\n", minimum);
				else
					printf("Tree is empty\n");
				print_tree(root);
				break;
			case 4:
				if (delete_minimum(&root) == FAILURE)
					printf("Tree is empty\n");
				print_tree(root);
				break;
			case 5:
				if (find_maximum(&root, &maximum) == SUCCESS)
					printf("Maximum data: %d\n", maximum);
				else
					printf("Tree is empty\n");
				print_tree(root);
				break;
			case 6:
				if (delete_maximum(&root) == FAILURE)
					printf("Tree is empty\n");
				print_tree(root);
				break;
			case 7:
				printf("Enter the data to search: ");
				if (read_int(&data) == FAILURE)
				{
					printf("Invalid input\n");
					break;
				}
				if (search(root, data) == SUCCESS)
					printf("%d found\n", data);
				else
					printf("%d not found\n", data);
				break;
			default:
				printf("Invalid option\n");
		}
		printf("Want to continue? Press [yY | nN]: ");
		if (scanf(" %c", &option) != 1)
			option = 'n';
	} while (option == 'y' || option == 'Y');

	free_tree(root);
	return 0;
}
