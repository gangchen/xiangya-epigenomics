#include "common.h"

FILE * openFile(char *fileName,char *mode){
	FILE *fp;
	fp = fopen(fileName,mode);

	if(fp == NULL)
	{
		printf("\nError on open [%s] file.......\n",fileName);
		printf("Press any button to EXIT...");
		getchar();
		exit(1);
	}
	if(feof(fp)){
		printf("\n At the end of file or file is empty.....");
		printf("Press any button to EXIT...");
		getchar();
		exit(0);
	}
	return fp;
}

void closeFile(FILE *fp){
	fclose(fp);
}


int readToBuff(FILE *fp,GBuff *gb){
	int i = 0;
	int state = 0;
	char temp[10] = {0};
	for(i = 0;i < BUFF_ROWS && !feof(fp);i++){
		fgets(gb->buff[i],BUFF_COLS,fp);
		/*if(strlen(gb->buff[i]) <=2){
			printf("%d空行%d\n",strlen(gb->buff[i]),i);
			continue;
		}*/		
	}
	//printf("-->%s<--\n",gb->buff[i-1]);
	/*state = sscanf(gb->buff[i-1][0],"%s",temp);
	if(state==EOF || state==0){
		i = i - 1;	
		printf("空行\n");
	}*/

	if(i<BUFF_COLS && strlen(gb->buff[i-1]) < 3){
		i = i - 1;	
		printf("空行\n");
	}
	//printf("i = %d\n",i);

	//去掉最后的空行
	/*if(strlen(gb->buff[i-1])<=2){
		i = i - 1;
		printf("0000===>i = %d--%s--\n",i,gb->buff[i]);
	}*/
	gb->start = 0;
	gb->end = i-1;
	return i;
}

int writeFromBuff(FILE *fp,GBuff *gb){
	int i = 0;
	for(i = 0;i <= gb->end;i++){
		fputs(gb->buff[i],fp);
	}
	return 0;
}

char * trim(char * ptr)
{
    int start,end,i;
    if (ptr)
    {
        for(start=0; isspace(ptr[start]); start++)
            ;
        for(end=strlen(ptr)-1; isspace(ptr[end]); end--)
            ;
        for(i=start; i<=end; i++)
            ptr[i-start]=ptr[i];
        ptr[end-start+1]='\0';
        return (ptr);
    }
    else
        return NULL;
}

char *lTrim(char *ptr){
	int start = 0,end = 0,i = 0;
    if (ptr)
    {
		end=strlen(ptr)-1;
        for(start=0; isspace(ptr[start]); start++);
        
        for(i=start; i<=end; i++)
            ptr[i-start]=ptr[i];
        ptr[end-start+1]='\0';
        return (ptr);
    }
    return NULL;
}


