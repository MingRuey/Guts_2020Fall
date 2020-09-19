// 考慮一個單向 linked list:
typedef struct __list {
    int data;
    struct __list *next;
} list;

// 在不存在環狀結構的狀況下，以下函式能夠對 linked list 元素從小到大排序，
// 請補完程式碼:
list *sort(list *start) {
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    LL0;

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right; ) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                LL1;
            } else {
                LL2;
                merge = merge->next;
            }
            LL3;
        } else {
            if (!merge) {
                LL4;
            } else {
                LL5;
                merge = merge->next;
            }
            LL6;
        }
    }
    return start;
}