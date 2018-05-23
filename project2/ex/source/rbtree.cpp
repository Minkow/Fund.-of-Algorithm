#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/unistd.h> //����RDTSC�Ĵ�����ͷ�ļ� 

FILE *fp;
char filename[300];

enum NodeColor{RED,BLACK};//ö������RED=0 BLACK=1 

struct RBTreeNode
{
	int size,key;
	enum NodeColor color;
	RBTreeNode *left,*right,*p;//��������(����ֵcolor,size) 
};

struct RBTree
{
	RBTreeNode *root,*nil;//�������ݽṹ��root,nil��ΪRBTreeNode�������� 
};

void LeftRotate(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *y=x->right;
	x->right=y->left;
	if(y->left!=T->nil)
		y->left->p=x;
	y->p=x->p;
	if(x->p==T->nil)
		T->root=y;
	else if(x==x->p->left)
		x->p->left=y;
	else x->p->right=y;
	y->left=x;
	x->p=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;//��ת������ʹ��������size����ʧЧ������ά������ 
}	//�Խ̲Ĵ����ʵ�֣��������Գ� 

void RightRotate(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *y=x->left;
	x->left=y->right; //y��rchild��Ϊx��lchild
	if(y->right!=T->nil)
		y->right->p=x;
	y->p=x->p; //y��Ϊ�µĸ� 
	if(x->p==T->nil)
		T->root=y;
	else if(x==x->p->right)
		x->p->right=y;
	else x->p->left=y;
	y->right=x;//x��Ϊy��rchild 
	x->p=y;
	y->size=x->size;
	x->size=x->left->size+x->right->size+1;//��ת������ʹ��������size����ʧЧ������ά������ 
}	//�Խ̲Ĵ����ʵ�֣������������е�left<->right���� 

void RBInsertFixup(RBTree *T,RBTreeNode *z)
{
	RBTreeNode *y;
	while(z->p->color==RED)
	{
		if(z->p==z->p->p->left)//zΪ��ߵĽڵ㣬��һ��ΪzΪ�ұ߽ڵ㣬������ȫ�Գ� 
		{
			y=z->p->p->right;
			if(y->color==RED)//case1������Ϊ��ɫ 
			{
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else 
			{
				if(z==z->p->right)//case2
				{
					z=z->p;
					LeftRotate(T,z);//����ת��Ϊcase3 
				}
				z->p->color=BLACK;//case3
				z->p->p->color=RED;
				RightRotate(T,z->p->p);
			}
		}
		
		else
		if(z->p==z->p->p->right)
		{
			y=z->p->p->left;
			if(y->color==RED)
			{
				z->p->color=BLACK;
				y->color=BLACK;
				z->p->p->color=RED;
				z=z->p->p;
			}
			else 
			{
				if(z==z->p->left)
				{
					z=z->p;
					RightRotate(T,z);
				}
				z->p->color=BLACK;
				z->p->p->color=RED;
				LeftRotate(T,z->p->p);
			}
		}
		T->root->color=BLACK;
	}
}//�Խ̲ĵ�ʵ�� 

void RBInsert(RBTree *T,RBTreeNode *z)//���룺������ȷ��λ��֮��ִ�в��롣 
{
	RBTreeNode *x,*y;
	y=T->nil;
	x=T->root;	
	while(x!=T->nil)
	{
		x->size++;// ���룺�²����㵽������,ÿ������size+1
		y=x;
		if(z->key<x->key)//����key�Ĵ�Сȷ������ 
			x=x->left;
		else 
			x=x->right;
	}	
	z->p=y;
	if(y==T->nil) 
		T->root=z;
	else 
	{
		if(z->key<y->key)
			y->left=z;
    	else
			y->right=z;
	}
	z->left=T->nil;
	z->right=T->nil;
	z->color=RED;
	z->size=1;
	z->left->size=0;
	z->right->size=0;

	RBInsertFixup(T,z);//�޸��������ɫ���� 
}//�Խ̲��ϴ����ʵ�� 

void RBTransplant(RBTree *T,RBTreeNode *u,RBTreeNode *v)//����u,v�滻 
{
	if(u->p==T->nil)
		T->root=v;
	else if(u==u->p->left)
		u->p->left=v;
	else 
		u->p->right=v;
	v->p=u->p;
}

RBTreeNode *TreeMinimum(RBTree *T,RBTreeNode *x)//��С�ؼ��֣�����ָ�� 
{
	while(x->left!=T->nil)
	{
		x=x->left;
	}
	return x;
} 

void RBDeleteFixup(RBTree *T,RBTreeNode *x)
{
	RBTreeNode *w;
	while(x!=T->root&&x->color==BLACK)//��x�ĺ����������ƶ� 
	{
		if(x==x->p->left)//���������ҶԳƵ� 
		{
			w=x->p->right;
			if(w->color==RED)
			{//case1:�ı�w��x.p����ɫ�ٽ�����ת��ת����������� 
				w->color=BLACK;
				x->p->color=RED;
				LeftRotate(T,x->p);
				w=x->p->right;
			}
			if(w->left->color==BLACK&&w->right->color==BLACK)
			{//case2:x��brother�Ǻڣ�����w�������ӽڵ㶼�Ǻ�
				w->color=RED;
				x=x->p;
			}
			else
			{
				if(w->right->color==BLACK)
				{//case3��x��brother�Ǻ�ɫ��w��lchild�Ǻ�,rchild�Ǻڡ�  
					w->left->color=BLACK;
					w->color=RED;
					RightRotate(T,w);
					w=x->p->right;//����w��w.left����ɫ����תת��Ϊcase4  
				}
			w->color=x->p->color;//case4��wΪ�ڣ�w��rchildΪ�� 
			x->p->color=BLACK;
			w->right->color=BLACK;
			LeftRotate(T,x->p);
			x=T->root;
			}
		}
			
		else if(x==x->p->right)
		{
			w=x->p->left;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->p->color=RED;
				RightRotate(T,x->p);
				w=x->p->left;
			}
			if(w->right->color==BLACK&&w->left->color==BLACK)
			{
				w->color=RED;
				x=x->p;
			}
			else
			{
			if(w->left->color==BLACK)
				{
					w->right->color=BLACK;
					w->color=RED;
					LeftRotate(T,w);
					w=x->p->left;
				}
			w->color=x->p->color;
			x->p->color=BLACK;
			w->left->color=BLACK;
			RightRotate(T,x->p);
			x=T->root;
			}
		}
	}
	x->color=BLACK;
}

