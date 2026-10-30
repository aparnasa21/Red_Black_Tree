#include "rbt.h"

int delete_minimum(tree_t **root)
{
	data_t min;

	if (find_minimum(root, &min) == FAILURE)
		return FAILURE;

	return delete(root, min);
}
