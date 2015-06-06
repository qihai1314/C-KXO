#define REDRAW_PART 1
#define REDRAW_ALL  2

extern unsigned int key;
extern int mode,index,need_redraw;
extern COMMONDATA common_data;
extern double *value;
int InputDefProc (double *,int,int,int,int,int);

extern SETUPDATA setup_data;

#define MODE_EXIT 0

void ShowTitle (char *title);