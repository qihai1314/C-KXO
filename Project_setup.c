#include "headfile.h"
#include "runmain.h"

const unsigned char L_GRAPH_SETUP[]={
0,0,0,0,0,0,
0,0,0,0,0,0,
0x23,0xC3,0xFE,0,0,0,
0x12,0x42,0x52,0,0,0,
0x02,0x43,0xFE,0,0,0,
0x02,0x70,0x20,0,0,0,
0x74,0x07,0xFF,0,0,0,
0x1B,0xE1,0x04,0,0,0,
0x12,0x21,0xFC,0,0,0,
0x11,0x41,0x04,0,0,0,
0x18,0x81,0xFC,0,0,0,
0x11,0x41,0x04,0,0,0,
0x0E,0x37,0xFF,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0x02,0x04,0xA8,0x02,0,0,
0x02,0x02,0xC8,0x03,0xE0,0,
0x02,0x07,0xEF,0x02,0,0,
0x0A,0x81,0x92,0x02,0,0,
0x0A,0x42,0xD2,0x1F,0xC0,0,
0x12,0x24,0xAA,0x10,0x40,0,
0x22,0x11,0x0A,0x10,0x40,0,
0x42,0x17,0xE4,0x1F,0xC0,0,
0x02,0x02,0x44,0,0,0,
0x02,0x01,0xCA,0x24,0xA0,0,
0x0E,0x06,0x31,0x64,0x90,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0};
SETUPDATA setup_data = {4,""};


void ChangeSetup ()
{
	double data[4];
	data[0] = setup_data.point;
	index = 0;
	need_redraw = REDRAW_PART;

	Bdisp_AllClr_DDVRAM();
	DrawPicture(0,0,48,32,L_GRAPH_SETUP);
	Bdisp_AreaReverseVRAM(0,0,127,14);

	do
	{
		if (need_redraw == REDRAW_PART)
		{
			int i;
			data[0] > 12 ? data[0] = 12.0:data[0] < 0?data[0]=0:0;
			data[0] = (int)data[0];
			for (i=0;i<1;++i)
				PrintFloat (data[i],42,16,index == i,0);
		}
		GetKey (&key);
		if (key==KEY_CTRL_EXIT)break;
		InputDefProc (data,1,42,16,0,0);
	}
	while (1);
	
	setup_data.point = data[0];
}
