#ifndef TREATMENT_H_INCLUDED
#define TREATMENT_H_INCLUDED

#include "userInterface.h"

/*this is the unique function the you should call :

char(*treatment)(ArgList*) : the argument list treatment function that you defined
void*((argvInitFunc)(char *command)) : the Argv init function you defined
int userArgCount : the number of arguments defined by user in execution
char*argv[] : the aray string of arguments defined by user in execution
int defaultArgCount : the number of argument that you defined by default
const char *command, ... : all the commands you defined by default in user exection
*/

int treatment(ArgList *argList);                 //the treatment function

void argTreatment(int(*treatment)(ArgList*), Argv*((argvInitFunc)(char *command)),
                int userArgCount, char *argv[],
                int defaultArgCount, const char *command, ...);

#endif // TREATMENT_H_INCLUDED
