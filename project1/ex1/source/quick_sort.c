#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;//ȫ�ֱ�����������¼����
int heapsize;

int cmp(char *a,char *b)
{
    if(strlen(a)!=strlen(b)) 
    {
    	return strlen(a)-strlen(b);
	}
    else
	{
        return strcmp(a,b);
    }
}
//�������򣬵�����strcmp�����ǵ��������Ż��������strcmp����ʱ��϶̣�����Ӱ�첻��
//�˴�����ֵ������1����0�����������߸��� 
 

int Partition(char A[][17],int p,int r)
{
    int j;
    char x[17],t[17];
    strcpy(x, A[r]);
    int i=p-1;
    for (j=p; j<r; j++)
	{
        if (cmp(A[j],x)<=0)
		{
            i++;
            strcpy(t,A[j]);
            strcpy(A[j],A[i]);
            strcpy(A[i],t);
        }
    }
    strcpy(t, A[i+1]);
    strcpy(A[i+1], A[r]);
    strcpy(A[r], t);
    return i+1;
}

void QuickSort(char A[][17],int p,int r)
{
	int q;
    if(p<r)
	{
        q=Partition(A, p, r);
        QuickSort(A, p, q-1);
        QuickSort(A, q+1, r);
    }
}
//......������д�� 

int main()
{
    //clock_t start,finish;
    LARGE_INTEGER num;
    long long start,end,freq;
    double t;
    FILE*fp;
    int b,i;
    char (*p)[17];
    char filename[300];
    
    printf("input base x of the length(3^x)\n");
    scanf("%d",&b);
    n=pow(3,b);
    
    heapsize=n-1;
    
    p=(char (*)[17])malloc(sizeof(char)*17*n);//��ά���飬�����Է����ڴ�ռ� 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\heap_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 
    
    for(i=0;i<n; i++)
	{
        fscanf(fp,"%s\n",p[i]);
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
        fprintf(fp, "%s\n",p[i]);
    }
    fclose(fp);//дoutput�ļ� 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\quick_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Quick Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Quick sort : %f seconds\n",t);
    return 0;
}
