/*
** EPITECH PROJECT, 2021
** MyRPG
** File description:
** entity_init
*/

#include "Rpg/Fight/fight.h"
#include "Rpg/Interfaces/inventory.h"
#include "Rpg/rpg.h"

void entity_init(entity_t *entity)
{
    entity->spell_select = -1;
    if (entity->type == PLAYER)
        player_set_equipment_stats((player_t *)entity->datas);
    entity->stats->current_life = entity->stats->life;
    entity_start_turn(entity, 1);
}
