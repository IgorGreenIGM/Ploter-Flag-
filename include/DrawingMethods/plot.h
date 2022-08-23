#ifndef PLOT_H_INCLUDED_
#define PLOT_H_INCLUDED_

//typedef enum _bool _bool;
enum _bool
{
    _true = 1,
    _false = 0
};

extern _bool is_filesLoaded;
extern _bool is_grid;
extern _bool is_axis;
extern _bool is_fullScreen;
extern _bool is_animation;
extern _bool is_info;

extern char *filesPaths[];
extern int nbFiles;

void plot(void);
void mainDisplay(void);
void mainKeyboard(unsigned char key, int x, int y);
char *setWindowTitle(void);

#endif // PLOT_H_INCLUDED_