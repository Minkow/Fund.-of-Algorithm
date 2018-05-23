#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 3000

typedef struct node   //���� 
{  
   int adjvex;  //�ڽӶ��� 
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
FILE *fp,*fp1;
char filename[300];
char filename1[300];

char *color[]={"red","orange","yellow","green","cyan","blue","purple","white","maroon","tan","pink","turquoise","yellowgreen","darkgrey","darkgoldenrod","chartreuse","lightsalmon"};
//graghwiz��ɫ��
 
int top;//ջ��ָ��
int Stack[729];
bool instack[729];// Ture��ʾ��ջ��
int DFN[729];//DFS���ʴ���
int LOW[729];//����ִ���� 
int Dindex;  //����ʱ�� 

char **p=color;//��ɫ�ַ�������ָ�� 

AdjList *adj=(AdjList *)malloc(sizeof(AdjList));

void CreateGraph(AdjList *adj,int m,int x[9999],int y[9999])  
{  
    int n,e,i,s,d; 
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
    for(i=1;i<=e;i++)   //��ȡ�ļ� 
    {  
    	s=x[i-1];
    	d=y[i-1];
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
    int n=adj->VexNum;//�������������Ҫ����ÿһ����
    EdgeNode *q=NULL;  
    int i;  
    for(i=1;i<=n;i++)  
    {  
        q=adj->vertex[i].firstedge;  
        while(q!=NULL)  
        {  
            fprintf(fp1,"%d->%d\n",adj->vertex[i].name,adj->vertex[q->adjvex].name);//grapgwiz���������� 
            q=q->next;  
        }  
    }  
}  

void tarjan(int u)  
{  
    int v;
	EdgeNode *q=NULL; 
    DFN[u]=LOW[u]=++Dindex; //��ֵ��ֵΪ����ʱ�� 
    Stack[++top]=u;  //u��ջ(ջ��) 
    instack[u]=true;  //��ʾu��ջ�� 
    for(q=adj->vertex[u].firstedge;q;q=q->next)//�����пɴ�ߵ�����  
    {  
        v=q->adjvex;  
        if (!DFN[v])		//����LOW[u]  
        {  
            tarjan(v);  
            if(LOW[v]<LOW[u])  
				LOW[u]=LOW[v]; //ȡMininum 
        }  
        else if (instack[v]&&DFN[v]<LOW[u])  
            LOW[u]=DFN[v];  
    }  
    
    if(DFN[u]==LOW[u])  //һ��ǿ��ͨ�������ҵ� 
    {  
    	fprintf(fp,"("); 
        do
        {
            v=Stack[top --];  
            instack[v]=false;  //v���γ�ջ 
            if(u==v) fprintf(fp,"%d",v); 
			else fprintf(fp,"%d ",v);  //fprintf��ʱ�临�ӶȲ���Ӱ��Ƚϴ󣬲���ʱ���ʱ���ע�͵��� 
			fprintf(fp1,"%d [shape=circle, style=filled, fillcolor=%s]\n",v,*p);    //graphwiz�����ɽڵ���Ϣ 
        }  
        while (u != v);//һֱ��v=u�������ڸ�ǿ��ͨ����  
        fprintf(fp,")\n");   //ͬ�� 
        p++;
    }  
}  

void solve(int m)  
{  
    int i;  
    top=Dindex=0;  
    memset(DFN,0,sizeof(DFN)); 
    for (i=1;i<=a[m];i++)   //�����н��ִ���㷨 
        if (!DFN[i])  
            tarjan(i); 
}  


int main()  
{  
    int i,j;
    int x[9999],y[9999];

	for(i=0;i<5;i++)
	{	
		sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\input\\size%d\\input.txt",i+1);
    	fp=fopen(filename, "r");
    	for(j=0;j<b[i];j++)
    	{
    		fscanf(fp,"%d,%d\n",&x[j],&y[j]);
		}
		CreateGraph(adj,i,x,y);
		fclose(fp);
	
	
		sprintf(filename,"D:\\code\\PB14011074-project4\\project1\\output\\size%d\\output1.txt",i+1);  
		fp=fopen(filename, "w");
		sprintf(filename1,"D:\\code\\PB14011074-project4\\project1\\output\\size%d\\outputgraph.dot",i+1);  
		fp1=fopen(filename1,"w");
		fprintf(fp1,"digraph g {\n");
		p=color;
		solve(i);  //ִ���㷨  
		fprintf(fp1,"\n");
		DisplayGraph(adj);
		fprintf(fp1,"\noverlap=false\nfontsize=12;\n}\n");
		fclose(fp);
	}
	
	return 0;
}  
