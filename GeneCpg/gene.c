#include <limits.h>
#include "common.h"
#include "gene.h"

#define COLS 6
#define GENE_BASE_SIZE		4100
#define INCREMENT		1000
#define TSS_BASE_SIZE	100
#define CPG_BASE_SIZE	 100

Chromosome chromosomes[CHROMOSOME_COUNT];//24条染色体

int getIndex(char *p);
int mallocGeneArray(GeneArray *ga);
int initGeneArray(GeneArray *ga);
int mallocCpg(CpgArray *cpgArray);
int initCpg(CpgArray *cpgArray);
int mallocTssArray();


int storeOneGene(char *ptr[]);

int init(){
	int i = 1, j = 0;
	for(i=1;i<CHROMOSOME_COUNT;i++){
		strcpy(chromosomes[i].name,"undef");
		chromosomes[i].cpgCount = 0;
		chromosomes[i].geneCount = 0;
		chromosomes[i].tssCount = 0;
		mallocGeneArray(&chromosomes[i].geneArray);
		initGeneArray(&chromosomes[i].geneArray);
		mallocCpg(&chromosomes[i].cpgArray);
		initCpg(&chromosomes[i].cpgArray);
	}
	return 0;
}

int processGene(GBuff *gb){
	int i = 0,j = 0,index = -1;
	char *ptr[COLS];
	char *t = NULL;

	for(i=gb->start;i<=gb->end;i++){
		j = 0;
		t = gb->buff[i];
		while(j < COLS && (ptr[j++] = strtok(t," \t")) != NULL){
			t = NULL;
		}

		if(j != COLS){
			printf("--Data format ERROR in Gene file...Skip this line[%d]--\t\n%s\n",i+1,gb->buff[i]);
			continue;
		}
		storeOneGene(ptr);
	}
	return 0;
}

int getChromosomeIndex(char *p){
	int index = -1;
	int length = 0;
	if(p == NULL || (length = strlen(p)) < 4){
		return index;
	}
	
	if(isalpha(p[3])){
		index = toupper(p[3]) - 'X' + 23;
	}else{
		index = p[3] - '0';
		if(length > 4 && isdigit(p[4])){
			index = index*10 + p[4] - '0';
		}
	}
	return index;
}

int storeOneGene(char *ptr[]){
	int chromosomeIndex = 0;
	GeneArray *ga = NULL;
	Gene * genes = NULL;
	if(ptr == NULL){
		return -1;
	}
	chromosomeIndex = getChromosomeIndex(ptr[2]);
	if(chromosomeIndex < 1 || chromosomeIndex > 24 ){
		return -1;
	}
	//如果容量不够时，需重新分配内存
	ga = &(chromosomes[chromosomeIndex].geneArray);

	if(ga->length >= ga->capacity){
		genes = (Gene *)realloc(ga->genes,(ga->capacity + INCREMENT)*sizeof(Gene));
		if(!genes){
			printf("Error Occurred While Reallocate Memory to GENE.....\n");
			printf("Press ENTER to EXIT......\n");
			getchar();
			//free memory
			exit(1);
		}
		ga->genes = genes;
		ga->capacity += INCREMENT;
	}
	strcpy(ga->genes[ga->length].name,ptr[1]);
	ga->genes[ga->length].start = atol(ptr[4]);
	ga->genes[ga->length].end = atol(ptr[5]);
	ga->length++;
	chromosomes[chromosomeIndex].geneCount++;
	//printf("store gene[ %s ] to chromosome[%d] success.\n",ptr[1],index);
	return 0;
}

int mallocGeneArray(GeneArray *ga){
	ga->genes = (Gene *)malloc((GENE_BASE_SIZE) * sizeof(Gene));
	if(ga->genes == NULL){
		printf("Error Occurred While Allocate Memory for Gene.....\n");
		printf("Press ENTER to EXIT......\n");
		getchar();
		exit(1);
	}
	ga->capacity = GENE_BASE_SIZE;
	ga->length = 0;
	return 0;
}

