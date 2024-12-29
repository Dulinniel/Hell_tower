#include "../headers/inventory.h"
#include <stdlib.h>

#define KEYBOARD_LETTER_i 105

// Gestion de l'affichage de l'inventaire
void inventory_event_handler(Entity *self, SDL_Event *event) 
{
  static int inventory_visible = 0;
  if (event->type == SDL_KEYUP && event->key.keysym.sym == KEYBOARD_LETTER_i) 
  {
    inventory_visible = !inventory_visible;
    if ( !inventory_visible ) 
    {
      printf("Je suis ici\n");
      SDL_SetRenderDrawColor(self->renderer, 0, 0, 0, 0);
      SDL_RenderClear(self->renderer);
      return;
    }

    for ( size_t i = 0; i < 5; ++i )
    { 
      SDL_SetRenderTarget(self->renderer, self->texture);
      SDL_SetRenderDrawColor(self->renderer, 255, 0, 0, 255);
      SDL_RenderClear(self->renderer);
      SDL_SetRenderTarget(self->renderer, NULL);
    }
  }
}

// Création des entités de l'inventaire
void create_inventory(Scene *scene, SDL_Renderer *renderer) 
{
  for ( size_t i = 0; i < 5; ++i ) 
  {
    SDL_Rect square = {100 + i * 60, 100, 50, 50};
    SDL_Texture *red_square = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
    Entity *slot = create_entity(red_square, renderer, square, inventory_event_handler, NULL);
    add_entity(scene, slot);
  }
}