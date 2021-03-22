/*
** EPITECH PROJECT, 2020
** My runner
** File description:
** handle settings inputs
*/

#include "States/Settings/settings_state.h"

static int handle_key(sfEvent event, state_t *state)
{
    switch (event.key.code) {
    case sfKeyEscape:
        end_state(state->game_data, SETTINGS_STATE);
        return 1;
    default:
        return 0;
    }
}

int settings_handle_input(state_t *state)
{
    game_data_t *data = state->game_data;
    sfEvent event;

    while (sfRenderWindow_pollEvent(data->window, &event)){
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->window);
        if (event.type == sfEvtKeyReleased && handle_key(event, state))
            return 1;
    }
    return 1;
}