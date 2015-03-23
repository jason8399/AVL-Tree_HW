//main.c

#include <stdio.h>
#include <stdlib.h>
#include "AVL_Tree.h"

void menu(){
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. EXIT\n");
}

int main(int argc, const char *argv[]){
	int unbalanced;
	char input[2];
	treePointer root = NULL;
	element x;
	while(1){
		menu();
		scanf("%s", input);
		switch(*input){
			case '1':
				printf("Please enter a number: \n");
				scanf("%d", &x.key);
				avlInsert(&root, x, &unbalanced);
				print_tree(&root);
				break;
			case '2':
				printf("Please enter a number: \n");
				scanf("%d", &x.key);
				avlDelete(&root, x, &unbalanced);
				print_tree(&root);
				break;
			case '3':
				return 0;
				break;
			default:
				printf("Unknow Comman\n");
		}
	}
	return 0;
}
