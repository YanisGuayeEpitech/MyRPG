/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** MyRPG_destroy
*/

#include <stdlib.h>
#include "Rpg/rpg.h"

void rpg_destroy(rpg_t *rpg)
{
    destroy_inventory(rpg);
    if (rpg->map)
        map_destroy(rpg->map);
    player_destroy(rpg->player);
    my_hash_map_drop(&rpg->spells);
    allies_destroy(&rpg->allies);
    quests_destroy(&rpg->quests);
    sfSprite_destroy(rpg->battle_end.item_sprite);
    sfSprite_destroy(rpg->battle_end.menu_sprite);
    free(rpg);
}
