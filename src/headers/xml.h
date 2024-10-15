struct XMLNode {
  char* tag_name; // Tag name
  char* value;    // Node value

  struct XMLNode* next_sibling;  // Pointer to the next Node
  struct XMLNode* first_child;   // Pointer to the first Node

  // Here but not supported yet
  struct XMLAttribute* attributes;
};

struct XMLAttribute {
  char* name;   // Attribute name
  char* value; // Attribute value

  struct XMLAttribute* next; // Next attribute
};

char* TrimWhitespace(char* str);
struct XMLNode* ParseXMLFile(const char* filename);
struct XMLNode* CreateXMLNode(const char* tag_name, const char* value);
void AddChildNode(struct XMLNode* parent, struct XMLNode* child)