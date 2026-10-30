#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

#define RED   0
#define BLACK 1
#define IS_RED(n) ((n) != NULL && (n)->color == RED)

typedef int data_t;

typedef struct node
{
	struct node *left;
	data_t data;
	struct node *right;
	int color;
}tree_t;

int insert(tree_t **root, data_t item);
int delete(tree_t **root, data_t item);
int search(tree_t *root, data_t item);
int find_minimum(tree_t **root, data_t *min);
int delete_minimum(tree_t **root);
int find_maximum(tree_t **root, data_t *max);
int delete_maximum(tree_t **root);
void print_tree(tree_t *root);
void rotate_left(tree_t **node);
void rotate_right(tree_t **node);

#endif
