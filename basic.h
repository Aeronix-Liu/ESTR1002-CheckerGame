#ifndef _BASIC_H
#define _BASIC_H 
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
void initialize(int board[89]);
void display(int board[89]);
char check_endgame(const int *board,int steps);
void ReadMove(char input[]);
int turn(int steps);

void initialize(int board[89])
{
	for(int i=0;i<89;i++){
		if(i<10||i%10==0||i%10==9)
		board[i]=-1;
		else
		board[i]=0;
	}
	board[11]=board[12]=board[13]=board[21]=board[22]=board[31]=1;
	board[68]=board[77]=board[78]=board[86]=board[87]=board[88]=2;
}

void display(int board[89])
{
	printf("  1 2 3 4 5 6 7 8\n");
	for(int i=1;i<=8;i++){
		printf("%d ",i);
		for(int j=1;j<=8;j++){
			if(board[10*i+j]==0)
			printf(". ");
			if(board[10*i+j]==1)
			printf("# ");
			if(board[10*i+j]==2)
			printf("0 ");
		}
		printf("\n");
	}
}

char check_endgame(const int *board,int steps)                  // 0-continue; 1-blue wins; 2-red wins;
{                                                            //3-draw
	if(steps>200)
	return 3;
	int sum1=board[11]+board[12]+board[13]+board[21]+board[22]+board[31];
	int sum2=board[68]+board[77]+board[78]+board[86]+board[87]+board[88];
	if(board[11]*board[12]*board[13]*board[21]*board[22]*board[31]!=0&&sum1>6)
	return 2;
	else if(board[68]*board[77]*board[78]*board[86]*board[87]*board[88]!=0&&sum2<12)
	return 1;
	else
	return 0;
}

void ReadMove(char input[]){
	scanf("%s",input);
}

int turn(int steps){
	if(steps%2==0)
	return 1;
	else
	return 2;
}
#endif