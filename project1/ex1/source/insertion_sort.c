#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

int n;//ȫ�ֱ�����������¼����

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
 
void InsertionSort(char A[][17])
{
    int i,j;
    char key[17];
    for (j=1; j<n; j++)
	{
        strcpy(key, A[j]);
        i=j-1;
        while(i>=0&&cmp(A[i],key)>0)
		{
            strcpy(A[i+1], A[i]);
            i--;
        }
        strcpy(A[i+1], key);
    }
}
//���Ž̲�д�� 

int main()
{
	//clock_t start,end;
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
    
    p=(char (*)[17])malloc(sizeof(char)*17*n);//��ά���飬�����Է����ڴ�ռ� 
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\input\\input_strings.txt", "r"))==NULL)
	{
        printf("error\n");
        exit(0);
    }
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\insertion_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 
    
    for(i=0;i<n; i++)
	{
        fscanf(fp,"%s\n",p[i]);
    }
    fclose(fp);//���ļ�
    
    //start=clock();//��ʱ������clock���������ڽϴ�������� 
    QueryPerformanceFrequency(&num);//����winapi�е�΢�뼶���ʱ�����ڽ�С�������� 
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start=num.QuadPart;
    InsertionSort(p);
    QueryPerformanceCounter(&num);
    end=num.QuadPart;
    //finish=clock();//��ʱ���� 
    //t=(double)(finish-start)/CLK_TCK;
    t=(double)(end-start)/freq;
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\insertion_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Insertion Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Insertion sort : %f seconds\n",t);
    return 0;
}
