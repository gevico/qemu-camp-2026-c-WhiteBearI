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

int st[5][5] = {0};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

struct coord {
	int x;
	int y;
}a[30];

int tot = 0;
int dfs(int x, int y, int k) {
	a[k].x = x;
	a[k].y = y;
	if (x == 4 && y == 4) {
		tot = k;
		return 1;
	}
	st[x][y] = 1;
	for (int i = 0; i < 4; i ++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx > 4 || ny < 0 || ny > 4 || maze[nx][ny] ||st[nx][ny]) continue;
		if (dfs(nx, ny, k + 1)) return 1;
	}
	st[x][y] = 0;
	return 0;
}

int main(void)
{
	// TODO: 在这里添加你的代码
    dfs(0, 0, 0);
	for (int i = tot; i >= 0; i --) {
		printf("(%d,%d)\n", a[i].x, a[i].y);
	}

	return 0;
}