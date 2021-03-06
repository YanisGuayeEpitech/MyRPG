/*
** EPITECH PROJECT, 2021
** My Rpg
** File description:
** layer create
*/

#include <libmy/memory/alloc.h>

#include "Rpg/Map/layer.h"

layer_t *layer_create(sfTexture *tex, int tiles_size)
{
    layer_t *layer = my_calloc(1, sizeof(layer_t));

    layer->tex = tex;
    layer->tiles_size = tiles_size;
    return layer;
}
