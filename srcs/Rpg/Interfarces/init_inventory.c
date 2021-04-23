 /*
** EPITECH PROJECT, 2020
** my_hunter
** File description:
** init game
*/

#include "Rpg/rpg.h"
#include <stdio.h>
#include <string.h>
#include "dirent.h"

item_t inventory_init_blanck_item(void)
{
    item_t i;

    i.earth = 0;
    i.elem = 0;
    i.fire = 0;
    i.level = 0;
    i.life = 0;
    i.name = NULL;
    i.rarity = 0;
    i.res_earth = 0;
    i.res_water = 0;
    i.res_wind = 0;
    i.res_fire = 0;
    i.water = 0;
    i.wind = 0;
    return (i);
}

extern inventory_t inventory_init(void)
{
    inventory_t inv;

    inv.scroll = 0;
    inv.sprite = sfSprite_create();
    inv.texture = sfTexture_createFromFile("./assets/Inventory/items_sheet.png", NULL);
    inv.items = malloc(sizeof(item_t) * 200);
    for (uint i = 0; i != 200; i++)
        inv.items[i] = rpg_create_blank_item();
    inv.ui_inventory = sfSprite_create();
    inv.ui_int_texture = sfTexture_createFromFile("./assets/Inventory/inventory_menu.png", NULL);
    sfSprite_setScale(inv.ui_inventory, (sfVector2f){4, 4});
    sfSprite_setTexture(inv.ui_inventory, inv.ui_int_texture, sfFalse);
    sfSprite_setTexture(inv.sprite, inv.texture, sfFalse);
    sfSprite_setTextureRect(inv.sprite, (sfIntRect){0, 0, 16, 16});
    sfSprite_setScale(inv.sprite, (sfVector2f){4, 4});
    inv.text = sfText_create();
    inv.font = sfFont_createFromFile("./assets/Fonts/pixel.ttf");
    sfText_setFont(inv.text, inv.font);
    sfText_setColor(inv.text, sfWhite);
    sfText_setCharacterSize(inv.text, 37);
    inv.equipement = malloc(sizeof(item_t) * 4);
    for (int i = 0; i != 4; i++) {
        inv.equipement[i].name = malloc(sizeof(char) * 1);
        inv.equipement[i] = rpg_create_blank_item();
    }
    inv.container =  sfSprite_create();
    sfSprite_setTexture(inv.container, inv.ui_int_texture , sfFalse);
    sfSprite_setTextureRect(inv.container, (sfIntRect){0, 0, 16, 16});
    sfSprite_setScale(inv.container, (sfVector2f){4, 4});
    inv.tooltip = sfSprite_create();
    inv.texture_tooltip = sfTexture_createFromFile("./assets/Inventory/items_tooltip.png", NULL);
    sfSprite_setTexture(inv.tooltip, inv.texture_tooltip, sfFalse);
    sfSprite_setScale(inv.tooltip, (sfVector2f){9, 9});
    inv.stat_text = sfText_create();
    inv.stat_font =  sfFont_createFromFile("./assets/Fonts/pixel.ttf");
    sfText_setFont(inv.stat_text, inv.stat_font);
    sfText_setCharacterSize(inv.stat_text, 30);
    sfText_setColor(inv.stat_text, sfWhite);
    inv.is_open = false;
    inv.item_selected = rpg_create_blank_item();
    return (inv);
}
