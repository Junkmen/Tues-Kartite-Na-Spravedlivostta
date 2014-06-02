#include "board.h"

void PrintBoard(struct board_t board) {
	
	printf("\n\n\n\n\nPLAYER:PLAYER1 (%d),MANA %d/%d,TURN:x",board.Player[0].health,board.Player[0].manapool.mana ,board.Player[0].manapool.max_mana);
	printf("\n___________________________________________________________________\n|");
	int i;
	for (i = 0; i < 5; i++) {
		if(board.Player[0].Open_Spots_Hand[i] == 1) printf("      |");
		else print_card(board.Player[0].cards_in_hand.card_deck[i],1);
	}
	printf("\n###################################################################\n#");
	for (i = 0; i < 5; i++) {
		if (board.Card_Positions[i][0] == -1) printf("      #");
		else print_card(board.Cards_on_Board.card_deck[board.Card_Positions[i][0]],0);
	}
	printf("\n#");
	for (i = 0; i < 5; i++) {
		if (board.Card_Positions[i][1] == -1) printf("      #");
		else print_card(board.Cards_on_Board.card_deck[board.Card_Positions[i][1]],0);
	}
	printf("\n###################################################################\n|");
	for (i = 0; i < 5; i++) {
		if(board.Player[1].Open_Spots_Hand[i] == 1) printf("      |");
		else print_card(board.Player[1].cards_in_hand.card_deck[i],1);
	}
	printf("\n___________________________________________________________________\n|");
	printf("PLAYER:PLAYER2 (%d),MANA %d/%d,TURN:x\n",board.Player[1].health,board.Player[1].manapool.mana ,board.Player[1].manapool.max_mana);	
	
}

int DeckFromFile(struct board_t *board, int pPlayer, char *filename) {	
	FILE *fp;
	char str[1800];
	char *buff;
	fp = fopen(filename, "r");
	if (fp == NULL) return 0;
	while( fgets(str, 1800, fp) ) {
		buff = strtok(str, ",");
		sscanf(buff,"%s", &board->Player[pPlayer].deck.card_deck[board->Player[pPlayer].deck.size].name);

		buff = strtok(NULL, ",");
		sscanf(buff,"%d", &board->Player[pPlayer].deck.card_deck[board->Player[pPlayer].deck.size].mana);
		
		buff = strtok(NULL, ",");
		sscanf(buff,"%d", &board->Player[pPlayer].deck.card_deck[board->Player[pPlayer].deck.size].damage);

		buff = strtok(NULL, ",");
		sscanf(buff,"%d", &board->Player[pPlayer].deck.card_deck[board->Player[pPlayer].deck.size].health);
	
		board->Player[pPlayer].deck.size++;	
	}
	fclose(fp);
	return 1;
}

int init_board(struct board_t *board)
{
	int i;
	for (i = 0; i < 5; i++) {
		board -> Card_Positions[i][0] = -1;
		board -> Card_Positions[i][1] = -1;
		board -> Open_Spots[i] = 1;
		board -> Player[0].Open_Spots_Hand[i] = 1;
		board -> Player[1].Open_Spots_Hand[i] = 1;
		board -> Card_Active[i][0] = 0;
		board -> Card_Active[i][1] = 0;
	
	}
	board -> Cards_on_Board.size = 0;
	board -> Player[0].health = xMAXHEALTH;
	board -> Player[1].health = xMAXHEALTH;
	board -> Player[0].cards_in_hand.size = 0;
	board -> Player[1].cards_in_hand.size = 0;
	board -> Player[0].deck.size = 0;
	board -> Player[1].deck.size = 0;
	board -> Player[0].manapool.mana = 1;
	board -> Player[0].manapool.max_mana = 1;
	board -> Player[1].manapool.mana = 1;
	board -> Player[1].manapool.max_mana = 1;
	if(!DeckFromFile(board,0,"p1deck.csv")) return 0;
	if(!DeckFromFile(board,1,"p1deck.csv")) return 0;
	return 1;
}

int can_play_card(struct board_t *board, int first_pl, int card, int num_lane) {
	
	if(board -> Card_Positions[num_lane][first_pl] == -1) {
		if (can_put_card( board -> Player[first_pl].cards_in_hand.card_deck[card],board -> Player[first_pl].manapool)) {
			return 1;
		} else {
			return 2;
		}
	} 
	return 0;

}
int play_card(struct board_t *board, int first_pl, int card, int num_lane){
	int result = can_play_card(board,first_pl,card,num_lane);
	if (result == 1) {
	
		struct card_t card_to_board = board->Player[first_pl].cards_in_hand.card_deck[card];
		board -> Card_Positions[num_lane][first_pl] = board -> Cards_on_Board.size;
		board -> Open_Spots[ board -> Card_Positions[num_lane][first_pl]] = 0;	
		push_card(card_to_board, &board->Cards_on_Board);
		board -> Player[first_pl].Open_Spots_Hand[card] = 1;
		board -> Card_Active[num_lane][first_pl] = 0;
		MP_use_card(card_to_board,&board->Player[first_pl].manapool);
	}	
	return result;

}
void turn_end(struct board_t *board, int first_pl) {
	int i;
	int other_pl = 1 - first_pl;
	for (i = 0; i < 5 ; i++) {
		board -> Card_Active[i][0]++;
		board -> Card_Active[i][1]++;
	}
	for (i = 0; i < 5; i++) {
		if (board -> Card_Positions[i][first_pl] != -1 && board-> Card_Active[i][first_pl]>1) 
			if (board -> Card_Positions[i][other_pl] != -1) 
			{
				int winner = card_attack( &board -> Cards_on_Board.card_deck[board -> Card_Positions[i][first_pl]] , &board -> Cards_on_Board.card_deck[board ->Card_Positions[i][other_pl]]);
				switch (winner) {
					case 1:	board -> Open_Spots[board -> Card_Positions[i][other_pl]] = 1;
						board -> Card_Positions[i][other_pl] = -1;

					case 2: board -> Open_Spots[board -> Card_Positions[i][first_pl]] = 1;
						board -> Card_Positions[i][first_pl] = -1;

					default: board -> Open_Spots[board -> Card_Positions[i][other_pl]] = 1;
						 board -> Card_Positions[i][other_pl] = -1;
						 board -> Open_Spots[board -> Card_Positions[i][first_pl]] = 1;
						 board -> Card_Positions[i][first_pl] = -1;
				}			
			} else {
				change_hp(&board-> Player[other_pl],  board-> Cards_on_Board.card_deck[ board -> Card_Positions[i][first_pl]].damage*-1);
			}
	}
	if (board -> Player[first_pl].manapool.max_mana < 10)
		board -> Player[first_pl].manapool.max_mana++;
	board -> Player[first_pl].manapool.mana = board -> Player[first_pl].manapool.max_mana;
}

/*
	If Card_Positions[x][z] = -1 => Slot is empty.
	If Open_Slots[x] = 1 Slot is open.

*/
