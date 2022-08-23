#ifndef USERINTERFACE_H_INCLUDED_
#define USERINTERFACE_H_INCLUDED_

/*Define your Argument vector structure here : 
 *This Argv struct is defined for analysing and treating a command by the easiest way as possible,
 *then you should define an argument vector initialisation function and a argument list treatment function
 *function according to your own declaration,
 */

typedef struct Argv Argv; //this name must never be changed or modified
struct Argv
{
    char firstCharacter;
    char *CommandString;    
    int commandLength;
    char *wholeArg;

    Argv *next;
};

Argv *initializeArg(char *command);         //the initialisation function

#endif