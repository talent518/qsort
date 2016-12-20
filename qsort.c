#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>

#define MICRO_IN_SEC 1000000.00

#define swap_ptr(ptr,ptr2,tmp,size) do {\
		memcpy(tmp, ptr, size);\
		memcpy(ptr, ptr2, size);\
		memcpy(ptr2, tmp, size);\
	} while(0)

double microtime() {
	struct timeval tp = {0};

	if (gettimeofday(&tp, NULL)) {
		return 0;
	}

	return (double)(tp.tv_sec + tp.tv_usec / MICRO_IN_SEC);
}

// 冒泡排序
void bubble_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
	assert(base);
	assert(nmemb);
	assert(size);
	assert(compar);
	
	register void *ptr,*eptr;
	register size_t i;
	register int flag;
	register void *tmp=malloc(size);
	
	for(i=0; i<nmemb-1; i++) {
		flag = 1;
		eptr = base+(nmemb-i-1)*size;
		for(ptr=base; ptr<eptr; ptr+=size) {
			if((*compar)(ptr,ptr+size)>0) {
				swap_ptr(ptr,ptr+size,tmp,size);
				flag = 0;
			}
		}
		if(flag) {
			break;
		}
	}
	free(tmp);
}

void quick_sort_swap(void *begin, void *end, size_t size, int (*compar)(const void *, const void *), void *tmp) {
	register void *bptr=begin,*eptr=end;
	
	memcpy(tmp, bptr, size);
	
	while(bptr<eptr) {
		while(bptr<eptr && (*compar)(eptr, tmp)>=0) {
			eptr -= size;
		}
		memcpy(bptr, eptr, size);
		
		while(bptr<eptr && (*compar)(bptr, tmp)<=0) {
			bptr += size;
		}
		memcpy(eptr, bptr, size);
	}
	
	memcpy(bptr, tmp, size);
	
	if(begin<bptr-size) {
		quick_sort_swap(begin, bptr-size, size, compar, tmp);
	}
	
	if(bptr+size<end) {
		quick_sort_swap(bptr+size, end, size, compar, tmp);
	}
}

// 快速排序
void quick_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
	register void *tmp=malloc(size);
	
	quick_sort_swap(base, base+(nmemb-1)*size, size, compar, tmp);
	
	free(tmp);
}

static int icmp(const int *a, const int *b) {
	return *a>*b?1:(*a==*b?0:-1);
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
	/*
	bubble_sort(list, isize/1000, sizeof(int), icmp);
	printf("=======================================\n");
	printf("========== sorted int list ============\n");
	printf("=======================================\n");
	for(i=0; i<isize; i++) {
		printf("%3d\n", list[i]);
	}
	*/
	
	double tmptime,tmptime2,tmptime3;
	
	tmptime=microtime();
	
	for(i=0;i<10;i++) {
		memcpy(list,list2,sizeof(list));
		quick_sort(list, isize, sizeof(int), icmp);
	}
	
	tmptime2=microtime();
	
	for(i=0;i<10;i++) {
		memcpy(list,list2,sizeof(list));
		qsort(list, isize, sizeof(int), icmp);
	}
	
	tmptime3=microtime();
	
	printf("%lf\n%lf\n", tmptime2-tmptime, tmptime3-tmptime2);
	return 0;
}
