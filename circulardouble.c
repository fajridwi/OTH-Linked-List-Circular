#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* first;
    Node* last;
} list_integer;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertLast(list_integer* l, Node* p) {
    if (l->first == NULL && l->last == NULL) {
        l->first = p;
        l->last = p;
        p->next = l->first;
        p->prev = l->last;
    } else {
        p->prev = l->last;
        l->last->next = p;
        l->last = p;
        l->first->prev = l->last;
        l->last->next = l->first;
    }
}

void printList(const list_integer* l) {
    if (l->first == NULL) return;

    Node* current = l->first;
    do {
        printf("Address: %p, Data: %d\n", (void*)current, current->data);
        current = current->next;
    } while (current != l->first);
}

void sortList(list_integer* l) {
    if (l->first == NULL) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = l->first;

        while (ptr1->next != l->first) {
            if (ptr1->data > ptr1->next->data) {
                Node* tempPrev = ptr1->prev;
                Node* tempNext = ptr1->next->next;
                Node* tempCurrentNext = ptr1->next;

                if (ptr1->next == l->last) {
                    l->last = ptr1;
                }
                if (ptr1 == l->first) {
                    l->first = tempCurrentNext;
                }

                ptr1->next->prev = tempPrev;
                ptr1->next->next = ptr1;
                ptr1->prev = tempCurrentNext;
                ptr1->next = tempNext;

                if (tempPrev != NULL) {
                    tempPrev->next = tempCurrentNext;
                }
                if (tempNext != NULL) {
                    tempNext->prev = ptr1;
                }

                swapped = 1;
            } else {
                ptr1 = ptr1->next;
            }
        }
        lptr = ptr1;
    } while (swapped);
}

int main() {
    list_integer l = {NULL, NULL};
    int N, i, data;
    
    printf("Masukkan jumlah data: ");
    scanf("%d", &N);

    printf("Masukkan data:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &data);
        Node* newNode = createNode(data);
        insertLast(&l, newNode);
    }

    printf("List sebelum pengurutan:\n");
    printList(&l);

    sortList(&l);

    printf("List setelah pengurutan:\n");
    printList(&l);

    return 0;
}