void RBDelete(RBTree *T,RBTreeNode *z)
{
	RBTreeNode *x,*y,*v;
	y=z;
	v=z->p;
	enum NodeColor yocolor=y->color;
	if(z->left==T->nil)//lchildΪnil�������������nilֻ��һ����û��child��ֱ��ɾ֮����ֲ������������ 
	{
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}//ɾ������ɾ�����֮�ϵ�ÿ������size-1��������ļ������������֡� 
		x=z->right;
		RBTransplant(T,z,z->right);//�������滻�� 
	}
	else if(z->right==T->nil)//������Գ� 
	{
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}
		x=z->left;
		RBTransplant(T,z,z->left);
	}
	else//child��Ϊnil����ʱ�ҵ���������Сֵ���滻��ɾ��ԭ������Сֵ�ڵ�λ�þͿ����� 
	{
		y=TreeMinimum(T,z->right);//�ҵ���������Сֵ 
		v=y->p;
		y->size=z->size-1;//���yȡ��z��size-1 
		while(v!=T->nil)
		{
			v->size--;
			v=v->p;
		}
		yocolor=y->color;
		x=y->right;
		if(y->p==z)//case1:��������Сֵ������rchild 
			x->p=y;
		else//case2:����rchild 
		{
			RBTransplant(T,y,y->right);
			y->right=z->right;
			y->right->p=y;
		}
		RBTransplant(T,z,y);//y�滻z 
		y->left=z->left;
		y->left->p=y;
		y->color=z->color;//�ָ�y֮�ϵĺ������ɫ���� 
	}
	if(yocolor==BLACK)
		RBDeleteFixup(T,x);
}

RBTreeNode *RBSelect(RBTreeNode *x,int i)//���Ҹ���Ԫ�� 
{
	int r;
	r=x->left->size+1;
	if(i==r)
	{
		return x;
	}
	else if(i<r)//С��ȥ����ң�����ȥ�ұߣ��ݹ�ʵ�� 
		return RBSelect(x->left,i);
	else
		return RBSelect(x->right,i-r);
}

int RBRank(RBTree *T,RBTreeNode *x)//ȷ��Ԫ�ص��� 
{
	RBTreeNode *y;
	int r;
	r=x->left->size+1;
	y=x;
	while(y!=T->root)
	{
		if(y==y->p->right)
			r=r+y->p->left->size+1;
		y=y->p;
	}
	return r;
}

