#include<stdio.h>
#include "lib/board.h"

int main()
{
	struct card_t card[2];
	struct deck_t deck1;
	struct player_t Player1;
	struct board_t board;
	int winner = 0;
	int pTurn = 0;
	int pCard = 0;
	int mLane = 0;
	// INIT STUFF HERE !
	if (!init_board(&board)) {
		printf("Error.File Not Found! WTF, DO NOT TOUCH THE DATA !\n");
		return -1;
	}
	// =================
	winner = 0;
	while(winner == 0) {
		pCard = 0;
		turn_begin(&board.Player[pTurn]);
		//Print Board Here !
		PrintBoard(board);
		//==================
		while (pCard != 6) {
			printf("Choose card:");
			scanf("%d",&pCard);
			if (pCard !=6 && board.Player[pTurn].Open_Spots_Hand[pCard-1] != 1) {
				printf("\nChoose lane:");
				scanf("%d",&mLane);
				int result = play_card(&board,pTurn,pCard-1,mLane-1);
						PrintBoard(board);
			}		
			
		}
		turn_end(&board,pTurn);
		pTurn = 1-pTurn;	
		if (board.Player[pTurn].health <= 0) winner = pTurn+1;	
	}
	if("\n\nWinner is Player: %d\n\n",winner);
	
	return 0;
}
