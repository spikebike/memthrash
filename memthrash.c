#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define ARRAYSIZE 256*1024*1024/sizeof(long long)

void * initAr(long long *a, int size)
{
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

	while ((c = getopt (argc, argv, "g:")) != EOF)
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
		printf ("Allocating 256MB\n");
		bigAr[i]=malloc(ARRAYSIZE*sizeof(long long));
		initAr(bigAr[i],ARRAYSIZE);
	}
	sum=0;
	for (int i=0;i<iter; i++)
	{
		for (int j=0;j<iter; i++)
		{
			sum+=bigAr[i][j];
		}
	}
	printf ("sum=%lli\n",sum);
}

	
