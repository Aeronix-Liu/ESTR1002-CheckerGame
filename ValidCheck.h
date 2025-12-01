#ifndef _VALIDCHECK_H
#define _VALIDCHECK_H
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
char Is4Digits(char input[]);
char InBoard(int ori,int des);
char ValidStart(int ori,int turn,const int*board );
char ValidEnd(int des,const int* board);
char ValidJump(int ori,int via,const int *board);

char Is4Digits(char input[]){
	if(strlen(input)!=4){
		return 0;
	}
	for(int i=0;i<4;i++){
		if(!isdigit(input[i]))
		return 0;
	}
	return 1;
}

char InBoard(int ori,int des){
	if(ori<11||ori>88||ori%10==0||ori%10==9)
	return 0;
	if(des<11||des>88||des%10==0||des%10==9)
	return 0;
	return 1;
}

char ValidStart(int ori,int turn,const int* board){
	if(board[ori]!=turn)
	return 0;
	return 1;
}

char ValidEnd(int des,const int*board){
	if(board[des]!=0)
	return 0;
	return 1;
}

char ValidJump(int ori,int via,const int *board){
	if((abs(ori-via)%9!=0)&&(abs(ori-via)%10!=0)&&(abs(ori-via)%11!=0)&&(abs(ori-via)>7))
	return 0;
	if(ori==via)
	return 0;
	int end=2*via-ori;
	if(board[end]!=0)
	return 0;
	if(end>88||end<11||end%10==0||end%10==9)
	return 0;
	if(ori>via){
		if(ori-via<8){                   //row jump
			for(int i=ori-1;i>end;i--){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}                       //row jump ends
		else if((ori-via)%10==0){           //column jump
			for(int i=ori-10;i>end;i=i-10){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}             //column jump ends
		else if((ori-via)%9==0){             //diagonal jump1
			for(int i=ori-9;i>end;i=i-9){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}
		else if((ori-via)%11==0){            //diagonal jump2
			for(int i=ori-11;i>end;i=i-11){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}
	}
	
	else{
		if(via-ori<8){                   //row jump
			for(int i=end-1;i>ori;i--){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}                       //row jump ends
		else if((via-ori)%10==0){           //column jump
			for(int i=end-10;i>ori;i=i-10){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}             //column jump ends
		else if((via-ori)%9==0){             //diagonal jump1
			for(int i=end-9;i>ori;i=i-9){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}
		else if((via-ori)%11==0){            //diagonal jump2
			for(int i=end-11;i>ori;i=i-11){
				if(i==via)
				continue;
				if(board[i]!=0)
				return 0;
			}
			return 1;
		}
	}
}

#endif