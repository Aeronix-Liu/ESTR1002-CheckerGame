#ifndef _VERTWO_AI
#define _VERTWO_AI
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include "basic.h"
#include "ValidCheck.h"
#include "FindAllMoves.h"
#define SWAP(A,B) {int tmp=A;A=B;B=tmp;}
#include<stdlib.h>
#include<time.h>
#include "dumb_ai_player.h"
#include<limits.h>
#include "onelayer.h"
int twolayer_player(int player , const int *board);
int NewObjective(int player , const int *board);

int NewObjective(int player , const int *board){
	int score1,score2;
	score1=score2=0;
	if(check_endgame(board,1)==player)
	return INT_MAX;
	if(check_endgame(board,1)==3-player)
	return INT_MIN;
	{
		int aim;
	    char visited[6]={0};
	    int mypiece[6];
	    FindMyPiece(board,mypiece,player);
		for(int i=0;i<6;i++){
			int mindis=98;
			int dis[6];
			for(int k=0;k<6;k++)
			dis[k]=98;
			int minposi;
		    if(i==0)
		    aim=88;
		    else if(i==1)
		    aim=87;
		    else if(i==2)
		    aim=78;
		    else if(i==3)
		    aim=68;
		    else if(i==4)
		    aim=77;
		    else
		    aim=86;
		    if(player==2)
		    aim=99-aim;
		    for(int j=0;j<6;j++){
		    	if(visited[j]==0){
		    		dis[j]=FindDistance(aim,mypiece[j]);
				}
			}
			for(int j=0;j<6;j++){
				if(dis[j]<mindis){
					minposi=j;
					mindis=dis[j];
				}
			}
			if(board[aim]==3-player){
				score1=score1+mindis/2;
			}
			else{
				score1=score1+mindis;
			}
			visited[minposi]=1;
	    }
    }
	    
	{
		int aim;
	    char visited[6]={0};
	    int mypiece[6];
	    FindMyPiece(board,mypiece,3-player);
		for(int i=0;i<6;i++){
			int mindis=98;
			int dis[6];
			for(int k=0;k<6;k++)
			dis[k]=98;
			int minposi;
		    if(i==0)
		    aim=88;
		    else if(i==1)
		    aim=87;
		    else if(i==2)
		    aim=78;
		    else if(i==3)
		    aim=68;
		    else if(i==4)
		    aim=77;
		    else
		    aim=86;
		    if(player==1)
		    aim=99-aim;
		    for(int j=0;j<6;j++){
		    	if(visited[j]==0){
		    		dis[j]=FindDistance(aim,mypiece[j]);
				}
			}
			for(int j=0;j<6;j++){
				if(dis[j]<mindis){
					minposi=j;
					mindis=dis[j];
				}
			}
			if(board[aim]==player){
				score2=score2+mindis/2;
			}
			else{
				score2=score2+mindis;
			}
			visited[minposi]=1;
	    }
	}
	return score2-score1;
}

int twolayer_player(int player , const int *board){
	int tmpboard[89];
	for(int i=0;i<89;i++){
		tmpboard[i]=board[i];
	}
	int mypiece[6];
	FindMyPiece(tmpboard,mypiece,player);
	char Allgraph[89][89]={0};
	FindAllMoves(3-player,tmpboard,Allgraph);
	int bestori,bestdes;
	int maxscore=INT_MIN;
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypiece[i]][j]==1){
				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
				char Allgraph1[89][89]={0};
				FindAllMoves(player,tmpboard,Allgraph1);
				int mypiece1[6];
				FindMyPiece(tmpboard,mypiece1,3-player);
				int bestori1,bestdes1;
				int minscore=INT_MAX;
				for(int i1=0;i1<6;i1++){
					for(int j1=11;j1<89;j1++){
						if(Allgraph1[mypiece1[i1]][j1]==1){
							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
							int score=NewObjective(player,tmpboard);
							if(score<=minscore){
								minscore=score;
								bestori1=mypiece1[i1];
								bestdes1=j1;
							}
							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
						}
					}
				}
				if(minscore>=maxscore){
					maxscore=minscore;
					bestori=mypiece[i];
					bestdes=j;
				}
				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
			}
		}
	}
	return bestori*100+bestdes;
}

#endif