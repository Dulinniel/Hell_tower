typedef Item *PItem;

enum InventoryStatus
{
  INVENTORY_MAX_CAP_REACHED,
  ITEM_SUCCESSFULLY_ADDED,
  ITEM_FAILED_TO_ADD,
  ITEM_CONSUMED,
  ITEM_FAILED_TO_CONSUME,
  MEMORY_ALLOCATION_ERROR,
  UNKNOWN_ITEM,
  ITEM_FOUND,
  EMPTY_LIST,
  UPDATE_COMPLETE
};

struct GetItemResult 
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
}

PItem createTempItem(struct Inventory *list, struct Item element)
enum InventoryStatus addFirst(struct Inventory *list, struct Item element);
enum InventoryStatus addLast(struct Inventory *list, struct Item element);

int InventoryCurrentSize(struct Inventory *list);
enum InventoryStatus ConsumeItem(struct Inventory *list, const char* name, int amount);

void RemoveFromInventory(struct Inventory *list, struct Item element);
enum InventoryStatus UpdateInventory(struct Inventory *list, struct Item element);

enum InventoryStatus DisplayOrder(struct Inventory *list);
struct GetItemResult GetItem(struct Inventory *list, const char* name);