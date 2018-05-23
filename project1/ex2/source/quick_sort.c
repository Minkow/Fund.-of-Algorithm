#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;

int Partition(int A[],int p,int r)
{
    int x=A[r],t,j;
    int i=p-1;
    for (j=p;j<r;j++)
	{
        if(A[j]<=x)
		{
            i++;
            t=A[i];
			A[i]=A[j];
			A[j]=t;
        }
    }
    t=A[i+1];A[i+1]=A[r];A[r]=t;
    return i+1;
}

void QuickSort(int A[],int p,int r)
{
    if (p<r)
	{
        int q;
        q=Partition(A, p, r);
        QuickSort(A, p, q-1);
        QuickSort(A, q+1, r);
    }
}

int main()
{
    //clock_t start,finish;
    LARGE_INTEGER num;
    long long start,end,freq;
    double t;
    FILE *fp;
    int b,i;
    int *p;
    char filename[300];
    
    printf("input base x of the length(3^x)\n");
    scanf("%d",&b);
    n=pow(3,b);
    
    p=(int *)malloc(sizeof(int)*n); 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\quick_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 

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
    
    QuickSort(p,0,n-1);
    
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
        fprintf(fp,"%d\n",p[i]);
    }
    fclose(fp);//дoutput�ļ� 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\quick_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Quick Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Quick sort : %f seconds\n",t);
    return 0;
}
