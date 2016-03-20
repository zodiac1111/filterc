#ifndef T_HEAD
#define T_HEAD
#  define CL_RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define BLUE "\033[34m"
#  define PURPLE "\033[35m"
#  define CL_ATTR_REV "\033[7m"
#  define CL_ATTR_UNDERLINE "\033[4m"
#  define _COLOR "\033[0m"

#define ATCOMMAND_DEBUG 0
#  define CLOG_INFO(fmt, ...) \
		printf("I"GREEN"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__)
#  define CLOG_WARN(fmt, ...) \
		printf("I"YELLOW"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__)
#  define CLOG_ERR(fmt, ...) \
		printf("E"CL_RED"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__)

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
