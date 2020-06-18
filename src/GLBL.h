#ifndef GLBL_H
#define GLBL_H



namespace GLBL
{
	const int FPS = 60;
	const int DELAY_TIME = 1000 / FPS;

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	const int BACKGROUND_SRC_WIDTH = 1024;
	const int BACKGROUND_SRC_HEIGHT = 768;

	const int INTRO_BG_FRAME = 2;

	const int TOTAL_MENU_BUTTONS = 4;
	const int BUTTON_FRAME = 1;
	const int W_SRC_MENU_BUTTON = 492;
	const int H_SRC_MENU_BUTTON = 88;
	const int BUTTON_SPACE = (SCREEN_WIDTH / 100) * 2;

	const int TOTAL_LIGHTNING_FRAME = 2;
	const int TOTAL_SMOKE_FRAME = 9;

	const int TOTAL_CARDS = 44;
	const int SRC_CARD_W = 152;
	const int SRC_CARD_H = 224;
	const int SCREEN_SPACE = SCREEN_WIDTH / 64;
	const int DST_CARD_W = (SCREEN_WIDTH - (SCREEN_SPACE * 7)) / 6;
	const int DST_CARD_H = (SCREEN_HEIGHT / 3) - 2 * SCREEN_SPACE;
	const int DST_Y_PLAY_CARD = (SCREEN_HEIGHT / 3) * 2 + SCREEN_SPACE;

	const int DST_DECK_X = SCREEN_SPACE;
	const int DST_DECK_Y = SCREEN_SPACE;

	
	const int TOTAL_PLAY_BUTTON = 2; 
	const int SRC_PLAYBUTTON_W = 76;
	const int SRC_PLAYBUTTON_H = 76;
	const int DST_PLAYBUTTON_W = SCREEN_HEIGHT / 10;
	const int DST_PLAYBUTTON_H = DST_PLAYBUTTON_W;
	const int DST_FIRST_PLAY_BUTTON_X = SCREEN_WIDTH - 2 * DST_PLAYBUTTON_W - 2 * SCREEN_SPACE;

	const int DST_X_USED_CARD = SCREEN_WIDTH / 2 - DST_CARD_W / 2;
	const int DST_Y_USED_CARD = DST_Y_PLAY_CARD - DST_CARD_H / 2;

	const int DST_X_FIRST_PLAYER_TEXT = 2 * SCREEN_SPACE + DST_PLAYBUTTON_W;
	const int DST_X_SECOND_PLAYER_TEXT = SCREEN_WIDTH - (SCREEN_SPACE + DST_PLAYBUTTON_W + 48);
	const int DST_Y_PLAYER_TEXT = DST_DECK_Y + DST_CARD_H + 2 * SCREEN_SPACE;
//	const int DST_W_PLAYER_TEXT = 20;
//	const int DST_H_PLAYER_TEXT = 50;

	const int TOTAL_PLAY_HUD_ICONS = 3;

	const int START_HP = 30;
	const int START_GOLD = 15;
	const int START_MP = 15;


	const int FONT_SIZE = 48;
	const int DST_W_ONE_CHARACHTER = 24;

	const int SRC_OK_BUTTON_W = 341;
	const int SRC_OK_BUTTON_H = 76;
	const int DST_OK_BUTTON_W = SCREEN_WIDTH / 3;
	const int DST_OK_BUTTON_H = SCREEN_HEIGHT / 10;
	const int DST_OK_BUTTON_X = SCREEN_WIDTH / 3;
	const int DST_OK_BUTTON_Y = (SCREEN_HEIGHT / 10) * 6; 

	const int SRC_PLAYER_ICON_W_H = 100;
	const int SRC_COMP_ICON_Y = 0;
	const int SRC_LEFT_PLAYER_ICON_Y = 100;
	const int SRC_RIGHT_PLAYER_ICON_Y = 200;
	const int DST_PLAYER_ICON_W_H = SCREEN_WIDTH / 10;
	const int DST_PLAYER_ICONS_Y = SCREEN_SPACE;
	const int DST_LEFT_PLAYER_X = DST_DECK_X + DST_CARD_W + SCREEN_SPACE;
	const int DST_RIGHT_PLAYER_X = DST_FIRST_PLAY_BUTTON_X - DST_PLAYER_ICON_W_H - SCREEN_SPACE;

	const int DST_GAMEOVER_ICON_X = (SCREEN_WIDTH / 2) - (DST_PLAYER_ICON_W_H / 2);
	const int DST_GAMEOVER_ICON_Y = (SCREEN_HEIGHT / 10) * 2;


	struct position
	{
		int x_pos;
		int y_pos;
	};

	enum signal
	{
		none,
		quit,
		loadgame,
		savegame,
		newgamePC,
		newgamePlayer,
		introState,
		menuState,
		playState,
		confirmState,
		gameoverState,
		left_win,
		comp_win,
		right_win,
		AI_move
	};

	enum player_side
	{
		left,
		right
	};


	enum card_type
	{
		attack = 1,
		defense = 2
	};

	enum parameters_type
	{
		free,
		mana,
		gold,
		hp,
		none_type
	};
}

#endif
