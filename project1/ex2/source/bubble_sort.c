#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

int n;

void BubbleSort(int r[],int m)
{
    int i,j,k,t,flag;
    i=m;
    while(i>0)
	{
        k=0;
        flag=1;
        for(j=1;j<i;j++)
		{
            if (r[j-1]>r[j])
			{
                t=r[j];
				r[j]=r[j-1];
				r[j-1]=t;
				flag=0;//����������flag��Ϊ0�������Ѿ�����֮��ֱ������ѭ���� 
                k=j;//�����һ�ν������±걣�棬�Ӷ�����ѭ���ڱȽϵĴ��� 
            }
        }
        if(flag==1) break;
        i=k;
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
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex2\\output\\bubble_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 

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
    
    BubbleSort(p,n);
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex2\\output\\bubble_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Bubble Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Bubble sort : %f seconds\n",t);
    return 0;
}
