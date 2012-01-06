#include <limits.h>
#include <float.h>
#include "common.h"
#include "gene.h"
#include "tss.h"
#include "cpg.h"

void processG();
void processT();
void processC();
int test2();

GBuff gb;

void main(){
	init();
	processG();
	processT();
	processC();
	print_chromosomes();
	print_Total();
	//test2();
}

void processG(){
	long i = 0;
	FILE* fp = NULL;
	char p[1000];
	clock_t start = 0,finish = 0;
	long total = 0;
	fp = openFile("./data/genes_ucsc.ucsc","r");

	/*读第一行*/
	fgets(p,1000,fp);
	
	start  = clock();
	printf("start process Gene........\n");
	while(!feof(fp)){
		total += readToBuff(fp,&gb);
		processGene(&gb);
	}	
	finish = clock();
	printf("gene file: records total = %ld,time consumption : %f\n",total,(finish - start)/1000.0);
}

void processT(){
	long i = 0;
	FILE* fp = NULL;
	clock_t start = 0,finish = 0;
	long total = 0;
	fp = openFile("./data/all_list_adult_hg19.tab","r");

	start  = clock();
	printf("\nstart process Tss........\n");
	while(!feof(fp)){
		total += readToBuff(fp,&gb);
		processTss(&gb);
	}
	finish = clock();
	printf("tss file: records total = %ld,time consumption : %f\n",total,(finish - start)/1000.0);
}

void processC(){
	FILE *fp = NULL;
	char path[30] ="./data/CpGcluster/chr";
	char fileName[20] = "_CpGcluster.txt";
	char temp[100];
	char p[1000];
	long total = 0;
	clock_t start = 0,finish = 0;
	int i = 0;
	start  = clock();

	printf("\nstart process Cpg........\n");
	for(i=1;i<=24;i++){
		sprintf(temp,"%s%d%s",path,i,fileName);
		fp = openFile(temp,"r");
		fgets(p,1000,fp);
		
		while(!feof(fp)){
			total += readToBuff(fp,&gb);
			processCpg(&gb,i);
		}
		//printf("file[%s] has %ld records.",temp,total);
		fclose(fp);
		//total = 0;
	}	
	finish = clock();
	printf("cpg files: records total = %ld,time consumption : %f\n",total,(finish - start)/1000.0);

}
/*
void test(){
	int in=0,i = 0;
	char buffer[]="   #bin	name	chrom	strand	txStart	txEnd	cdsStart	cdsEnd	exonCount	exonStarts	exonEnds	score	name2	cdsStartStat	cdsEndStat	exonFrames";
	//char buffer[] = "";
	char *p[100];
	char *buff = buffer;
	while((p[in]=strtok(buff," \t"))!=NULL) {
                 in++;
                 buff=NULL; 
	}
	for(i=0;i<in;i++){
		printf("%d---%s\n",i,p[i]);
	}
	//printf("%d---%s\n",i,buffer);
}

void test2()
{
   int in=0,j = 0;
   char buffer[INFO_MAX_SZ]="Fred male 25,John male 62,Anna female 16";
   char *p[20];
   char *buf=buffer;

   while((p[in]=strtok(buf,","))!=NULL) {
             buf=p[in];
             while((p[in]=strtok(buf," "))!=NULL) {
                       in++;
                       buf=NULL;
                    }
                 p[in++]="***"; //表现分割
                 buf=NULL; }

   printf("Here we have %d strings\n",in);
   for (j=0; j<in; j++)
         printf(">%s<\n",p[j]);
}

*/

int test2()
{
 
 	printf("有符号小整型的最小值和最大值\n %d %d\n",CHAR_MIN,CHAR_MAX);
 
 	printf("符号小整型的最大值\n %u\n",UCHAR_MAX);
 
 	printf("符号短整型的最小值和最大值\n %d %d\n",SHRT_MIN,SHRT_MAX);
 
 	printf("无符号短整型的最大值\n %u\n",USHRT_MAX);
 
 	printf("有符号基本整型的最小值和最大值\n %d %d\n",INT_MIN,INT_MAX);
 
 	printf("符号基本整型的最大值\n %u\n",UINT_MAX);
 
 	printf("符号长整型的最小值和最大值\n %d %d\n",LONG_MIN,LONG_MAX);
 
	printf("符号长整型的最大值\n %u\n",ULONG_MAX);
 
	printf("单精度实数的最小绝对值和最大绝对值\n %lf %lf\n",FLT_MIN,FLT_MAX);
 
	printf("双精度实数的最小绝对值和最大绝对值\n %lf %lf\n",DBL_MIN,DBL_MAX);
	//system("pause");
	return 0;
} 
