#include "game_player.h"
#include "screens.h"

Player hero;

void player_init() {
	hero.x = 62;       
	hero.y = 53;       
	hero.state = PLAYER_STATE_IDLE;
	hero.dir = DIR_RIGHT;
	hero.state_timer = 0;
	hero.hp = PLAYER_MAX_HP;
	hero.mana = 0;
}


void player_attack_left() {
	if (hero.state == PLAYER_STATE_IDLE) {
		hero.state = PLAYER_STATE_ATTACK1;
		hero.dir = DIR_LEFT;
		hero.state_timer = 150;
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
	}
}

void player_attack_right() {
	if (hero.state == PLAYER_STATE_IDLE) {
		hero.state = PLAYER_STATE_ATTACK1;
		hero.dir = DIR_RIGHT;
		hero.state_timer = 150;
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
	}
}


void player_attack_left2() {
	if (hero.state == PLAYER_STATE_IDLE || hero.state == PLAYER_STATE_ATTACK1) {
		hero.state = PLAYER_STATE_ATTACK2;
		hero.dir = DIR_LEFT;
		hero.state_timer = 150;
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
	}
}

void player_attack_right2() {
	if (hero.state == PLAYER_STATE_IDLE || hero.state == PLAYER_STATE_ATTACK1) {
		hero.state = PLAYER_STATE_ATTACK2;
		hero.dir = DIR_RIGHT;
		hero.state_timer = 150;
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
	}
}

void player_shield(bool active) {
	if (active) {
		if (hero.state == PLAYER_STATE_IDLE) {
			hero.state = PLAYER_STATE_SHIELD;
		}
	} else {
		if (hero.state == PLAYER_STATE_SHIELD) {
			hero.state = PLAYER_STATE_IDLE;
			hero.state_timer = 0;
		}
	}
}

void player_take_damage() {
	if (hero.state != PLAYER_STATE_SHIELD && hero.state != PLAYER_STATE_DEFEAT) {
		hero.state = PLAYER_STATE_HURT;
		hero.state_timer = 300;
		
		if (hero.hp > 0) {
			hero.hp--;
		}
		
		if (hero.hp == 0) {
			hero.state = PLAYER_STATE_DEFEAT;
			hero.state_timer = 0; 
		}
		
		BUZZER_PlaySound(BUZZER_SOUND_3BEEP);
	}
}


void player_update(uint32_t dt) {
	if (hero.state_timer > 0) {
		if (hero.state_timer >= dt) {
			hero.state_timer -= dt;
		} else {
			hero.state_timer = 0;
		}

		if (hero.state_timer == 0) {
			if (hero.state == PLAYER_STATE_ATTACK1 || 
				hero.state == PLAYER_STATE_ATTACK2 || 
				hero.state == PLAYER_STATE_HURT) {
				hero.state = PLAYER_STATE_IDLE;
			}
		}
	}
}

void player_draw() {
	const unsigned char* bitmap = bitmap_hero_idle_right;
	uint8_t w = 22;
	uint8_t h = 19;
	int16_t draw_x = hero.x;
	int16_t draw_y = hero.y - 19; 

	switch (hero.state) {
		case PLAYER_STATE_IDLE:
			w = 22;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_idle_left;
				draw_x = hero.x - 11;
			} else {
				bitmap = bitmap_hero_idle_right;
				draw_x = hero.x - 11;
			}
			break;


		case PLAYER_STATE_ATTACK1:
			w = 32;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_attack_left;
				draw_x = hero.x - 21;
			} else {
				bitmap = bitmap_hero_attack_right;
				draw_x = hero.x - 11;
			}
			break;

		case PLAYER_STATE_ATTACK2:
			w = 35;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_attack2_left;
				draw_x = hero.x - 24; 
			} else {
				bitmap = bitmap_hero_attack2_right;
				draw_x = hero.x - 11;
			}
			break;

		case PLAYER_STATE_SHIELD:
			w = 16;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_shield_left;
				draw_x = hero.x - 8;
			} else {
				bitmap = bitmap_hero_shield_right;
				draw_x = hero.x - 8;
			}
			break;

		case PLAYER_STATE_HURT:
			if (hero.state_timer > 150) {
				return; 
			}
			w = 22;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_idle_left;
				draw_x = hero.x - 11;
			} else {
				bitmap = bitmap_hero_idle_right;
				draw_x = hero.x - 11;
			}
			break;

		case PLAYER_STATE_DEFEAT:
			w = 42;
			if (hero.dir == DIR_LEFT) {
				bitmap = bitmap_hero_defeat_left;
				draw_x = hero.x - 21;
			} else {
				bitmap = bitmap_hero_defeat_right;
				draw_x = hero.x - 21;
			}
			break;
	}

	view_render.drawBitmap(draw_x, draw_y, bitmap, w, h, WHITE);
}
