/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** update the player
*/

#include <libmy/printf.h>

#include "Rpg/rpg.h"

static void player_update_anim_dir(
    player_t *player, sfVector2f offset, sfVector2i start_dir)
{
    if (offset.x == 0 && offset.y == 0) {
        animations_reset(&player->entity->anim);
        player->entity->anim.paused = 1;
    } else
        player->entity->anim.paused = 0;
    if (start_dir.x != player->dir.x || player->dir.y != start_dir.y) {
        if (player->dir.y)
            animations_set_animation(
                &player->entity->anim, (player->dir.y == -1));
        if (player->dir.x)
            animations_set_animation(
                &player->entity->anim, 2 + (player->dir.x == 1));
    }
}

static void update_dir(player_t *player, sfVector2f offset)
{
    sfVector2i dir = player->dir;

    if (offset.x < 0)
        player->dir.x = -1;
    else if (offset.x > 0)
        player->dir.x = 1;
    if (offset.y < 0)
        player->dir.y = -1;
    else if (offset.y > 0)
        player->dir.y = 1;
    if ((offset.x == 0) ^ (offset.y == 0)) {
        player->dir.x -= player->dir.x * (offset.x == 0);
        player->dir.y -= player->dir.y * (offset.y == 0);
    }
    if (player->entity->fight == NULL)
        player_update_anim_dir(player, offset, dir);
}

static void fill_offset(player_t *player, sfVector2f *offset)
{
    float amplitude = 6;

    if (sfKeyboard_isKeyPressed(sfKeyZ))
        offset->y = -amplitude;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        offset->y = amplitude;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        offset->x = -amplitude;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        offset->x = amplitude;
    update_dir(player, *offset);
    if ((offset->x || offset->y) && player->rpg->quests.dialogue.is_talking)
        player->rpg->quests.dialogue.is_talking = false;
    if ((offset->x || offset->y) && player->rpg->battle_end.is_on)
        player->rpg->battle_end.is_on = false;
}

void player_update(player_t *player, float dt)
{
    sfVector2f offset = {0, 0};

    animations_update(&player->entity->anim, dt);
    if (!player->body)
        return;
    fill_offset(player, &offset);
    if (offset.x != 0)
        player->body->velocity.x = offset.x;
    if (offset.y != 0)
        player->body->velocity.y = offset.y;
    player->pos = (sfVector2f){
        player->body->pos.x * M_TO_PX, player->body->pos.y * M_TO_PX};
    if (player->body
        && ((int)player->body->pos.x != player->last_pos.x
            || (int)player->body->pos.y != player->last_pos.y)) {
        player->last_pos =
            (sfVector2i){player->body->pos.x, player->body->pos.y};
        zone_interract_move(player->rpg->map->current_zone);
    }
    sfRectangleShape_setPosition(player->entity->rect, player->pos);
}
