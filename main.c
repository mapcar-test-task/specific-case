#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* mapcar(struct Node* head, int (*func)(int)) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* new_head = (struct Node*) malloc(sizeof(struct Node));
    new_head->data = func(head->data);
    new_head->next = mapcar(head->next, func);
    return new_head;
}

// Вспомогательные функции для создания и печати списка
struct Node* create_node(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Функция, которую будем применять к каждому элементу списка
int square(int x) {
    return x * x;
}

int main() {
    struct Node* list = create_node(1);
    list->next = create_node(2);
    list->next->next = create_node(3);

    printf("Original list: ");
    print_list(list);

    struct Node* new_list = mapcar(list, square);
    printf("New list: ");
    print_list(new_list);

    // Освобождение памяти для каждого узла списка
    struct Node* current = list;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // Освобождение памяти для нового списка
    current = new_list;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
