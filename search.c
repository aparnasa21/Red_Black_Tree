#include "rbt.h"

int search(tree_t *root, data_t item)
{
	while (root)
	{
		if (item == root->data)
			return SUCCESS;
		root = (item < root->data) ? root->left : root->right;
	}
	return FAILURE;
}
