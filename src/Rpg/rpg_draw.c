/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** rpg draw
*/

#include "Rpg/rpg.h"

void rpg_draw(rpg_t *rpg)
{
    map_draw(rpg->map);
    rpg_inventory_draw(rpg);
}
