#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <math.h>

#define ARRAYSIZE 256*1024*1024/sizeof(long long)

void * initAr(long long *a, int size)
{
//	printf ("initializing 256MB i=%d\n",size);
	for (int i=0; i<size; i++)
	{
		a[i]=1;
	}
}

double
second ()
{
        struct timeval tp;
        struct timezone tzp;
        gettimeofday (&tp, &tzp);
        return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6);
}

int
main (int argc, char *argv[])
{
	int memCnt,iter;
	long long *bigAr[4096]; // big enough for 1TB
	long long sum;
	char c;
	double start,stop,interval,bandwidth;

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
	printf ("Allocating and initializing 256MB for each \".\"\n");
	for (int i=0; i< memCnt; i++)
	{
		bigAr[i]=malloc(ARRAYSIZE*sizeof(long long));
		fprintf (stderr,".");
		if (bigAr[i]==NULL) {
			printf ("Malloc failed at i=%d\n",i);
		}
		initAr(bigAr[i],ARRAYSIZE);
	}
	sum=0;
	printf ("\niter=%d size=%lu thrashing...\n",iter,ARRAYSIZE);
	start=second();
 	for (int i=0;i<iter; i++)
	{
		for (int j=0;j<memCnt; j++)
		{
//			printf ("i=%d p=%p\n",i,bigAr[i]);
			for (int k=0;k<ARRAYSIZE; k++)
			{
				sum+=bigAr[j][k];
			}
		}
	}
	stop=second();
	interval=stop-start;
	bandwidth=((double)iter*memCnt*ARRAYSIZE*sizeof(double))/(interval*pow(2,20));
//	bandwidth=((double)iter*memCnt*ARRAYSIZE*sizeof(double))/(interval);	
	if (sum == 23) {
		printf ("making sure compiler doesn't cheat\n");
	}
	printf ("read %dGB %d times in %f seconds =  %0.2f MB/sec\n",
			memCnt/4,iter,interval,bandwidth);
}

	
