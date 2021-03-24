/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** player physic init
*/

#include "Rpg/rpg.h"

void player_init_physic(player_t *player, pe_world_t *world)
{
    pe_body_t *body = player->body;
    pe_fixture_t *fixture = pe_fixture_init();

    if (body)
        pe_body_destroy(body);
    body = pe_body_init(DYNAMIC, 1, 5);
    body->can_sleep = 0;
    body->pos = VEC2F(player->pos.x / M_TO_PX, player->pos.y / M_TO_PX);
    body->linear_damping = 7;
    body->fixed_rotation = 1;
    fixture->restitution = 0.2;
    fixture->density = 30;
    pe_shape_init_rect(&fixture->shape, VEC2F(0, 0), VEC2F(1, 2));
    pe_body_add_fixture(body, fixture);
    pe_world_add_body(world, body);
    player->body = body;
}