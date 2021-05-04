/*
** EPITECH PROJECT, 2021
** My rpg
** File description:
** Rpg create
*/

#include <libmy/memory/alloc.h>

#include "Rpg/rpg.h"
#include "Rpg/Fight/spell.h"

rpg_t *rpg_create(state_t *state)
{
    rpg_t *rpg = my_calloc(1, sizeof(rpg_t));

    spells_init(rpg);
    rpg->state = state;
    rpg->wind = state->game_data->window;
    rpg->player = player_create();
    sfRectangleShape_setTexture(rpg->player->entity->rect,
        get_texture(&state->game_data->assets, "inspector"), true);
    animations_reset(&rpg->player->entity->anim);
    entity_init_spells(rpg->player->entity, rpg);
    rpg->map = map_create(rpg);
    return rpg;
}