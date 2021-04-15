/*
** EPITECH PROJECT, 2020
** my_hunter
** File description:
** main loop of my hunter
*/

#include "Rpg/rpg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sfVector2f get_mouse_pos_vec2f(sfRenderWindow *w)
{
    sfVector2i vec = sfMouse_getPositionRenderWindow(w);

    return (sfVector2f){vec.x, vec.y};
}

static bool sprite_is_hover(sfSprite *s, sfVector2f m_pos)
{
    sfVector2f pos = sfSprite_getPosition(s);
    sfIntRect rect = sfSprite_getTextureRect(s);
    sfVector2f scale = sfSprite_getScale(s);

    if (m_pos.x > pos.x && m_pos.x < pos.x + rect.width * scale.x) {
        if (m_pos.y > pos.y && m_pos.y < pos.y + rect.height * scale.y) {
            return (true);
        }
    }
    return (false);

}

static char *int_to_str(int i)
{
    char *str = malloc(sizeof(char) * 3);

    str[0] = i / 10 + '0';
    str[1] = i % 10 + '0';
    str[2] = 0;
    return (str);
}

static unsigned int rpg_inventory_draw_items_tooltip_draw_stats_one_line\
(rpg_t *game, char *name, unsigned char stat, unsigned char drawed_line)
{
    char *numeric_stat = int_to_str((int)stat);

    if (stat == 0) {
        free(numeric_stat);
        return 0;
    }
    sfText_setString(game->inventory.stat_text, name);
    sfText_setPosition(game->inventory.stat_text,
                       get_mouse_pos_vec2f(game->wind));
    sfText_move(game->inventory.stat_text,
                (sfVector2f){70, 140 + drawed_line * 50});
    sfRenderWindow_drawText(game->wind, game->inventory.stat_text, NULL);
    sfText_move(game->inventory.stat_text, (sfVector2f){200, 0});
    sfText_setString(game->inventory.stat_text, numeric_stat);
    sfRenderWindow_drawText(game->wind, game->inventory.stat_text, NULL);
    free(numeric_stat);
    return (1);
}

static void rpg_inventory_draw_items_tooltip_draw_stats(rpg_t *game,
                                                        item_t *items)
{
    int drawed_line = 0;

    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Earth : ", items->earth, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Fire : ", items->fire, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Water : ", items->water, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Wind : ", items->wind, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Life : ", items->life, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Res Earth : ", items->res_earth, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Res Fire: ", items->res_fire, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Res Water : ", items->res_water, drawed_line);
    drawed_line += rpg_inventory_draw_items_tooltip_draw_stats_one_line
        (game, "Res Wind : ", items->res_wind, drawed_line);
}

static void rpg_inventory_draw_items_tooltip(rpg_t *game, item_t *item)
{
    sfVector2i vec = sfMouse_getPositionRenderWindow(game->wind);
    sfVector2f new_vec = {vec.x, vec.y};

    if (!item->name)
        return;
    sfText_setPosition(game->inventory.text, new_vec);
    sfText_setString(game->inventory.text, item->name);
    sfSprite_setTextureRect(game->inventory.tooltip, (sfIntRect)
                                 {64 * item->rarity, 0, 64, 64});
    sfSprite_setPosition(game->inventory.tooltip,
                         get_mouse_pos_vec2f(game->wind));
    sfText_move(game->inventory.text, (sfVector2f){(576 - sfText_getLocalBounds(game->inventory.text).width) / 2, 70});
    sfRenderWindow_drawSprite(game->wind, game->inventory.tooltip, NULL);
    rpg_inventory_draw_items_tooltip_draw_stats(game, item);
    sfRenderWindow_drawText(game->wind, game->inventory.text, NULL);
}

static inline void set_item_texture_rect(sfSprite *sprite, item_t i)
{
    sfSprite_setTextureRect(sprite, (sfIntRect){i.rarity * 16,
                i.elem * 16, 16, 16});
}

static inline bool is_scrolling_deep(inventory_t *inv, unsigned int i)
{
    return ((bool)((inv->items[i].name && i < (unsigned int)40
                   + inv->scroll * 4) && (inv->scroll < 39)));
}

static inline int get_scroll(rpg_t *g)
{
    return (int)(g->inventory.scroll * 4);
}

static void rpg_inventory_draw_items(rpg_t *game)
{
    int save = -1;
    sfVector2i vec = sfMouse_getPositionRenderWindow(game->wind);
    sfVector2f new_vec = {vec.x, vec.y};
    sfVector2f pos = (sfVector2f){0, 0};

    sfSprite_setPosition(game->inventory.sprite, (sfVector2f){0, 0});
    for (int i = get_scroll(game); is_scrolling_deep(&game->inventory, i);i++) {
        set_item_texture_rect(game->inventory.sprite, game->inventory.items[i]);
        sfRenderWindow_drawSprite(game->wind, game->inventory.sprite, NULL);
        if (sprite_is_hover(game->inventory.sprite, new_vec))
            save = i;
        sfSprite_move(game->inventory.sprite, (sfVector2f){64, 0});
        pos.x++;
        if (pos.x == 4) {
            sfSprite_move(game->inventory.sprite, (sfVector2f){-320 + 64, 64});
            pos.x = 0;
            pos.y++;
        }
    }
    if (save != -1)
        rpg_inventory_draw_items_tooltip(game, &game->inventory.items[save]);
}



extern void rpg_inventory_draw(rpg_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyA))
        game->inventory.is_open = !(game->inventory.is_open);
    if (game->inventory.is_open) {
        sfRenderWindow_drawSprite(game->wind, game->inventory.ui_inventory, 0);
        rpg_inventory_draw_items(game);
    }
}

extern void rpg_add_item_to_inventory(rpg_t *game, item_t item)
{
    unsigned int i = 0;

    for (; game->inventory.items[i].name != NULL; i++);
    game->inventory.items[i] = item;
}

extern void destroy_inventory(rpg_t *game)
{
    for (uint i = 0; game->inventory.items[i].name; i++) {
        free(game->inventory.items[i].name);
    }
    free(game->inventory.items);
    free(game->inventory.item_selected);
    sfSprite_destroy(game->inventory.sprite);
    sfSprite_destroy(game->inventory.tooltip);
    sfTexture_destroy(game->inventory.texture);
    sfText_destroy(game->inventory.text);
    sfTexture_destroy(game->inventory.texture_tooltip);
    sfFont_destroy(game->inventory.font);
    sfText_destroy(game->inventory.stat_text);
    sfFont_destroy(game->inventory.stat_font);
    sfRenderWindow_destroy(game->wind);
}
