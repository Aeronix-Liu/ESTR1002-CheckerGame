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
int onelayer_ai_player(int player , const int *board);
int FindNearPiece(int ori,int des);
int objective(int player,int mypieceposi[6],const int *board);

int FindDistance(int ori,int des){
	return (ori%10-des%10)*(ori%10-des%10)+(ori/10-des/10)*(ori/10-des/10);
}

int objective(int player,int mypieceposi[6],const int *board){
	int score=0;
	int aim;
	char visited[6]={0};
	if(player==1){
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
		    aim=86;
		    else if(i==3)
		    aim==78;
		    else if(i==4)
		    aim=77;
		    else
		    aim=68;
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
	}
	score=-score;
	return score;
}
#endif