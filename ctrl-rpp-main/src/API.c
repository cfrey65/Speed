#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rpp.h"

//! Other Global Vars

// Returns 0 if successful (at window close)
// Returns 1 if GUI init error
// Returns an int > 1 if other error
int GUI_MGR(int w, int h, int x, int y, const char *title) {
    int MAIN_LOOP_STATUS = 0;
    int GUI_INIT_STATUS = 0;

    //? ////////////////////////////
    //?  Raylib GUI Initialization
    //? ////////////////////////////
    GUI_INIT_STATUS = GUI_Init(false, KEY_ESCAPE, (Vector2){w, h}, (Vector2){x, y}, title);
    if (GUI_INIT_STATUS != EXIT_SUCCESS) {
        strcpy(PRG_MSG, "(In GUI_Init) - An error occurred while initializing the window, or internal GUI values. ");
        return GUI_INIT_STATUS;
    }

    //? Run the GUI main loop to start the program
    MAIN_LOOP_STATUS = GUI_Main();
    if (MAIN_LOOP_STATUS != EXIT_SUCCESS) {
        // Internal process is responsible for setting the error text and return code
        return MAIN_LOOP_STATUS;
    }

    //? //////////////////////////////
    //?  Raylib GUI De-Initialization
    //? //////////////////////////////
    GUI_DeInit();

    //? Set exit message
    strcpy(PRG_MSG, "App exited with sensational class. ");

    //? Exit willfully, with no convictions
    return EXIT_SUCCESS;
}

void CustomLog(int msgType, const char *text, va_list args) {
    // Does nothing, just takes startup output from raylib so there is no console spam
}

// Prints last logged program error
void RPP_CALLBACK(int msgType) {
    //? Message preface 
    switch (msgType) {
        case 0: printf("*** SUCCESS: "); break;
        case 1: printf("*** ERROR IN GUI MANAGER: "); break;
        case 2: printf("*** ERROR IN PROGRAM: "); break;
        default: printf("*** PROGRAM MESSAGE: "); break;
    }

    //? Idk what this does i forgor :OOOOo
    //printf(PRG_MSG);

    //? Message postface (?)
    switch (msgType) {
        case 0:
        case 1: 
        case 2: printf("***\n*** Exiting program... ***\n"); break;
        default: printf("***\n*** You may continue :) don't break anything >:( ***\n"); break;
    }
}
