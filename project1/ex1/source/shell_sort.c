#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

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

void ShellSort(char A[][17],int n)
{
    int inc[5]={21,15,7,3,1},i,j,k=0;
    char t[17];
    while(inc[k]>n)
    	k++;//�ҵ��������� 
    	
    for(;k<5;k++)//�Զ�Ӧincrement������ 
    {
        for(i=inc[k];i<n;i++)//һ�����򣬽�d��Ԫ�ز��������� 
        {
        	if(cmp(A[i],A[i-inc[k]])<0)
        	{
        		strcpy(t,A[i]);
        		j=i-inc[k];
        		while(j>=0&&cmp(t,A[j])<0)//����R[i]����λ�� 
        		{
        			strcpy(A[j+inc[k]],A[j]);//���Ƽ�¼ 
        			j-=inc[k];//����ǰһ��¼ 
				}
				strcpy(A[j+inc[k]],t);//A[i]�����Ӧλ�� 
			}
		}
    }
}

                                 
int main()
{
	int inc[5]={21,15,7,3,1};
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
    
    sprintf(filename,"D:\\code\\PB14011074-project1\\ex1\\output\\shell_sort\\result_%d.txt",b);//����ֻ��Ϊ������ÿһ������֮ǰ���ļ�����д��·�����ѡ��� 
    
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
    
    ShellSort(p,n);

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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\shell_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Shell Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Shell sort : %f seconds\n",t);
    return 0;
}
