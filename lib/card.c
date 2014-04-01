#include "card.h"			
int card_attack(struct card_t *attacker, struct card_t *defender) 
{
	int survivor=0;
	attacker -> health -= defender -> damage;
	defender -> health -= attacker -> damage; 
	if(attacker -> health > 0) survivor++;
	if(defender -> health > 0) survivor+=2;
	return survivor;
}