int initGeneArray(GeneArray *ga){
	int i = 0;
	Gene *genes = ga->genes;
	for(i=0;i<ga->capacity;i++){
		genes[i].cpgCount = 0;
		genes[i].tssCount = 0;
		genes[i].firstTss.position = LONG_MAX;
		genes[i].start = 0;
		genes[i].end = 0;
		strcpy(genes[i].name,"undef");
		mallocTssArray(&genes[i].tssArray);
		mallocCpg(&genes[i].cpgArray);
		initCpg(&genes[i].cpgArray);
	}
	
	return 0;
}

int mallocTssArray(TssArray *tssArray){
	tssArray->tss = (Tss *)malloc((TSS_BASE_SIZE)*sizeof(Tss));
	if(tssArray->tss == NULL){
		printf("Error Occurred While Allocate Memory for Tss.....\n");
		printf("Press ENTER to EXIT......\n");
		getchar();
		exit(1);
	}
	tssArray->capacity = TSS_BASE_SIZE;
	tssArray->length = 0;
	return 0;
}

int mallocCpg(CpgArray *cpgArray){
	cpgArray->cpgs = (Cpg *)malloc((CPG_BASE_SIZE)*sizeof(Cpg));
	if(cpgArray->cpgs == NULL){
		printf("Error Occurred While Allocate Memory for Cpg.....\n");
		printf("Press ENTER to EXIT......\n");
		getchar();
		exit(1);
	}
	cpgArray->capacity = CPG_BASE_SIZE;
	cpgArray->length = 0;
	return 0;
}

int initCpg(CpgArray *cpgArray){
	int i = 0;
	for(i=0;i<cpgArray->capacity;i++){
		cpgArray->cpgs[i].from = 0;
		cpgArray->cpgs[i].to = 0;
		cpgArray->cpgs[i].spanCount = 0;
	}
	return 0;
}


void print_chromosomes(){
	long i = 1,j = 0,r = 0,geneTotal = 0,tssTotal = 0,cpgTotal = 0,
		cpgGeneTotal = 0,tssGeneTotal = 0,cpgAllGeneTotal = 0,tssAllGeneTotal = 0;
	FILE *fp = openFile("out.txt","w");	
	GeneArray *ga = NULL;
	Gene *gene = NULL;
	Cpg *cpgs = NULL;
	char chromosomeName[10] = "chr";
	fprintf(fp,"%-10s\t%-15s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\t%-10s\n","Chromosome","GeneName","TssCount","TssStart","CpgCount","CpgLoc","CpgLength","isSpan");
	for(i=1;i<CHROMOSOME_COUNT;i++){
		ga = &chromosomes[i].geneArray;
		cpgGeneTotal = 0;
		tssGeneTotal = 0;
		if(i>=23){
			sprintf(chromosomeName,"%s%c","chr",'X' + (i- 23));
		}else{
			sprintf(chromosomeName,"%s%d","chr",i);
		}

		for(j=0;j<ga->length;j++){
			gene = &ga->genes[j];
			for(r=0;r<gene->cpgCount;r++){
				if(r == 0){
					fprintf(fp,"%-10s\t%-15s\t%-10ld\t%-10ld\t%-10ld\t",chromosomeName,gene->name,gene->tssCount,gene->firstTss.position % LONG_MAX,gene->cpgCount);				
				}else{
					fprintf(fp,"%-10s\t%-15s\t%-10s\t%-10s\t%-10s\t"," "," "," "," "," ");
				}
				fprintf(fp,"%-10ld\t%-10ld\t%-10ld\n",gene->cpgArray.cpgs[r].from,gene->cpgArray.cpgs[r].to - gene->cpgArray.cpgs[r].from + 1,gene->cpgArray.cpgs[r].spanCount);
			}
			
			cpgGeneTotal += gene->cpgCount;
			tssGeneTotal += gene->tssCount;
			cpgAllGeneTotal += gene->cpgCount;
			tssAllGeneTotal += gene->tssCount;
		}
		/*不在基因中的Cpg */
		cpgs = chromosomes[i].cpgArray.cpgs;		
		for(j=0;j<chromosomes[i].cpgArray.length;j++){		
			//if(j == 0){
				fprintf(fp,"%-10s\t%-15s\t%-10s\t%-10s\t%-10ld\t",chromosomeName,"---","---","---",chromosomes[i].cpgCount - cpgGeneTotal);
				fprintf(fp,"%-10ld\t%-10ld\t%-10s\n",cpgs[j].from,cpgs[j].to - cpgs[j].from + 1,"-");
			//}else{
			//	fprintf(fp,"%-15s\t%-10s\t%-10s\t%-10s"," "," "," "," ");
			//}
		}
		
		printf("chr[%ld]: %ld genes,%ld cpgs,%ld tss,[%ld cpgs and %ld tss in genes].\n",i,chromosomes[i].geneCount,chromosomes[i].cpgCount,chromosomes[i].tssCount,cpgGeneTotal,tssGeneTotal);
		//printf("%s has \t%ld cpgs non_in genes.\n",chromosomeName,chromosomes[i].cpgArray.length);

		geneTotal += chromosomes[i].geneCount;
		cpgTotal += chromosomes[i].cpgCount;
		tssTotal += chromosomes[i].tssCount;
	}
	printf("---------------------------------------\n");
	printf("total cpgs in genes = %ld,total tss in genes =  %ld.\n",cpgAllGeneTotal,tssAllGeneTotal);
	printf("---------------------------------------\n");
	printf("total genes =  %ld\n",geneTotal);
	printf("total cpgs = %ld,total tss = %ld.\n",cpgTotal,tssTotal);
	fclose(fp);
}

