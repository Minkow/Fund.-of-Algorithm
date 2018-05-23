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
 

void MaxHeapify(char A[][17],int i)
{
    int l=2*i+1;//=LEFT(i)
    int r=2*(i+1);//=RIGHT(i)
    int largest;
    char ex[17];
    if(l<=heapsize&&cmp(A[l], A[i])>0)
        largest=l;
    else
        largest=i;
    if(r<=heapsize&&cmp(A[r], A[largest])>0)
        largest=r;
    if(largest!=i)
	{
        strcpy(ex,A[i]);
        strcpy(A[i],A[largest]);
        strcpy(A[largest],ex);
        MaxHeapify(A,largest);
    }
}

void BuildMaxHeap(char A[][17])
{
    int i;
    for(i=(n-1)/2;i>=0;i--)
        MaxHeapify(A,i);
}

void HeapSort(char A[][17])
{
	int i;
    BuildMaxHeap(A);
    char ex[17];
    for (i=n-1;i>0;i--)
	{
        strcpy(ex, A[i]);
        strcpy(A[i], A[0]);
        strcpy(A[0], ex);//exchange(A[1] with A[i]
        heapsize--;
        MaxHeapify(A, 0);
    }
}
//���ϣ�ȫ��������д�� 

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
    
    HeapSort(p);
    
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
    
    if((fp=fopen("D:\\code\\PB14011074-project1\\ex1\\output\\heap_sort\\time.txt", "a"))==NULL)//д��rusult_i.txt�� 
	{
        printf("error\n");
        exit(0);
    }
    fprintf(fp, "Heap Sort at base %d takes %f seconds\n",b,t);
    fclose(fp);//дtime�ļ� 
    
    printf("Heap sort : %f seconds\n",t);
    return 0;
}
