#ifndef T_HEAD
#define T_HEAD


typedef struct node{
	struct node* next;
	struct node* child;
	int min;
	int max;
}Node;

Node* new_node(int min,int max);

Node* add_child(Node* parent,Node* child);
Node* add_append(Node* root,Node* next);
Node* create_add_next(Node* root, int min, int max);
Node* create_add_child(Node* parent, int min, int max);
void tree_search(Node* root, Node* pre, int q);
void ptree(Node* node);
void fill_max(Node* link,int max);
#endif
