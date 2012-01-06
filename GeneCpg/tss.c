#include "gene.h"
#include "tss.h"
#define COLS 6
#define TSS_INCREMENT 10
#define CHR_COL 0
#define TSS_POSITION_COL 2

int storeOneTss(char *ptr[]);
long getGeneIndex(GeneArray *geneArray,long position);
char * parseTss(char *p);

int processTss(GBuff *gb){
	int i = 0,j = 0,flag = 0;
	char *ptr[COLS];
	char *t = NULL;
	char temp[1000];

	for(i=gb->start;i<=gb->end;i++){
		j = 0;
		t = gb->buff[i];
		strcpy(temp,t);
		parseTss(t);
		while(j < COLS && (ptr[j++] = strtok(t," \t")) != NULL){
			t = NULL;
		}

		if(j != COLS){
			printf("--Data format ERROR in Tss file...Skip this line[%d]--\t\n%s\n",i+1,gb->buff[i]);
			printf("---->%s<-----\n",temp);
			continue;
		}
		flag = storeOneTss(ptr);
	}
	return 0;
}

int storeOneTss(char *ptr[]){
	long chromosomeIndex = 0,geneIndex = 0,position = 0;
	Gene * gene = NULL;
	TssArray *tssArray = NULL;
	Tss *tss = NULL;
	//printf("storeOneTss.....\n");
	if(ptr == NULL){
		return -1;
	}
	chromosomeIndex = getChromosomeIndex(ptr[CHR_COL]);
	if(chromosomeIndex < 1 || chromosomeIndex > 24 ){
		printf("can not find this chromosome [ %s ].......\n",ptr[CHR_COL]);
		return -1;
	}

	position = atol(ptr[TSS_POSITION_COL]);
	chromosomes[chromosomeIndex].tssCount++;

	geneIndex = getGeneIndex(&chromosomes[chromosomeIndex].geneArray,position);

	if(geneIndex < 0){	
		//printf("can not find gene in chromosome[%d] for this tss[%ld].\n",index,position);
		//getchar();
		return -2;
	}
	
	gene = &chromosomes[chromosomeIndex].geneArray.genes[geneIndex];
	tssArray = &gene->tssArray;

	if(tssArray->length >= tssArray->capacity){
		tss = (Tss *)realloc(tssArray->tss,(tssArray->capacity + TSS_INCREMENT)*sizeof(Tss));
		if(!tss){
			printf("Error Occurred While Reallocate Memory to TSS.....\n");
			printf("Press ENTER to EXIT......\n");
			getchar();
			//free memory
			exit(1);
		}
		tssArray->tss = tss;
		tssArray->capacity += TSS_INCREMENT;
	}

	tssArray->tss[tssArray->length].position = position;
	tssArray->length++;
	gene->tssCount++;
	if(position < gene->firstTss.position){
		gene->firstTss.position = position;
	}
//	printf("store Tss[ %ld ] to chromosome[%d].gene[%s] success.\n",position,index,gene->name);

	return 0;
}

/* 找到tss那个基因上*/
long getGeneIndex(GeneArray *geneArray,long position){
	long i = 0;
	Gene *genes = geneArray->genes;
	for(i = 0;i<geneArray->length;i++){
		if(position >= genes[i].start && position <= genes[i].end){
			return i;
			break;
		}
	}
	return -1;
}

void print_tss(TssArray *tssArray){
	int i = 0;
	for(i=0;i<tssArray->length;i++){
		
	}
}

char * parseTss(char *p){
	char *t = p;
	int i = 0;
	while(!isalpha(t[i])){
		t[i++] = ' ';
	}
	return NULL;	
}
