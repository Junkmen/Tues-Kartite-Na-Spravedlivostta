#include "manapool.h"

int can_put_card(struct card_t card_to_put, struct manapool_t pool){
	
	if(card_to_put.mana <= pool.mana) 
		return 1;
	return 0;

}
int use_card(struct card_t *card, struct manapool_t *pool) {
	//Will be implemented in Board
	//Remove later.
}
int change_mana(struct manapool_t *manapool,int remove) {
	//Remove can be negative and positive.	
	manapool-> mana += remove;
	if (manapool -> mana > xMAXMANA) manapool -> mana = xMAXMANA;
}
