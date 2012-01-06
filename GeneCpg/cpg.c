#include "common.h"
#include "gene.h"

#define COLS 4
#define FROM_COLS 1
#define TO_COLS 2
#define CPG_INCREMENT 100

int storeOneCpg(char *ptr[],int chromosomeIndex);
long getGeneIndexForCpg(GeneArray *geneArray,long from,long to);
int isCpgSpanTss(TssArray *tssArray,long from,long to);

void processCpg(GBuff *gb,int chromosomeIndex){
	int i = 0,j = 0,flag = 0;
	char *ptr[COLS];
	char *t = NULL;

	for(i=gb->start;i<=gb->end;i++){
		j = 0;
		t = gb->buff[i];
		while(j < COLS && (ptr[j++] = strtok(t," \t")) != NULL){
			t = NULL;
		}

		if(j != COLS){
			printf("--Data format ERROR in Cpg file...Skip this line[%d]--\t\n%s\n",i+1,gb->buff[i]);
			continue;
		}
		storeOneCpg(ptr,chromosomeIndex);
	}
}

int storeOneCpg(char *ptr[],int chromosomeIndex){
	long geneIndex = 0,from = 0,to = 0;
	Gene * gene = NULL;
	CpgArray *cpgArray = NULL;
	Cpg *cpgs = NULL;
	if(ptr == NULL){
		return -1;
	}
	
	from = atol(ptr[FROM_COLS]);
	to = atol(ptr[TO_COLS]);
	
	geneIndex = getGeneIndexForCpg(&chromosomes[chromosomeIndex].geneArray,from,to);

	if(geneIndex >= 0){	
		gene = &chromosomes[chromosomeIndex].geneArray.genes[geneIndex];
		cpgArray = &gene->cpgArray;			
	}else{
		//printf("can not find gene in chromosome[%d] for this cpg[%ld].\n",index,position);
		//存入染色体中
		cpgArray = &chromosomes[chromosomeIndex].cpgArray;
	}

	if(cpgArray->length >= cpgArray->capacity){
		cpgs = (Cpg *)realloc(cpgArray->cpgs,(cpgArray->capacity + CPG_INCREMENT)*sizeof(Cpg));
		if(!cpgs){
			printf("Error Occurred While Reallocate Memory to Cpg.....\n");
			printf("Press ENTER to EXIT......\n");
			getchar();
			//free memory
			exit(1);
		}
		cpgArray->cpgs = cpgs;
		cpgArray->capacity += CPG_INCREMENT;
	}

	cpgArray->cpgs[cpgArray->length].from = from;
	cpgArray->cpgs[cpgArray->length].to = to;
	if(geneIndex >= 0){
		gene->cpgCount++;
		cpgArray->cpgs[cpgArray->length].spanCount = isCpgSpanTss(&gene->tssArray,from,to);
	}
	cpgArray->length++;
	chromosomes[chromosomeIndex].cpgCount++;
//	printf("store Tss[ %ld ] to chromosome[%d].gene[%s] success.\n",position,index,gene->name);

	return 0;
}

long getGeneIndexForCpg(GeneArray *geneArray,long from,long to){
	int i = 0;
	Gene * genes = geneArray->genes;
	for(i=0;i<geneArray->length;i++){
		if(from > genes[i].end || to < genes[i].start){
			continue;
		}
		return i;
	}
	return -1;
}

/*返回0 = 表示不跨越，>0 表示跨越的个数*/
int isCpgSpanTss(TssArray *tssArray,long from,long to){
	int i = 0;
	int count = 0;
	Tss * tss = tssArray->tss;
	for(i=0;i<tssArray->length;i++){
		if(tss[i].position >= from && tss[i].position <= to){
			count++;
		}
	}
	return count;
}
