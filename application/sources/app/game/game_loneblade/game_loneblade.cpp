#include "game_loneblade.h"
#include "game_player.h"
#include "game_monster.h"
#include "screens.h"

void game_loneblade_init() {
	player_init();
	monster_init();
}

void game_loneblade_update(uint32_t dt) {
	player_update(dt);
	monster_update(dt);
}

void game_loneblade_draw() {
	// Draw background/ground line
	view_render.drawLine(0, GAME_GROUND_Y, 124, GAME_GROUND_Y, WHITE);
	
	// Draw HUD (HP)
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(5, 4);
	view_render.print("HP: ");
	view_render.print(hero.hp);
	
	// Draw Entities
	player_draw();
	monster_draw();
}
