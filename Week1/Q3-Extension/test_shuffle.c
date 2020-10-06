#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "2020q3.h"
#include "shuffle.h"


void _print_list_helper(char *prefix, node_t *target)
{
    printf("    %s\n", prefix);
    printf("    ");
    print_list(target);
}

void test_get_length()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);
    add_entry(&head, 3);
    add_entry(&head, 4);
    assert(getlength(head) == 4);
}

void test_to_kth_node()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);
    add_entry(&head, 3);
    add_entry(&head, 4);

    node_t *target = head;
    printf("%s\n", __func__);
    _print_list_helper("before kth moving - head", head);
    _print_list_helper("before kth moving - target", target);
    to_kth_node(&target, 2);
    _print_list_helper("after kth moving - head", head);
    _print_list_helper("after kth moving - target", target);
}

void test_swap_inplace()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);
    add_entry(&head, 3);
    add_entry(&head, 4);

    node_t *target = head;
    printf("%s\n", __func__);
    _print_list_helper("before swap 1th <--> 3rd - head", head);
    _print_list_helper("before swap 1th <--> 3rd - target", target);
    to_kth_node(&target, 2);
    swap_inplace(head, target);
    _print_list_helper("after swap -1th <--> 3rd - head", head);
    _print_list_helper("after swap 1th <--> 3rd - target", target);
}

void test_shuffle()
{
    node_t *head = NULL;
    add_entry(&head, 1);
    add_entry(&head, 2);
    add_entry(&head, 3);
    add_entry(&head, 4);
    add_entry(&head, 5);
    add_entry(&head, 6);
    add_entry(&head, 7);

    printf("%s\n", __func__);
    _print_list_helper("before shuffle", head);
    fyshuffle(&head);
    _print_list_helper("after shuffle", head);
}


int main(int argc, char const *argv[])
{
    test_get_length();
    test_to_kth_node();
    test_swap_inplace();
    test_shuffle();
}
