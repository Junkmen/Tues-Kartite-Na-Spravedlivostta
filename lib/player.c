#include "player.h"

void turn_begin(struct player_t *player) {
	struct card_t card_to_use;
	draw_card(&player -> deck, &card_to_use);
	push_card(card_to_use, &player -> cards_in_hand);

}

int change_hp(struct player_t *player,int change) {
	player -> health += change;
	if (player -> health > xMAXHEALTH) player -> health = xMAXHEALTH;
}
