#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 12

typedef struct {
    char buffer[SIZE];
    int head, tail, count;
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = cb->tail = cb->count = 0;
}

bool isFull(CircularBuffer *cb)  {
    return cb->count == SIZE; }
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0; }

void write_cb(CircularBuffer *cb, char data) {
    if (isFull(cb)) { printf("[Overflow] Buffer is full!\n"); return; }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; // wrap around
    cb->count++;
}

char read_cb(CircularBuffer *cb) {
    if (isEmpty(cb)) { printf("[Underflow] Buffer is empty!\n"); return '\0'; }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; // wrap around
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[50];
    printf("Enter your name: ");
    scanf("%49s", name);

    strcat(name, "CE-ESY"); // append required suffix

    // Write each character into the buffer
    for (int i = 0; i < (int)strlen(name); i++)
        write_cb(&cb, name[i]);

    // Read back and print
    printf("Output: ");
    while (!isEmpty(&cb))
        printf("%c", read_cb(&cb));

    printf("\nBuffer empty: %s\n", isEmpty(&cb) ? "Yes" : "No");
    return 0;
}
