/* @author Mogou Igor Green
 * @mail igormogou86@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "../../include/GL/glut.h"
#include "../../include/ArgManager/argList.h"
#include "../../include/DrawingMethods/plot.h"
#include "../../include/ArgManager/userInterface.h"
#include "../../include/DrawingMethods/drawUtilities.h"

/// PLEASE FIRSTLY READ userInterface.h

_bool is_filesLoaded = _false;
// setting up the bools for graphicals parameters input check
_bool is_grid = _false;
_bool is_axis = _false;
_bool is_fullScreen = _false;
_bool is_info = _false;
_bool is_animation = _false;

int nbFiles = 0;
char *filesPaths[1];

// ArgList treatment method
int treatment(ArgList *argList)
{
    nbFiles = 0; // setting the number of valid file for plotting

    // we calculate the number of valid files for ploting
    for (Argv *arg_t = argList->first; arg_t != NULL; arg_t = arg_t->next)
    {
        if (!strcmp(arg_t->wholeArg, "-istream") && arg_t->next != NULL && arg_t->next->firstCharacter != '-')
            nbFiles++;
    }

    realloc(filesPaths, nbFiles); // memory allocation for the files paths array

    if (nbFiles == 0) // if there is no valid files for ploting, we finish the treatment function
    {
        printf("no files found for ploting \n");
        return -1;
    }
    else // else we start the real treament
    {
        for (Argv *arg_t = argList->first; arg_t != NULL; arg_t = arg_t->next) // we assign options as defined in the arglist
        {
            if (!strcmp(arg_t->wholeArg, "-grid"))
                is_grid = _true;
            if (!strcmp(arg_t->wholeArg, "-axis"))
                is_axis = _true;
            if (!strcmp(arg_t->wholeArg, "-animation"))
                is_animation = _true;
            if (!strcmp(arg_t->wholeArg, "-full"))
                is_fullScreen = _true;
            if (!strcmp(arg_t->wholeArg, "-info"))
                is_info = _true;
            if (!strcmp(arg_t->wholeArg, "-no-grid"))
                is_grid = _false;
            if (!strcmp(arg_t->wholeArg, "-no-axis"))
                is_axis = _false;
            else
                ;
        }

        int i = 0;
        // then we create an array an store the files paths into it
        for (Argv *arg_t = argList->first; arg_t != NULL; arg_t = arg_t->next)
        {
            if (!strcmp(arg_t->wholeArg, "-istream") && arg_t->next != NULL && arg_t->next->firstCharacter != '-')
            {
                filesPaths[i] = arg_t->next->wholeArg;
                i++;
            }
        }

        // having the array of valid files paths, we need before call ploting method to manage exception(unknow args/commands)
        // exceptions management :
        for (Argv *argv = argList->first; argv != NULL; argv = argv->next)
        {
            if (argv->firstCharacter == '-')
            {
                if (!strcmp(argv->CommandString, "istream"))
                {
                    if (argv->next == NULL)
                    {
                        printf("no file specified for \"istream\" command \n");
                    }
                    else if (argv->next->firstCharacter == '-')
                    {
                        printf("\"%s\" is not a valid path for input stream\n", argv->next->wholeArg);
                        argv = argv->next;
                    }
                    else
                        argv = argv->next;
                }
                else if (!strcmp(argv->CommandString, "full"))
                    ;
                else if (!strcmp(argv->CommandString, "grid"))
                    ;
                else if (!strcmp(argv->CommandString, "axis"))
                    ;
                else if (!strcmp(argv->CommandString, "info"))
                    ;
                else if (!strcmp(argv->CommandString, "no-grid"))
                    ;
                else if (!strcmp(argv->CommandString, "no-axis"))
                    ;
                else if (!strcmp(argv->CommandString, "animation"))
                    ;
                else
                    printf("\"%s\" is not a valid option\n", argv->CommandString);
            }
            else
                printf("\"%s\" is not a valid argument\n", argv->wholeArg);
        }
        // then we can call the ploting method :
        plot();
    }
    return 0;
}

/*Argv function initialisation :
According to the Argv struct, this function is called to initialise an 'Argv' element
regarding to the actual command*/
Argv *initializeArg(char *command)
{
    Argv *argv = (Argv *)malloc(sizeof(*argv));
    argv->firstCharacter = command[0];
    argv->commandLength = strlen(command);
    argv->CommandString = (char *)malloc((argv->commandLength - 1) * sizeof(char));
    memcpy((void *)(argv->CommandString), (void *)(command + 1), argv->commandLength - 1);
    argv->CommandString[argv->commandLength - 1] = '\0';
    argv->wholeArg = command;
    return argv;
}