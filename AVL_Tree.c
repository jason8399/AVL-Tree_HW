//AVL_Tree.c

#include <stdio.h>
#include <stdlib.h>
#include "AVL_Tree.h"

int avlFindMin(treePointer *parent){ /* Find minimum node */
	treePointer current, pre;
	if((*parent)->leftChild){
		current = pre = (*parent)->leftChild;
		while(current != NULL){
			pre = current;
			current = current->rightChild;
		}
	}
	else{
		current = pre = (*parent)->rightChild;
	}
	return pre->data.key;
}

int isLeaf(treePointer *parent){
	if((*parent)->leftChild || (*parent)->rightChild) return FALSE;
	return TRUE;
}

void avlInsert(treePointer *parent, element x, int *unbalanced){
	if(!*parent){ /*insert element into null tree*/
		*unbalanced = TRUE;
		*parent = malloc(sizeof(treeNode));
		(*parent)->leftChild = (*parent)->rightChild = NULL;
		(*parent)->bf = 0;
		(*parent)->data = x;
	}
	else if(x.key < (*parent)->data.key){
		avlInsert(&(*parent)->leftChild, x, unbalanced);
		if(*unbalanced){
			/*left barnch has grown higher*/
			switch((*parent)->bf){
				case -1:
					(*parent)->bf = 0;
					*unbalanced = FALSE;
					break;
				case 0:
					(*parent)->bf = 1;
					break;
				case 1:
					leftRotation(parent, unbalanced);
					break;
			}
		}
	}
	else if(x.key > (*parent)->data.key){
		avlInsert(&(*parent)->rightChild, x, unbalanced);
		if(*unbalanced){
			/*right barnch has grown higher*/
			switch((*parent)->bf){
				case 1:
					(*parent)->bf = 0;
					*unbalanced = FALSE;
					break;
				case 0:
					(*parent)->bf = -1;
					break;
				case -1:
					rightRotation(parent, unbalanced);
					break;
			}
		}
	}
	else{
		*unbalanced = FALSE;
		printf("The key is already in the tree\n");
	}
}

void avlDelete(treePointer *parent, element x, int *unbalanced){
	int parentKey;
	if(!*parent){ /*No Node in tree*/
		*unbalanced = FALSE;
		printf("The Tree is empty or NOT Found\n");
		return;
	}
	parentKey = (*parent)->data.key;
	if((x.key == (*parent)->data.key) && isLeaf(parent)){ /* is leaf */
		free(*parent);
		*parent = NULL;
		*unbalanced = TRUE;
		return;
	}
	if((x.key == (*parent)->data.key) && !isLeaf(parent)){ /* is not leaf */
		parentKey = (*parent)->data.key;  //<== To save the key prevent the key change at 'is not leaf'
		x.key = avlFindMin(parent);
		(*parent)->data.key = x.key;
	}
	if(x.key < parentKey){
		avlDelete(&(*parent)->leftChild, x, unbalanced);
		if(*unbalanced){
			switch((*parent)->bf){
				case 1:
					(*parent)->bf = 0;
					break;
				case 0:
					(*parent)->bf = -1;
					*unbalanced = FALSE;
					break;
				case -1:
					delRightRotation(parent, unbalanced);
					*unbalanced = TRUE;
					break;
			}
		}
	}
	else if(x.key > parentKey){
		avlDelete(&(*parent)->rightChild, x, unbalanced);
		if(*unbalanced){
			switch((*parent)->bf){
				case -1:
					(*parent)->bf = 0;
					break;
				case 0:
					(*parent)->bf = 1;
					*unbalanced = FALSE;
					break;
				case 1:
					delLeftRotation(parent, unbalanced);
					*unbalanced = TRUE;
					break;

			}
		}
	}
}

void leftRotation(treePointer *parent, int *unbalanced){
	treePointer grandChild, child;
	child = (*parent)->leftChild;
	if(child->bf == 1){
		/* LL Rotation */
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else{
		/* LR Roatation */
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;
		grandChild->rightChild = *parent;
		switch(grandChild->bf){
			case 1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 0:
				(*parent)->bf = child->bf = 0;
				break;
			case -1:
				(*parent)->bf = 0;
				child->bf = 1;
				break;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void delLeftRotation(treePointer *parent, int *unbalanced){
	treePointer grandChild, child;
	child = (*parent)->leftChild;
	if(child->bf == 1){
		/* LL Rotation */
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
		(*parent)->bf = 0;
	}
	else{
		/* LR Roatation */
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;
		grandChild->rightChild = *parent;
		switch(grandChild->bf){
			case -1:
				(*parent)->bf = -1;
				child->bf = 0;
				break;
			case 1:
				(*parent)->bf = child->bf = 0;
				break;
			case 0:
				(*parent)->bf = 0;
				child->bf = 1;
				grandChild->bf = 1;
				break;
		}
		*parent = grandChild;
	}
	*unbalanced = TRUE;
}

void rightRotation(treePointer *parent, int *unbalanced){
	treePointer grandChild, child;
	child = (*parent)->rightChild;
	if(child->bf == -1){
		/* RR Rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else{
		/* RL Rotataion */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;
		switch(grandChild->bf){
			case -1:
				(*parent)->bf = 1;
				child->bf = 0;
				break;
			case 0:
				(*parent)->bf = child->bf = 0;
				break;
			case 1:
				(*parent)->bf = 0;
				child->bf = -1;
				break;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void delRightRotation(treePointer *parent, int *unbalanced){
	treePointer grandChild, child;
	child = (*parent)->rightChild;
	if(child->bf == -1){
		/* RR Rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
		(*parent)->bf = 0;
	}
	else{
		/* RL Rotataion */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;
		switch(grandChild->bf){
			case -1:
				(*parent)->bf = 1;
				child->bf = 0;
				break;
			case 1:
				(*parent)->bf = child->bf = 0;
				break;
			case 0:
				(*parent)->bf = 0;
				child->bf = -1;
				grandChild->bf = -1;
				break;
		}
		*parent = grandChild;
	}
	*unbalanced = TRUE;
}

int _print_t(treePointer *parent, int is_left, int offset, int depth, char s[20][255]){
	char b[20];
	int i ,width = 5;

	if (!*parent) return 0;

	sprintf(b, " %03d ", (*parent)->data.key);

	int left  = _print_t(&(*parent)->leftChild,  1, offset, depth + 1, s);
	int right = _print_t(&(*parent)->rightChild, 0, offset + left + width, depth + 1, s);

	for (i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {

		for (i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width/2 + i] = '=';

		s[2 * depth - 1][offset + left + width/2] = '|';
		s[2 * depth - 1][offset + left + width + right + width/2] = '|';

	} else if (depth && !is_left) {

		for (i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width/2 + i] = '=';

		s[2 * depth - 1][offset + left + width/2] = '|';
		s[2 * depth - 1][offset - width / 2 - 1] = '|';
	}
	return left + width + right;
}

void print_tree(treePointer *parent){
	char s[20][255];
	int i;
	for (i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_print_t(parent, 0, 0, 0, s);

	for (i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}
