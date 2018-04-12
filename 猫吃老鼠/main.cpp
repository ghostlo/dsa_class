//
//  main.cpp
//  just for fun2
//
//  Created by time on 18/4/11.
//  Copyright © 2018年 ghostlo. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>
using namespace std;

typedef enum { AVAILABLE, WALL} Status;

struct Cell { //迷宫格点
    int x, y, num; Status status; //x坐标、y坐标、类型
    Cell *pr,*next;//格点的前驱,后继
};

Cell* catCell;
Cell* doorCell;
Cell* mouseCell;
Cell laby[10][10];

int map[10][10]={
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

void display1(){
    cout<<"C is cat "<<endl;
    cout<<"U is mouse "<<endl;
    cout<<"W is wall"<<endl;
    for ( int i = 0; i < 10; i++,cout<<"\n" )
        for ( int j = 0; j < 10; j++ )
        {
            if ( catCell->x == laby[i][j].x && catCell->y == laby[i][j].y )
                cout<<"C ";
            else if ( mouseCell->x == laby[i][j].x && mouseCell->y == laby[i][j].y )
                cout<<"U ";
            else if ( doorCell->x == laby[i][j].x && doorCell->y == laby[i][j].y)
                cout<<"O ";
            else if (laby[i][j].status ==WALL)
                cout<<"W " ;
            else cout<<"  " ;
        }
    cout<<"\n";
}

//void display(){//可以显示每一步中 每个空格的相对位置
//    for ( int i = 0; i < 10; i++,cout<<"\n" )
//        for ( int j = 0; j < 10; j++ )
//        {
//            if ( catCell->x == laby[i][j].x && catCell->y == laby[i][j].y )
//                cout<<"C ";
//            else if ( mouseCell->x == laby[i][j].x && mouseCell->y == laby[i][j].y )
//                cout<<"U ";
//            else if ( doorCell->x == laby[i][j].x && doorCell->y == laby[i][j].y)
//                cout<<"O ";
//            else if (laby[i][j].status ==WALL)
//                cout<<"W " ;
//            else cout<<laby[i][j].num<<" " ;
//        }
//}

void Labycell () {
    for ( int j = 0; j < 10; j ++ )
        for ( int i = 0; i < 10; i ++ )
        {
//            if(map[i][j]==0)//可以计算出一共43个空格点
//                ii++;
            laby[i][j].x = i;
            laby[i][j].y = j;
            int type = map[i][j];
            switch ( type )
            {
                case 1:
                    laby[i][j].status = WALL;
                    laby[i][j].num=-1;
                    break;
                case 0:
                    laby[i][j].status = AVAILABLE;
                    laby[i][j].num=30;
                    break;
                default:   exit ( -1 );
            }
        }
    catCell = &laby[rand() % 8 + 1][rand() % 8 + 1];
    doorCell = &laby[rand() % 8 + 1][rand() % 8 + 1];
    mouseCell = &laby[rand() % 8 + 1][rand() % 8 + 1];
    if(catCell->status==WALL||doorCell->status==WALL||mouseCell->status==WALL||catCell==doorCell||catCell==mouseCell||doorCell==mouseCell)
        Labycell();
}

void optimal_solution(Cell* s,Cell* t)//双栈主题算法
{
    for ( int j = 0; j < 10; j ++ )//初始化
        for ( int i = 0; i < 10; i ++ )
        {
            int type = map[i][j];
            if(type==0) laby[i][j].pr=laby[i][j].next=NULL;
        }
    stack<Cell*> c11;
    stack<Cell*> c12;
    Cell* c01=s;
    Cell* c02=c01;//辅助
    Cell* c03=t;
//    cout<<c->x<<" "<<c->y<<" "<<c->num<<endl;
//    c=c+10;
    int iii=1;
    c12.push(c01);
    while(iii<=30)
    {
        while(!c12.empty())
        {
            c01=c12.top();
            c12.pop();
            if((c02=c01+10)->num>iii)//east
            {
                c11.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01+1)->num>iii)//south
            {
                c11.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01-10)->num>iii)//west
            {
                c11.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01-1)->num>iii)//north
            {
                c11.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
        }
        iii++;
        while(!c11.empty())
        {
            c01=c11.top();
            c11.pop();
            if((c02=c01+10)->num>iii)//east
            {
                c12.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01+1)->num>iii)//south
            {
                c12.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01-10)->num>iii)//west
            {
                c12.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
            if((c02=c01-1)->num>iii)//north
            {
                c12.push(c02);
                c02->pr=c01;
                c02->num=iii;
            }
        }
        iii++;
    }
    while(c03!=s)
    {
        c03->pr->next=c03;
        c03=c03->pr;
    }
    for ( int j = 0; j < 10; j ++ )
        for ( int i = 0; i < 10; i ++ )
        {
            int type = map[i][j];
            if(type==0) laby[i][j].num=30;
        }
//    cout<<c->x<<" "<<c->y<<" "<<c->num<<endl;
}

void findanddone(int N,int M){
    while(1)
    {
        cout<<"mouse's position is :"<<mouseCell->x<<","<<mouseCell->y<<endl;
        cout<<"cat's position is :"<<catCell->x<<","<<catCell->y<<endl;
        display1();
        int j=N;
        for(;j>0;j--)
        {
            optimal_solution(mouseCell, doorCell);
            mouseCell=mouseCell->next;
            if(mouseCell==doorCell)
            {
                cout<<"mouse have run away.";
                cout<<"按任意键继续"<<endl;
                getchar();
                getchar();
                exit(0);
            }
        }
        j=M;
        for(;j>0;j--)
        {
            optimal_solution(catCell, mouseCell);
            catCell=catCell->next;
            if(catCell==mouseCell)
            {
                cout<<"mouse is died.";
                cout<<"按任意键继续"<<endl;
                getchar();
                exit(0);
            }
        }
        getchar();
        system("cls");
    }
}

int main()
{
    int catsp,mousesp;
    srand((unsigned)time( NULL ));
    Labycell();
    cout<<"please enter mouse's speed:";
    cin>>catsp;
    cout<<"please enter cat's speed:";
    cin>>mousesp;
    if(catsp>3||catsp<0||mousesp>3||mousesp<0)
    {
        cout<<"the speed is not legal.";
        cout<<"按任意键继续"<<endl;
        getchar();
        getchar();
        return 0;
    }
    if(catCell==&laby[8][8])
    {
        cout<<"cat can't move."<<endl;
        cout<<"mouse can run away"<<endl;
        cout<<"按任意键继续"<<endl;
        getchar();
        getchar();
        return 0;
    }
    if(mouseCell==&laby[8][8])
    {
        cout<<"mouse can't move."<<endl;
        cout<<"按任意键继续"<<endl;
        getchar();
        getchar();
        return 0;
    }
    if(doorCell==&laby[8][8])
    {
        cout<<"mouse can't have access to door."<<endl;
        cout<<"it will be ate"<<endl;
        cout<<"按任意键继续"<<endl;
        getchar();
        getchar();
        return 0;
    }
    findanddone(catsp,mousesp);
    return 0;
}