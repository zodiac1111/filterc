#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <regex.h>

#include "t.h"
#define DEMO_SEARCH 11
#define DEBUG_SEARCH 0
int main(void)
{
	CLOG_INFO("start");
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int n = 0;
	int ret_regcomp;
	int ret_regexec;
	fp = fopen("simple.c", "r");
	if (fp==NULL) {
		return -1;
	}
	Node* root = new_node(0, 0);
	regex_t regex_if;
	regex_t regex_else;
	regex_t regex_endif;
	int search_num=0;
	/* Compile regular expression */
	ret_regcomp = regcomp(&regex_if, "\\s*#\\s*if.*$", 0);
	if (ret_regcomp) {
		CLOG_ERR("Could not compile regex\n");
		return (1);
	}
	ret_regcomp = regcomp(&regex_else, "\\s*#\\s*el.*$", 0);
	if (ret_regcomp) {
		CLOG_ERR("Could not compile regex\n");
		return(1);
	}
	ret_regcomp = regcomp(&regex_endif, "\\s*#\\s*endif.*$", 0);
	if (ret_regcomp) {
		CLOG_ERR("Could not compile regex\n");
		return(1);
	}
	Node* cnode = root;
	Node* hnode[10] = { NULL };
	int level = 0;
	while ((read = getline(&line, &len, fp))!=-1) {
		n++;
		//printf("%d [%zu]:	%s",n, read,line);
		/* Execute regular expression */
		ret_regexec = regexec(&regex_if, line, 0, NULL, 0);
		if (!ret_regexec) {
			CLOG_INFO("找到if [%d] %d, \"%s\"", level+1, n, line);
			cnode = create_add_child(cnode, n, 0);
			ptree(root);
			hnode[level] = cnode;
			level++;
		}
		ret_regexec = regexec(&regex_else, line, 0, NULL, 0);
		if (!ret_regexec) {
			CLOG_INFO("找到else [%d] %d, \"%s\"", level, n, line);
			cnode = create_add_next(cnode, n, 0);
			ptree(root);
		}
		ret_regexec = regexec(&regex_endif, line, 0, NULL, 0);
		if (!ret_regexec) {
			CLOG_INFO("找到endif [%d] %d, \"%s\"", level, n, line);
			level--;
			cnode = hnode[level];
			create_add_next(cnode, n, 0);
			fill_max(cnode, n);
			ptree(root);

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
	CLOG_WARN("打印树");
	ptree(root);
	CLOG_INFO("search");
	CLOG_WARN("start search %d", DEMO_SEARCH);
	tree_search(root, root, DEMO_SEARCH);
	while(1){
		CLOG_INFO("Input search num:0~%d",n);
		scanf("%d",&search_num);
		tree_search(root, root, search_num);
	}


	return 0;
}
/**
 * 填充最大值
 * @param link
 * @param max
 */
void fill_max(Node* link, int max)
{
	while (link!=NULL) {
		link->max = max;
		link = link->next;
		fill_max(link, max);
	}
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
	if (curr->min<q&&q<curr->max) {
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
