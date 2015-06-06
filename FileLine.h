


#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//#define USE_VCDEMO

typedef unsigned char	BOOLL ;

#define TRUE	1
#define FALSE	0


#ifdef USE_VCDEMO
  typedef FILE * FHANDLE;
  #define IsFileOpenOK(fp) (fp!=NULL)
#else
  typedef int FHANDLE;
  #define IsFileOpenOK(handle) (handle>=0)
#endif


#ifdef USE_VCDEMO

//#define FONTCHARACTER               unsigned short
  #define FONTCHARACTER               char

  #define _OPENMODE_READ              0x01
  #define _OPENMODE_READ_SHARE        0x80
  #define _OPENMODE_WRITE             0x02
  #define _OPENMODE_READWRITE         0x03
  #define _OPENMODE_READWRITE_SHARE   0x83

  #define _CREATEMODE_BINARY          1
  #define _CREATEMODE_DIRECTORY       5

	FHANDLE Bfile_OpenFile(const FONTCHARACTER *filename, int mode);
	int Bfile_CreateFile(const FONTCHARACTER *filename, int size);
	
	int Bfile_SeekFile(FHANDLE HANDLE, int pos);
	int Bfile_GetFileSize(FHANDLE HANDLE);
	#define Bfile_CloseFile(handle) fclose(handle)
	
	int Bfile_ReadFile(FHANDLE HANDLE, void *buf, int size, int readpos);
	int Bfile_WriteFile(FHANDLE HANDLE, const void *buf, int size);
	int Bfile_DeleteFile(const FONTCHARACTER *filename);
#endif


//返回文件行数,不存在或不成功则返回-1
int GetFileLineNum(const FONTCHARACTER * filename);
//读文件filename行nLineNo(0~)内容,存于cBuf[],最多读入长度nMaxLen,OK则返回读入的行长度,不存在或不成功则返回-1
int ReadFileLine(const FONTCHARACTER * filename,int nLineNo,char cBuf[],int nMaxLen);
//写文件filename行nLineNo(0~)内容cBuf[],OK则返回写入的行序号(0~),不成功则返回-1
int WriteFileLine(const FONTCHARACTER * filename,int nLineNo,char cBuf[]);
//写文件filename的量szSect[]=内容cBuf[],OK则返回写入的行序号(0~),不成功则返回-1,如 "A=123" ,szSect[]="A", cBuf[]="123"
int WriteIniLine(const FONTCHARACTER * filename,char szSect[],char cBuf[]);
//读文件filename的量szSect[]=内容到cBuf[],OK则返回读入实际长度,不成功则返回-1,如 "A=123" ,szSect[]="A", cBuf[]="123"
int ReadIniLine(const FONTCHARACTER * filename,char szSect[],char cBuf[],int nMaxLen);

