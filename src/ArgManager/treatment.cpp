#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../../include/ArgManager/argList.h"
#include "../../include/ArgManager/userInterface.h"

// function setting the argList with default args and user-args
// note : we start by the treatment of default args then user-args
void argTreatment(int (*treatment)(ArgList *), Argv *((argvInitFunc)(char *command)), int userArgCount, char *argv[], int defaultArgCount, const char *command, ...)
{
    ArgList *argList = (ArgList *)malloc(sizeof(*argList)); // we create an argList
    initiliserArgList(argList);

    if (defaultArgCount != 0) // if the defaut-defined args is not 0
    {
        va_list ap;
        va_start(ap, command);
        addArgvInList(argList, initializeArg((char *)command)); // we copy all the defalut-defined command into the list
        for (int i = 1; i < defaultArgCount; i++)
            addArgvInList(argList, argvInitFunc(va_arg(ap, char *)));
        va_end(ap); // we end the commands reading
    }

    for (int i = 1; i <= userArgCount; i++)
        addArgvInList(argList, argvInitFunc(argv[i])); // the we copy all user defined args into the list

    // we send the arglist to the treatment function
    treatment(argList);
    destroyList(argList); // then we destroy the argList
    free(argList);        // we free the allocated memory
}
