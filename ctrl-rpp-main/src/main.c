#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "rpp.h"

int main(int argc, char *argv[]) {
    //? Executable expects window width and height
    if (argc != 3) {
        printf("Please provide the executable with two numbers, seperated by a space, to be the window width and height.\n");
        return EXIT_FAILURE;
    }

    //? Parse dimensions
    int width = (int)strtol(argv[1], NULL, 0);
    int height = (int)strtol(argv[2], NULL, 0);

    //? Call GUI manager entry point
    // Providing negative numbers for any dimension will set it to default values
    //      Default dimensions: 800px wide by 600px tall
    //      Default position: (monitor height - 600) / 2 [x pos]
    //                        (monitor width - 800) / 2 [y pos]
    int EXIT_CODE = 0;
    EXIT_CODE = GUI_MGR(width, height, -1, -1, "rpp test run");

    //? Print last system message with exit code
    RPP_CALLBACK(EXIT_CODE);

    //? Exit gracefully with a little bow
    if (EXIT_CODE != 0) {
        return EXIT_FAILURE;
    }
    else {
        return EXIT_SUCCESS;
    }
}