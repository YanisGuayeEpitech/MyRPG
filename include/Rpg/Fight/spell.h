/*
** EPITECH PROJECT, 2021
** rpg
** File description:
** spell
*/

#ifndef SPELL_H_
#define SPELL_H_

#include "Rpg/Entities/stats.h"

enum spell_type_e { SPELL_ATTACK, SPELL_HEAL, SPELL_EFFECT, SPELL_DEBUFF };
enum effect_type_e { EFFECT_DAMAGE, EFFECT_BOOST };

typedef struct spell_base {
    char *name;
    int po;
    int pa;
    int area;
    enum spell_type_e type;
} spell_base_t;

typedef struct spell_attack {
    spell_base base;
    int damages[4];
} spell_attack_t;

typedef struct spell_heal {
    spell_base base;
    int value;
} spell_heal_t;

typedef struct spell_effect {
    spell_base base;
    int lifetime;
    enum effect_type_e type;
    int damages[4];
    stats_t buff;
} spell_effect_t;

typedef struct spell_debuff {
    spell_base base;
    enum effect_type_e type;
} spell_debuff_t;

#endif /* !SPELL_H_ */