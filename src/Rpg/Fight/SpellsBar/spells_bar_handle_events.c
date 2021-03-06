/*
** EPITECH PROJECT, 2021
** MyRPG
** File description:
** spells_bar_handle_events
*/

#include "Rpg/Fight/fight.h"
#include "Rpg/rpg.h"
#include "Rpg/Fight/spells_bar.h"

int spells_bar_get_hovered(spells_bar_t *bar)
{
    sfRenderWindow *window = bar->fight->rpg->state->game_data->window;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f view_pos =
        sfRenderWindow_mapPixelToCoords(window, mouse_pos, bar->view);
    sfVector2i spell_pos = {-1, -1};
    int id;

    spell_pos.x = view_pos.x / FRAME_WIDTH;
    spell_pos.y = view_pos.y / FRAME_WIDTH;
    if (view_pos.x < 0 || view_pos.y < 0 || spell_pos.x >= SPELLS_BAR_WIDTH
        || spell_pos.y >= SPELLS_BAR_HEIGHT)
        return -1;
    id = spell_pos.x + spell_pos.y * SPELLS_BAR_WIDTH;
    if (sfColor_toInteger(sfRectangleShape_getFillColor(bar->frames[id])) == 0)
        return -1;
    return id;
}

void spells_bar_update_outlines(spells_bar_t *bar)
{
    for (int i = 0; i < bar->nb_frames; i++)
        sfRectangleShape_setOutlineColor(bar->frames[i],
            (i == bar->current_frame) ? sfColor_fromRGB(252, 120, 0)
                                      : sfColor_fromRGB(72, 104, 89));
}

static int update_selected(spells_bar_t *bar)
{
    int id = spells_bar_get_hovered(bar);

    if (id == -1)
        return 0;
    if (bar->current_frame == id)
        bar->current_frame = -1;
    else {
        if (id == -1
            || MY_VEC_GET_ELEM(spell_base_t *, &bar->last_entity->spells, id)
                    ->ap
                > bar->last_entity->stats->current_pa)
            bar->current_frame = -1;
        else {
            bar->current_frame = id;
            play_sound(&bar->fight->rpg->state->game_data->audio, "select");
        }
    }
    spells_bar_update_outlines(bar);
    spells_bar_update_entity_spell(bar);
    return 1;
}

int spells_bar_handle_events(spells_bar_t *bar, sfEvent *event)
{
    sfRenderWindow *window = bar->fight->rpg->state->game_data->window;

    if (spells_bar_handle_move(bar, event, window))
        return 1;
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseLeft && update_selected(bar))
        return 1;
    return 0;
}
