#include<stdio.h>
#include "lib/card.h"
#include "lib/deck.h"

int main()
{
	struct card_t card[2];
	struct deck_t deck1;
	card[0].health = 2;
	card[0].damage = 3;
	card[1].health = 2;
	card[1].damage = 1;

	push_card(card[0],&deck1);
	
	printf("%d\n",card_attack(&card[0],&card[1]));

	return 0;
}
