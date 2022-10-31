#ifndef _TLDLIST_H_INCLUDED_
#define _TLDLIST_H_INCLUDED_

#include <malloc.h>
#include <stdio.h>
#include "date.h"
#include "tldlist.h"
#include <string.h>

typedef struct tldlist {
	struct tldnode* root;
	Date* time_begin;
	Date* time_end;
	int count;
}TLDList;
typedef struct tldnode {
	char* data;
	int add_num;
	struct tldnode* left;
	struct tldnode* right;
}TLDNode;
typedef struct tlditerator {
	int size;
	struct tldnode* now_pointer;
	struct tldnode* back;
}TLDIterator;


TLDList* tldlist_create(Date* begin, Date* end) {
	TLDList* List = malloc(sizeof(TLDList));
	if (List)
	{
		List->count = 0;
		List->root = NULL;
		List->time_begin = begin;
		List->time_end = end;
		return List;
	}
	else
	{
		return NULL;
	}
};



void destory_treenode(TLDNode* node)
{
	if (node != NULL)
	{
		destory_treenode(node->left);
		destory_treenode(node->right);
		free(node);
		node = NULL;
	}
}

void tldlist_destroy(TLDList* tld) {
	destory_treenode(tld->root);
	free(tld);
};



int tldlist_add(TLDList* tld, char* hostname, Date* d) {
	if ((date_compare(d,tld->time_begin)>=0)&&(date_compare(d,tld->time_end)<=0))
	{
		tld->count++;
		TLDNode* tldnode = malloc(sizeof(TLDNode));
		char* str_tld = malloc(sizeof((strrchr(hostname, '.') + 1)));
		str_tld = strcpy(str_tld, strrchr(hostname, '.') + 1);
		tldnode->data = str_tld;
		tldnode->add_num = 1;
		tldnode->left = NULL;
		tldnode->right = NULL;
		if (tld->root==NULL)
		{
			tld->root = tldnode;
		}
		else {
			TLDNode* pointer = tld->root;
			while (1)
			{
				if (strcmp(tldnode->data, pointer->data) == 0)
				{
					pointer->add_num++;
					break;
				}
				else if (strcmp(tldnode->data, pointer->data) < 0)
				{
					if (pointer->left==NULL)
					{
						pointer->left = tldnode;
						break;
					}
					else
					{
						pointer = pointer->left;
					}	
				}
				else {
					if (pointer->right == NULL)
					{
						pointer->right = tldnode;
						break;
					}
					else
					{
						pointer = pointer->right;
					}
				}
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
};






long tldlist_count(TLDList* tld) {
	return tld->count;
};




TLDIterator* tldlist_iter_create(TLDList* tld) {
	int size = tld->count;
	TLDIterator* iter = malloc(sizeof(TLDIterator));
	iter->size = size;
	TLDNode* pt = malloc(sizeof(TLDNode));
	iter->now_pointer = tld->root;
	iter->back = pt;
	return iter;
};




TLDNode* tldlist_iter_next(TLDIterator* iter) {
	TLDNode* back = malloc(sizeof(TLDNode));
	while (iter->now_pointer)
	{
		if (iter->now_pointer->left == NULL) {
			back = iter->now_pointer;
			iter->now_pointer = iter->now_pointer->right;
			return back;
		}
		else {
			iter->back = iter->now_pointer->left;
			while (iter->back->right!=NULL && iter->back->right != iter->now_pointer)
			{
				iter->back = iter->back->right;
			}
			if (iter->back->right==NULL)
			{
				iter->back->right = iter->now_pointer;
				iter->now_pointer = iter->now_pointer->left;
			}
			else
			{
				iter->back->right = NULL;
				back = iter->now_pointer;
				iter->now_pointer = iter->now_pointer->right;
				return back;
			}
		}
	}
	return NULL;
};




void tldlist_iter_destroy(TLDIterator* iter) {
	free(iter);
};


char* tldnode_tldname(TLDNode* node) {
	return node->data;
};



long tldnode_count(TLDNode* node) {
	return node->add_num;
};

#endif /* _TLDLIST_H_INCLUDED_ */
