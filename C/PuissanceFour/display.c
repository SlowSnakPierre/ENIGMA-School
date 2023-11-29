#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "init.h"

#define MAX_INPUT_LENGTH 255


char *utf8_scanf(size_t length)
{
#ifdef P4_WINDOWS_CONSOLE
    wchar_t wstr[MAX_INPUT_LENGTH];
    char *res = (char*)(malloc(length * sizeof (char)));

    unsigned long read;
    void *con = GetStdHandle(STD_INPUT_HANDLE);

    ReadConsole(con, wstr, length, &read, NULL);

    int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, res, sizeof (res), NULL, NULL);
    res[size] = 0;

    return res;

#else
    char *res = (char*)(malloc(length * sizeof (char)));
    scanf("%s", res);

    return res;
#endif
}



static void errorArgs(const char* arg) {
    P4_CLEAR_CONSOLE;

    if (arg == NULL)
        printf("Error: Parameters are invalids.\n");
    else
        printf("Error: The Parameter \"%s\" is invalid.\n", arg);

    printf("Parameters are:\n");
    printf("\tln:<value>\n");
    printf("\tcl:<value>\n");
    printf("\nExemple: \"Puissance4.exe -ln:10 -cl:12\"\n");
    printf("\t->make a grid of 10 lines et de 12 columns.\n");
    P4_SLEEP(5000);
    exit(1);
}

static void errorRange(bool line) {
    P4_CLEAR_CONSOLE;

    printf("Error: The number of ");

    if (line) printf("lines");
    else      printf("columns");

    printf(" must be between 4 et 20.\n");
    P4_SLEEP(5000);
    exit(1);
}

static bool compareString(const char* s1, const char* s2, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (s1[i] != s2[i])
            return false;
    }

    return true;
}

void getDimensions(int argc, char** argv, int* lines, int* columns) {
    if (argc <= 1) {
        *lines = P4_DEFAULT_LINES;
        *columns = P4_DEFAULT_COLUMNS;
        return;
    }

    if (argc > 3) {
        errorArgs(NULL);
    }

    char ln[10];
    char cl[10];

    bool ln_set = false;
    bool cl_set = false;

    if (compareString(argv[1], "-ln:", 4)) {
        strcpy(ln, argv[1]);
        ln_set = true;
    }
    else if (compareString(argv[1], "-cl:", 4)) {
        strcpy(cl, argv[1]);
        cl_set = true;
    }


    if (argc == 3) {
        if (compareString(argv[2], "-ln:", 4)) {
            if (ln_set)
                errorArgs(argv[2]);
            else {
                strcpy(ln, argv[2]);
                ln_set = true;
            }
        }
        else if (compareString(argv[2], "-cl:", 4)) {
            if (cl_set)
                errorArgs(argv[2]);
            else {
                strcpy(cl, argv[2]);
                cl_set = true;
            }
        }
        else
            errorArgs(argv[2]);
    }


    if (ln_set) {
        int val = atoi(ln + (sizeof ("-ln:")-1));
        if (val < 4 || val > 20)
            errorRange(1);

        *lines = val;
    } else {
        *lines = P4_DEFAULT_LINES;
    }

    if (cl_set) {
        int val2 = atoi(cl + (sizeof ("-cl:")-1));
        if (val2 < 4 || val2 > 20)
            errorRange(0);

        *columns = val2;
    } else {
        *columns = P4_DEFAULT_COLUMNS;
    }
}