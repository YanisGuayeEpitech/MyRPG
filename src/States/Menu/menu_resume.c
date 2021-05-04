/*
** EPITECH PROJECT, 2020
** My runner
** File description:
** Menu - resume
*/

#include <libmy/io/iostream.h>

#include "States/Menu/menu_state.h"

int menu_state_resume(menu_state_t *state, state_id_t last_state)
{
    my_puts("Menu State\n");
    my_fflush(MY_STDOUT);
    (void)state;
    (void)last_state;
    return 0;
}