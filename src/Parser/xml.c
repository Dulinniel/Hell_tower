#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/xml.h"

char* TrimWhitespace(char* str) {
  while (isspace((unsigned char)*str)) str++;
  if (*str == 0) return str;

  char* end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;
  end[1] = '\0';

  return str;
}

struct XMLNode* ParseXMLFile(const char* filename) 
{
  FILE* file = fopen(filename, "r");
  if (!file) 
  {
    printf("Erreur lors de l'ouverture du fichier.\n");
    return NULL;
  }

  char line[256];
  struct XMLNode* root = NULL;
  struct XMLNode* current_node = NULL;

  while (fgets(line, sizeof(line), file)) 
  {
    char* trimmed_line = TrimWhitespace(line);
      
    // Detect opening tag
    if (trimmed_line[0] == '<' && trimmed_line[1] != '/') 
    {
      char* tag_name = strtok(trimmed_line + 1, ">");
            
      // Create new node
      struct XMLNode* new_node = CreateXMLNode(tag_name, NULL);

      // Create root node
      if (!root) root = new_node;
      else AddChildNode(current_node, new_node);

      current_node = new_node;
    } else if (trimmed_line[0] == '<' && trimmed_line[1] == '/') current_node = root;  // Pour un parser simple, on remonte au parent directement
    else if (current_node) current_node->value = strdup(trimmed_line);
  }

  fclose(file);
  return root;
}

struct XMLNode* CreateXMLNode(const char* tag_name, const char* value) {
  struct XMLNode* node = (struct XMLNode*)malloc(sizeof(struct XMLNode));
  node->tag_name = strdup(tag_name);
  node->value = value ? strdup(value) : NULL;
  node->next_sibling = NULL;
  node->first_child = NULL;
  node->attributes = NULL;
  return node;
}

void AddChildNode(struct XMLNode* parent, struct XMLNode* child) 
{
  if (parent->first_child) 
  {
    struct XMLNode* sibling = parent->first_child;
    while (sibling->next_sibling) sibling = sibling->next_sibling;    
    sibling->next_sibling = child;
  } else parent->first_child = child;
}