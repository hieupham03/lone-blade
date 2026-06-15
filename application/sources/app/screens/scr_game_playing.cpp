#include "scr_game_playing.h"
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
	view_render.drawRect(0, 0, 124, 60, WHITE);
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(15, 25);
	view_render.print("GAMEPLAY SCREEN");
	view_render.setCursor(6, 40);
	view_render.print("Press MODE to Menu");
}

void scr_game_playing_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY: {
        APP_DBG_SIG("SCREEN_ENTRY scr_game_playing\n");
    } break;
    
    case AC_DISPLAY_BUTON_MODE_PRESSED: {
        APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_PRESSED in scr_game_playing -> back to Menu\n");
        BUZZER_PlaySound(BUZZER_SOUND_CLICK);
        SCREEN_BACK();
    } break;
    
    default:
        break;
    }
}
