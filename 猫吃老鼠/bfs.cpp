#include<stdio.h>
#define MAX_ROW 10
#define MAX_COL 10

struct point
{
    int row, col, predecessor;
} queue[512];

int head = 0, tail = 0;

void enqueue(struct point p)
{
    queue[tail++] = p;
}

struct point dequeue(void)
{
    return queue[head++];
}

int is_empty(void)
{
    return head == tail;
}

int maze[MAX_ROW][MAX_COL] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,1,1},
    {1,0,0,1,1,1,1,0,0,1},
    {1,1,0,1,0,0,1,1,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,0,0,0,0,1,1},
    {1,0,0,1,1,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};

void visit(int row, int col)
{
    struct point visit_point = { row, col, head - 1 };
    maze[row][col] = 2;
    enqueue(visit_point);
}

int bfs(int startx,int starty,int finalx,int finaly)
{
    struct point p = { startx, starty, -1 };

    maze[p.row][p.col] = 2;
    enqueue(p);

    while (!is_empty())
    {
        p = dequeue();
        if (p.row == finalx && p.col == finaly)
            break;
        if (p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0) /* right */
            visit(p.row, p.col + 1);
        if (p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0)/* down */
            visit(p.row + 1, p.col);
        if (p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) /* left */
            visit(p.row, p.col - 1);
        if (p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) /* up */
            visit(p.row - 1, p.col);
//        print_maze();
    }
    if (p.row == finalx && p.col == finaly)
    {
        p = queue[p.predecessor];
            // printf("(%d, %d)\n", p.row, p.col);
        if(p.row-finalx==0&&p.col-finaly==1)
            return 1;//west
        if(p.row-finalx==1&&p.col-finaly==0)
            return 2;//north
        if(p.row-finalx==0&&p.col-finaly==-1)
            return 3;//east
        if(p.row-finalx==-1&&p.col-finaly==0)
            return 4;//south
        else
            printf("oh,there's a problem\n");
    }
    else
        printf("No path!\n");
    return 0;
}
