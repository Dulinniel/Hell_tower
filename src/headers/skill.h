#ifndef SKILL_H
#define SKILL_H

#include <stdint.h>
#include "./rarity.h"

enum SkillType 
{
  SPELL = 1 << 0,
  TECHNIQUE = 1 << 1,
  PSYCHIC = 1 << 2,
  FIRE = 1 << 3,
  ICE = 1 << 4,
  AIR = 1 << 5,
  WATER = 1 << 6,
  EARTH = 1 << 7,
  THUNDER = 1 << 8,
  ACID = 1 << 9,
  ETHER = 1 << 10,
  LIGHT = 1 << 11,
  SHADOW = 1 << 12,
  MANA = 1 << 13,
  BLOOD = 1 << 14,
  VOID = 1 << 15,
  HOLY = 1 << 16,
  NECROTIC = 1 << 17,
  DEMONIC = 1 << 18,
  CURSE = 1 << 19,
  POISON = 1 << 20,
  BURN = 1 << 21,
  STRIKE = 1 << 22,
  SLASH = 1 << 23,
  BLUDGE = 1 << 24,
  PIERCE = 1 << 25
};

enum DamageType 
{
  BURN = 1 << 0,
  POISON = 1 << 1,
  BLEED = 1 << 2,
  WITHER = 1 << 3,
  CORRUPTION = 1 << 4,
  DRAIN = 1 << 5,
  STUN = 1 << 6,
  PARALYSIS = 1 << 7
};

struct FixedDamage 
{
  uint8_t damage_type;
  size_t damage_value;
};

struct LastingDamage 
{
  uint8_t damage_type;
  size_t damage_value;
  uint8_t duration;
  uint8_t chance;
};

struct Skill 
{
  unsigned int id;
  const char* name;
  const char* description;
  enum Rarity rank;
  uint8_t min_level;
  uint8_t max_level;
  size_t skill_types;
  uint8_t cooldown;
  uint8_t load_turn;
  uint8_t mana_cost;
  uint8_t num_fixed_damages;
  uint8_t num_lasting_damages;
  struct FixedDamage fixed_damages[4];
  struct LastingDamage lasting_damages[4];
};

#endif