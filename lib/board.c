#include "board.h"

int can_play_card(struct board_t *board, int first_pl, int card, int num_lane) {
	
	if(board -> Card_Positions[num_lane][first_pl] = -1) {
		if (can_put_card( board -> Player[first_pl].cards_in_hand.card_deck[card],board -> Player[first_pl].manapool)) {
			return 1;
		} 
		return 2;
	} else {
		return 0;
	}

}
int play_card(struct board_t *board, int first_pl, int card, int num_lane){
	
	if (can_play_card(board,first_pl,card,num_lane) == 1) {
	
		struct card_t card_to_board = board->Player[first_pl].cards_in_hand.card_deck[card];
		board -> Card_Positions[num_lane][first_pl] = board -> Cards_on_Board.size;
		board -> Open_Spots[ board -> Card_Positions[num_lane][first_pl]] = 0;	
		push_card(card_to_board, &board->Cards_on_Board);
	}	

}
void turn_end(struct board_t *board, int first_pl) {
	int i;
	int other_pl = 1 - first_pl;
	for (i = 0; i < 5; i++) {
		if (board -> Card_Positions[i][first_pl] != -1) 
			if (board -> Card_Positions[i][other_pl] != -1) 
			{
				int winner = card_attack( &board -> Cards_on_Board.card_deck[board -> Card_Positions[i][first_pl]] , &board -> Cards_on_Board.card_deck[board ->Card_Positions[i][other_pl]]);
				switch (winner) {
					case 1:	board -> Open_Spots[board -> Card_Positions[i][other_pl]] = 1;
						board -> Card_Positions[i][other_pl] = -1;

					case 2: board -> Open_Spots[board -> Card_Positions[i][other_pl]] = 1;
						board -> Card_Positions[i][first_pl] = -1;

					default: break;
				}			
			} else {
				board-> Player[other_pl].health -= board-> Cards_on_Board.card_deck[ board -> Card_Positions[i][first_pl]].damage;
			}
	}
	board -> Player[first_pl].manapool.max_mana++;
	board -> Player[first_pl].manapool.mana = board -> Player[first_pl].manapool.max_mana;
}

/*
	If Card_Positions[x][z] = -1 => Slot is empty.
	If Open_Slots[x] = 1 Slot is open.

*/
