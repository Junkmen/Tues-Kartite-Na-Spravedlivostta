#ifndef xBOARD
#define xBOARD
#include <player.h>

struct board_t {
	struct player_t Player1;
	struct player_t Player2;
	struct deck_t   Cards_on_Board;
	int Card_Positions[5][5];
};






#endif
