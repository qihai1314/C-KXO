#include <stdio.h>
#include "cvs.h"
#include "zbzfs.h"
//#include "public.h"
#include "headfile.h"



double sd_to_xya( double stake, double distance, double angle, int xy );

double xy_to_sd( double PX, double PY, int sd );

double sd_to_xya( double stake, double distance, double angle, int xya )
{	

    int iter;
	s_pqx temp;
	for(iter=0; iter<l_pqx.length; iter++)
	{	
        temp = GetList(&l_pqx,iter);
		if( stake>=temp.ss && stake<=temp.es )
		{	
		    intialCZb(temp.ss, temp.es, temp.sx, temp.sy, temp.sa, temp.v, temp.sp, temp.ep);
			
			switch( xya )
			{	case 0:
					return zbzs_x(stake, distance, angle);
					break;
				case 1:
					return zbzs_y(stake, distance, angle);
					break;
				default:
					return zbzs_a(stake, distance, angle);
			}
		}
	}
	return 0;
	
}


double xy_to_sd( double PX, double PY, int sd )
{	

	double x = PX;
	double y = PY;

	double stake   = 0;		
	double mindist = 0;		
	
	int inum = 0;		

	double ex, ey, ea;
	double ped;
	double sx, sy, sa;	
	double psd;		
    double swapdist;
	int iter;
	s_pqx temp,temp1;
	for(iter=0; iter<l_pqx.length-1; iter++)
	{	
        temp  = GetList(&l_pqx,iter);
		temp1 = GetList(&l_pqx,iter+1);
		sx = temp.sx;
		sy = temp.sy;
		sa = temp.sa;
		psd = (y - sy) * cos( rad(sa - 90) ) - (x - sx) * sin( rad(sa - 90) ); //结果可能正负
		
		intialCZb(temp.ss, temp.es, temp.sx, temp.sy, temp.sa, temp.v, temp.sp, temp.ep);
		//ex = zbzs_x(temp.es, 0, 0);
		//ey = zbzs_y(temp.es, 0, 0);
		//ea = zbzs_a(temp.es, 0, 0);
		ex = temp1.sx;
		ey = temp1.sy;
		ea = temp1.sa;
		ped = (y - ey) * cos( rad(ea -90) ) - (x - ex) * sin( rad(ea - 90) );

		if( psd * ped <= 0)  
		{	inum++;
			if( inum==1 )
			{	mindist = zbfs_d(x, y);
				stake = zbfs_s(x, y);
			}
			else
			{	swapdist = zbfs_d(x, y);
				if( fabs(swapdist) < fabs(mindist) )
				{	mindist = swapdist;
					stake = zbfs_s(x, y);
				}
			}
		}
	}

	if( inum == 0 )
	{	return -(1e10);
	}

	if( sd==0 )
	{	return stake;
	}
	else
	{	return mindist;
	}
}