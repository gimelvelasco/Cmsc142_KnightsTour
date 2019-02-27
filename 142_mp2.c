/*
==============================================
Cmsc 42
Machine Problem 2

VELASCO, Gimel David F.
MENESES, Juancho Rodrigo
==============================================
				KNIGHT'S TOUR
==============================================
Input: Initial Position of Knight in the board
Output: The Path of the Knight's Tour
==============================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <time.h>
#include <windows.h>
#define DIM 8

struct node{
	int row,col; //row and column
	int visited; //0 - unvisited | 1 - visited
	struct node *neighbors[8]; //the 8 possible tiles the knight can jump to
	struct node *templink; //a linear link just for conveniece of accessing all the tiles
};

void insert_templink(struct node *e,struct node **h);

void print_templink(struct node **h);

void link_neighbors(struct node **h);

struct node * search_rowcol(struct node **h, int i, int j);

void print_board(struct node **h);

int pathfinder_dfs(struct node **h, struct node *kpos, int knight_jump, int tree_step);

void print_neighbors(struct node **h);

int main(){
	int i,j,k;//loops
	int r,c;//brd navigator
	char rowc,colc;//switch
	/////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////
	do{//the existence of the loop here is for the error handling
		scanf("\n%c%c",&colc,&rowc);
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
	printf("--------------------------------------");
	/////////////////////////////////////////////////////////////////
	int trial;
	for(trial=0;trial<3;trial++){
	/////////////////////////////////////////////////////////////////
	struct timeb start, end;
	int diff;
	///////////////////Initializing Data Structure///////////////////
	struct node **head = (struct node **) malloc(sizeof(struct node *));
	*head = NULL;
	struct node *temp = (struct node *) malloc(sizeof(struct node));

	for(i=0;i<DIM;i++){
		for(j=0;j<DIM;j++){
			temp = (struct node *) malloc(sizeof(struct node));
			temp->row = i;
			temp->col = j;
			temp->visited = 0;
			for(k=0;k<8;k++){
				temp->neighbors[k] = NULL;
			}
			temp->templink = NULL;
			insert_templink(temp,head);
		}
	}
	link_neighbors(head);
	/////////////////////////////////////////////////////////////////
	ftime(&start);
	//print_templink(head);
	//print_neighbors(head);
	//print_board(head);
	///////////////////Solving the Knight's Tour using Backtracking/Depth First Search
	struct node *p = search_rowcol(head,r,c);
	if(pathfinder_dfs(head,p,1,1) == 1){
		printf("\nPath of Knight's Tour starting in %c%c:\n",colc,rowc);
		print_board(head); //FINAL OUTPUT Print
	}
	else{
		printf("\nNo Path found for Knight starting in %c%c.\n",colc,rowc);
		print_board(head);
	}
	//int result = pathfinder_dfs(head,p,1,1);
	//printf("Result: %d\n",result);
	//print_templink(head);
	//print_neighbors(head);
	///////////////////
	ftime(&end);
	diff = (int)(1000*(end.time-start.time)+(end.millitm-start.millitm));
    printf("\nElapsed time is %u ms\n", diff);
	}
	/////////////////////////////////////////////////////////////////
	return 0;
	/////////////////////////////////////////////////////////////////
}

void insert_templink(struct node *e,struct node **h){
	if(*h == NULL){//if empty
		*h = e;
	}
	else{
		struct node *p = *h;
		while(p->templink != NULL){
			p = p->templink;
		}
		e->templink = p->templink;
		p->templink = e;
	}
}

void print_templink(struct node **h){
	struct node *p = *h;
	if(p == NULL){
		printf("No elements in list.\n");
	}
	else{
		printf("\tLIST\n");
		while(p != NULL){
			printf("RC: %d,%d V: %d, Next: %p\n",p->row, p->col, p->visited, p->templink);
			p = p->templink;
		}
	}
}

void link_neighbors(struct node **h){
	int i,j,k,boxStartRow,boxStartCol;
	struct node *p = *h;
	struct node *t;
	int row_inc[8] = {1,2,2,1,-1,-2,-2,-1};
	int col_inc[8] = {-2,-1,1,2,2,1,-1,-2};
	while(p != NULL){
		k=0;
		for(i=0;i<8;i++){
			if(((p->row+row_inc[i] >= 0) && (p->row+row_inc[i] <= 7)) && ((p->col+col_inc[i] >= 0) && (p->col+col_inc[i] <= 7))){//if within the left and right and within top and bottom
					p->neighbors[k] = search_rowcol(h,p->row+row_inc[i],p->col+col_inc[i]);
					k++;
			}
		}
		//printf("%d ",k);
		p = p->templink;
	}
}

struct node * search_rowcol(struct node **h, int i, int j){
	struct node *p = *h;
	while(p != NULL){
		if(p->row == i && p->col == j){
			return p;
		}
		p = p->templink;
	}
	return NULL;
}

void print_board(struct node **h){
	struct node *p = *h;
	int i,j;
	//FINAL OUTPUT Print
	printf("R C| A   B   C   D   E   F   G   H  \n");
	for(i=0;i<DIM;i++){
		printf(" %d |", DIM-i);
		for(j=0;j<DIM;j++){
			if(p->visited<10){//for the one-digit numbers
				printf(" 0%d ", p->visited);
			}
			else{
				printf(" %d ", p->visited);
			}
			p = p->templink;
		}
		printf("\n");
	}
	//
}

int pathfinder_dfs(struct node **h, struct node *kpos, int knight_jump, int tree_step){
	int i,j,nctr,result;
	////////////////////////////////////////////////////
	struct node *p = kpos;
	p->visited = knight_jump;
	//if((tree_step-1)%100 == 0){
	//	system("cls");
	//	print_board(h);
	//}
	if(knight_jump == 64){
		p->visited = 64;
		return 1;
	}
	for(nctr=0;nctr<8;nctr++){
		if(p->neighbors[nctr] != NULL){
			if(p->neighbors[nctr]->visited == 0){//if neighbor is unvisited, move there
				struct node *t = p->neighbors[nctr];
				if(pathfinder_dfs(h,t,knight_jump+1,tree_step+1) == 1){
					return 1;
				}
			}
		}
	}
	p->visited = 0;
	return 2;
}

void print_neighbors(struct node **h){
	struct node *p = *h;
	int nctr;
	if(p == NULL){
		printf("No elements in list.\n");
	}
	else{
		printf("\tLIST\n");
		while(p != NULL){
			printf("RC: %d,%d\n",p->row, p->col);
			for(nctr=0;nctr<8;nctr++){
				if(p->neighbors[nctr] != NULL){
					printf("%d%d, ",p->neighbors[nctr]->row, p->neighbors[nctr]->col);
				}
				else{
					break;
				}
			}
			printf("\n");
			p = p->templink;
		}
	}
}

/*
Pseudocode
Put Knight in first tile
Do until the knight has 64 jumps
	Do until there is no more tile to step on
		Jump to the next unvisited tile
	Go back and try the next neighbor

*/