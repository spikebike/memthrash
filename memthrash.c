#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define ARRAYSIZE 256*1024*1024/sizeof(long long)

void * initAr(long long *a, int size)
{
	printf ("initializing 256MB i=%d\n",size);
	for (int i=0; i<size; i++)
	{
		a[i]=1;
	}
}

int
main (int argc, char *argv[])
{
	int memCnt,iter;
	long long *bigAr[4096]; // big enough for 1TB
	long long sum;
	char c;

	while ((c = getopt (argc, argv, "g:i:")) != EOF)
	{
		switch (c) {
			case 'g':
				memCnt=4*atoi(optarg);
			break;
			case 'i':
				iter=atoi(optarg);
			break;
		}
	}
	for (int i=0; i< memCnt; i++)
	{
		bigAr[i]=malloc(ARRAYSIZE*sizeof(long long));
		printf ("Allocating 256MB %d ptr=%p\n",i,bigAr[i]);
		if (bigAr[i]==NULL) {
			printf ("Malloc failed\n");
		}
		initAr(bigAr[i],ARRAYSIZE);
	}
	sum=0;
	printf ("iter=%d size=%lu thrashing...\n",iter,ARRAYSIZE);
 	for (int k=0;k<iter; k++)
	{
		for (int i=0;i<memCnt; i++)
		{
			printf ("i=%d p=%p\n",i,bigAr[i]);
			for (int j=0;j<ARRAYSIZE; j++)
			{
				sum+=bigAr[i][j];
			}
		}
	}
	printf ("sum=%lli\n",sum);
}

	
