#ifndef FINDALLMOVES1_H
#define FINDALLMOVES1_H
void BFS(char graph[89][89],int* queue,int curlen);
void BuildGraph(int board[89],char graph[89][89]);
char judge(int queue[],int size,int x);
void FindAllMoves(int steps,int board[],char Allgraph[89][89]);
char search(int ori,int des,char Allgraph[89][89]);

void BuildGraph(int board[89],char graph[89][89]){
	for(int i=11;i<89;i++){
		if(board[i]==0){
			for(int j=11;j<89;j++){
				if(board[j]==1||board[j]==2){
					if(ValidJump(i,j,board)){
						graph[i][2*j-i]=1;
					}
				}
			}
		}
	}
}

char judge(int queue[],int size,int x){
	for(int i=0;i<size;i++){
		if(queue[i]==x)
		return 0;
	}
	return 1;
}

void FindAllMoves(int steps,int board[],char Allgraph[89][89])
{
	int pieceposi[12];
	for(int i=0;i<12;i++){
		pieceposi[i]=0;
	}
	int mypieceposi[6];
	for(int i=0;i<6;i++){
		mypieceposi[i]=0;
	}
	int j1=0;
	int j2=0;
	for(int i=11;i<89;i++){
		if(board[i]==1||board[i]==2){
			pieceposi[j1]=i;
			j1++;
			if(board[i]==turn(steps)){
				mypieceposi[j2]=i;
				j2++;
			}
		}
    }
    for(int i=0;i<6;i++){
		char visited[89];
        for(int j=0;j<89;j++){
    	    visited[j]=0;
	    }
	    visited[mypieceposi[i]]=1;
	    int tmp[89];
        for(int j=0;j<89;j++){
    	    tmp[j]=board[j];
	    }
	    tmp[mypieceposi[i]]=0;
		char graph[89][89]={0};        
	    BuildGraph(tmp,graph);
	    int queue[89]={0};
	    queue[0]=mypieceposi[i];
	    int curlen=1;
	    BFS(graph,queue,curlen);
	    for(int j=0;queue[j]!=0;j++){
	    	Allgraph[mypieceposi[i]][queue[j]]=1;
		}
		if(mypieceposi[i]%10!=1){
			if(board[mypieceposi[i]-1]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]-1]=1;
		}
		if(mypieceposi[i]%10!=8){
			if(board[mypieceposi[i]+1]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]+1]=1;
		}
		if(mypieceposi[i]/10!=1){
			if(board[mypieceposi[i]-10]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]-10]=1;
		}
	    if(mypieceposi[i]/10!=8){
			if(board[mypieceposi[i]+10]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]+10]=1;
		}
		if(mypieceposi[i]%10!=1&&mypieceposi[i]/10!=1){
			if(board[mypieceposi[i]-11]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]-11]=1;
		}
		if(mypieceposi[i]%10!=8&&mypieceposi[i]/10!=1){
			if(board[mypieceposi[i]-9]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]-9]=1;
		}
		if(mypieceposi[i]%10!=1&&mypieceposi[i]/10!=8){
			if(board[mypieceposi[i]+9]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]+9]=1;
		}
        if(mypieceposi[i]%10!=8&&mypieceposi[i]/10!=8){
			if(board[mypieceposi[i]+11]==0)
			Allgraph[mypieceposi[i]][mypieceposi[i]+11]=1;
		}
		Allgraph[mypieceposi[i]][mypieceposi[i]]=0;
    }
}

char search(int ori,int des,char Allgraph[89][89]){
	return Allgraph[ori][des];
}

void BFS(char graph[89][89],int *queue,int curlen){
	char te=0;
	for(int i=0;i<89&&*(queue+i)!=0;i++){
		for(int j=11;j<89;j++){
			if(graph[*(queue+i)][j]==1&&judge(queue,curlen,j)){
				*(queue+curlen)=j;
				curlen++;
				te=1;
			}
		}
	}
	if(te==0){
		return;
	}
	BFS(graph,queue,curlen);
}
#endif