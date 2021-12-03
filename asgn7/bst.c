#include "bst.h"
#include <stdio.h>
#include <stdlib.h>


//prof long's lecture slide
static int max(int x, int y){
	return x > y ? x : y;
}

Node *bst_create(void){
	return NULL;
}

//prof long's lecture slide
uint32_t bst_height(Node *root){
	if(root){
		return 1 + max(bst_height(root->left), bst_height(root->right));
	}
	return 0;
}

uint32_t bst_size(Node *root){
	if(root == NULL){
		return 0;
	}
	return 1 + bst_size(root->left) + bst_size(root->right);
}

//from prof slides check back on this NULL THING
Node *bst_find(Node *root, char *oldspeak){
	if(root){
		if(root->oldspeak > oldspeak){
			return bst_find(root->left, oldspeak);
		}
		else if(root->oldspeak < oldspeak) {
			return bst_find(root->right, oldspeak);
		}
	}
	return root;
}

//from prof slides
Node *bst_insert(Node *root, char *oldspeak, char *newspeak){
	if(root){
		if(root->oldspeak > oldspeak){
			root->left = bst_insert(root->left, oldspeak, newspeak);
		}
		else{
			root->right = bst_insert(root->right, oldspeak, newspeak);
		}
		return root;
	}
	return node_create(oldspeak, newspeak);
}

//from profs slides
void bst_print(Node *root){
	if(root){
		bst_print(root->left);
		printf("%s\n", root->oldspeak);
		bst_print(root->right);
	}
}

void bst_delete(Node **root){
	if(root == NULL){
		return;
	}
	
	//delete the subtrees
	bst_delete(&(*root)->left);
	bst_delete(&(*root)->right);
	
	free(root);
	return;
}