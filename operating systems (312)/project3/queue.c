//
//  queue.c
//  homework2
//
//	150140707
//	Muhammet UÇAN
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue* temp = (Queue*) malloc(sizeof(Queue));
    temp->front = NULL;
    temp->last = NULL;
    temp->size = 0;
    return temp;
}

Node* createNode(applicant* in_applicant) {
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = *in_applicant;
    temp->next = NULL;
    return temp;
}

int isEmpty(Queue* in_queue) {
    return (in_queue->front == NULL);
}

void enqueue(Queue* in_queue, Node* node) {
    if (in_queue->front == NULL) {
        in_queue->last = node;
        in_queue->front = in_queue->last;
        return;
    }
    in_queue->last->next = node;
    in_queue->last = node;
}

void deleteNode(Node* temp) {
    free(temp);
}

Node* dequeue(Queue* in_queue) {
    if (isEmpty(in_queue)) return NULL;
    Node* temp = in_queue->front;
    in_queue->front = in_queue->front->next;
    in_queue->size--;
    temp->next = NULL;
    return temp;
}

void deleteQueue(Queue* in_queue) {
    Node *temp;
    while (!isEmpty(in_queue)) {
        temp = in_queue->front;
        in_queue->front = in_queue->front->next;
        deleteNode(temp);
    }
    free(in_queue);
}

