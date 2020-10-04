#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "2020q3.h"


void _print_list_helper(char *prefix, node_t *target)
{
    printf("    %s\n", prefix);
    printf("    ");
    print_list(target);
}

void test_swap_single_item()
{
    node_t *head = NULL;
    add_entry(&head, 1);

    printf("%s\n", __func__);
    _print_list_helper("before swap: ", head);
    node_t *new_head = swap_pair(head);
    _print_list_helper("after swap: ", new_head);
}

void test_swap_two_items()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);

    printf("%s\n", __func__);
    _print_list_helper("before swap: ", head);
    node_t *new_head = swap_pair(head);
    _print_list_helper("after swap: ", new_head);
}

void test_swap_multiple_items()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);
    add_entry(&head, 3);
    add_entry(&head, 4);

    printf("%s\n", __func__);
    _print_list_helper("before swap: ", head);
    node_t *new_head = swap_pair(head);
    _print_list_helper("after swap: ", new_head);
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;
    test_swap_single_item();
    test_swap_two_items();
    test_swap_multiple_items();
}
