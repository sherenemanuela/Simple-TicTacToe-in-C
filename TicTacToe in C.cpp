#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int freeSpaces, player;
char board[3][3];
const char mark[2] = {'X', 'O'};

// function to empty board values
void initializeBoard(){
   for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
         board[i][j] = ' ';
      }
   }
   
   freeSpaces = 9;
}

// function to print current board values
void printBoard(){
	printf("\n");
  	printf("  %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
   	printf(" ---|---|---\n");
   	printf("  %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
   	printf(" ---|---|---\n");
   	printf("  %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
   	printf("\n");
}

// function to print the match results
void printWinner(char winner){
	system("cls");
	printBoard();
	
   	if(winner == mark[0]){
   		if(player == 1) printf(" YOU WIN!");
      	else printf(" PLAYER 1 WINS!");
   	}	
   	else if(winner == mark[1]){
      	if(player == 1) printf(" YOU LOSE!");
      	else printf(" PLAYER 2 WINS");
   	}
   	else{
      	printf(" IT'S A TIE!");
   	}
}

// function to get player's next move
void playerTurn(int turn){
	int row, col;
	
   	do{
   		system("cls");
   		printBoard();
   		printf(" Enter row and column [row-col] (1-3): ");
      	scanf("%d-%d", &row, &col);
      	row--; col--;
		
		// if grid is empty
      	if(board[row][col] == ' '){
			board[row][col] = mark[turn];
			freeSpaces--;
        	break;
      	}
      	else{
      		printf("%c\n", board[row][col]);
      		printf("Invalid move!\n");
      	}
   	} while(board[row][col] != ' ');
}

// function to check the winner of the game
char checkWinner(){
	//check rows
   	for(int i = 0; i < 3; i++){
    	if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
	    	return board[i][0];
	  	}
   	}
   	
   	//check columns
   	for(int i = 0; i < 3; i++){
    	if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
        	return board[0][i];
      	}
   	}
   	
   	//check diagonals
   	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
    	return board[0][0];
   	}
   	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
    	return board[0][2];
   	}

   	return ' ';
}

// function to check if there are next moves left
int chanceExists(char winner){
	// if there are no moves left
	if(winner != ' ' || freeSpaces == 0){
	    return 0;
	}
	return 1;
}

void computerTurn(){
	int row, col;
	
	//creates a seed based on current time
   	srand(time(0));

   	if(freeSpaces > 0){
	   	do{
	   		row = rand() % 3;
         	col = rand() % 3;
      	}while(board[row][col] != ' ');
      
      	board[row][col] = mark[1];
  	}
   	else{
      	printWinner(' ');
   	}
}

int main(){
   char winner, response;

   	do{
	   	winner = ' ';
      	response = ' ';
      	initializeBoard();
		
		system("cls");
		printf(" How many player(s) are playing? (1-2): ");
		scanf("%d", &player);
		
      	while(winner == ' ' && freeSpaces != 0){
	    	
	    	system("cls");
	    	
	        // first player turn
	        if(player > 1) printf(" PLAYER 1 TURN\n");
	        
	        playerTurn(0);
	        winner = checkWinner();
	        
			if(!chanceExists(winner)) break;
	        
	        system("cls");
	        
			// second player turn
			if(player == 1){
				computerTurn();
			}
			else{
				printf(" PLAYER 2 TURN\n");
				playerTurn(1);
			}
		    winner = checkWinner();
		    
		    if(!chanceExists(winner)) break;
      	}
      	
		printWinner(winner);
      	printf("\n\n Would you like to play again? (Y/N): ");
      	scanf("%c");
      	scanf("%c", &response);
   } while (response == 'Y' || response == 'y');
	
	system("cls");
   	printf("Thanks for playing!");

   return 0;
}
