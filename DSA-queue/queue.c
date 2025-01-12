#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

struct Queue {
    int front, rear;
    int array[CAPACITY];
};

void initializeQueue(struct Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
}

int isFull(struct Queue* queue) {
    return (queue->rear == CAPACITY - 1);
}

int isEmpty(struct Queue* queue) {
    return (queue->front > queue->rear);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot enqueue %d\n", item);
        return;
    }
    queue->array[++queue->rear] = item;
    printf("Enqueued: %d\n", item);
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    }
    return queue->array[queue->front++];
}

void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->array[i]);
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int choice, value;

    do {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(&queue, value);
            break;
        case 2:
            value = dequeue(&queue);
            if (value != -1) {
                printf("Dequeued: %d\n", value);
            }
            break;
        case 3:
            display(&queue);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
