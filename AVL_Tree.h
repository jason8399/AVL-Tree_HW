//AVL_Tree.h

#define TRUE 1;
#define FALSE 0;

typedef struct {
	int key;
} element;

typedef struct treeNode *treePointer;

struct treeNode{
	treePointer leftChild;
	element data;
	int bf;
	treePointer rightChild;
};

typedef struct treeNode treeNode;

int avlFindMin(treePointer *parent);
int isLeaf(treePointer *parent);
void avlInsert(treePointer *parent, element x, int *unbalanced);
void avlDelete(treePointer *parent, element x, int *unbalanced);
void leftRotation(treePointer *parent, int *unbalanced);
void rightRotation(treePointer *parent, int *unbalanced);
int _print_t(treePointer *parent, int is_left, int offset, int depth, char s[20][255]);
void print_tree(treePointer *parent);
