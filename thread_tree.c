#include <stdio.h>
#include <stdlib.h>

enum Tag {link,thread};
typedef struct TNode{
    int ltag,rtag,val;
    struct TNode *lchild,*rchild;
}TNode,*Tree;

typedef struct ts{
    Tree *stackframe[100];
    int top;
}ts;

int setup_tree(Tree *T,int num[]);  //按照num中前序给定的元素,建立二叉树
int push(ts *s,Tree *t);
int pop(ts *s,Tree **t);
void Inorder_visit(ts *s,Tree *T);  //二叉树中序遍历
int Inorder_threading(ts *s,Tree *T);   //二叉树线索化
void thtree_visit(Tree T);  //线索树中序遍历

void thtree_visit(Tree T){
    Tree p=T->lchild;
    while(p!=T){
        while(p->ltag==link)    p=p->lchild;
        printf("%d\t",p->val);
        while(p->rtag==thread&&p->rchild!=T)    p=p->rchild,printf("%d\t",p->val);
        p=p->rchild;
    }
}

int Inorder_threading(ts *s,Tree *T){   //二叉树线索化
    Tree H=malloc(sizeof(TNode)),*pre,*p;
    if(!H)  return 0;
    H->lchild=*T,H->ltag=link,H->rtag=thread;
    if(!*T) H->rchild=NULL;
    else{
        pre=T,p=T;
        while(s->top>0||*p){
            while(*p){
                push(s,p);
                p=&(*p)->lchild;
            }
            pop(s,&p);
            if(!(*p)->lchild)   (*p)->lchild=*pre,(*p)->ltag=thread;
            if(!(*pre)->rchild) (*pre)->rchild=*p,(*pre)->rtag=thread;
            pre=p;
            p=&(*p)->rchild;
        }
        H->rchild=*pre,(*pre)->rchild=H,(*pre)->rtag=thread;
    }
    *T=H;
    return 1;
}

void Inorder_visit(ts *s,Tree *T){
    Tree *p=T;
    while(s->top>0||*p){
        while(*p){
            push(s,p);
            p=&(*p)->lchild;
        }
        pop(s,&p);
        printf("%d\t",(*p)->val);
        p=&(*p)->rchild;
    }
}

int push(ts *s,Tree *t){
    if(s->top>=0&&s->top<100){
        s->stackframe[s->top++]=t;
        return 1;
    }else   return 0;
}

int pop(ts *s,Tree **t){
    if(s->top>0&&s->top<=100){
        if(t)   *t=s->stackframe[--s->top];
        else    s->top--;
        return 1;
    }else   return 0;
}

int setup_tree(Tree *T,int *num){
    int val=num[num[0]];
    if(val){
        if(!(*T=malloc(sizeof(TNode)))) return 0;
        (*T)->val=num[num[0]++],(*T)->rtag=(*T)->ltag=link;
        (*T)->lchild=(*T)->rchild=NULL;
        setup_tree(&(*T)->lchild,num);
        setup_tree(&(*T)->rchild,num);
    }else{
        num[0]++;
    }
    return 1;
}

int main(){
    ts s={0}; 
    int num[]={1,4,2,1,0,0,3,8,0,0,7,0,0,5,0,0};
    Tree T=NULL; setup_tree(&T,num);
    Inorder_threading(&s,&T);
    puts(""); thtree_visit(T);
    return 0;
}