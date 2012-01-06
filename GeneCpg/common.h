#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFF_ROWS 45000
#define BUFF_COLS 7000

typedef struct GeneBuff{
	char buff[BUFF_ROWS][BUFF_COLS];
	int start;//valid index:start positon(>=0)
	int end;//valid index:end position
}GBuff;

FILE* openFile(char *fileName,char *mode);
void closeFile(FILE *fp);

/* read data from file,and store into gb*/
int readToBuff(FILE *fp,GBuff *gb);

/* write data(which is store in gb) to file*/
int writeFromBuff(FILE *fp,GBuff *gb);

//È¥¿Õ¸ñ
char * trim(char *ptr);
char * lTrim(char *ptr);

#endif