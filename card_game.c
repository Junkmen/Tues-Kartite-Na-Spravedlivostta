#include<stdio.h>
#include "lib/board.h"

int main()
{
	struct card_t card[2];
	struct deck_t deck1;
	struct player_t Player1;
	struct board_t board;
	card[0].health = 2;
	card[0].damage = 3;
	card[0].mana = 5;
	card[1].health = 2;
	card[1].damage = 1;
	board.Player[0].deck.size = 0;
	board.Player[0].manapool.mana = 5;
	board.Player[0].cards_in_hand.size = 0;
	board.Card_Positions[0][0] = -1;
	push_card(card[0],&board.Player[0].deck);
	print_card(board.Player[0].deck.card_deck[0]);
	turn_begin(&board.Player[0]);
	print_card(board.Player[0].cards_in_hand.card_deck[0]);
	printf("\n%d\n",can_play_card(&board,0,0,0));
	play_card(&board,0,0,0);
	print_card(board.Cards_on_Board.card_deck[0]);
	board.Player[1].health = 30;
	board.Card_Positions[0][1] = -1;
	turn_end(&board, 0);
	printf("\n%d\n",board.Player[1].health);
	return 0;
}
