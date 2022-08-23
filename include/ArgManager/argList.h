#ifndef ARGLIST_H_INCLUDED
#define ARGLIST_H_INCLUDED

#include "userInterface.h"

typedef struct ArgList ArgList;
struct ArgList                      //the argList Structure definition
{
    int argNumber;
    Argv *first;
};

void initiliserArgList(ArgList *argList);

Argv *searchLastElement(ArgList *argList);

void addArgvInList_Queue(ArgList *argList, Argv *argv);

void addArgvInList(ArgList *argList, Argv *argv);

void destroyList(ArgList *argList);

#endif // ARGLIST_H_INCLUDED
