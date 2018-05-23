#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

int n;

void Merge(int A[],int p, int q, int r)
{
    int i,j;
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1],R[n2+1];
    for(i=0; i<n1; i++)
	{
        L[i]=A[p+i];
    }
    for(j=0; j<n2; j++)
	{
        R[j]=A[q+j+1];
    }
    L[n1]=65535;
    R[n2]=65535;
    i=0;
    j=0;
    int k;
    for (k=p; k<r+1; k++)
	{
        if (L[i]<=R[j])
		{
            A[k]=L[i];
            i++;
        }
        else
		{
            A[k]=R[j];
            j++;
        }
    }
}

void MergeSort(int A[], int p, int r)
{
    int q;
    if(p<r)
	{
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
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
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\merge_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 

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
    
    MergeSort(p,0,n-1);
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\merge_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Merge Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Merge sort : %f seconds\n",t);
    return 0;
}
