//本人真诚地保证：
//本人独立完成了本程序的设计、编码、纠错、分析与改进工作。
//在此，未与其他人讨论，交流。
//程序凡是引用到别人程序或文献之处，都在注释里很清楚地注明了引用出处。
//我从未抄袭或盗用他人程序，无论是修改式的还是原封不动式的抄袭。
//龙宇杰
// thanks 邓俊辉老师
void randLaby() { //生成随机的迷宫
   labySize = LABY_MAX / 2 + rand() % ( LABY_MAX / 2 ); 
   /*DSA*/printf ( "Using a laby of size %d ...\n", labySize ); 
   getchar();
   for ( int i = 0; i < labySize; i++ )
      for ( int j = 0; j < labySize; j++ ) {
         laby[i][j].x = i;
         laby[i][j].y = j;
         laby[i][j].status = WALL; //边界格点必须是墙
      }
   for ( int i = 1; i < labySize - 1; i++ )
      for ( int j = 1; j < labySize - 1; j++ )
         if ( rand() % 4 ) laby[i][j].status = AVAILABLE; //75%的格点为空可用
   startCell = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
   goalCell  = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
   startCell->status = goalCell->status = AVAILABLE; //起始格点必须可用
}