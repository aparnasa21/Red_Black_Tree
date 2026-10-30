#include "rbt.h"

int find_maximum(tree_t **root, data_t *max)
{
	tree_t *temp = *root;

	if (temp == NULL)
		return FAILURE;

	while (temp->right)
		temp = temp->right;

	*max = temp->data;
	return SUCCESS;
}
