typedef struct g {
    void* game;
    void (*updateEnviroment) (void* game);
    void* (*getEnv) (void* game);
    void* (*pause) (void* game);
} game;

extern game mainGame;