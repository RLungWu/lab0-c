#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (head) {
        INIT_LIST_HEAD(head);
        return head;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (head == NULL) {
        return;
    }

    struct list_head *cur, *safe;

    list_for_each_safe (cur, safe, head) {
        element_t *free_node = list_entry(cur, element_t, list);
        free(free_node->value);
        list_del(cur);
        free(free_node);
    }

    free(head);
    return;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head) {  // false for queue is null
        return false;
    }

    element_t *new_elem = malloc(sizeof(element_t));
    if (!new_elem) {  // false for malloc failed
        return false;
    }

    new_elem->value = strdup(s);
    if (!new_elem->value) {  // false for strdup failed
        free(new_elem);
        return false;
    }

    list_add(&new_elem->list, head);
    // free(new_elem->value);
    // free(new_elem);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    return (q_insert_head(head->prev, s));
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (list_empty(head)) {
        if (list_empty(head)) {
            return NULL;
        }

        element_t *elem = list_first_entry(head, element_t, list);

        list_del(&elem->list);
        // printf("delete112 %p\n", &elem->list);
        // free(&elem->list);

        if (sp) {
            strncpy(sp, elem->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }

        return elem;
    }

    element_t *elem = list_first_entry(head, element_t, list);
    list_del(&elem->list);
    // free(&elem->list);


    if (sp) {
        strncpy(sp, elem->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    return elem;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return q_remove_head(head->prev->prev, sp, bufsize);
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;
    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (head == NULL || head->next == head || head->prev == head)
        return false;  // Ensure the list is not empty or improperly initialized

    if (list_is_singular(head)) {
        element_t *elem = list_first_entry(head, element_t, list);
        list_del(&elem->list);
        free(elem->value);
        free(elem);
        return true;
    }

    struct list_head *slow = head->next;  // Start from the first actual element
    struct list_head *fast = head->next;

    // Use the fast and slow pointer technique to find the middle element
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Now, slow should be at the middle element
    if (slow != head) {
        list_del(slow);
        element_t *elem = list_entry(slow, element_t, list);
        free(elem->value);
        free(elem);
        return true;
    }

    return false;
}


//等下探討
/* Delete the middle node in queue */

// bool q_delete_mid(struct list_head *head)
// {
//     // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

//     if (!head || list_empty(head)) {
//         return false;
//     }

//     int mid = q_size(head) / 2;

//     // Get to the target node
//     struct list_head *current = head->next;
//     for (int i = mid; i > 0; i--) {
//         current = current->next;
//     }
//     list_del(current);
//     element_t *delete_node = list_entry(current, element_t, list);
//     free(delete_node->value);
//     delete_node->value = NULL;
//     free(delete_node);

//     return true;
// }

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
