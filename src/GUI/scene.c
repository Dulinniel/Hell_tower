#include <stdlib.h>
#include "../headers/scene.h"

/*
* @name: create_entity
* @description: Create a new Entity Object
* @return:
* * * type: struct Entity
* * * Success: Pointer to an Entity Object
* * * Fail: 
* * * * * 1. Error during memory allocation -> NULL
* @params:
* * * texture -> Pointer to the texture of the entity ( SDL_Texture )
* * * renderer -> Pointer to the original renderer of the entity ( SDL_Renderer )
* * * rect -> A rectangle to draw on the screen ( SDL_Rect )
* * * (*on_event)(Entity*, SDL_Event*) -> A generic function that is triggered to some event hooks ( void )
* * * (*update)(Entity*, float) -> A generic function to update what's on the screen ( void )
*/
Entity* create_entity(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect, void (*on_event)(Entity*, SDL_Event*), void (*update)(Entity*, float)) 
{
  Entity *entity = malloc(sizeof(Entity));
  entity->texture = texture;
  entity->renderer = renderer;
  entity->rect = rect;
  entity->on_event = on_event;
  entity->update = update;
  return entity;
}

/*
* @name: add_entity
* @description: Add an Entity Object into a scene
* @return:
* * * type: void
* * * Success: Add the entity in the scene object
* * * Fail: 
* * * * * 1. Error during memory allocation -> NULL
* @params:
* * * scene -> Pointer to the Scene you want to add the entity ( struct Scene )
* * * entity -> The Entity object you want to add ( struct Entity )
*/
void add_entity(struct Scene *scene, struct Entity *entity) 
{
  scene->entities = realloc(scene->entities, sizeof(Entity*) * (scene->entity_count + 1));
  scene->entities[scene->entity_count++] = entity;
}

/*
* @name: handle_events
* @description: Call the on_event function of each entities in a scene
* @return:
* * * type: void
* * * Success: on_event function is successfully called and the even triggered
* * * Fail: 
* * * * * 1. The event does not exists -> Type Error
* * * * * 2. The Scene is NULL -> SegFault
* * * * * 3. There is an error in the entity function implementation -> Unknown
* @params:
* * * scene -> Pointer to the Scene you want to add the entity ( struct Scene )
* * * event -> The Event to triggered ( SDL_Event )
*/
void handle_events(struct Scene *scene, SDL_Event *event) 
{
  for (size_t i = 0; i < scene->entity_count; ++i) 
  {
    if (scene->entities[i]->on_event) scene->entities[i]->on_event(scene->entities[i], event);
  }
}

/*
* @name: update_scene
* @description: Call the update function of each entities in a scene
* @return:
* * * type: void
* * * Success: update function is successfully called and the Entity is updated
* * * Fail: 
* * * * * 1. The Scene is NULL -> SegFault
* * * * * 2. There is an error in the update function implementation -> Unknown
* @params:
* * * scene -> Pointer to the Scene you want to update the entity ( struct Scene )
* * * delta_time -> Time difference from the start ( float )
*/
void update_scene(struct Scene *scene, float delta_time) 
{
  for (size_t i = 0; i < scene->entity_count; ++i) 
  {
    if (scene->entities[i]->update) scene->entities[i]->update(scene->entities[i], delta_time);
  }
}

/*
* @name: render_scene
* @description: Render the scene on the screen
* @return:
* * * type: void
* * * Success: Something appear on the screen
* * * Fail: 
* * * * * 1. The Scene is NULL -> SegFault
* * * * * 2. The Entity is NULL -> SegFault
* @params:
* * * scene -> Pointer to the Scene you want to render the entities ( struct Scene )
* * * renderer -> The Event to triggered ( SDL_Renderer )
*/
void render_scene(struct Scene *scene, SDL_Renderer *renderer) 
{
  for (size_t i = 0; i < scene->entity_count; ++i) 
  {
    SDL_RenderCopy(renderer, scene->entities[i]->texture, NULL, &scene->entities[i]->rect);
  }
}
