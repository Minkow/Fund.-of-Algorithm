#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define INF 65535 

int a[5]={9,27,81,243,729};
int b[5]={18,81,324,1215,4374};
int graph[729][729];//���ڽӾ�����ʽ��ʾͼ 
int d[729][729];   
int path[729][729]; //���Ա������·�� 
int cnt;//���ȼ��� 
FILE *fp;

void FloydWarshall(int n)
{
    int i,j,k;
    for(k=0;k<a[n];k++)
        for(i=0;i<a[n];i++)
            for(j=0;j<a[n];j++)
                if(d[i][k]!=INF&&d[k][j]!=INF&&d[i][j]>d[i][k]+d[k][j])
                {
                    d[i][j]=d[i][k]+d[k][j];
                    path[i][j]=k;        //i��jҪ����K�ڵ㣬ǰ������ 
                }
}

void Inf()
{//��ʼ��Ϊ������ 
	int i,j;
	for(i=0;i<729;i++)
		for(j=0;j<729;j++)
		{
            graph[i][j]=INF;  
        }
}

void Init()
{//����graph��ʼ��d��ͬʱ��ǰ������Ϊ�� 
	int i,j;
	for(i=0;i<729;i++)
		for(j=0;j<729;j++)
		{
            d[i][j]=graph[i][j];
            path[i][j]=0;     
        }
}

void ShortestPath(int i,int j,int k)//����ǰ�����󣬵ݹ�ʵ��������·�� 
{
    if(path[i][j]==0)
    {
    	if(j==k) fprintf(fp,"%d",j);
		else fprintf(fp,"%d->", j);
        return;
    }
    else
    {
    	cnt++;
        ShortestPath(i, path[i][j],k);
        ShortestPath(path[i][j],j,k);
    }
}

int main()
{
	char filename[300];
	int weight,x,y,i,j,k;
	LARGE_INTEGER num;
    long long start,end,freq;
    double t;
	
	for(i=0;i<5;i++)
	{
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\input\\size%d\\input.txt",i+1);
		fp=fopen(filename, "r");
		  //���ļ� 
		Inf();
		for(j=0;j<b[i];j++)
		{
			fscanf(fp,"%d,%d %d\n",&x,&y,&weight);
			graph[x][y]=weight;
		}
		fclose(fp);
		QueryPerformanceFrequency(&num);//����winapi�е�΢�뼶���ʱ�����ڽ�С�������� 
		freq=num.QuadPart;
		QueryPerformanceCounter(&num);
		start=num.QuadPart;
		Init();
		FloydWarshall(i);
		QueryPerformanceCounter(&num);
    	end=num.QuadPart;
    	t=(double)(1000.0*(end-start)/freq);
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\output\\size%d\\output2.txt",i+1);
		fp=fopen(filename, "w");
		for(j=0;j<a[i];j++)
		{
			for(k=0;k<a[i];k++)
			{
				if(j!=k)
				{
					fprintf(fp,"(");
					fprintf(fp,"%d->",j);
					cnt=1;
					ShortestPath(j,k,k);
					fprintf(fp,")");
					fprintf(fp,"   Path Length is %d",cnt);
					fprintf(fp,"\n");
				}
			}
		}
		fclose(fp);
		sprintf(filename,"D:\\code\\PB14011074-project4\\project2\\output\\size%d\\time2.txt",i+1);
		fp=fopen(filename, "w");
		fprintf(fp,"Exp%d takes %f ms",i+1,t);
		fclose(fp);
	}
	
	
	
}
