#include "aiv_list.h"
#include <stdlib.h>

aiv_list_t aiv_list_new() {
    aiv_list_t list;
    list.head = NULL;
    list.tail = NULL;
    list.count = 0;
    return list;
}

void aiv_list_destroy(aiv_list_t* list) {
    aiv_list_node_t* current = list->head;
    while(current) {
        aiv_list_node_t* next = current->next;
        free(current);
        current = next;
    }
}


bool aiv_list_is_empty(aiv_list_t* list) {
    return list->count == 0;
}

void aiv_list_add(aiv_list_t* list, void* item) {
    aiv_list_node_t* node = (aiv_list_node_t*)malloc(sizeof(aiv_list_node_t));
    node->data = item;
    node->prev = NULL;
    node->next = NULL;

    if (aiv_list_is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {   //  node1 <-- node2  
        aiv_list_node_t* prev = list->tail;
        node->prev = prev;
        prev->next = node;
        list->tail = node;
    }

    list->count++;
}

void aiv_list_remove(aiv_list_t* list, aiv_list_node_t* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    free(node);
    list->count--;
}

void aiv_list_remove_at(aiv_list_t* list, size_t index) {
    if (index >= list->count) {
        return;
    }

    aiv_list_node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    aiv_list_remove(list, current);
}

int aiv_list_get_size(aiv_list_t* list) {
    return list->count;
}

void* aiv_list_get_item_at(aiv_list_t* list, size_t index, void** out_item) {
    if (index >= list->count) {
        *out_item = NULL;
        return NULL;
    }

    aiv_list_node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

void aiv_list_set_item_at(aiv_list_t* list, size_t index, void* item) {
    if (index >= list->count) {
        return;
    }

    aiv_list_node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = item;
}