#include "card.h"	
#include<stdio.h>		
int card_attack(struct card_t *attacker, struct card_t *defender) 
{
	int survivor=0;
	attacker -> health -= defender -> damage;
	defender -> health -= attacker -> damage; 
	if(attacker -> health > 0) survivor++;
	if(defender -> health > 0) survivor+=2;
	return survivor;
}
void print_card(struct card_t card,int i) {
	if(card.mana < 0) card.mana = 0;
	if (i == 1)
	printf("%d|%d (%d)|", card.health,card.damage,card.mana);
	else printf(" %d|%d  #", card.health,card.damage);
}
