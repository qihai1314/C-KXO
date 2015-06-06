#ifndef CVS_H
#define CVS_H

extern double stod(const char *s);
extern int stoi(const char *s);
extern double deg(double dms);
extern double dms(double deg);
extern double  rad(double deg);
extern double arad(double rad);
extern double sign(double value);
extern double azimuth(double x1, double y1, double x2, double y2);

#endif	//CVS_H