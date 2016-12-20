#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifdef HAVE_ZEND_QSORT
#include "zend_qsort.c"
#define ISWAP_CC
#else
#include "zend_sort.c"
#define ISWAP_CC , iswap
#endif

#define MICRO_IN_SEC 1000000.00

double microtime() {
	struct timeval tp = {0};

	if (gettimeofday(&tp, NULL)) {
		return 0;
	}

	return (double)(tp.tv_sec + tp.tv_usec / MICRO_IN_SEC);
}


static int icmp(const int *a, const int *b) {
	return *a>*b?1:(*a==*b?0:-1);
}

static void iswap(int *a, int *b) {
	int i = *a;
	
	*a = *b;
	*b = i;
}

int main(int argc, char *argv[]) {
	const size_t isize = 1000000;
	const size_t imax = 10000000;
	int list[isize],list2[isize];
	int i;

	struct timeval tp = {0};

	if (gettimeofday(&tp, NULL)) {
		return 0;
	}

	srand(tp.tv_sec/1000);
	
	/*
	printf("=======================================\n");
	printf("========== source int list ============\n");
	printf("=======================================\n");
	*/
	for(i=0; i<isize; i++) {
		list[i]=rand()%imax;
		list2[i]=list[i];
		//printf("%3d\n", list[i]);
	}
#if 0
	zend_qsort(list, isize, sizeof(int), icmp ISWAP_CC);
	printf("=======================================\n");
	printf("========== sorted int list ============\n");
	printf("=======================================\n");
	for(i=0; i<isize; i++) {
		printf("%3d\n", list[i]);
	}
#else
	double tmptime,tmptime2,tmptime3;
	
	tmptime=microtime();
	
	for(i=0;i<10;i++) {
		memcpy(list,list2,sizeof(list));
		zend_qsort(list, isize, sizeof(int), icmp ISWAP_CC);
	}
	
	tmptime2=microtime();
	
	for(i=0;i<10;i++) {
		memcpy(list,list2,sizeof(list));
		qsort(list, isize, sizeof(int), icmp);
	}
	
	tmptime3=microtime();
	
	printf("%lf\n%lf\n", tmptime2-tmptime, tmptime3-tmptime2);
#endif
	return 0;
}
