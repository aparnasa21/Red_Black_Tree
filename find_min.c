#include "rbt.h"

int find_minimum(tree_t **root, data_t *min)
{
	tree_t *temp = *root;

	if (temp == NULL)
		return FAILURE;

	while (temp->left)
		temp = temp->left;

	*min = temp->data;
	return SUCCESS;
}
