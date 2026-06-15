#include "screens.h"
#include "scr_game_over.h"

static void view_scr_game_over();

view_dynamic_t dyn_view_game_over = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_over
};

view_screen_t scr_game_over = {
	&dyn_view_game_over,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

static void view_scr_game_over() {
	view_render.clear();
	view_render.drawRect(0, 0, 124, 60, WHITE);
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(20, 25);
	view_render.print("GAME OVER");
	view_render.setCursor(6, 40);
	view_render.print("Press MODE to Menu");
}

void scr_game_over_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY scr_game_over\n");
	} break;

	case AC_DISPLAY_BUTON_MODE_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_PRESSED scr_game_over -> Back to Menu\n");
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
		SCREEN_BACK();
	} break;

	default:
		break;
	}
}
