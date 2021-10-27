typedef struct dialogue {
    int entity_id;
    char *dialogue_entry;
    char *dialogue_option;
}dialogue;

typedef struct map {
    int entity_id;
    SDL_Surface *display_map;
    SDL_Surface *collision_map;
    SDL_Surface *draw_map;
}map;

typedef struct position {
    int entity_id;
    SDL_Rect sprite_position;
}position;

typedef struct sprite {
    int entity_id;
    SDL_Surface *sprite_surface;
}sprite;

typedef struct statistic {
    int entity_id;
    int command;
    int tactical;
    int operations;
}statistic;

