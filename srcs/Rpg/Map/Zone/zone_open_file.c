/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** zone open file
*/

#include <stdlib.h>
#include "Rpg/Map/zone.h"
#include "My/my_file.h"
#include "My/my_display.h"
#include "My/my_convert.h"

static void read_infos(zone_t *zone, char *file_content, size_t *i)
{
    zone->nb_layers = my_get_number_pass(file_content, i);
    zone->size.x = my_get_number_pass(file_content, i);
    zone->size.y = my_get_number_pass(file_content, i);
    zone_init(zone, zone->nb_layers, zone->size);
}

int get_nb_pass(unsigned char *content, size_t *i, int pass)
{
    int layer = 0;

    while (content[*i] > 2) {
        layer *= 253;
        layer += content[*i] - 3;
        (*i)++;
    }
    if (pass)
        (*i)++;
    return layer;
}

static void read_pos(zone_t *zone, sfVector2i pos, \
size_t *i, unsigned char *content)
{
    int layer;
    int tile;

    if (content[*i] < 3)
        return;
    do {
        if (content[*i] == 1)
            (*i)++;
        layer = get_nb_pass(content, i, 1);
        tile = get_nb_pass(content, i, 0);
        if (layer > 0)
            layer_place_tile(zone->layers[layer - 1], pos, tile);
    } while (content[*i] == 1);
}

void zone_init_from_file(zone_t *zone, char *file)
{
    char *file_content = NULL;
    size_t i = 0;

    if (!my_readfile(&file_content, file)) {
        my_putstr_err("Can't read map\n");
        return;
    }
    read_infos(zone, file_content, &i);
    for (int x = 0; x < zone->size.x; x++) {
        for (int y = 0; y < zone->size.y; y++) {
            read_pos(zone, (sfVector2i){x, y}, &i, \
            (unsigned char *)file_content);
            i += (file_content[i] != 0);
        }
    }
    free(file_content);
}