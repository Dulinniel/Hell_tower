#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headers/inventory.h";

#define IS_SUCCESS(status) ((status) < 100)
#define IS_ERROR(status) ((status) >= 100)

// Basic Capacity of the inventory 
const int MAX_INVENTORY_SIZE = 5;

/*
* @name: CreateTempItem
* @description: Create the basic information about the Item to add, to avoid repetition in addFirst and addLast Function
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: Status code ITEM_CREATED + Pointer to an item
* * * Fail: 
* * * * * 1. Inventory full -> Status code INVENTORY_MAX_CAP_REACHED + Empty item
* * * * * 2. Error during memory allocation -> Status code INVENTORY_MAX_CAP_REACHED + Empty item
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * element -> Item structure ( struct Item )
*/
struct InventoryOutputPackage CreateTempItem(struct Inventory *list, struct Item element)
{
  struct InventoryOutputPackage result;
  result.status = ITEM_CREATED;
  result.item = (struct Item){0};
  
  int InventorySize = InventoryCurrentSize(list);

  if ( InventorySize != MAX_INVENTORY_SIZE ) 
  {
    PItem tempItem = (PItem)malloc(sizeof(struct Item));
  
    if ( tempItem != NULL )
    {
      strcpy(tempItem->name, element.name);
      tempItem->amount = element.amount;

      tempItem->next = list->start;
      tempItem->previous = NULL;

      result.item = tempItem;
    } else result.status = MEMORY_ALLOCATION_ERROR; 
  } else result.status = MAX_INVENTORY_SIZE;

  return result;
}

/*
* @name: AddFirst
* @description: Add an item to the beginning of the Double-linked list
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: Status code ITEM_SUCCESSFULLY_ADDED + Item structure 
* * * Fail: Error from CreateTempItem function
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * element -> Item structure ( struct Item )
*/
struct InventoryOutputPackage AddFirst(struct Inventory *list, struct Item element)
{
  struct InventoryOutputPackage newItem = CreateTempItem(list, element);

  if ( IS_ERROR(newItem.status) ) return newItem; 

  if (list->start == NULL) list->end = newItem.item;
  else list->start->previous = newItem.item;
  
  list->start = newItem.item;
  list->size += 1;

  newItem.status = ITEM_SUCCESSFULLY_ADDED;

  return newItem;
}

/*
* @name: AddLast
* @description: Push an item to the end of the Double-linked list
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: Status code ITEM_SUCCESSFULLY_ADDED + Item structure
* * * Fail: Error from CreateTempItem function
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * element -> Item structure ( struct Item )
*/
struct InventoryOutputPackage AddLast(struct Inventory *list, struct Item element)
{
  struct InventoryOutputPackage newItem = CreateTempItem(list, element);

  if ( IS_ERROR(newItem.status) ) return newItem;

  newItem.item->next = NULL;
  newItem.item->previous = list->end;
  
  if (list->end == NULL) list->start = newItem.item;
  else list->end->next = newItem.item;
  
  list->end = newItem.item;
  list->size += 1;

  newItem.status = ITEM_SUCCESSFULLY_ADDED;

  return newItem;

}

/*
* @name: ConsumeItem
* @description: Substract the amount of item consumed or remove it from the double-linked list
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: The status code ITEM_SUCCESSFULLY_CONSUMED + empty item structure
* * * Fail: 
* * * * * 1. Item not found in the inventory -> Status code UNKNOWN_ITEM + empty item structure
* * * * * 2. Number of item to consume greather than the actual amount of items in the inventory -> Status code ITEM_FAILED_TO_CONSUME + empty item structure
* * * * * 3. The list is empty -> Status code EMPTY_LIST + empty item structure
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * name -> The name of the item to consume ( cont char* )
* * * amount -> Number of item to consume ( int )
*/
struct InventoryOutputPackage ConsumeItem(struct Inventory *list, const char* name, int amount)
{
  struct GetItemResult Item = GetItem(list, name);
  struct InventoryOutputPackage result;
  result.status = ITEM_SUCCESSFULLY_CONSUMED;
  result.item = (struct Item){0};

