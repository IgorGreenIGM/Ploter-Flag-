#ifdef WIN32
#include <windows.h>
#endif

#include <time.h>

#include "../../include/GL/glut.h"
#include "../../include/DrawingMethods/plot.h"
#include "../../include/DrawingMethods/streamRead.h"
#include "../../include/DrawingMethods/drawStream.h"
#include "../../include/DrawingMethods/drawUtilities.h"
#include "../../include/StreamOperations/StreamOperations.h"

//ploting files streams method
void plot(void)
{
    int argc = 1;
    char *argv[1] = {(char *)"no-args"};
    glutInit(&argc, argv);  // Glut Windows init Functions

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    //we set the window name given by the concatened names of the input streams names and "plot result method"
    glutCreateWindow(setWindowTitle());    

    // Mapping definition
    glScalef(0.1, 0.1, 0.1);
    glTranslatef(-9, -9, 0);

    if (is_fullScreen)  glutFullScreen();   // if there was a fullscreen arg, we init the full screen mode 

    glutDisplayFunc(mainDisplay); // then we call the display callback function

    glutKeyboardFunc(mainKeyboard); //we call the keyboard callback function

    glutMainLoop();
}

//the display callback method 
void mainDisplay(void)
{
    glClearColor(0.104f, 0.104f, 0.104f, 1);    //we start by clearing the screen with a gray color
    glClear(GL_COLOR_BUFFER_BIT);

    //setting graphics display options...
    glEnable(GL_BLEND);
    glEnable(GL_DOUBLEBUFFER);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.0f);

    srand(time(NULL)); // initialising seed for the random color generating function

    // drawing grid and axis if they are specified 
    if (is_axis)    drawAxis();
    if (is_grid)    drawGrid();

    // we calculate the scale (the maximum scale all the specified input streams to avoid cut graphs)
    double scale_x = 0, scale_y = 0;
    calculateScale(&scale_x, &scale_y, filesPaths, nbFiles);

    FILE *fileStreams[nbFiles]; // then we create a files streams buffer for all the input files
    for (int i = 0; i < nbFiles; i++)
    {
        fileStreams[i] = fopen(filesPaths[i], "r");     //we open each file
        //we test if the status information of each file has not been displayed yet 
        if (!is_filesLoaded)
        {
            if (fileStreams[i] == NULL)
            {
                printf("ERROR cannot open the file \"%s\"\n", filesPaths[i]);
                if(nbFiles == 1) return;
            }
            else
                printf("\nFILE \"%s\" found \n", filesPaths[i]);
        }
    }
    is_filesLoaded = _true; // we disable the display of files loading check

    // then we plot all the input streams, either is there is an animated flag or not
    if (is_animation)
    {
        for (int i = 0; i < nbFiles; i++)
            drawStreamAnimation(fileStreams[i], scale_x, scale_y);
        is_animation = _false;
    }
    else
    {
        for (int i = 0; i < nbFiles; i++)
            drawStream(fileStreams[i], scale_x, scale_y);
    }

    if (is_info) // we display informations for each input stream
    {
        printf("\n\n");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("|         INPUT STREAM FILE INFORMATION          |\n");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

        for (int i = 0; i < nbFiles; i++)
        {
            printf("FILE : %s\n", filesPaths[i]);
            printFileInfo(filesPaths[i], scale_x, scale_y);
            printf("--------------------------------------------------\n\n");
        }
        is_info = _false; // disabling the info display
    }

    // closing all the input streams buffers
    for (int i = 0; i < nbFiles; i++)
        fclose(fileStreams[i]);
    glFlush();
}

// setting the window title method : "Plot Result : " + fileName1 + '|' + fileName2 ...
char *setWindowTitle(void)
{
    int filesPathsLen = 0, totalLen = 0, k = strlen((const char *)"Plot Result : ");
    for (int i = 0; i < nbFiles; i++)
        filesPathsLen += strlen(filesPaths[i]); // calculate the total input streams length
    totalLen = filesPathsLen + nbFiles + strlen((const char *)"Plot Result : "); //calculate the totla len

    char *windowTitle = (char *)malloc((totalLen * sizeof(char))); // mem allocation for the window name

    memset(windowTitle, 0x7C , totalLen);
    strcpy(windowTitle, (const char *)"Plot Result : ");

    windowTitle[totalLen - 1] = 0x0;
    for (int i = 0; i < nbFiles; i++)   //then we add files name in the window name var 
    {
        for (int j = 0; j < strlen(filesPaths[i]); j++)
        {
            windowTitle[k] = filesPaths[i][j];
            k++;
        }
        k++;
    }
    return windowTitle;
}

//the keyboard callback method : if the key 0x1B is pressed (Escape), we exit the program
void mainKeyboard(unsigned char key, int x, int y)
{
    if (key == 0x1B)
        exit(EXIT_SUCCESS);
}