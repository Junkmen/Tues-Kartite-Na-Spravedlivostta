#ifndef xPLAYERH
#define xPLAYERH

#include "manapool.h"
#define xMAXHEALTH 30
struct player_t {
	int health;
	struct deck_t deck;
	struct manapool_t manapool;
	struct deck_t cards_in_hand;
	int Open_Spots_Hand[5];
};

int change_hp(struct player_t *player,int change);
void turn_begin(struct player_t *player);

#endif 
