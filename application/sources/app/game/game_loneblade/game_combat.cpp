#include "game_combat.h"
#include "game_monster.h"
#include "game_player.h"
#include "screens.h"
#include <stdlib.h>

void combat_register_hit(player_dir_t dir, int16_t range) {
	Monster* pool = monster_get_pool();
	bool hit_any = false;

	for (int i = 0; i < MAX_MONSTERS; i++) {
		Monster* m = &pool[i];
		if (!m->active) continue;

		int16_t mx = m->x_scaled / 1000;
		bool in_range = false;

		if (dir == DIR_LEFT) {
			if (mx <= hero.x && (hero.x - mx) <= range) {
				in_range = true;
			}
		} else {
			if (mx >= hero.x && (mx - hero.x) <= range) {
				in_range = true;
			}
		}

		if (in_range) {
			hit_any = true;

			if (m->hp > 0) {
				m->hp--;
			}

			if (m->hp == 0) {
				m->active = false;

				hero.mana += 15;
				if (hero.mana > PLAYER_MAX_MANA) {
					hero.mana = PLAYER_MAX_MANA;
				}
				
				BUZZER_PlaySound(BUZZER_SOUND_BANG);
			} else {

				if (rand() % 2 == 0) {
					m->state = MONSTER_STATE_STUNNED;
					m->state_timer = 400;
				} else {
					m->state = MONSTER_STATE_KNOCKBACK;
					m->state_timer = 200;
				}

				BUZZER_PlaySound(BUZZER_SOUND_CLICK);
			}
		}
	}

	if (!hit_any) {
		BUZZER_PlaySound(BUZZER_SOUND_CLICK);
	}
}