  if ( list->size == 0 ) result.status = EMPTY_LIST;
  if ( Item.status == UNKNOWN_ITEM ) result.status = UNKNOWN_ITEM;

  if ( amount > Item.item.amount ) result.status = ITEM_FAILED_TO_CONSUME;

  Item.item.amount -= amount;

  if ( Item.item.amount == 0 ) RemoveFromInventory(list, name);
  else UpdateInventory(list, &result.item);

  return result;

}

/*
* @name: UpdateInventory
* @description: Actually Update the double-linked list content with a new value
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: The status code UPDATE_COMPLETE + empty item structure 
* * * Fail: 
* * * * * 1. List is empty -> Status code EMPTY_LIST + empty item structure 
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * name -> The name of the item to consume ( cont char* )
*/
struct InventoryOutputPackage UpdateInventory(struct Inventory *list, struct Item *item) 
{
  struct InventoryOutputPackage result;
  result.status = UPDATE_FAILED;
  result.item = (struct Item){0};
  
  if ( list->size == 0 ) result.status = EMPTY_LIST;

  PItem current = list->start;

  while (current != NULL && result.status != UPDATE_COMPLETE) 
  {
    if (strcmp(current->name, item->name) == 0) 
    {
      current->amount = item->amount;
      result.status = UPDATE_COMPLETE;
      result.item = current;
    }
    current = current->next;
  }

  return result;

}

/*
* @name: RemoveFromInventory
* @description: Remove an element from the double-linked list
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: The status code UPDATE_COMPLETE + empty structure item
* * * Fail: 
* * * * * 1. List is empty -> Status code EMPTY_LIST + empty structure item
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * Item -> An item structure ( struct Item )
*/
struct InventoryOutputPackage RemoveFromInventory(struct Inventory *list, struct Item element);
{
  struct InventoryOutputPackage result;
  result.status = UPDATE_FAILED;
  result.item = (struct Item){0};
  if ( list->size == 0 ) result.status = EMPTY_LIST;

  PItem current = list->start;

  while (current != NULL && result.status != REMOVE_COMPLETE) 
  {
    if (strcmp(current->name, name) == 0) 
    {
      if (current == list->start) 
      {
        list->start = current->next;
        if (list->start != NULL) list->start->previous = NULL;
      }
      else if (current == list->end) 
      {
        list->end = current->previous;
        if (list->end != NULL) list->end->next = NULL;
      }
      else 
      {
        current->previous->next = current->next;
        if (current->next != NULL) current->next->previous = current->previous;            
      }

      free(current);
      result.status = REMOVE_COMPLETE;
    }
    current = current->next;
  }

  list->size -= 1;

  return result;

}

/*
* @name: GetItem
* @description: Get an item in the double-linked list
* @return:
* * * type: struct InventoryOutputPackage
* * * Success: The status code ITEM_FOUND + Found item structure
* * * Fail: 
* * * * * 1. List is empty -> Status code EMPTY_LIST + Empty Item struct
* * * * * 1. Item not found -> Status code UNKNOW_ITEM + Empty Item struct
* @params:
* * * list -> Pointer to the double-linked list ( struct Inventory )
* * * name -> The name of the item to look for ( const char* )
*/
struct InventoryOutputPackage GetItem(struct Inventory *list, const char* name)
{
  struct InventoryOutputPackage result;
  PItem current = list->start;

  result.status = UNKNOWN_ITEM;
  result.item = (struct Item){0};

  if ( list->size == 0 ) result.status = EMPTY_LIST;
  
  while (current != NULL) 
  {
    if (strcmp(current->name, name) == 0) 
    {
      result.item = *current;
      result.status = ITEM_FOUND;
    }
    current = current->next;
  }

  return result;
}