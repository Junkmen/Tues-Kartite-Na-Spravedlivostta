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
	while(winner == 0) {
	
		turn_begin(&board.Player[pTurn]);
		//Print Board Here !

		//==================
		while (pCard != 6) {
			printf("Choose card:");
			scanf("%d",&pCard);
			printf("\nChoose lane:");
			scanf("%d",&mLane);
			int result = play_card(&board,pTurn,pCard,mLane);
			
			
		}
		turn_end(&board,pTurn);			
	}
	
	return 0;
}
