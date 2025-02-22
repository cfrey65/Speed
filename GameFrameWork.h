typedef struct gaming {
    void* game;
    size_t envSize = 1;
    void (*updateEnviroment) (void* game, char c);
    void* (*getEnv) (void* game);
    void* (*pause) (void* game);
    void (*deleteEnv) (void* env);
    char* interrupts;
    int numInt;
} g;

global g* mainGame;