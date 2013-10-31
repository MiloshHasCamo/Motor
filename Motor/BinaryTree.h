#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdlib.h>

struct node
{
	void* val;
	node* left;
	node* right;
};

class BinaryTree
{
    public:
        BinaryTree();
        ~BinaryTree();

        void Insert ( int key );
        node *Search( int key );
        void DestroyTree();

    private:
        void DestroyTree ( node *leaf );
        void Insert ( int key, node *leaf );
        node *Search ( int key, node *leaf );
        
        node *root;
};

#endif//BINARYTREE_H_