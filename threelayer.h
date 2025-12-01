#ifndef _VERTHREE_AI
#define _VERTHREE_AI
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
#include "twolayer.h"
#include "NearEnd.h"
int DeepSearch(int player, int *board){
	char Allgraph[89][89]={0};
	int mypiece[6];
	FindMyPiece(board,mypiece,player);
	FindAllMoves(3-player,board,Allgraph);
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypiece[i]][j]==1){
				SWAP(board[mypiece[i]],board[j]);
				if(check_endgame(board,1)==player)
				return mypiece[i]*100+j;
				SWAP(board[mypiece[i]],board[j]);
			}
		}
	}
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypiece[i]][j]==1){
				SWAP(board[mypiece[i]],board[j]);
				char Allgraph1[89][89]={0};
				FindAllMoves(3-player,board,Allgraph1);
				int mypiece1[6];
				FindMyPiece(board,mypiece1,player);
				for(int i1=0;i1<6;i1++){
					for(int j1=11;j1<89;j1++){
						if(Allgraph1[mypiece1[i1]][j1]==1){
							SWAP(board[mypiece1[i1]],board[j1]);
							if(check_endgame(board,1)==player)
							return mypiece[i]*100+j;
							SWAP(board[mypiece1[i1]],board[j1]);
						}
					}
				}
				SWAP(board[mypiece[i]],board[j]);
			}
		}
	}
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypiece[i]][j]==1){
				SWAP(board[mypiece[i]],board[j]);
				char Allgraph1[89][89]={0};
				FindAllMoves(3-player,board,Allgraph1);
				int mypiece1[6];
				FindMyPiece(board,mypiece1,player);
				for(int i1=0;i1<6;i1++){
					for(int j1=11;j1<89;j1++){
						if(Allgraph1[mypiece1[i1]][j1]==1){
							SWAP(board[mypiece1[i1]],board[j1]);
							int mypiece2[6];
							char Allgraph2[89][89]={0};
							FindMyPiece(board,mypiece2,player);
							FindAllMoves(3-player,board,Allgraph2);
							for(int i2=0;i2<6;i2++){
								for(int j2=11;j2<89;j2++){
									if(Allgraph2[mypiece2[i2]][j2]==1){
										SWAP(board[mypiece2[i2]],board[j2]);
										if(check_endgame(board,1)==player)
										return mypiece[i]*100+j;
										SWAP(board[mypiece2[i2]],board[j2]);
									}
								}
							}
							SWAP(board[mypiece1[i1]],board[j1]);
						}
					}
				}
				SWAP(board[mypiece[i]],board[j]);
			}
		}
	}
	return 0;
}

int threelayer_player(int player , const int *board){
	int tmpboard[89];
	for(int i=0;i<89;i++){
		tmpboard[i]=board[i];
	}
	if(separate1(tmpboard)||separate2(tmpboard)){
		for(int i=11;i<89;i++){
			if(tmpboard[i]==3-player)
			tmpboard[i]=0;
		}
		int tmp=DeepSearch(player,tmpboard);
		if(tmp)
		return tmp;
		return twolayer_player(player,board);
	}
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
				if(check_endgame(tmpboard,1)==player)
				return mypiece[i]*100+j;
				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
			}
		}
	}
	for(int i=0;i<6;i++){
		for(int j=11;j<89;j++){
			if(Allgraph[mypiece[i]][j]==1){
				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
				if(check_endgame(tmpboard,1)==player){
					return mypiece[i]*100+j;
				}
				char Allgraph1[89][89]={0};
				FindAllMoves(player,tmpboard,Allgraph1);
				int mypiece1[6];
				FindMyPiece(tmpboard,mypiece1,3-player);
				int minscore=INT_MAX;
				for(int i1=0;i1<6;i1++){
					for(int j1=11;j1<89;j1++){
						if(Allgraph1[mypiece1[i1]][j1]==1){
							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
							char Allgraph2[89][89]={0};
							FindAllMoves(3-player,tmpboard,Allgraph2);
							int mypiece2[6];
							FindMyPiece(tmpboard,mypiece2,player);
							int maxscore1=INT_MIN;
							for(int i2=0;i2<6;i2++){
								for(int j2=11;j2<89;j2++){
									if(Allgraph2[mypiece2[i2]][j2]==1){
										SWAP(tmpboard[mypiece2[i2]],tmpboard[j2]);
//										if(check_endgame(tmpboard,1)==player){
//											return mypiece[i]*100+j;
//										}
										int score=NewObjective(player,tmpboard);
										if(score>=maxscore1){
											maxscore1=score;
										}
										SWAP(tmpboard[mypiece2[i2]],tmpboard[j2]);
									}
								}
							}
							if(maxscore1<=minscore){
								minscore=maxscore1;
							}
							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
//							printf("%d to %d\n%d to %d\n score=%d\n \n",mypiece[i],j,mypiece1[i1],j1,minscore);
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