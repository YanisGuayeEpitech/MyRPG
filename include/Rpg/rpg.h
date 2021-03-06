/*
** EPITECH PROJECT, 2021
** My rpg
** File description:
** MyRPG struct
*/

#ifndef MY_RPG_H
#define MY_RPG_H

#include "Quests/quests.h"
#include "Rpg/Entities/allies.h"
#include "Rpg/Entities/player.h"
#include "Rpg/Interfaces/inventory.h"
#include "Rpg/Interfaces/battle_end.h"
#include "Rpg/Map/map.h"
#include "Rpg/Map/physic.h"
#include "GameEngine/game_head.h"

#define M_TO_PX 32.f

typedef struct rpg {
    /// key type: 'char *'
    /// Value value: 'spell_base_t *'
    my_hash_map_t spells;
    state_t *state;
    sfRenderWindow *wind;
    map_t *map;
    player_t *player;
    inventory_t inventory;
    allies_t allies;
    quest_list_t quests;
    battle_end_t battle_end;
} rpg_t;

rpg_t *rpg_create(state_t *state);
void rpg_handle_event(rpg_t *rpg, sfEvent event);
void rpg_update(rpg_t *rpg, float dt);
void rpg_draw(rpg_t *rpg);
void rpg_destroy(rpg_t *rpg);

#endif /* !MY_RPG_H */
