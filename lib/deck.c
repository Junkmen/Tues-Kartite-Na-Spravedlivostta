#include "deck.h"

//Puts a card into deck
int push_card(struct card_t card_to_push, struct deck_t *player_deck)
{
	if (player_deck -> size < _DECK_) {
		player_deck -> card_deck[player_deck -> size++] = card_to_push;
		return 0;
	} else {
		return 1;
	}
}
//Gets a card from deck
int draw_card(struct deck_t *player_deck, struct card_t *card)
{
	if(player_deck -> size > 0) {
		*card = player_deck -> card_deck[--(player_deck->size)];
		return 0;
	} else {
		return 1;
	}
}
//Lets say its pretty much usless :D  
int look_card(struct deck_t *player_deck, struct card_t card)
{
	if(player_deck -> size > 0) {
		card = player_deck -> card_deck[player_deck->size-1];
		return 0;
	} else {
		return 1;
	}
}
