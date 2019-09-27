//
//  main.cpp
//  C++ Primer
//
//  Created by prmeasure on 8/20/19.
//  Copyright © 2019 simon. All rights reserved.

#include<iostream>
#define MAX_NODE 50
using namespace std;

//struct Node
//{
//    char data;      // data代表节点的数字(内容)
//    Node * L, * R;    // L,R 又分别为左右节点
////    Node* R;
//};

class Node{
public:
    char data;
    Node *L, *R;
    Node():L(NULL),R(NULL){}
};


//Node* T; // 创建一个指针T 指向这个二叉树的首地址（即这个二叉树的根节点）

// ================先创建一个二叉树 //
Node* creatNode(Node* &T)   // 先序创建
{
    char ch;
    if ((ch = getchar()) == '#')  // 按照一个二叉树的前序遍历输入若子节点为空就输入 #
    {
        T = NULL;
    }
    else
    {
        T = new Node;
        T->data = ch;
        creatNode(T->L);
        creatNode(T->R);
    }
    return T;
}
// ================完成二叉树的创建 //


// ================前序遍历 //
void PreOrder(Node* &T)
{
    if (T == NULL)//如果二叉树为空直接返回结束程序，下同
        return;
    else
    {
        cout << T->data << " ";  //先输出根节点的那个数字
        PreOrder(T->L);          //然后访问左孩子，开始递归
        PreOrder(T->R);          //左孩子访问完成，开始右孩子递归
    }
}

void PreOrderNor(Node *T)     //先序周游非递归算法(用栈实现)
{
    Node *st[MAX_NODE],*p = NULL;
    int top = -1;
    if(T != NULL)
    {
        top++;
        st[top] = T;                     //根节点入栈
        while(top>-1)                       //判断当栈非空时循环
        {
            p = st[top];                    //栈顶内容赋给p(即将输入的内容存放在p中)
            top--;
            cout<<p->data<<" ";             //输出栈顶内容
            if(p->R != NULL)       //右孩子入栈
            {
                top++;
                st[top] = p->R;
            }
            if(p->L != NULL)        //左孩子入栈
            {
                top++;
                st[top] = p->L;
            }
        }
        cout<<endl;
    }
}

// ================中序遍历 //
void InOrder(Node* &T)
{
    if (T == NULL)
        return;
    else
    {
        InOrder(T->L);
        cout << T->data << " ";
        InOrder(T->R);
    }
}

void InOrderNor(Node *T) //中序周游非递归实现(用栈实现)
{
    Node *st[MAX_NODE],*p =NULL;
    int top = -1;
    if(T !=NULL)
    {
        p = T; //将root赋给p
        while(top>-1 || p !=NULL)  //当栈不为空且root存在的时候，开始遍历左孩子
        {
            while(p !=NULL) //将root进栈，并将指针向左孩子方向移动，直到移动至叶子
            {
                top++;
                st[top] = p;
                p = p->L;
            } //左孩子部分已遍历完
            if(top>-1) //开始函数的输出部分
            {
                p = st[top]; //将左孩子放入栈中并准备输出
                top--;
                cout<<p->data<<" ";
                p = p->R; //将指针移动到具有相同父节点的右孩子上
            }
        }
        cout<<endl;
    }
}

// ================后序遍历 //
void PosOrder(Node* &T)
{
    if (T == NULL)
        return;
    else
    {
        PosOrder(T->L);
        PosOrder(T->R);
        cout << T->data << " ";
    }
}


void PosOrderNor(Node *T) //后序周游非递归实现(借用栈与下标)
{
    Node *st[MAX_NODE],*p =NULL;
    int flag,top = -1; //flag为所设下标
    if(T !=NULL)
    {
        do
        {
            while(T !=NULL)//将左节点入栈
            {
                top++;
                st[top] = T;//逐步实现将左孩子放进栈中
                T = T->L;//指针指向左孩子,直到叶子
            }
            p = NULL;//将p置空，防止野指针出现
            flag = 1;//设置下标
            while(top != -1 && flag)
            {
                T = st[top];
                if(T->R == p)//此时的叶节点的右孩子不存在的时候
                {
                    cout<<T->data<<" ";//直接输出当前节点的数据
                    top--;
                    p = T;//p指向刚刚被访问的节点
                }
                else
                {
                    T = T->R;//
                    flag = 0;
                }
            }
        }while(top != -1);
        cout<<endl;
    }
}

int main()
{
    cout << "输入一个二叉树(按照这个二叉树的前序遍历输入，若子节点为空就输入 #  ):" << endl;
    Node* T = creatNode(T);
    cout << "前序遍历:";
    PreOrderNor(T);
//    PreOrder(T);
    cout << endl;
    cout << "中序遍历:";
    InOrderNor(T);
    cout << endl;
    cout << "后序遍历:";
    PosOrderNor(T);
    cout << endl;
    delete    T;
    return 0;
}

//abd##e##cf##g##
//ma#c##be##f##

