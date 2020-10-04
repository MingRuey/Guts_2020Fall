#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **head)
{
    for (node_t **current = head;
         *current && (*current)->next;
         current = &(*current)->next->next) {
        node_t *tmp = *current;
        *current = (*current)->next;
        tmp->next = (*current)->next;
        (*current)->next = tmp;
    }
}

void reverse(node_t **head)
{
    node_t *prev = NULL;
    while (*head) {
        node_t *next = (*head)->next;
        (*head)->next = prev;
        prev = *head;
        *head = next;
    }
    *head = prev;
}

/*
 * Reverse linked-list 'head',
 * attach the reversed end to tail,
 * and return the new head.
 */
node_t *rev_recursive(node_t *tail, node_t **head)
{
    node_t *next = (*head)->next;
    (*head)->next = tail;
    if (!next) {
        return *head;
    }
    return rev_recursive(*head, &next);
}

void reverse_recur(node_t **head)
{
    *head = rev_recursive(NULL, head);
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}
