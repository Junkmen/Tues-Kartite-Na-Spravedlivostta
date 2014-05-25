#ifndef xBOARD
#define xBOARD
#include "player.h"

struct board_t {
	struct player_t Player[2];
	struct deck_t   Cards_on_Board;
	int Card_Positions[5][2];
	int Open_Spots[10];
};
init_board(struct board_t *board);
int can_play_card(struct board_t *board, int first_pl, int card, int
num_lane);
int play_card(struct board_t *board, int first_pl, int card, int
num_lane);
void turn_end(struct board_t *board, int first_pl);




#endif
