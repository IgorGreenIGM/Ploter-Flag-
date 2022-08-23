#include <stdlib.h>

#include "../../include/ArgManager/argList.h"
#include "../../include/ArgManager/userInterface.h"

//Function which initialisation of the Argv list
void initiliserArgList(ArgList *argList)
{
    argList->argNumber = 0;
    argList->first = NULL;
}

//Function which search and return the last Argv element in an argList
Argv *searchLastElement(ArgList *argList)
{
    if(argList->argNumber == 1)  return argList->first;
    else
    {
        Argv *actual = argList->first;
        while(actual != NULL)
        {
            if(actual->next == NULL) return actual;
            actual = actual->next;
        }
    }
    return NULL;
}

//Function which add an Argv element in queue of an argList
void addArgvInList_Queue(ArgList *argList, Argv *argv)
{
    Argv *last = searchLastElement(argList);
    last->next = argv;
    argv->next = NULL;
}

//adding an Argv Element in the ArgvList method
void addArgvInList(ArgList *argList, Argv *argv)
{
        if(argList->argNumber == 0)
        {
            argList->first = argv;
            argv->next = NULL;
            argList->argNumber = 1;
        }
        else
        {
            addArgvInList_Queue(argList, argv);
            argList->argNumber++;
        }
}

//Function which destroy an argList 
void destroyList(ArgList *argList)
{
    for(int i=1; i<=argList->argNumber; i++)
    {
        Argv *to_delete = argList->first;
        argList->first = argList->first->next;
        free(to_delete);
    }
}
