/*
** EPITECH PROJECT, 2021
** My rpg
** File description:
** Rpg create
*/

#include <libmy/memory/alloc.h>

#include "Rpg/rpg.h"

rpg_t *rpg_create(state_t *state)
{
    rpg_t *rpg = my_calloc(1, sizeof(rpg_t));

    rpg->state = state;
    rpg->wind = state->game_data->window;
    rpg->player = player_create();
    rpg->map = map_create(rpg);
    return rpg;
}
