#ifndef CARD
#define CARD

struct card_t {

	char name[25];
	int health;
	int damage;
	int mana;

};

int card_attack(struct card_t *attacker, struct card_t *defender);
void print_card(struct card_t card,int i);
#endif
