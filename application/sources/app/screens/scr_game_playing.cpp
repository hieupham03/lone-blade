#include "screens.h"
#include "scr_game_playing.h"
#include "game_player.h"

static void view_scr_game_playing();

view_dynamic_t dyn_view_game_playing = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_playing
};

view_screen_t scr_game_playing = {
	&dyn_view_game_playing,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

static void view_scr_game_playing() {
	view_render.clear();
	
	view_render.drawLine(0, 53, 124, 53, WHITE);
	
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(5, 4);
	view_render.print("HP: ");
	view_render.print(hero.hp);
	
	view_render.setCursor(75, 4);
	view_render.print("MANA: ");
	view_render.print(hero.mana);
	
	player_draw();
}

void scr_game_playing_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY scr_game_playing\n");
		player_init(); 
		
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_GAME_TICK, 33, TIMER_PERIODIC);
	} break;

	case SCREEN_EXIT: {
		APP_DBG_SIG("SCREEN_EXIT scr_game_playing\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_GAME_TICK);
	} break;

	case AC_DISPLAY_GAME_TICK: {
		player_update(33);
	} break;

	case AC_DISPLAY_BUTON_DOWN_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_PRESSED: Attack Left\n");
		player_attack_left();
	} break;

	case AC_DISPLAY_BUTON_UP_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_PRESSED: Attack Right\n");
		player_attack_right();
	} break;

	case AC_DISPLAY_BUTON_MODE_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_PRESSED scr_game_playing -> Quay ve Menu\n");
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
		SCREEN_BACK();
	} break;

	default:
		break;
	}
}
