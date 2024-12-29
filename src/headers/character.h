enum Race
{
  DWARF,
  HUMAN,
  ELF,
  ORC,
  HALFLING,
  BEASTMAN,
  REPTILIAN
};

enum Gender
{
  MAN,
  WOMAN
};

enum Jobs
{
  BLACKSMITH,
  BARTENDER,
  ENCHANTER,
  HEALER,
  WAR_MAGE,
  SLAVE,
  GLADIATOR,
  PROFESSOR,
  SOLDIER,
  CLERIC,
  FLETCHER,
  HUNTER,
  EXPLORATOR,
  MINER,
  ALCHEMIST,
  COOK,
  FISHER,
  FARMER,
  MERCHANT,
  ENGINEER,
  ASSASSIN
};

enum Class
{
  MAGE,
  WARRIOR,
  TANK,
  ROGUE,
  ARCHER,
  SPEARMAN,
  SWORDSMAN,
  MAN_AT_ARM,
  PRIEST
};

struct Identity
{
  const char* name;
  enum Race race;
  enum Gender gender;
  unsigned char age;
  unsigned char weight;
  unsigned char height;
};

struct Specialities
{
  enum Class class;
  enum Jobs job;
};

struct Energy
{
  size_t life;
  size_t mana;
  size_t stamina;
};

struct Needs
{
  size_t hunger;
  size_t thirst;
  size_t breath;
  float heat;
};

struct Craft
{
  size_t smithing;
  size_t potting;
  size_t cooking;
  size_t brewing;
  size_t sewing;
};

struct Other
{
  size_t luck;
  size_t charisma;
  size_t style;
  size_t intelligence;
  size_t agility;
  float reputation;
};

struct Elemental_Resistance
{
  size_t fire_resistance;
  size_t water_resistance;
  size_t earth_resistance;
  size_t air_resistance; // Ignore this one ( Yes, I find myself funny )
  size_t ice_resistance;
  size_t thunder_resistance;
  size_t acid_resistance;
  size_t ether_resistance;
};

struct Magical_Resistance
{
  struct Elemental_Resistance elemental_resistance;
  size_t light_resistance;
  size_t shadow_resistance;
  size_t mana_resistance;
  size_t blood_resistance;
  size_t void_resistance;
  size_t holy_resistance;
  size_t necrotic_resistance;
  size_t demonic_resistance;
  size_t curse_resistance;
};

struct Elemental_Strength
{
  size_t fire_strength;
  size_t water_strength;
  size_t earth_strength;
  size_t air_strength;
  size_t ice_strength;
  size_t thunder_strength;
  size_t acid_strength;
  size_t ether_strength;
};

struct Magical_Strength
{
  struct Elemental_Strength elemental_strength;
  size_t light_strength;
  size_t shadow_strength;
  size_t mana_strength;
  size_t blood_strength;
  size_t void_strength;
  size_t holy_strength;
  size_t necrotic_strength;
  size_t demonic_strength;
};

struct Physical_Resistance
{
  size_t poisoning_resistance;
  size_t burning_resistance;
  size_t striking_resistance;
  size_t piercing_resistance;
  size_t slashing_resistance;
  size_t bludgeoning_resistance;
  size_t fall_resistance;
};

struct Physical_Strength
{
  size_t poisoning_Strength;
  size_t striking_Strength;
  size_t piercing_Strength;
  size_t slashing_Strength;
  size_t bludgeoning_Strength;
};

struct Psychical_Resistance
{
  float fear_resistance;
  float possession_resistance;
  float confusion_resistance;
  float taunt_resistance; // 0 for any competitive LoL player
};

struct Psychical_Strength
{
  size_t fear_strength;
  size_t possession_strength;
  size_t confusion_strength;
  size_t taunt_strength;
};

struct Resistance
{
  struct Magical_Resistance magical_resistance;
  struct Physical_Resistance physical_resistance;
  struct Psychical_Resistance psychical_Resistance;
};

struct Critical_Damages
{
  size_t critical_rate;
  float critical_damage;
};

struct Strength
{
  struct Magical_Strength magical_strength;
  struct Physical_Strength physical_strength;
  struct Psychical_Strength psychical_strength;
  struct Critical_Damages critical;
};

struct Character
{
  struct Identity identity;
  struct Specialities specialities;
  struct Energy energy;
  struct Needs needs;
  struct Strength strength;
  struct Resistance resistance;
  struct Craft craft;
  struct Other other;
};

//struct Character CreateCharacter(struct Character character);
//void DisplayCharacterInfo(struct Character *character);
void UpdateStat(size_t *stat, int delta);

//void Attack(struct Character *attacker, struct Character *defender);
void UpdateNeeds(struct Character *character, size_t timePassed);
void UpdateOxygen(struct Character *character, size_t timePassed);

const char* GetRaceName(enum Race race);
const char* GetGenderName(enum Gender gender);
const char* GetJobsName(enum Jobs job);
const char* GetClassName(enum Class class);