void PreOrder(RBTree *T,RBTreeNode *x)//ǰ��������ݹ�ʵ�֣������ơ� 
{
	if(x!=T->nil)
	{
		fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		PreOrder(T,x->left);
		PreOrder(T,x->right);
	}
}

void InOrder(RBTree *T,RBTreeNode *x)
{  
    if(x!=T->nil) 
    {         
        InOrder(T,x->left);  
        fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
        printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
        InOrder(T,x->right);  
    } 
}  

void PostOrder(RBTree *T,RBTreeNode *x)
{
	if(x!=T->nil)
	{
		PostOrder(T,x->left);
		PostOrder(T,x->right);
		fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
		printf("key:%d\tcolor:%d\tsize:%d\n",x->key,x->color,x->size);
	}
}

inline unsigned long long GetNTime()//������RDTSC�Ĵ��������汣��Ϊʱ�������� 
{
       __asm ("RDTSC");
}

int main()
{
    long long start,end,freq,s1,s2,total=0;
    RBTree *T=new RBTree;
    int i,j,n;
	
	T->nil=new RBTreeNode;
	T->nil->size=0;
	T->nil->key=151;//151Ϊ���ֵ 
	T->nil->color=BLACK;
	T->nil->left=NULL;
	T->nil->right=NULL;
	T->nil->p=NULL;
	T->root=T->nil;//������ĳ�ʼ�� 
	
	scanf("%d",&n);
	int *p=new int[n];
	long long *t=new long long[n/10];
	RBTreeNode *q=new RBTreeNode[n];//Ԥ�ȷ���ýڵ���ڴ�ռ� 
		
	if((fp=fopen("D:\\code\\PB14011074-project2\\ex\\input\\input.txt", "r"))==NULL)
	{
        printf("error\n");
    }
    
    for(i=0;i<n;i++)
	{
        fscanf(fp,"%d\n",&p[i]);
    }
    fclose(fp);
    
    for(i=0;i<n/10;i++)
    {
    	start=GetNTime();
    	for(j=0;j<10;j++)
    	{	
			(q[i*10+j]).key=p[i*10+j];
    		RBInsert(T,&q[i*10+j]);
    	}
    	end=GetNTime();
    	t[i]=end-start;
	}
//����Ϊ����ڵ㣬10��һ�� 
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\preorder.txt",n);
	fp=fopen(filename,"a");	
    PreOrder(T,T->root);
	fclose(fp);
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\inorder.txt",n);
	fp=fopen(filename,"a");	
    InOrder(T,T->root);
    fclose(fp);
	
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\postorder.txt",n);
	fp=fopen(filename,"a");	
    PostOrder(T,T->root);
    fclose(fp);

	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\time1.txt",n);
	fp=fopen(filename,"w");
	for(i=0;i<n/10;i++)
	{
		fprintf(fp, "Insert up to Node %d0 takes %d cpu cycles\n",i+1,t[i]);
		printf("Insert up to Node %d0 takes %d cpu cycles\n",i+1,t[i]);
	}
	
	for(i=0;i<n/10;i++)
	{
		total+=t[i];
	}
	
	fprintf(fp,"Total takes %d cpu cycles",total);
	printf("Total takes %d cpu cycles",total);
	
	fclose(fp);
	 
//����Ϊɾ�� 
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\delete_data.txt",n);
	fp=fopen(filename,"a");
	
	RBTreeNode *r=new RBTreeNode;

	r=RBSelect(T->root,n/4);	
	fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	printf("key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	start=GetNTime();
	RBDelete(T,r);
	end=GetNTime();
    s1=end-start;
    
    r=RBSelect(T->root,n/2-1);
    fprintf(fp,"key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	printf("key:%d\tcolor:%d\tsize:%d\n",r->key,r->color,r->size);
	start=GetNTime();
	RBDelete(T,r);
	end=GetNTime();
    s2=end-start;
    
    fclose(fp);
    
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\time2.txt",n);
    fp=fopen(filename,"a");
    fprintf(fp,"Delete node n/4 takes %d cpu cycles\n",s1);
	fprintf(fp,"Delete node n/2 takes %d cpu cycles\n",s2);
	printf("Delete node n/4 takes %d cpu cycles\n",s1);
	printf("Delete node n/2 takes %d cpu cycles\n",s2);
    fclose(fp);		
	sprintf(filename,"D:\\code\\PB14011074-project2\\ex\\output\\size%d\\delete_inorder.txt",n);
	fp=fopen(filename,"a");
    InOrder(T,T->root);
    fclose(fp);

	return 0;
}

