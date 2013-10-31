#include "BinaryTree.h"

BinaryTree::BinaryTree ( )
{
	root = NULL;
}

BinaryTree::~BinaryTree ( )
{
	DestroyTree ( );
}

void BinaryTree::DestroyTree ( node* leaf )
{
	if ( leaf != NULL )
	{
		DestroyTree ( leaf->left );
		DestroyTree ( leaf->right );
		delete leaf;
	}
}

void BinaryTree::Insert ( int key, node* leaf )
{
	int* temp = (int*)leaf->val;
	int& temp2 = *temp;

	if ( key < temp2 )
	{
		if ( leaf->left != NULL )
		{
			Insert ( key, leaf->left );
		} else {
			leaf->left = new node;
			leaf->left->val = &key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	} else if ( key >= temp2 ) {
		if ( leaf->right != NULL ) {
			Insert ( key, leaf->right );
		} else {
			leaf->right = new node;
			leaf->right->val = &key;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
		}
	}
}

node* BinaryTree::Search ( int key, node* leaf )
{
	int* temp = (int*)leaf->val;
	int& temp2 = *temp;

	if(leaf!=NULL)
	{
		if ( key == temp2 )
		  return leaf;
		if(key<temp2)
		  return Search(key, leaf->left);
		else
		  return Search(key, leaf->right);
	}
	else return NULL;
}

node* BinaryTree::Search ( int key )
{
	return Search ( key, root );
}

void BinaryTree::DestroyTree ( )
{
	DestroyTree ( root );
}