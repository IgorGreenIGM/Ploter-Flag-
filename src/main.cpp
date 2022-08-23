/*
 * @author IgorGreenIG
 * @mail skypunch.artwork@gmail.com 
 */

#include <stdlib.h>
#include "../include/ArgManager/argList.h"
#include "../include/ArgManager/treatment.h"


int main(int argc, char *argv[])
{
    // we call the Treatment method with the user args and 02 defaults args 
    argTreatment(&treatment, &initializeArg, argc-1, argv, 2, "-axis", "-grid");
    return 0;
}