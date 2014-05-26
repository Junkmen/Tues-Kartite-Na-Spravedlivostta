#include "player.h"

void turn_begin(struct player_t *player) {
	struct card_t card_to_use;
	int i;
	for (i = 0; i < 5; i ++) {
		if (player -> Open_Spots_Hand[i] == 1) {
			draw_card(&player -> deck, &card_to_use);
			player -> cards_in_hand.card_deck[i] = card_to_use;
			player -> Open_Spots_Hand[i] = 0;
			break;
		}
	}
	
}

int change_hp(struct player_t *player,int change) {
	player -> health += change;
	if (player -> health > xMAXHEALTH) player -> health = xMAXHEALTH;
}
