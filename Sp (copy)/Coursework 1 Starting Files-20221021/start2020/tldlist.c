#ifndef _TLDLIST_H_INCLUDED_
#define _TLDLIST_H_INCLUDED_

#include <malloc.h>
#include <stdio.h>
#include "date.h"
#include "tldlist.h"
#include <string.h>

typedef struct tldlist{
    Date* begin_date;
    Date* end_date;
    struct tldnode* root;
    int total_count;
} TLDList;
typedef struct tldnode{
    char* hostname_tld;
    int count_number ;
    struct tldnode* left;
    struct tldnode* right;
} TLDNode;
typedef struct tlditerator{
    struct tldnode *leftnode[10000];
    int size;
    int top;
    struct tldnode* current_node;
} TLDIterator;

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end){
    TLDList* tld_list = malloc(sizeof(TLDList));
    if (tld_list){
        tld_list->begin_date = begin;
        tld_list->end_date = end;
        tld_list->root = NULL;
        tld_list->total_count = 0;
        return tld_list;
    }
    else{
        return NULL;
    }
};


/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld){
    free(tld);
};


/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
    if (date_compare(d,tld->begin_date) >= 0 && date_compare(d,tld->end_date) <= 0){
        tld->total_count ++ ;
        TLDNode* tld_node = malloc(sizeof(TLDNode));
        char* topleveldomains =  malloc(sizeof(strrchr(hostname,'.') + 1));
        tld_node->hostname_tld = topleveldomains;
        tld_node->left = NULL;
        tld_node->right = NULL;
        tld_node->count_number =1;
        // add the node 
        if(tld->root == NULL){
            tld->root = tld_node;
        }
        while (tld->root){
            if(strcmp(tld_node->hostname_tld,tld->root->hostname_tld) < 0){
                if(tld->root->left == NULL){
                    tld->root->left = tld_node;
                    break;
                }
                else{
                    tld->root = tld->root->left;
                }
                
            }
            else if(strcmp(tld_node->hostname_tld,tld->root->hostname_tld) > 0){
                if(tld->root->right == NULL){
                    tld->root->right = tld_node;
                    break;
                }
                else{
                    tld->root = tld->root->right;
                }
            }
            else if(strcmp(tld_node->hostname_tld,tld->root->hostname_tld) == 0){
                tld->root->count_number += 1;
                break;
            }
        }
        return 1;
    }
    else{
        return 0;
    }
};


/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
    return tld->total_count;
};

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator* iter = malloc(sizeof(TLDIterator));
    TLDNode* l_node = malloc(sizeof(TLDNode));
    l_node = tld->root;
    iter->current_node = l_node;
    iter->size = 0;
    iter->top = 0;

    while (l_node){
        iter->leftnode[iter->top++] = l_node;
        iter->size++;
        l_node = l_node->left;
    }
    if (!iter){
    	return NULL;
    }
    else{
    	return iter;
    }
};

int tldlist_iter_HasNext(TLDIterator *iter){
    if (iter->size > 0){
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
    if (tldlist_iter_HasNext(iter) == 0){
        return NULL;
    }
    TLDNode* next_node = malloc(sizeof(TLDNode));
    next_node = iter->leftnode[iter->top - 1];
    iter->size--;
    iter->top--;
    next_node = next_node->right;
    while (next_node){
        iter->leftnode[iter->top++] = next_node;
        iter->size++;
        next_node = next_node->left;
    }
    if(!next_node){
    	return NULL;
    }
    else{
    	return next_node;
    }
};

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
    free(iter);
};

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
    return node->hostname_tld;
};
    

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
    return node->count_number;
};

#endif /* _TLDLIST_H_INCLUDED_ */
