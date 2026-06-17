#include "game_monster.h"
#include "game_player.h"
#include "screens.h"
#include <stdlib.h>

static Monster monster_pool[MAX_MONSTERS];
static int32_t spawn_timer;

// Helper to spawn a new monster
static void spawn_monster() {
	int slot = -1;
	for (int i = 0; i < MAX_MONSTERS; i++) {
		if (!monster_pool[i].active) {
			slot = i;
			break;
		}
	}
	if (slot == -1) return;

	Monster* m = &monster_pool[slot];
	m->active = true;
	m->state = MONSTER_STATE_WALKING;
	m->state_timer = 0;
	m->anim_timer = 0;
	m->anim_frame = 0;

	// Randomly spawn Left (X = -10) or Right (X = 134)
	if (rand() % 2 == 0) {
		m->x_scaled = -10 * 1000;
		m->dir = 1; // moves right towards center
	} else {
		m->x_scaled = 134 * 1000;
		m->dir = -1; // moves left towards center
	}

	// Randomly choose type: NORMAL (60%), ARMORED (25%), FLYING (15%)
	int r = rand() % 100;
	if (r < 60) {
		m->type = MONSTER_TYPE_NORMAL;
		m->hp = 3;
		m->speed = 36;
		m->y = 53;
	} else if (r < 85) {
		m->type = MONSTER_TYPE_ARMORED;
		m->hp = 5;
		m->speed = 30; 
		m->y = 53;
	} else {
		m->type = MONSTER_TYPE_FLYING;
		m->hp = 1;
		m->speed = 40; 
		m->y = 38; 
	}
}



void monster_init() {
	for (int i = 0; i < MAX_MONSTERS; i++) {
		monster_pool[i].active = false;
		monster_pool[i].x_scaled = 0;
		monster_pool[i].y = 53;
		monster_pool[i].state = MONSTER_STATE_WALKING;
		monster_pool[i].state_timer = 0;
		monster_pool[i].hp = 0;
		monster_pool[i].speed = 0;
		monster_pool[i].dir = 1;
		monster_pool[i].anim_timer = 0;
		monster_pool[i].anim_frame = 0;
	}
	spawn_timer = 1200; 
}

void monster_spawn_trigger() {
	spawn_monster();
}

Monster* monster_get_pool() {
	return monster_pool;
}

uint8_t monster_get_active_count() {
	uint8_t count = 0;
	for (int i = 0; i < MAX_MONSTERS; i++) {
		if (monster_pool[i].active) count++;
	}
	return count;
}

void monster_update(uint32_t dt) {
	if (spawn_timer > (int32_t)dt) {
		spawn_timer -= dt;
	} else {
		spawn_timer = 0;
	}

	if (spawn_timer == 0) {
		uint8_t active_count = 0;
		for (int i = 0; i < MAX_MONSTERS; i++) {
			if (monster_pool[i].active) active_count++;
		}
		if (active_count < MAX_MONSTERS) {
			spawn_monster();
		}
		spawn_timer = 1200 + (rand() % 1201); // Random 1.2s to 2.4s
	}

	// 2. FSM Update for each monster
	for (int i = 0; i < MAX_MONSTERS; i++) {
		Monster* m = &monster_pool[i];
		if (!m->active) continue;

		// Update state timer
		if (m->state_timer > dt) {
			m->state_timer -= dt;
		} else {
			m->state_timer = 0;
		}

		// Update animation frame timer
		m->anim_timer += dt;
		if (m->anim_timer >= 200) {
			m->anim_timer = 0;
			m->anim_frame = !m->anim_frame;
		}

		int16_t x = m->x_scaled / 1000;

		switch (m->state) {
			case MONSTER_STATE_WALKING: {
				if (m->state_timer > 0) {
					break;
				}

				int16_t dist_to_hero = (m->dir == 1) ? (62 - x) : (x - 62);
				if (dist_to_hero <= MONSTER_ATTACK_RANGE) {
					m->state = MONSTER_STATE_PRE_ATTACK;
					m->state_timer = 250; 
				} else {
					m->x_scaled += (int32_t)m->dir * m->speed * dt;
				}
				break;
			}

			case MONSTER_STATE_PRE_ATTACK: {
				if (m->state_timer == 0) {
					player_take_damage();

					m->state = MONSTER_STATE_WALKING;
					m->state_timer = 800; 
				}
				break;
			}

			case MONSTER_STATE_STUNNED: {
				if (m->state_timer == 0) {
					m->state = MONSTER_STATE_WALKING;
					m->state_timer = 200; 
				}
				break;
			}

			case MONSTER_STATE_KNOCKBACK: {
				int32_t kb_speed = 60; 
				m->x_scaled -= (int32_t)m->dir * kb_speed * dt;

				if (m->state_timer == 0) {
					m->state = MONSTER_STATE_WALKING;
					m->state_timer = 200; 
				}
				break;
			}
		}
	}
}

void monster_draw() {
	for (int i = 0; i < MAX_MONSTERS; i++) {
		Monster* m = &monster_pool[i];
		if (!m->active) continue;

		int16_t x = m->x_scaled / 1000;
		int16_t y = m->y;

		if (m->state == MONSTER_STATE_PRE_ATTACK && m->anim_frame) {
			continue;
		}

		switch (m->type) {
			case MONSTER_TYPE_NORMAL: {
				int16_t draw_x = x - 6;
				int16_t draw_y = y - 14;

				view_render.drawBitmap(draw_x, draw_y, bitmap_monster_normal, 12, 14, WHITE);

				if (m->state == MONSTER_STATE_STUNNED) {
					view_render.drawPixel(x - 2, draw_y - 2, WHITE);
					view_render.drawPixel(x + 2, draw_y - 2, WHITE);
				}
				break;
			}

			case MONSTER_TYPE_ARMORED: {
				int16_t draw_x = x - 8;
				int16_t draw_y = y - 19;

				view_render.drawBitmap(draw_x, draw_y, bitmap_monster_armored, 16, 19, WHITE);

				if (m->hp < 2) {
					view_render.drawLine(draw_x + 3, draw_y + 3, draw_x + 13, draw_y + 16, BLACK);
					view_render.drawLine(draw_x + 13, draw_y + 3, draw_x + 3, draw_y + 16, BLACK);
				}

				if (m->state == MONSTER_STATE_STUNNED) {
					view_render.drawPixel(x - 3, draw_y - 2, WHITE);
					view_render.drawPixel(x + 3, draw_y - 2, WHITE);
				}
				break;
			}

			case MONSTER_TYPE_FLYING: {
				int16_t draw_x = x - 6;
				int16_t draw_y = y - 8;

				const unsigned char* bitmap = m->anim_frame ? bitmap_monster_fly_frame1 : bitmap_monster_fly_frame2;
				view_render.drawBitmap(draw_x, draw_y, bitmap, 12, 8, WHITE);

				if (m->state == MONSTER_STATE_STUNNED) {
					view_render.drawPixel(x - 2, draw_y - 2, WHITE);
					view_render.drawPixel(x + 2, draw_y - 2, WHITE);
				}
				break;
			}
		}
	}
}
