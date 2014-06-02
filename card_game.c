#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "lib/board.h"

int seedNotGiven = 1;
void RunSimpleAI(struct board_t *board, int pTurn) {
	int hasMana = 1;
	int CardToPlay = 0;
	while(hasMana) {
		int i;
		for (i = 1; i < 5; i++ ) {
			if (board -> Player[pTurn].Open_Spots_Hand[i] != 1) //Check if there is Card in the hand slot
				if (board->Player[pTurn].cards_in_hand.card_deck[i].mana < board -> Player[pTurn].cards_in_hand.card_deck[CardToPlay].mana) //Checks mana cost on the current card vs selected .
					CardToPlay = i;
		}
		//Look for empty lanes to put the card in.
		for (i = 0; i < 5; i ++) 
			if (board -> Card_Positions[i][pTurn] == -1) {
					i = play_card(board,pTurn,CardToPlay,i);
					if (i == 2) hasMana = 0;
					break;
			}

	}
}
//Stefan Iliev. - Special Project: Card Generator. 
struct card_t GenerateCard() {
	if (seedNotGiven) {
		srand(time(NULL));
		seedNotGiven = 0;
	}
	struct card_t GeneratedCard;
	
	int damage = rand()%10+1;
	GeneratedCard.damage = damage;

	int health = rand()%12+1;
	float dec = health/1.8;
	if (dec > damage) health = damage * 1.8; 
	GeneratedCard.health = health;
	
	int manacost = rand()%((damage+health)/2)+1;
	if (manacost > 10) manacost = 10;
	GeneratedCard.mana = manacost;

	return GeneratedCard;
}

struct deck_t GenerateMultipleCards(int NumberOfCards) {
	int i = 0;
	struct deck_t deck;
	deck.size = 0;
	while (i < NumberOfCards) {
		push_card(GenerateCard(),&deck);
		i++;
	}
	return deck;
}

int WriteGeneratedDeckToFile(struct deck_t *deck,char *filename) {
	FILE *fp;
	int prevSize = deck -> size;
	struct card_t CardToWrite;
	fp = fopen(filename, "w");
	if (fp == NULL) return 0; //Check for errors in creating/rewriting file.
	while( deck->size != 0 ) {
		
		draw_card(deck,&CardToWrite);
		fprintf(fp,"NEMA IME,%d,%d,%d,\n",CardToWrite.mana,CardToWrite.damage,CardToWrite.health);

	}
	deck -> size = prevSize;
	fclose(fp);
	return 1;
}

//Fuck it.GG.Nabs.Bronze 5.EZ. inb4 200 errors

int main()
{
	struct board_t board;
	int winner = 0;
	int pTurn = 0;
	int pCard = 0;
	int mLane = 0;
	struct card_t generatedCard;
	struct deck_t generatedDeck = GenerateMultipleCards(30);
	WriteGeneratedDeckToFile(&generatedDeck,"idiocracy.csv");
	generatedCard = GenerateCard();
	print_card(generatedCard,1);
	// INIT STUFF HERE !
	if (!init_board(&board)) {
		printf("Error.File Not Found! WTF, DO NOT TOUCH THE DATA !\n");
		return -1;
	}
	// =================
	winner = 0;
	while(winner == 0) {
		pCard = 0;
		turn_begin(&board.Player[pTurn]);
		//Print Board Here !
		PrintBoard(board);
		//==================
		if (pTurn == 0) 
		while (pCard != 6) {
			printf("Choose card:");
			scanf("%d",&pCard);
			if (pCard !=6 && board.Player[pTurn].Open_Spots_Hand[pCard-1] != 1) {
				printf("\nChoose lane:");
				scanf("%d",&mLane);
				int result = play_card(&board,pTurn,pCard-1,mLane-1);
						PrintBoard(board);
			}		
			
		}
		else RunSimpleAI(&board,pTurn);
		turn_end(&board,pTurn);
		if (board.Player[pTurn].health <= 0) {				
			winner = 1-pTurn;		
			break;	
		}		
		pTurn = 1-pTurn;				
	}
	printf("\n\nWinner is Player: %d\n\n",winner+1);
	
	return 0;
}
