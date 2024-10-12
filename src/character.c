#include <stdio>
#include "./headers/character.h"

const unsigned float BASE_HUNGER_FACTOR_AUGMENTATION = 0.1;
const unsigned float BASE_THIRST_FACTOR_AUGMENTATION = 0.2;
const unsigned float BASE_OXYGEN_NEEDS_FACTOR_AUGMENTATION = 1.5;

void UpdateStat(size_t *stat, int delta) 
{
  if (*stat + delta < 0) *stat = 0;
  else *stat += delta;
}

void UpdateNeeds(struct Character *character, size_t timePassed) 
{
  character->needs.hunger += timePassed * BASE_HUNGER_FACTOR_AUGMENTATION;
  character->needs.thirst += timePassed * BASE_THIRST_FACTOR_AUGMENTATION;
}

void UpdateOxygen(struct Character *character, size_t timePassed)
{
  character->needs.breath -= timePassed * BASE_OXYGEN_NEEDS_FACTOR_AUGMENTATION; 
}

const char* GetRaceName(enum Race race)
{
  switch (race)
  {
  case DWARF: return "Dwarf";
  case HUMAN: return "Human";
  case ELF: return "Elf";
  case ORC: return "Orc";
  case HALFLING: return "Halfling";
  case BEASTMAN: return "Beastman";
  case REPTILIAN: return "REPTILIAN";
  default: return "unknown";
  }
}

const char* GetGenderName(enum Gender gender)
{
  switch (gender)
  {
  case MAN: return "Man";
  case WOMAN: return "Woman";
  default: return "Unknown"; // Oh fuck, this line will get me in a lot of trouble
  }
}

const char* GetJobsName(enum Jobs job)
{
  switch (job)
  {
  case BLACKSMITH: return "Blacksmith";
  case BARTENDER: return "Bartender";
  case ENCHANTER: return "Enchanter";
  case HEALER: return "Healer";
  case WAR_MAGE: return "War Mage";
  case SLAVE: return "Slave";
  case GLADIATOR: return "Gladiator";
  case PROFESSOR: return "Professor";
  case SOLDIER: return "Soldier";
  case CLERIC: return "Cleric";
  case FLETCHER: return "Fletcher";
  case HUNTER: return "Hunter";
  case EXPLORATOR: return "Explorator";
  case MINER: return "Miner";
  case ALCHEMIST: return "Alchemist";
  case COOK: return "Cook";
  case FISHER: return "Fisher";
  case FARMER: return "Farmer";
  case MERCHANT: return "Merchant";
  case ENGINEER: return "Engineer";
  case ASSASSIN: return "Assassin";
  default: return "Unknown";
  }
}

const char* GetClassName(enum Class class)
{
  switch (job)
  {
  case MAGE: return "Mage";
  case WARRIOR: return "Warrior";
  case TANK: return "Tank";
  case ROGUE: return "Rogue";
  case ARCHER: return "Archer";
  case SPEARMAN: return "Spearman";
  case SWORDSMAN: return "Swordsman";
  case MAN_AT_ARM: return "Man at Arm";
  case PRIEST: return "Priest";
  default: return "Unknown";
  }
}