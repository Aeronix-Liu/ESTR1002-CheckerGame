#ifndef _VERONE_AI
#define _VERONE_AI
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
int onelayer_player(int player , const int *board);
int objective(int player,int mypieceposi[6]);
void FindMyPiece(const int *board,int mypiece[6],int player);
int FindDistance(int ori,int des);

void FindMyPiece(const int *board,int mypiece[6],int player){
	int k=0;
	for(int i=11;i<89;i++){
		if(board[i]==player){
			mypiece[k]=i;
			k++;
		}
	}
}

int FindDistance(int ori,int des){
	return (ori%10-des%10)*(ori%10-des%10)+(ori/10-des/10)*(ori/10-des/10);
}

int objective(int player,int mypieceposi[6]){
	int score=0;
	int aim;
	char visited[6]={0};
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
		    		dis[j]=FindDistance(aim,mypieceposi[j]);
				}
			}
			for(int j=0;j<6;j++){
				if(dis[j]<mindis){
					minposi=j;
					mindis=dis[j];
				}
			}
			score=score+dis[minposi];
			visited[minposi]=1;
	    }
	score=-score;
	return score;
}

int onelayer_player(int player , const int *board){
	int mypiece[6];
	for(int i=0;i<6;i++){
		mypiece[i]=0;
	}
	int k=0;
	for(int i=11;i<89;i++){
		if(board[i]==player){
			mypiece[k]=i;
			k++;
		}
	}
	int bestori,bestdes;
	char Allgraph[89][89];
	for(int i=0;i<89;i++){
		for(int j=0;j<89;j++){
			Allgraph[i][j]=0;
		}
	}
	FindAllMoves(3-player,board,Allgraph);
	int maxscore=INT_MIN;
    	for(int i=0;i<6;i++){
		    for(int j=11;j<89;j++){
			    if(Allgraph[mypiece[i]][j]==1){
				    int mem=mypiece[i];
				    mypiece[i]=j;
				    int score=objective(player,mypiece);
				    if(score>maxscore){
				    	maxscore=score;
					    bestori=mem;
				    	bestdes=j;
				    }
				    mypiece[i]=mem;
			    }
		    }
	    }
	return bestori*100+bestdes;
}
#endif