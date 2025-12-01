#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include "basic.h"
#include "ValidCheck.h"
#include "FindAllMoves.h"
#define SWAP(A,B) {int tmp=A;A=B;B=tmp;}
#include "dumb_ai_player.h"
#include<stdlib.h>
#include<time.h>
#include "onelayer.h"
#include<limits.h>
#include "twolayer.h"
#include "threelayer.h"
#include "NearEnd.h"
int main()
{
	int board[89];
	int mode;
	printf("Please choose your mode:\n");
	printf("mode 1:human to human\n");
	printf("mode 2:human to computer\n");
	scanf("%d",&mode);
	while(mode!=1&&mode!=2&&mode!=3&&mode!=4){
		printf("choose your mode again\n");
		scanf("%d",&mode);
	}
	if(mode==1){
		initialize(board);
		int steps=0;
		while(check_endgame(board,steps)==0){
			if(turn(steps)==1)
			printf("Player 1's turn\n");
			else
			printf("Player 2's turn\n");
			display(board);
			char input[50];
			int ori,des;
			ori=0;
			des=0;
			while(1){
				ReadMove(input);
				if(!Is4Digits(input)){
					printf("Invalid input format, please input again:");
					continue;
				}
				ori=(input[0]-'0')*10+input[1]-'0';
	            des=(input[2]-'0')*10+input[3]-'0';
				if(!InBoard(ori,des)){
					printf("Input out of the game board, please input again:");
					continue;
				}
				if(!ValidStart(ori,turn(steps),board)){
				    printf("Invalid starting location, please input again:");
				    continue;
				}
				if(!ValidEnd(des,board)){
					printf("Invalid ending location, please input again:");
					continue;
				}
				char Allgraph[89][89];
				memset(Allgraph,0,sizeof(Allgraph));
				FindAllMoves(steps,board,Allgraph);
				if(search(ori,des,Allgraph))
				break;
				printf("The move violates the game rule, please input again:");
			}                            // judge the input
            SWAP(board[ori],board[des]);
			steps++;
			printf("\n");
		}      //the while loop judge whether the game ends
		if(check_endgame(board,steps)==1){
			display(board);
			printf("\nPlayer 1 wins!");
		}
		else if(check_endgame(board,steps)==2){
			display(board);
			printf("\nPlayer 2 wins!");
		}
		else if(check_endgame(board,steps)==3){
			display(board);
			printf("\nEnds with a draw.");
		}
	}
	if(mode==2){ 
		int player;
		printf("choose yourself as player 1 or 2:\n");
		scanf("%d",&player);
		initialize(board);
		int steps=0;
		while(check_endgame(board,steps)==0){
			if(turn(steps)==1)
			printf("Player 1's turn\n");
			else
			printf("Player 2's turn\n");
			display(board);
			char input[50];
			int ori,des;
			ori=0;
			des=0;
			while(1){
				if(turn(steps)==player){
					ReadMove(input);
					if(!Is4Digits(input)){
					printf("Invalid input format, please input again:");
					continue;
				    }
				    ori=(input[0]-'0')*10+input[1]-'0';
	                des=(input[2]-'0')*10+input[3]-'0';
				    if(!InBoard(ori,des)){
					    printf("Input out of the game board, please input again:");
					    continue;
				    }
				    if(!ValidStart(ori,turn(steps),board)){
				        printf("Invalid starting location, please input again:");
				        continue;
				    }
				    if(!ValidEnd(des,board)){
					    printf("Invalid ending location, please input again:");
					    continue;
				    }
				    char Allgraph[89][89]={0};
				    FindAllMoves(steps,board,Allgraph);
				    if(search(ori,des,Allgraph))
				    break;
				    printf("The move violates the game rule, please input again:");
				}
				    
				else{
					int tmp;
					tmp=threelayer_player(turn(steps),board);
					ori=tmp/100;
					des=tmp%100;
					printf("%d\n",tmp);
					break;
				}
			}
			SWAP(board[ori],board[des]);
			steps++;
			printf("\n");
		}
		if(check_endgame(board,steps)==1){
			display(board);
			printf("\nPlayer 1 wins!");
		}
		else if(check_endgame(board,steps)==2){
			display(board);
			printf("\nPlayer 2 wins!");
		}
		else if(check_endgame(board,steps)==3){
			display(board);
			printf("\nEnds with a draw.");
		}
	}
	if(mode==3){
		initialize(board);
		int steps=0;
		int player;
		printf("choose the smarter bot as player 1 or 2:\n");
		scanf("%d",&player);
		while(check_endgame(board,steps)==0){
			if(turn(steps)==1)
			printf("Player 1's turn\n");
			else
			printf("Player 2's turn\n");
			display(board);
			char input[50];
			int ori,des;
			ori=0;
			des=0;
			if(turn(steps)==player){
				int tmp;
				tmp=threelayer_player(turn(steps),board);
				ori=tmp/100;
				des=tmp%100;
				printf("%d\n",tmp);
			}
			else{
				int tmp;
				tmp=twolayer_player(turn(steps),board);
				ori=tmp/100;
				des=tmp%100;
				printf("%d\n",tmp);
			}
			SWAP(board[ori],board[des]);
			steps++;
			printf("\n");
		}  
		if(check_endgame(board,steps)==1){
			display(board);
			printf("\nPlayer 1 wins!");
		}
		else if(check_endgame(board,steps)==2){
			display(board);
			printf("\nPlayer 2 wins!");
		}
		else if(check_endgame(board,steps)==3){
			display(board);
			printf("\nEnds with a draw.");
		}
	}
	if(mode==4){
		for(int i=0;i<89;i++){
		if(i<10||i%10==0||i%10==9)
		board[i]=-1;
		else
		board[i]=0;
	    }
		board[67]=board[75]=board[78]=board[86]=board[87]=board[88]=1;
		printf("depth=%d",DeepSearch(1,board));
	}
}

//function list:

//BFS(graph,queue,curlen)

//BuildGraph(board,graph)

//check_endgame(board,steps):  0-continue  1-red wins  2-blue wins  3-draw

//convert(input,ori,des):char to read origin and destination: failed trial

//display(board)

//FindAllMoves(steps,board,validmoves)

//Findmypiece(board,player,mypieceposi[6])

//initialize(board)

//InBoard(ori,des)

//Is4Digits(input)

//IsValidMove(ori,des,turn,board)

//judge(queue,size,element)

//ReadMove(input)

//turn(steps):  1-Blue    2-Red

//ValidEnd(des,board)

//ValidJump(ori,via,board)

//ValidStart(ori,steps,board)