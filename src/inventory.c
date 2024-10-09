#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./headers/inventory.h";

const int MAX_INVENTORY_SIZE = 5;

PItem createTempItem(struct Inventory *list, struct Item element)
{
  int InventorySize = InventoryCurrentSize(list);

  if ( InventorySize == MAX_INVENTORY_SIZE ) return INVENTORY_MAX_CAP_REACHED;

  PItem tempItem = (PItem)malloc(sizeof(struct Item));
  
  if ( tempItem == NULL ) return MEMORY_ALLOCATION_ERROR;
  
  strcpy(tempItem->name, element.name);
  tempItem->amount = element.amount;

  tempItem->next = list->start;
  tempItem->previous = NULL;

  return tempItem;
}

enum InventoryStatus addFirst(struct Inventory *list, struct Item element)
{
  PItem newItem = createTempItem(list, element);
  
  if (list->start == NULL) list->pFin = newItem;
  else list->start->previous = newItem;
  
  list->start = newItem;
  return ITEM_SUCCESSFULLY_ADDED;
}

enum InventoryStatus addLast(struct Inventory *list, struct Item element)
{
  PItem newItem = createTempItem(list, element);  

  newItem->next = NULL;
  newItem->previous = list->end;
  
  if (list->end == NULL) list->start = newItem;
  else list->end->next = newItem;
  
  list->end = newItem;
  return ITEM_SUCCESSFULLY_ADDED;

}

int InventoryCurrentSize(struct Inventory *list) 
{
  int count = 0;
  PItem current = list->start;

  while (current != NULL) 
  {
    count++;
    current = current->next;
  }

  return count;
}

enum InventoryStatus ConsumeItem(struct Inventory *list, const char* name, int amount);
{
  struct GetItemResult Item = GetItem(list, name);
  if ( Item.status == UNKNOWN_ITEM ) return UNKNOWN_ITEM;

  if ( amount > Item.item.amount ) return ITEM_FAILED_TO_CONSUME;

  Item.item.amount -= amount;

  if ( Item.item.amount == 0 ) RemoveFromInventory(list, name);
  else UpdateInventory(list, &result.item);

  return ITEM_SUCCESSFULLY_CONSUMED

}

enum InventoryStatus UpdateInventory(struct Inventory *list, struct Item *item) 
{
  PItem current = list->start;

  while (current != NULL) 
  {
    if (strcmp(current->name, item->name) == 0) 
    {
      current->amount = item->amount;
      return UPDATE_COMPLETE;
    }
    current = current->next;
  }
}

void RemoveFromInventory(struct Inventory *list, struct Item element);
{
  PItem current = list->start;

  while (current != NULL) 
  {
    if (strcmp(current->name, name) == 0) 
    {
      // Si l'item à supprimer est au début
      if (current == list->start) 
      {
        list->start = current->next;
        if (list->start != NULL) list->start->previous = NULL;
      }
      // Si l'item à supprimer est à la fin
      else if (current == list->end) 
      {
        list->end = current->previous;
        if (list->end != NULL) list->end->next = NULL;
      }
      // Si l'item est au milieu
      else 
      {
        current->previous->next = current->next;
        if (current->next != NULL) current->next->previous = current->previous;            
      }

      free(current); // Libérer la mémoire de l'item
      return; // Sortir après avoir supprimé l'item
    }
    current = current->next;
  }
}

struct GetItemResult GetItem(struct Inventory *list, const char* name)
{
  struct GetItemResult result;
  PItem current = list->start;

  result.status = UNKNOWN_ITEM;
  result.item = (struct Item){0};

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