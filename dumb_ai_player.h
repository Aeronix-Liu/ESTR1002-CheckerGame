#ifndef DUMB_AI_PLAYER_H
#define DUMB_AI_PLAYER_H
#include<stdio.h>
#include "FindAllmoves.h"
#include<stdlib.h>
#include<time.h>

int dumb_ai_player(int player , const int *board);
typedef struct Moves{
	int ori,des;
}Moves;
char goodmove(Moves m,int player);
int dumb_ai_player(int player , const int *board)
{
	char Allgraph[89][89];
	for(int i=0;i<89;i++){
		for(int j=0;j<89;j++){
			Allgraph[i][j]=0;
		}
	}
	FindAllMoves(3-player,board,Allgraph);
	srand(time(NULL));
	int Validmove_num=0;
	int mypieceposi[6];
	for(int i=0;i<6;i++){
		mypieceposi[i]=0;
	}
	int j1=0;
	for(int i=11;i<89;i++){
		if(board[i]==player){
			mypieceposi[j1]=i;
			j1++;
		}
	}
	Moves Allmoves[320];
	for(int i=0;i<320;i++){
		Allmoves[i].ori=0;
		Allmoves[i].des=0;
	}
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypieceposi[i]][j]==1){
				Allmoves[Validmove_num].ori=mypieceposi[i];
				Allmoves[Validmove_num].des=j;
				Validmove_num++;
			}
		}
	}
	while(1){
		int index=rand()%Validmove_num;
		if(goodmove(Allmoves[index],player)){
			return Allmoves[index].ori*100+Allmoves[index].des;
		}
	}
}

char goodmove(Moves m,int player){
	if(player==1){
		if( ( m.des/10+m.des%10 )>( m.ori/10+m.ori%10 ) )
	    return 1;
	    return 0;
	}
	else{
		if( ( m.des/10+m.des%10 )<( m.ori/10+m.ori%10 ) )
	    return 1;
	    return 0;
	}
}
#endif