void print_Total(){
	long i = 1,j = 0,r = 0,geneTotal = 0,tssTotal = 0,cpgTotal = 0,
		cpgGeneTotal = 0,tssGeneTotal = 0,cpgAllGeneTotal = 0,tssAllGeneTotal = 0;
	//FILE *fp = openFile("out.txt","w");
	
	GeneArray *ga = NULL;
	Gene *gene = NULL;
	Cpg *cpgs = NULL;
	char chromosomeName[10] = "chr";
	freopen("total.txt","w",stdout);
	for(i=1;i<CHROMOSOME_COUNT;i++){
		ga = &chromosomes[i].geneArray;
		cpgGeneTotal = 0;
		tssGeneTotal = 0;
		if(i>=23){
			sprintf(chromosomeName,"%s%c","chr",'X' + (i- 23));
		}else{
			sprintf(chromosomeName,"%s%d","chr",i);
		}

		for(j=0;j<ga->length;j++){
			gene = &ga->genes[j];
			
			cpgGeneTotal += gene->cpgCount;
			tssGeneTotal += gene->tssCount;
			cpgAllGeneTotal += gene->cpgCount;
			tssAllGeneTotal += gene->tssCount;
		}
		/*不在基因中的Cpg */
		cpgs = chromosomes[i].cpgArray.cpgs;		
		
		printf("%ld. chrom[%ld]: 有 %ld genes,%ld cpgs,%ld tss,其中在Gene上有：%ld cpgs 和 %ld tss .\n",i,i,chromosomes[i].geneCount,chromosomes[i].cpgCount,chromosomes[i].tssCount,cpgGeneTotal,tssGeneTotal);

		geneTotal += chromosomes[i].geneCount;
		cpgTotal += chromosomes[i].cpgCount;
		tssTotal += chromosomes[i].tssCount;
	}
	printf("---------------------------------------\n");
	printf("total cpgs in genes = %ld,total tss in genes =  %ld.\n",cpgAllGeneTotal,tssAllGeneTotal);
	printf("---------------------------------------\n");
	printf("total genes =  %ld\n",geneTotal);
	printf("total cpgs = %ld,total tss = %ld.\n",cpgTotal,tssTotal);
}


