#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool enqueue(Queue *q, People p) {
    if (q->count >= MAX_PEOPLE) {
        return false;
    }
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % MAX_PEOPLE;
    q->count++;
    return true;
}

People dequeue(Queue *q) {
    People empty = {-1};
    if (q->count <= 0) {
        return empty;
    }
    People p = q->data[q->head];
    q->head = (q->head + 1) % MAX_PEOPLE;
    q->count--;
    return p;
}

People peek(Queue *q) {
    People empty = {-1};
    if (q->count <= 0) {
        return empty;
    }
    return q->data[q->head];
}

bool isEmpty(Queue *q) {
    return q->count == 0;
}

int main() {
    Queue q;
    int total_people = 50;
    int report_interval = 5;

    // 初始化队列，将所有人员加入队列
    initQueue(&q);
    for (int i = 1; i <= total_people; i++) {
        People p = {i};
        enqueue(&q, p);
    }

    // 模拟约瑟夫环过程
    while (q.count > 1) {
        // 报数1到report_interval-1的人移到队列末尾
        for (int i = 1; i < report_interval; i++) {
            People p = dequeue(&q);
            enqueue(&q, p);
        }
        // 第report_interval个人被淘汰
        People eliminated = dequeue(&q);
        printf("淘汰: %d\n", eliminated.id);
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}