/*
** EPITECH PROJECT, 2021
** MyRPG
** File description:
** stats_init
*/

#include "Rpg/Entities/stats.h"
#include "functions.h"

void stats_init_blank(stats_t *stats)
{
    stats->life = 0;
    stats->mp = 0;
    stats->ap = 0;
    stats->current_life = 0;
    stats->current_pa = 0;
    stats->current_pm = 0;
    stats->level = 1;
    stats->xp = 0;
    for (int i = 0; i < 4; i++) {
        stats->elements[i] = 0;
        stats->resistances[i] = 0;
    }
}

void stats_init(stats_t *stats, int *elements, int *resistances, int life)
{
    for (int i = 0; i < 4; i++) {
        stats->elements[i] = elements[i];
        stats->resistances[i] = resistances[i];
    }
    stats->life = life;
}

void stats_init_pa_pm(stats_t *stats, int ap, int mp)
{
    stats->ap = ap;
    stats->mp = mp;
}
