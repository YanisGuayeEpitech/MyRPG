/*
** EPITECH PROJECT, 2021
** rpg
** File description:
** infobox_spell_destroy
*/

#include "Rpg/InfoBox/infobox_spell.h"

void infobox_spell_destroy(infobox_spell_base_t *info)
{
    switch (info->spell->type) {
        case SPELL_ATTACK:
            infobox_spell_attack_destroy((infobox_spell_attack_t *)info);
            break;
        case SPELL_HEAL:
            infobox_spell_heal_destroy((infobox_spell_heal_t *)info);
            break;
        case SPELL_DEBUFF:
            infobox_spell_debuff_destroy((infobox_spell_debuff_t *)info);
            break;
        default: break;
    }
    sfText_destroy(info->name);
    sfText_destroy(info->pa);
    sfText_destroy(info->po);
    sfText_destroy(info->area);
    sfText_destroy(info->type);
    sfText_destroy(info->turn_limit);
}