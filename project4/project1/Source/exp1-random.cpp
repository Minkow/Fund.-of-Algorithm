#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTEX_NUM 729

typedef char VertexType; 

typedef struct node   //���� 
{  
   int adjvex;  //�ڽӶ���
   int weight;  //Ȩֵ 
   node* next;  
}EdgeNode;  
  
typedef struct     //ͷ��� 
{  
   int name;  	//������� 
   EdgeNode* firstedge;  //ͷָ�� 
}VertexNode;  
  
typedef struct   
{   
    int VexNum,ArcNum;  //������ͱߵ����� 
	VertexNode vertex[MAX_VERTEX_NUM];  //ͷ������� 
}AdjList;  //

int a[5]={9,27,81,243,729};  //ͷ������ 
int b[5]={18,81,324,1215,4374};  //�߸���
FILE *fp;
char filename[300];

AdjList *adj=(AdjList *)malloc(sizeof(AdjList));

void CreateGraph(AdjList *adj,int m)  
{  
    int n,e,i,s,d,w; 
	n=a[m];
	e=b[m];   
    adj->VexNum=n;
    adj->ArcNum=e; 
    EdgeNode *q=NULL;  
    //��ʼ����ͷ���    
    for(i=1;i<=n;i++)  
    {  
        adj->vertex[i].name=i;  
        adj->vertex[i].firstedge=NULL;  
    }
    srand((unsigned) time(NULL));
    for(i=1;i<=e;i++)   //������ɱ� 
    {  
    	s=rand()%n+1;
    	d=rand()%n+1;  //�������ɣ������ر� 
        q=(EdgeNode *)malloc(sizeof(EdgeNode)); //����һ������  
        if(q==NULL)  
            return;  
        q->adjvex=d;   
        q->next=adj->vertex[s].firstedge;//�ڵ����κ���  
        adj->vertex[s].firstedge=q;  
    } 
}

void DisplayGraph(AdjList *adj)  
{  
    int n=adj->VexNum;//�������������Ҫ����ÿһ�����  
    EdgeNode *q=NULL;  
    int i;  
    for(i=1;i<=n;i++)  
    {  
        q=adj->vertex[i].firstedge;  
        while(q!=NULL)  
        {  
            //printf("%d,%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);
            fprintf(fp,"%d,%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);
            q=q->next; 
        }  
    }  
  
}  

int main()  
{  
    int i,j;      
    for(i=1;i<=5;i++)
    {
    sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\input\\size%d\\input.txt",i);  //���ɵ�ͼд���ļ� 
    fp=fopen(filename, "w");
    CreateGraph(adj,i-1);  
    DisplayGraph(adj);
    fclose(fp);
	}
	return 0;
}  
