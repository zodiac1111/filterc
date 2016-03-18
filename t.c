#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <regex.h>

#include "t.h"

#define DEBUG_SEARCH 1
int main(void)
{
	CLOG_INFO("start");
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int n = 0;
	char get[200] = { 0 };
	int r = 0;
	int reti;
	fp = fopen("simple.c", "r");
	if (fp==NULL) {
		return -1;
	}
	Node* root = new_node(0, 0);
	regex_t regex_if;
	regex_t regex_else;
	regex_t regex_endif;
	/* Compile regular expression */
	reti = regcomp(&regex_if, "\\s*#\\s*if.*$", 0);
	if (reti) {
		CLOG_ERR("Could not compile regex\n");
		exit(1);
	}
	reti = regcomp(&regex_else, "\\s*#\\s*el.*$", 0);
	if (reti) {
		CLOG_ERR("Could not compile regex\n");
		exit(1);
	}
	reti = regcomp(&regex_endif, "\\s*#\\s*endif.*$", 0);
	if (reti) {
		CLOG_ERR("Could not compile regex\n");
		exit(1);
	}
	Node* s_if = root;
	Node* cnode = root;
	Node* hnode[10] = { NULL };
	Node* s_else = root;
	Node* s_end = root;
	int level = 0;
	while ((read = getline(&line, &len, fp))!=-1) {
		n++;
		//printf("%d [%zu]:	%s",n, read,line);
		/* Execute regular expression */
		reti = regexec(&regex_if, line, 0, NULL, 0);
		if (!reti) {
			CLOG_INFO("找到if %d, \"%s\"", n, line);
			cnode = create_add_child(cnode, n, 0);
			hnode[level] = cnode;
			level++;
		}
		reti = regexec(&regex_else, line, 0, NULL, 0);
		if (!reti) {
			CLOG_INFO("找到else %d, \"%s\"", n, line);
			cnode = create_add_next(cnode, n, 0);
		}
		reti = regexec(&regex_endif, line, 0, NULL, 0);
		if (!reti) {
			CLOG_INFO("找到endif %d, \"%s\"", n, line);
			s_else = create_add_next(cnode, n, 0);
			level--;
			cnode = hnode[level];

		}
	}

	fclose(fp);

#if 0
	Node* n2 = create_add_next(root, 5, 13);
	Node* n3 = create_add_next(root, 13, 13);

	Node* n21 = create_add_child(n2, 7, 9);
	Node* n22 = create_add_next(n21, 9, 9);

	Node* n31 = create_add_child(n2, 10, 12);
	Node* n32 = create_add_next(n31, 12, 12);
#endif
	ptree(root);
	CLOG_INFO("search");
	//tree_search(root, root, 11);
	return 0;
}
/**
 *
 */
void make_tree()
{

}
/**
 * 打印树
 */
void ptree(Node* node)
{
	if (node!=NULL) {
		CLOG_INFO("node(%p) %d %d Child=%p Next=%p"
			, node, node->min, node->max, node->child, node->next);
		if (node->child!=NULL) {
			//CLOG_INFO("node-child %d %d", node->child->min, node->child->max);
			ptree(node->child);
		}
		if (node->next!=NULL) {
			//CLOG_INFO("node-next %d %d", node->next->min, node->next->max);
			ptree(node->next);
		}

	}
}
/**
 * 树中查找
 * @param root
 * @param q
 */
void tree_search(Node* curr, Node* pre, int q)
{
#if DEBUG_SEARCH
	CLOG_INFO("Now=find %d in  [%d %d]", q, curr->min, curr->max);
	CLOG_INFO("Pre=[%d %d]", pre->min, pre->max);
#endif
	if (curr->min<q&&curr->max>q) {
		CLOG_WARN("%d", curr->min);
		if (curr->child!=NULL) {
#if DEBUG_SEARCH
			CLOG_INFO("child");
#endif
			//pre = curr;
			//CLOG_INFO("Child=%d %d %d", curr->child->min, curr->child->max, q);
			tree_search(curr->child, curr, q);
		}
		if (curr->next!=NULL) {
#if DEBUG_SEARCH
			CLOG_INFO("next");
#endif
			//CLOG_INFO("Next=%d %d %d", curr->next->min, curr->next->max, q);
			tree_search(curr->next, curr, q);
		}
	} else {
		if (curr->min>q) {
			return;
		}
		if (pre->child!=NULL) {
			tree_search(pre->child, curr, q);
		}
	}
}
Node* create_add_child(Node* parent, int min, int max)
{
	Node* curr = new_node(min, max);
	add_child(parent, curr);
	return curr;
}

Node* create_add_next(Node* head, int min, int max)
{
	Node* curr = new_node(min, max);
	add_append(head, curr);
	return curr;
}
/**
 * 追加一个子节点,返回父节点
 * @param parent
 * @param child
 * @return
 */
Node* add_child(Node* parent, Node* child)
{
	if (parent==NULL) {
		parent = child;
		return child;
	}
	while (parent->child!=NULL) {
		parent = parent->child;
	}
	parent->child = child;
	return child;
}

/**
 * 追加后继节点,返回父节点
 * @param root
 * @param next
 * @return
 */
Node* add_append(Node* root, Node* last)
{
	if (root==NULL) {
		root = last;
		return last;
	}
	while (root->next!=NULL) {
		root = root->next;
	}
	root->next = last;
	return last;
}
/**
 * 新建一个节点
 * @param min
 * @param max
 * @return
 */
Node* new_node(int min, int max)
{
	Node* n = (Node*) malloc(sizeof(Node));
	if (n==NULL) {
		return n;
	}
	n->next = NULL;
	n->child = NULL;
	n->min = min;
	n->max = max;
	return n;
}
