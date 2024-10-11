typedef Item *PItem;

enum InventoryStatus
{
  ITEM_SUCCESSFULLY_ADDED = 0,
  ITEM_CONSUMED = 1,
  ITEM_CREATED = 2,
  ITEM_FOUND = 3,
  UPDATE_COMPLETE = 4,
  REMOVE_COMPLETE = 5,

  INVENTORY_MAX_CAP_REACHED = 100,
  ITEM_FAILED_TO_ADD = 101,
  ITEM_FAILED_TO_CONSUME = 102,
  MEMORY_ALLOCATION_ERROR = 103,
  UNKNOWN_ITEM = 104,
  EMPTY_LIST = 105,
  UPDATE_FAILED = 106
};

struct InventoryOutputPackage 
{
  struct Item item;
  enum InventoryStatus status;
};

struct Item
{
  char name[100];
  int amount;
  PItem next;
  PItem previous;
};

struct Inventory
{
  PItem cursor;
  PItem start;
  PItem end;
  size_t size;
}

struct InventoryOutputPackage CreateTempItem(struct Inventory *list, struct Item element)
struct InventoryOutputPackage AddFirst(struct Inventory *list, struct Item element);
struct InventoryOutputPackage AddLast(struct Inventory *list, struct Item element);

struct InventoryOutputPackage ConsumeItem(struct Inventory *list, const char* name, int amount);

struct InventoryOutputPackage RemoveFromInventory(struct Inventory *list, struct Item element);
struct InventoryOutputPackage UpdateInventory(struct Inventory *list, struct Item element);

struct InventoryOutputPackage GetItem(struct Inventory *list, const char* name);