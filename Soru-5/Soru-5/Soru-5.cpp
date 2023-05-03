#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

struct Queue {
    int front, rear;
    char items[MAX_SIZE];
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(struct Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}
int isFull(struct Queue* queue) {
    if (queue->front == 0 && queue->rear == MAX_SIZE - 1)
        return 1;
    if (queue->front == queue->rear + 1)
        return 1;
    return 0;
}

// Kuyruða bir eleman ekler
void enqueue(struct Queue* queue, char value) {
    if (isFull(queue)) {
        printf("Kuyruk dolu!\n");
    }
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        queue->items[queue->rear] = value;
    }
}

char dequeue(struct Queue* queue) {
    char item;
    if (isEmpty(queue)) {
        printf("Kuyruk boþ!\n");
        item = '\0';
    }
    else {
        item = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        }
        else {
            queue->front = (queue->front + 1) % MAX_SIZE;
        }
    }
    return item;
}

void removeDuplicates(char* str) {
    struct Queue* queue = createQueue();
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++) {
        if (isEmpty(queue) || str[i] != queue->items[queue->rear]) {
            enqueue(queue, str[i]);
        }
        else {
            dequeue(queue);
        }
    }
    i = 0;
    while (!isEmpty(queue)) {
        str[i++] = dequeue(queue);
    }
    str[i] = '\0';
}

int main() {
    char str[MAX_SIZE];
    printf("Dizi girin: ");
    gets(str);
    removeDuplicates(str);
    printf("Sonuç: %s\n", str);
    return 0;
}

