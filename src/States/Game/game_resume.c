/*
** EPITECH PROJECT, 2020
** My runner
** File description:
** Menu - resume
*/

#include <libmy/io/iostream.h>

#include "States/Game/game_state.h"

int game_state_resume(game_state_t *state, state_id_t last_state)
{
    my_puts("Game State\n");
    my_fflush(MY_STDOUT);
    (void)state;
    (void)last_state;
    return 0;
}