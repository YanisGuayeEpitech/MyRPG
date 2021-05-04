/*
** EPITECH PROJECT, 2021
** rpg
** File description:
** stats_destroy
*/

#include <stdlib.h>
#include "Rpg/Entities/stats.h"

void stats_destroy(stats_t *stats)
{
    my_vec_free(&stats->effects, NULL);
    free(stats);
}