#include "headfile.h"

extern const int box_width;

unsigned int WaitKey ()
{
	unsigned int key;
	GetKey(&key);
	return key;
}

char GetPressNumChar(int key)
{
	char ch = 0;
	if (key>=KEY_CHAR_0 && key<=KEY_CHAR_9)
		ch = key;
	else if(key==KEY_CHAR_MINUS || key== KEY_CHAR_PMINUS)
		ch = '-';
	else if (key == KEY_CHAR_DP)
		ch = '.';
	return ch;
}
char GetPressChar(int key)
{
	char ch = 0;
	if (	key>=KEY_CHAR_0 && key<=KEY_CHAR_9 || 
			key>=KEY_CHAR_A && key<=KEY_CHAR_Z)
		ch = key;
	else if(key==KEY_CHAR_MINUS || key== KEY_CHAR_PMINUS)
		ch = '-';
	else if (key == KEY_CHAR_DP)
		ch = '.';
	return ch;
}
int InputString(int x,int y,char *c,int type,int len)// type:0.num 1.char
{
	unsigned int key;
	char ch;
	int i = strlen(c),f = 0,j;
	DrawClearBox (x,y,x+box_width*6+3,y+8+3,1);
	c[i] = ch = 0;
	for(j=0;j<box_width;++j)PrintXY(x+2+j*6,y+2,(uchar*)" ",0);
	PrintXY(6*box_width+x+2-i*6,y+2,(uchar*)c,0);
	while (1)
	{
		GetKey (&key);
		if (ch= (!type)?GetPressNumChar(key):GetPressChar(key))
		{
			if (i<len)
			{
				if(ch=='.')
				{
					if (!f) c[i++] = ch,f=1;
				}
				else
				{
					c[i++] = ch;
				}
			}
		}
		else
		{
			if (key==KEY_CTRL_AC)
				i = 0,f=0;
			else if (key==KEY_CTRL_DEL)
			{
				if (i>0)
				{
					if	(c[i-1]=='.')	f=0;
					c[i--] = 0;	
				}
				
			}
			switch (key)
			{
				default:break;
				case KEY_CTRL_EXE:
				case KEY_CTRL_EXIT:
				case KEY_CTRL_UP:
				case KEY_CTRL_DOWN:
					return key;
			}
		}
		c[i] = ch = 0;
		for(j=0;j<box_width;++j)PrintXY(x+2+j*6,y+2,(uchar*)" ",0);
		PrintXY(6*box_width+x+2-i*6,y+2,(uchar*)c,0);
	}
}
