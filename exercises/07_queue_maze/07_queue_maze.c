#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

struct Point {
    int row;
    int col;
};

struct Queue {
    struct Point data[MAX_ROW * MAX_COL];
    int front;
    int rear;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(struct Queue *q, struct Point p) {
    q->data[q->rear++] = p;
}

struct Point dequeue(struct Queue *q) {
    return q->data[q->front++];
}

int isEmpty(struct Queue *q) {
    return q->front == q->rear;
}

int main(void)
{
    // 方向数组：上、下、左、右
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // 记录访问状态和前驱节点
    int visited[MAX_ROW][MAX_COL] = {0};
    struct Point prev[MAX_ROW][MAX_COL];
    
    struct Queue q;
    initQueue(&q);
    
    struct Point start = {0, 0};
    struct Point end = {4, 4};
    
    // BFS
    enqueue(&q, start);
    visited[start.row][start.col] = 1;
    
    while (!isEmpty(&q)) {
        struct Point current = dequeue(&q);
        
        // 到达终点
        if (current.row == end.row && current.col == end.col) {
            break;
        }
        
        // 探索四个方向
        for (int i = 0; i < 4; i++) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];
            
            // 边界检查、墙壁检查、未访问检查
            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL &&
                maze[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                prev[nr][nc] = current;
                struct Point next = {nr, nc};
                enqueue(&q, next);
            }
        }
    }
    
    // 如果没有找到路径
    if (!visited[end.row][end.col]) {
        printf("No path!\n");
        return 0;
    }
    
    // 从终点回溯到起点，打印路径
    struct Point path[MAX_ROW * MAX_COL];
    int path_len = 0;
    struct Point cur = end;
    
    while (cur.row != start.row || cur.col != start.col) {
        path[path_len++] = cur;
        cur = prev[cur.row][cur.col];
    }
    path[path_len++] = start;
    
    // 打印路径（从终点到起点）
    for (int i = 0; i < path_len; i++) {
        printf("(%d, %d)\n", path[i].row, path[i].col);
    }
    
    return 0;
}