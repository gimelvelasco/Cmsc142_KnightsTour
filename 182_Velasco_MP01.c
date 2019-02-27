#include<stdio.h>
#define DIM 8

//The convention of the priority values and the potential destination squares are based on the given standards

int main(){
	int board[DIM][DIM] =	{{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0}};
	int priob[DIM][DIM] =	{{1,2,3,3,3,3,2,1},
							{2,3,4,4,4,4,3,2},
							{3,4,5,5,5,5,4,3},
							{3,4,5,5,5,5,4,3},
							{3,4,5,5,5,5,4,3},
							{3,4,5,5,5,5,4,3},
							{2,3,4,4,4,4,3,2},
							{1,2,3,3,3,3,2,1}};
	int pvps[DIM] = {0.0};//priority value of possible steps
	int i,j;//loops
	int r,c;//brd navigator
	int step=1;
	int minprio,minindex;
	char rowc,colc;//switch
	
	//INTRO
	printf("\tWelcome to\n\tTHE KNIGHT'S TOUR\n\n\n\n");
	//
	printf("R C| A   B   C   D   E   F   G   H  \n");//initial board printer - this is for user-friendliness
	for(i=0;i<DIM;i++){
		printf(" %d |", DIM-i);
		for(j=0;j<DIM;j++){
			printf(" __ ");
		}
		printf("\n");
	}
	//
	printf("\nSelect Initial Position of Knight: ");
	//
	do{//the existence of the loop here is for the error handling
		scanf("%c%c",&colc,&rowc);
		//the two switches converts the coordinates to be able to access the 2D array
		switch(colc){
			case 'A':
				c = 0;
				break;
			case 'B':
				c = 1;		
				break;
			case 'C':
				c = 2;
				break;
			case 'D':
				c = 3;
				break;
			case 'E':
				c = 4;
				break;
			case 'F':
				c = 5;
				break;
			case 'G':
				c = 6;
				break;
			case 'H':
				c = 7;
				break;
			default:
				c = 8;
				printf("\nInvalid Input. Try Again: ");
				break;
		}
		switch(rowc){
			case '8':
				r = 0;
				break;
			case '7':
				r = 1;
				break;
			case '6':
				r = 2;
				break;
			case '5':
				r = 3;
				break;
			case '4':
				r = 4;
				break;
			case '3':
				r = 5;
				break;
			case '2':
				r = 6;
				break;
			case '1':
				r = 7;
				break;
			default:
				r = 8;
				printf("\nInvalid Input. Try Again: ");
				break;
		}
	}while(r==8||c==8);
	//
	priob[r][c] = 10;//this marks the initial square as 'visited'
	//
	do{//this block is the 'backbone' of the algorithm
		//
		board[r][c] = step;//this marks the number of step on the tile that the knight is stepping on
		//this block puts the priority value of possible steps into the one dim array
			//pos 0
		if((r-1<0||r-1>7)||(c+2<0||c+2>7)){//if out of bounds
			pvps[0] = 10;
		}
		else if(priob[r-1][c+2]==10){//if already visited
			pvps[0] = 10;	
		}
		else{
			pvps[0] = priob[r-1][c+2];
		}
			//pos 1
		if((r-2<0||r-2>7)||(c+1<0||c+1>7)){//if out of bounds
			pvps[1] = 10;
		}
		else if(priob[r-2][c+1]==10){//if already visited
			pvps[1] = 10;	
		}
		else{
			pvps[1] = priob[r-2][c+1];
		}	
			//pos 2
		if((r-2<0||r-2>7)||(c-1<0||c-1>7)){//if out of bounds
			pvps[2] = 10;
		}
		else if(priob[r-2][c-1]==10){//if already visited
			pvps[2] = 10;	
		}
		else{
			pvps[2] = priob[r-2][c-1];
		}	
			//pos 3
		if((r-1<0||r-1>7)||(c-2<0||c-2>7)){//if out of bounds
			pvps[3] = 10;
		}
		else if(priob[r-1][c-2]==10){//if already visited
			pvps[3] = 10;	
		}
		else{
			pvps[3] = priob[r-1][c-2];
		}	
			//pos 4
		if((r+1<0||r+1>7)||(c-2<0||c-2>7)){//if out of bounds
			pvps[4] = 10;
		}
		else if(priob[r+1][c-2]==10){//if already visited
			pvps[4] = 10;	
		}
		else{
			pvps[4] = priob[r+1][c-2];
		}	
			//pos 5
		if((r+2<0||r+2>7)||(c-1<0||c-1>7)){//if out of bounds
			pvps[5] = 10;
		}
		else if(priob[r+2][c-1]==10){//if already visited
			pvps[5] = 10;	
		}
		else{
			pvps[5] = priob[r+2][c-1];
		}	
			//pos 6
		if((r+2<0||r+2>7)||(c+1<0||c+1>7)){//if out of bounds
			pvps[6] = 10;
		}
		else if(priob[r+2][c+1]==10){//if already visited
			pvps[6] = 10;	
		}
		else{
			pvps[6] = priob[r+2][c+1];
		}	
			//pos 7
		if((r+1<0||r+1>7)||(c+2<0||c+2>7)){//if out of bounds
			pvps[7] = 10;
		}
		else if(priob[r+1][c+2]==10){//if already visited
			pvps[7] = 10;	
		}
		else{
			pvps[7] = priob[r+1][c+2];
		}
		//
		minprio = 10;//this resets the minimum
		for(i=0;i<DIM;i++){//gets value of top priority (minimum)
			if(minprio>pvps[i]){
				minprio = pvps[i];
				minindex = i;
			}
		}
		//

		//
		switch(minindex){//this block of code moves the knight to the new position
			case 0:
				r = r-1;
				c = c+2;
				break;
			case 1:
				r = r-2;
				c = c+1;
				break;
			case 2:
				r = r-2;
				c = c-1;
				break;
			case 3:
				r = r-1;
				c = c-2;
				break;
			case 4:
				r = r+1;
				c = c-2;
				break;
			case 5:
				r = r+2;
				c = c-1;
				break;
			case 6:
				r = r+2;
				c = c+1;
				break;
			case 7:
				r = r+1;
				c = c+2;
				break;
			default:
			
				break;
		}
		//
		step++;
		priob[r][c] = 10;//this will 'mark' the current square as 'visited'
		//
	}while(minprio!=10);
	//
	
	//FINAL OUTPUT Print
	printf("\n\nR C| A   B   C   D   E   F   G   H  \n");
	for(i=0;i<DIM;i++){
		printf(" %d |", DIM-i);
		for(j=0;j<DIM;j++){
			if(board[i][j]<10){//for the one-digit numbers
				printf(" 0%d ", board[i][j]);
			}
			else{
				printf(" %d ", board[i][j]);
			}
		}
		printf("\n");
	}
	//
	return 0;
	
	/*
	Bonus:
	The Knight will be able to finish the tour at starting squares:
	A7
	B2
	B6
	D3
	*/
}