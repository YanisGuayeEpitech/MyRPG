/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** zone destroy
*/

#include <stdlib.h>
#include "Rpg/Map/zone.h"

void zone_destroy(zone_t *zone)
{
    if (zone->layers) {
        for (int i = 0; i < zone->nb_layers; i++)
            layer_destroy(zone->layers[i]);
        free(zone->layers);
    }
    if (zone->battle.layer)
        layer_destroy(zone->battle.layer);
    free(zone->battle.tiles);
    free(zone->special);
    if (zone->world)
        pe_world_destroy(zone->world);
    free(zone);
}