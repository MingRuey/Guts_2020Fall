#ifndef _FY_SHUFFLE__
#define _FY_SHUFFLE__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"
#include "time.h"


// Get length of single linked-list
int getlength(node_t *head)
{
    int len = 0;
    while (head) {
        head = head->next;
        len++;
    }
    return len;
}

// Move pointer k steps forward
void to_kth_node(node_t **start, int k)
{
    while (k--) {
        if (!(*start)) { break; }
        *start = (*start)->next;
    }
}

// Swap positions of two nodes in linked-list
void swap_inplace(node_t *node1, node_t *node2)
{
    node_t tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
    node2->next = node1->next;
    node1->next = tmp.next;
}

// Fisher-Yates shuffle on single linked-list, inplace.
void fyshuffle(node_t **head)
{
    unsigned int randseed = time(NULL);
    node_t *current = *head;
    for (int len = getlength(*head); len > 1; len--) {
        int rnd = rand_r(&randseed) % len;
        node_t *target = current;
        to_kth_node(&target, rnd);
        swap_inplace(target, current);
        current = current->next;
    }
}

#endif