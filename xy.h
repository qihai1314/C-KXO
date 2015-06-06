////////////////////////////
// 文件名：xy.h
//
// 功能：坐标计算
///////////////////////////

#ifndef XY_H
#define XY_H

// 已知里程/偏距/角度计算坐标
// xya=0返回x;xya=1返回y;xya=n返回a;超出计算范围返回-1e10
double sd_to_xya( double stake, double distance, double angle, int xy );

// 已知坐标反算里程及偏距
// sd=0返回值为里程,sd=1返回值为偏距(负值为左偏/正值为右偏),超出计算范围返回1e10
double xy_to_sd( double PX, double PY, int sd );

#endif	// XY_H
