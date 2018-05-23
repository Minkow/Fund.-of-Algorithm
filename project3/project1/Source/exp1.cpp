#include<stdio.h>
#include<stdlib.h>
#include<sys/unistd.h>

#define n 28//���ݹ�ģ 
#define INF 10000000//���������Ϊһ������ 

FILE *fp;

void MatrixChainOrder(int *p,int m[n+1][n+1],int s[n+1][n+1])
{
	int i,j,k,l,q;
	for(i=0;i<=n;++i)
		m[i][i] = 0;
	for(l=2;l<=n;l++)  //l��chain���� 
	{
		for(i=1;i<=n-l+1;i++)  //���㵱ǰl����С���� 
		{
			j=i+l-1; //��i��ʼ����i+l-1����������Ϊl��chain 
			m[i][j]=INF;  //����ʼ�� 
			for(k=i;k<=j-1;k++)  //������Ѱ�����Ż��� 
			{
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k; //��¼���ֵ�λ�� 
				}
			}
		}
	}
}

void PrintOptimalParens(int s[n+1][n+1],int i,int j)
{//�򵥵ĵݹ����������� 
	if(i==j)
	{
 		printf("A%d",i);
		fprintf(fp,"A%d",i);
	}
	else
	{
		printf("(");
		fprintf(fp,"(");
		PrintOptimalParens(s,i,s[i][j]);
		PrintOptimalParens(s,s[i][j]+1,j);
		printf(")");
		fprintf(fp,")");
	}
}

inline unsigned long long GetNTime()  
{  
    __asm("RDTSC");  
}//�����ã���¼��ǰcpu������ 

int main()
{
	int p[n+1];//p����chain�Ĺ�ģ 
	int m[n+1][n+1]={0};
	int s[n+1][n+1]={0};
	int i,j;
	long long start,end,t;	

	if((fp=fopen("D:\\code\\PB14011074-project3\\project1\\input\\input1.txt", "r"))==NULL)
	{
		printf("error\n");
		exit(0);
	}

	for(i=0;i<=n;i++)
	{
		fscanf(fp,"%d\n",&p[i]);
	}
	fclose(fp);//���ļ�
	
	fp=fopen("D:\\code\\PB14011074-project3\\project1\\Output\\output.txt","a");
	fprintf(fp,"n=%d:\n",n);
	start=GetNTime();
	MatrixChainOrder(p,m,s);
	end=GetNTime();
	t=end-start;	
	PrintOptimalParens(s,1,n);
	fprintf(fp,"\n");
	printf("\n");
	fclose(fp);
	
	fp=fopen("D:\\code\\PB14011074-project3\\project1\\Output\\time.txt","a");
	fprintf(fp,"n=%d takes %d CPU cycles\n",n,t);
	return 0;
}

