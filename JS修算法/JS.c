#include "headfile.h"

int ZS()
{
	double Ca,DKa,DKb,Xa,Ya;
	double Ra,Rb,Pa,Pb;
	double pi,h,W,z,v;
	double U,dk,p,c,J_out;
	int k;
	int n=10;
	int i=0;
	
	if (yscs.k<qxys[0].p_qdk)	yscs.k=qxys[0].p_qdk;
	if (yscs.k>qxys[setup.db_num].p_zdk)	yscs.k=qxys[setup.db_num].p_zdk;
	while(yscs.k<qxys[i].p_qdk || yscs.k>qxys[i].p_zdk){
		i++;
	}
	if (yscs.k>=qxys[i].p_qdk	&&	yscs.k<=qxys[i].p_zdk){
		Ca=qxys[i].p_qda;
		DKa=qxys[i].p_qdk;
		DKb=qxys[i].p_zdk;
		Xa=qxys[i].p_qdx;
		Ya=qxys[i].p_qdy;
		Ra=qxys[i].p_qdr;
		Rb=qxys[i].p_zdr;
	}
    
	if (Ra==0 && Rb!=0){
	Pa=0;
	Pb=1/Rb;
	}
	else if (Rb==0 && Ra!=0){
	Pb=0;
	Pa=1/Ra;
	}
	else if (Ra==0 && Rb!=0){
	Pa=0;
	Pb=0;
	n=1;
	}
	else if (Ra!=0 && Rb!=0){
	Pa=1/Ra;
	Pb=1/Rb;
	}
	pi=Pa+(Pb-Pa)*abs(yscs.k-DKa)/abs(DKb-DKa);
	J_out=0.5*(Pa+pi)*abs(yscs.k-DKa);
	h=fabs(yscs.k-DKa)/n;
    W==0;
	z==0;
	U==0;
	v==0;
	for(k=1;k<2*n-1;k++){
	dk=DKa+k*h/2;
	p=Pa+(Pb-Pa)*abs(dk-DKa)/abs(DKb-DKa);
	c=Ca+0.5*(Pa-p)*abs(dk-DKa);
	}
	if (k%2==0){
	W=W+cos(c);
	z=z+sin(c);
	}
	else if (k%2==1){
	U=U+cos(c);
	v=v+sin(c);
	}
	yscs.xn = Xa+h/6.0*(cos(Ca)+4.0*U+2.0*W+cos(J_out)); 
	yscs.ye = Ya+h/6.0*(sin(Ca)+4.0*U+2.0*z+sin(J_out)); 
	yscs.fn=J_out;
	zfset.ks=yscs.k;
	return 1;	
}

int FS()
{
	double fi,fj,fw;
	int cc;
	
	yscs.d=0.0;	cc=0;

	do{
		
		ZS();
		fi = sqrt((yscs.xn-yscs.x1)*(yscs.xn-yscs.x1)+(yscs.ye-yscs.y1)*(yscs.ye-yscs.y1));
 		fj = atan((yscs.ye-yscs.y1)/(yscs.xn-yscs.x1+1e-12));
		fj = fj/ PI * 180.0;
		if (yscs.xn -yscs.x1< 0.0)	fj += 180.0;
		if (fj<0.0)	fj += 360.0;
		fw=fi*sin((yscs.fn-fj-90.0)*PI/180.0);
		yscs.k=yscs.k+fw;
		++cc;
		if (cc>=80)	fw=0.00001;

	}while(fabs(fw)>0.0001);
		ZS();
		yscs.d=(yscs.y1-yscs.ye)/sin((yscs.fn+90.0)*PI/180.0);
		return 1;
}

int GC()
{
	double gr,gf,ge,gp;
	double ga,gi,gw,gt,gz;
	int i=0;
	if (yscs.k<sqxys[0].s_qdk)	SQX_ERR();
	while(yscs.k<sqxys[i].s_qdk || yscs.k>sqxys[i].s_zdk){
		i++;
	}
	
	ge=sqxys[i].s_qdi;
	gf=sqxys[i].s_zdi;
	ga=sqxys[i].s_bpk;
	gz=sqxys[i].s_bph;
	gr=sqxys[i].s_r;
	gt=gr*fabs(gf-ge)/2;
	if (gf-ge>0)	gw=1;	else gw=-1;
	if (yscs.k<ga)	gi=-ge;	else gi=gf;
	gp=fabs(ga-yscs.k);
	if (gp-gt>0)	yscs.gch=gz+gi*gp;	else yscs.gch=gz+gi*gp+gw*((gt-gp)*(gt-gp))/2/gr;
	
	return 1;
}

int HP()
{
	int i=0;
	double hpj,hpv,hpg,hpe,hpl;
	if (yscs.k<hpys[0].h_qdk)	HP_ERR();
	while(yscs.k<hpys[i].h_qdk || yscs.k>hpys[i].h_zdk){
		i++;
	}
		hpe=hpys[i].h_qdk;
		hpj=hpys[i].h_qdi;
		hpv=hpys[i].h_zdi;
		hpg=hpys[i].h_zdk;

	hpl=hpg-hpe;
	if (hpj==hpv) yscs.hpd=hpj;	else yscs.hpd=(hpj+((hpv-hpj)/hpl)*(yscs.k-hpe));
	return 1;	
}
