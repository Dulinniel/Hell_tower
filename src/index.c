#include <SDL2/SDL.h>
#include <stdio.h>
#include "./headers/scene.h"
#include "./headers/inventory.h"

#define SCREEN_WIDTH  2000
#define SCREEN_HEIGHT 1500

int main(int argc, char const *argv[])
{
  SDL_Window* window = NULL;
  // SDL_Surface* screen_surface = NULL;
  Scene scene = { .entities = NULL, .entity_count = 0 };
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
  {
    printf("SDL Could not initialize because: %s\n", SDL_GetError());
    return -1;
  }

  window = SDL_CreateWindow("Test shit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  create_inventory(&scene, renderer);
  // screen_surface = SDL_GetWindowSurface(window);
  // SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
  // SDL_UpdateWindowSurface(window);
  SDL_Event event;
  unsigned char quit = 0;
  unsigned int last_time = SDL_GetTicks();
  while ( quit == 0 )
  {
    unsigned int current_time = SDL_GetTicks();
    float delta_time = (current_time - last_time) / 1000.0f;
    last_time = current_time;
    while ( SDL_PollEvent(&event) ) 
    {
      if ( event.type == SDL_QUIT ) quit = 1;
      else handle_events(&scene, &event);
    }

    update_scene(&scene, delta_time);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_scene(&scene, renderer);
    SDL_RenderPresent(renderer);
  }

  for (size_t i = 0; i < scene.entity_count; ++i) \
  {
    SDL_DestroyTexture(scene.entities[i]->texture);
    free(scene.entities[i]);
  }

  free(scene.entities);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow( window );
  SDL_Quit();

  return 0;
}