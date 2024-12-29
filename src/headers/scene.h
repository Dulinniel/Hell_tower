#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <stddef.h>

typedef struct Entity
{
  SDL_Texture *texture;
  SDL_Renderer *renderer;
  SDL_Rect rect;
  void (*on_event)(struct Entity *self, SDL_Event *event);
  void (*update)(struct Entity *self, float delta_time);
} Entity;

typedef struct Scene
{
  Entity **entities;
  size_t entity_count;
} Scene;


Entity* create_entity(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect, void (*on_event)(Entity*, SDL_Event*), void (*update)(Entity*, float));

void add_entity(struct Scene *scene, struct Entity *entity);
void handle_events(struct Scene *scene, SDL_Event *event);
void update_scene(struct Scene *scene, float delta_time);
void render_scene(struct Scene *scene, SDL_Renderer *renderer);

#endif