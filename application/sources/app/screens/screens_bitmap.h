#ifndef __SCREENS_BITMAP_H__
#define __SCREENS_BITMAP_H__

#include "view_render.h"

// scr_welcome
extern const unsigned char PROGMEM bitmap_dolphin[];

// Hero Sprites (New)
// bitmap_hero_idle_left: 22x19px
extern const unsigned char PROGMEM bitmap_hero_idle_left[];
// bitmap_hero_idle_right: 22x19px
extern const unsigned char PROGMEM bitmap_hero_idle_right[];
// bitmap_hero_attack_left: 32x19px
extern const unsigned char PROGMEM bitmap_hero_attack_left[];
// bitmap_hero_attack_right: 32x19px
extern const unsigned char PROGMEM bitmap_hero_attack_right[];
// bitmap_hero_attack2_left: 28x19px
extern const unsigned char PROGMEM bitmap_hero_attack2_left[];
// bitmap_hero_attack2_right: 28x19px
extern const unsigned char PROGMEM bitmap_hero_attack2_right[];
// bitmap_hero_shield_left: 16x19px
extern const unsigned char PROGMEM bitmap_hero_shield_left[];
// bitmap_hero_shield_right: 16x19px
extern const unsigned char PROGMEM bitmap_hero_shield_right[];
// bitmap_hero_defeat_left: 42x19px
extern const unsigned char PROGMEM bitmap_hero_defeat_left[];
// bitmap_hero_defeat_right: 42x19px
extern const unsigned char PROGMEM bitmap_hero_defeat_right[];
// bitmap_hero_ulti_left: 13x19px
extern const unsigned char PROGMEM bitmap_hero_ulti_left[];
// bitmap_hero_ulti_right: 13x19px
extern const unsigned char PROGMEM bitmap_hero_ulti_right[];

// Monster Bitmaps
extern const unsigned char PROGMEM bitmap_monster_normal[];
extern const unsigned char PROGMEM bitmap_monster_armored[];
extern const unsigned char PROGMEM bitmap_monster_fly_frame1[];
extern const unsigned char PROGMEM bitmap_monster_fly_frame2[];

#endif //__SCREENS_BITMAP_H__
