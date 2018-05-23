#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;

void CountingSort(int A[],int B[],int k)
{
    int i,C[k+1];
    for (i=0;i<=k;i++)
	{
        C[i]=0;
    }
    for (i=0;i<n;i++)
	{
        C[A[i]]=C[A[i]]+1;
    }
    for (i=1;i<=k; i++)
	{
        C[i]=C[i]+C[i-1];
    }
    for (i=n-1;i>=0;i--)
	{
        B[C[A[i]]-1]=A[i];
        C[A[i]]=C[A[i]]-1;
    }
}
//������д�� 

int main()
{
    //clock_t start,finish;
	LARGE_INTEGER num;
	long long start,end,freq;
	double t;
	FILE *fp;
	int b,i;
	int *p;
	int *q;
	char filename[300];
    
	printf("input base x of the length(3^x)\n");
	scanf("%d",&b);
	n=pow(3,b);
	
	p=(int *)malloc(sizeof(int)*n); 
	q=(int *)malloc(sizeof(int)*n); 
    
	if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\counting_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 

    for(i=0;i<n; i++)
	{
        fscanf(fp,"%d\n",&p[i]);
    }
	fclose(fp);//���ļ�
    
	//start=clock();//��ʱ������clock���� 
	QueryPerformanceFrequency(&num);//����winapi�е�΢�뼶���ʱ�����ڽ�С�������� 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
	
	CountingSort(p,q,65535);
    
    QueryPerformanceCounter(&num);
    end=num.QuadPart;
    t=(double)(end-start)/freq;
    
	//finish=clock();//��ʱ���� 
	//t=(double)(finish-start)/CLK_TCK;
    
    
	if((fp=fopen(filename, "w"))==NULL)//д��rusult_i.txt�� 
	{
		printf("error\n");
		exit(0);
	}
    for (i=0;i<n; i++)
	{
		fprintf(fp,"%d\n",q[i]);
    }
	fclose(fp);//дoutput�ļ� 
    
	if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\counting_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
		printf("error\n");
		exit(0);
	}
	fprintf(fp, "Counting Sort at base %d takes %f seconds\n",b,t);
	fclose(fp);//дtime�ļ� 
    
	printf("Counting sort : %f seconds\n",t);
	return 0;
}
