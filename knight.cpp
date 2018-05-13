#include <iostream>
#include <iomanip>
using namespace std;
int chess[200][200]={0};        //定义棋盘
int run[8][2]={{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};//遍历下一个马的位置
int cnt=1;                //记录马踏的每一步
int N;
void print()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            cout<<setw(5)<<chess[i][j];
        cout<<endl;
    }
    exit(0);
}
void horse(int x,int y)
{
    int a,b,i,N2=N*N;
    for(i=0;i<8;i++)
    {
        a=x+run[i][0];
        b=y+run[i][1];
        if(a>=0&&a<N&&b>=0&&b<N&&!chess[a][b])
        {
            chess[a][b]=++cnt;
            if(cnt<N2) horse(a,b);
            else  print();
        }
    }
}
int main()
{
    int i=0,j=0;
    cout<<"以下输入均要求大于0,N不要太大\n输入N:"<<endl;
    cin>>N;
    cout<<"输入起始x:"<<endl;
    cin>>i;
    cout<<"输入起始y:"<<endl;
    cin>>j;
    if(i<=0||j<=0||N<=0||N>=200||!(i<=N&&j<=N))
    {
        cout<<"又不看说明\nsay gg\n另外，x,y不要超过N哟\n";
        exit(0);
    }
    chess[i-1][j-1]=1;     //直接将马置于该位置，该位置为第一步
    horse(i-1,j-1);
    cout<<"没有找到路哎\n";
    return 0;
}
