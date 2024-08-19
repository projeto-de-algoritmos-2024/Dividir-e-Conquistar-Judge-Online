#include <stdio.h>
#include <stdlib.h>

// Função para mesclar duas listas encadeadas ordenadas
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    // Cria um nó fictício para começar a lista mesclada
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    // Enquanto ambas as listas têm elementos, escolhe o menor para adicionar
    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Anexa qualquer elemento restante de l1 ou l2
    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    // Retorna o início da lista mesclada
    return dummy.next;
}

// Função para mesclar k listas encadeadas ordenadas
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    // Inicialmente, a lista resultante é a primeira lista
    struct ListNode* result = lists[0];

    // Mescla cada lista subsequente na lista resultante
    for (int i = 1; i < listsSize; i++) {
        result = mergeTwoLists(result, lists[i]);
    }

    return result;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}