#ifndef NEAREND_H
#define NEAREND_H
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
char separate1(const int *board){
	int piece1[6],piece2[6];
	FindMyPiece(board,piece1,1);
	FindMyPiece(board,piece2,2);
	int leastmod10,leastdivide10,mostmod10,mostdivide10;
	leastmod10=leastdivide10=9;
	mostmod10=mostdivide10=0;
	for(int i=0;i<6;i++){
		if(piece1[i]%10<leastmod10)
		leastmod10=piece1[i]%10;
		if(piece1[i]/10<leastdivide10)
		leastdivide10=piece1[i]/10;
		if(piece2[i]%10>mostmod10)
		mostmod10=piece2[i]%10;
		if(piece2[i]/10>mostdivide10)
		mostdivide10=piece2[i]/10;
	}
	if(leastmod10>mostmod10||leastdivide10>mostdivide10)
	return 1;
	return 0;
}

char separate2(const int *board){
	int piece1[6],piece2[6];
	FindMyPiece(board,piece1,1);
	FindMyPiece(board,piece2,2);
	int sum1,sum2=0;
	for(int i=0;i<6;i++){
		if(piece1[i]/10+piece1[i]%10<sum1)
		sum1=piece1[i]/10+piece1[i]%10;
	}
	for(int i=0;i<6;i++){
		if(piece2[i]/10+piece2[i]%10>sum2)
		sum2=piece1[i]/10+piece1[i]%10;
	}
	if(sum1>sum2)
	return 1;
	return 0;
}

char NearEnd(int player,const int *board){
	int mypiece[6];
	FindMyPiece(board,mypiece,player);
	if(player==1){
		for(int i=0;i<6;i++){
			if(mypiece[i]/10<4||mypiece[i]%10<4)
			return 0;
		}
		return 1;
	}
	if(player==2){
		for(int i=0;i<6;i++){
			if(mypiece[i]/10>5||mypiece[i]%10>5)
			return 0;
		}
		return 1;
	}
}

int OneSideObjective(int player,const int *board){
	int score=0;
	int aim;
	int mypiece[6];
	FindMyPiece(board,mypiece,player);
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
		    		dis[j]=FindDistance(aim,mypiece[j]);
				}
			}
			for(int j=0;j<6;j++){
				if(dis[j]<mindis){
					minposi=j;
					mindis=dis[j];
				}
			}
			score=score+mindis;
			visited[minposi]=1;
	    }
	return score;
}

int Opti_NewObjective(int player , const int *board){
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

//int Opti_twolayer_player(int player , const int *board){
//	char te=separate(board);
//	int tmpboard[89];
//	for(int i=0;i<89;i++){
//		tmpboard[i]=board[i];
//	}
//	int mypiece[6];
//	FindMyPiece(tmpboard,mypiece,player);
//	char Allgraph[89][89]={0};
//	FindAllMoves(3-player,tmpboard,Allgraph);
//	int bestori,bestdes;
//	int maxscore=INT_MIN;
//	for(int i=0;i<6;i++){
//		for(int j=11;j<89;j++){
//			if(Allgraph[mypiece[i]][j]==1){
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//				char Allgraph1[89][89]={0};
//				FindAllMoves(player,tmpboard,Allgraph1);
//				int mypiece1[6];
//				FindMyPiece(tmpboard,mypiece1,3-player);
//				int bestori1,bestdes1;
//				int minscore=INT_MAX;
//				for(int i1=0;i1<6;i1++){
//					for(int j1=11;j1<89;j1++){
//						if(Allgraph1[mypiece1[i1]][j1]==1){
//							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
//							int score=NewObjective(player,tmpboard);
//							if(te)
//							score=Opti_NewObjective(player,tmpboard);
//							if(score<=minscore){
//								minscore=score;
//								bestori1=mypiece1[i1];
//								bestdes1=j1;
//							}
//							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
//						}
//					}
//				}
//				if(minscore>=maxscore){
//					maxscore=minscore;
//					bestori=mypiece[i];
//					bestdes=j;
//				}
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//			}
//		}
//	}
//	return bestori*100+bestdes;
//}
//int fourlayer_player(int player , const int *board){
//	int tmpboard[89];
//	for(int i=0;i<89;i++){
//		tmpboard[i]=board[i];
//	}
//	int mypiece[6];
//	FindMyPiece(tmpboard,mypiece,player);
//	char Allgraph[89][89]={0};
//	FindAllMoves(3-player,tmpboard,Allgraph);
//	int bestori,bestdes;
//	int maxscore=INT_MIN;
//	for(int i=0;i<6;i++){
//		for(int j=11;j<89;j++){
//			if(Allgraph[mypiece[i]][j]==1){
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//				if(check_endgame(tmpboard,1)==player)
//				return mypiece[i]*100+j;
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//			}
//		}
//	}
//	for(int i=0;i<6;i++){
//		for(int j=11;j<89;j++){
//			if(Allgraph[mypiece[i]][j]==1){
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//				char Allgraph1[89][89]={0};
//				FindAllMoves(player,tmpboard,Allgraph1);
//				int mypiece1[6];
//				FindMyPiece(tmpboard,mypiece1,3-player);
//				int bestori1,bestdes1;
//				int minscore=INT_MAX;
//				for(int i1=0;i1<6;i1++){
//					for(int j1=11;j1<89;j1++){
//						if(Allgraph1[mypiece1[i1]][j1]==1){
//							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
//							int mypiece2[6];
//							FindMyPiece(tmpboard,mypiece2,player);
//							char Allgraph2[89][89]={0};
//							FindAllMoves(3-player,tmpboard,Allgraph2);
//							int maxscore1=INT_MIN;
//							for(int i2=0;i2<6;i2++){
//								for(int j2=11;j2<89;j2++){
//									if(Allgraph2[mypiece2[i2]][j2]==1){
//										SWAP(tmpboard[mypiece2[i2]],tmpboard[j2]);
//										if(check_endgame(tmpboard,1)==player)
//										return mypiece[i]*100+j;
//										int mypiece3[6];
//										FindMyPiece(tmpboard,mypiece3,3-player);
//										char Allgraph3[89][89];
//										FindAllMoves(player,tmpboard,Allgraph3);
//										int minscore1=INT_MAX;
//										for(int i3=0;i3<6;i3++){
//											for(int j3=11;j3<89;j3++){
//												if(Allgraph3[mypiece3[i3]][j3]==1){
//													SWAP(tmpboard[mypiece3[i3]],tmpboard[j3]);
//													int score=NewObjective(player,tmpboard);
//													if(score<=minscore1){
//														minscore1=score;
//													}
//													SWAP(tmpboard[mypiece3[i3]],tmpboard[j3]);
//												}
//											}
//										}
//										if(minscore1>=maxscore1){
//											maxscore1=minscore1;
//										}
//										SWAP(tmpboard[mypiece2[i2]],tmpboard[j2]);
//									}
//								}
//							}
//							if(maxscore1<=minscore){
//								minscore=maxscore1;
//							}
//							SWAP(tmpboard[mypiece1[i1]],tmpboard[j1]);
//						}
//					}
//				}
//				if(minscore>=maxscore){
//					maxscore=minscore;
//					bestori=mypiece[i];
//					bestdes=j;
//				}
//				SWAP(tmpboard[mypiece[i]],tmpboard[j]);
//			}
//		}
//	}
//	return bestori*100+bestdes;
//}

#endif