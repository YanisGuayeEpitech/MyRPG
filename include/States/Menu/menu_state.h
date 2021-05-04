/*
** EPITECH PROJECT, 2020
** My runner
** File description:
** menu state
*/

#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameEngine/state.h"
#include <sw/widget.h>
#include <sw/layouts/vertical.h>
#include <sw/widgets/button.h>

#include "menu_cst.h"

typedef struct menu_state {
    state_t base;
    sw_base_t *gui_base;
} menu_state_t;

state_t *menu_state_create(game_data_t *data);
void menu_init_gui(menu_state_t *state);
int menu_state_resume(menu_state_t *state, state_id_t last_state);
int menu_state_handle_events(menu_state_t *state);
int menu_state_update(menu_state_t *state, float dt);
int menu_state_draw(menu_state_t *state, float dt);
int menu_state_pause(menu_state_t *state, state_id_t new_state);
void menu_state_destroy(menu_state_t *state, state_id_t from);

#endif /* !MENU_STATE_H */