//
//  main.cpp
//  C++ Primer
//
//  Created by prmeasure on 8/20/19.
//  Copyright © 2019 simon. All rights reserved.
/*
 链表相加：
     给定两个链表，分别表示两个非负整数。它们的数字逆序存储在链表中，且每个结点只存储一个数字，计算两个数的和，并且返回和的链表头指针。
     如：输入：2→4→3、5→6→4，输出：7→0→8
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

//链表节点定义：value-节点，pNext-指向下一个节点的指针
typedef struct tagSNode{
    int value;
    //结构体嵌套
    tagSNode* pNext;
    //初始化节点
    tagSNode(int v):value(v),pNext(NULL) {}
}SNode;

//打印链表
void Print(SNode* pHead){
    SNode* p = pHead->pNext;
    while(p){
        cout<<p->value<<" ";
        p = p->pNext;
    }
    cout<<endl;
}
//删除分配结点空间
void Destroy(SNode* pHead){
    SNode* p = pHead->pNext;
    while(p){
        pHead->pNext = p->pNext;//与头插法相反
        delete p;
        p = pHead->pNext;
    }
    delete pHead;
}

//链表相加
SNode* ListAdd(SNode* pHead1,SNode* pHead2){
    SNode* pSum = new SNode(0);
    SNode* pTail = pSum;       //新结点插入pTail的后面
    SNode* p1 = pHead1->pNext;
    SNode* p2 = pHead2->pNext;
    SNode* pCur = NULL;
    int carry = 0;             //进位
    int value;
    //处理两者都存在的加法
    while(p1&&p2){        // while(p1&&p2)中表示p1和p2都不为空指针
        value = p1->value + p2->value +carry;
        carry = value / 10;
        value %= 10;
        pCur = new SNode(value);
        pTail->pNext = pCur;
        pTail = pCur;
        p1 = p1->pNext;
        p2 = p2->pNext;
    }

    //处理长的链表
    SNode* p = p1 ? p1 : p2;
    while(p){
        value = p->value +carry;
        carry = value / 10;
        value %= 10;
        pCur = new SNode(value);
        pTail->pNext = pCur;
        pTail = pCur;
        
        p = p->pNext;
    }
    //处理可能存在的进位
    if(carry!=0){
        pTail->pNext = new SNode(carry);
    }
    return pSum;
}

int main()
{
    int p1[3] ={3,4,2};
    int p2[3] ={4,6,5} ;
    
    // 创建第一个链表
    SNode* pHead1 = new SNode(0);
    for(int i=0;i<sizeof(p1)/sizeof(p1[0]);i++){
        SNode* p = new SNode(p1[i]);
        p->pNext = pHead1->pNext;
        pHead1->pNext = p;
    }
    // 创建第二个链表
    SNode* pHead2 = new SNode(0);
    for(int i=0;i<sizeof(p2)/sizeof(p2[0]);i++){
        SNode* p = new SNode(p2[i]);
        p->pNext = pHead2->pNext;
        pHead2->pNext = p;
    }
    Print(pHead1);
    Print(pHead2);
    SNode* pSum = ListAdd(pHead1,pHead2);
    Print(pSum);
    Destroy(pHead1);
    Destroy(pHead2);
    Destroy(pSum);
    return 0;
}

