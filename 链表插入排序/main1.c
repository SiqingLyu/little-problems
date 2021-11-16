#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//    定义链表中的节点
typedef struct node
{
    int member;                //    节点中的成员
    struct node *pNext;        //    指向下一个节点的指针
} Node,*pNode;

//    函数声明
pNode CreateList();                 //  创建链表函数
pNode select_sort(pNode );
void TraverseList(pNode );            //  遍历链表函数
int Insert_Node(pNode ,int ,int);    //    链表节点插入函数,第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据
int Del_Node(pNode,int );        //    删除链表节点,第一个参数是头节点，第二个参数是删除第几个节点，第三个作为
int main()
{
    pNode pHead = NULL;                //  定义初始化头节点，等价于 struct Node *pHead == NULL
    int data;                        // 作为Insert_Node函数的第三个参数
    int num;                        //    作为Inset_Node函数第二个参数
    char choose;
    int N,i;
    int return_val;
    printf("请输入N:");
     scanf("%d",&N);
               //  创建一个非循环单链表，并将该链表的头结点的地址付给pHead

    for(i=0; i<N*2; i++)
    {
       /* printf("是否还要进行如下操作：\n");
        printf("1.插入数据(A)      2.删除数据(D)      3.输出数据(Q)\n");
        printf("请输入：");*/
        scanf("%c",&choose);
        switch (choose)
        {
        case 'A':
        {
            if(pHead==NULL)
                 pHead = CreateList();
            else
            {
            printf("请输入要在第几个节点前插入数据：");
            scanf("%d",&num);
            printf("请输入要插入的数据：");
            scanf("%d",&data);
            if(Insert_Node(pHead,num,data) == 1)
            {
                printf("插入成功\n插入后的数据是：\n");
                TraverseList(pHead);
            }
            else
            {
                printf("插入失败\n");
            }
            printf("操作完成后的数据是：");
            TraverseList(pHead);

            }

        }continue;
        case 'D':
        {
            printf("请输入要删除第几个节点的数据：");
            scanf("%d",&num);
            return_val = Del_Node(pHead,num);
            if (return_val == 0)
            {
                printf("删除失败。\n");
            }
            else
            {
                printf("删除成功。删除的元素是：%d\n",return_val);
            }
            printf("操作完成后的数据是：");
            TraverseList(pHead);
        }continue;
        case 'Q':
            TraverseList(pHead);continue;
        }
    }

    return 0;
}

//    创建链表函数
pNode CreateList()
{
                                          //    用于下面循环
                                         //    用来存放有效节点的字数
    int val;                                        //    用于临时存放用户输入的数据
    pNode pHead = (pNode)malloc(sizeof(Node));        //  分配一个不存放有效数据的头结点
    pNode pTail = pHead;                            //    链表的最后一个节点
    pTail->pNext = NULL;                            //    最后一个节点的指针置为空


        printf("数值：");
        scanf("%d",&val);
        pNode pNew = (pNode)malloc(sizeof(Node));    //    为节点分配空间
        pNew->member = val;                            //将用户输入的数据赋给节点的成员
        pTail->pNext = pNew;                        //将最后一个节点的指针指向下一个新的节点
        pNew->pNext = NULL;                            //将新节点中的指针置为空
        pTail = pNew;                                //将新节点赋给最后的一个节点

    return pHead;                                    //返回头节点

}

//    遍历链表函数
void TraverseList(pNode pHead)
{
    //select_sort(pHead);
    pNode p = pHead->pNext;                            //将头节点的指针给予临时节点p
    while(NULL != p)                                //节点p不为空，循环
    {
        printf("%d ",p->member);
        p = p->pNext;
    }
    printf("\n");
    return ;
}

//    链表节点插入函数
//    第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据
int Insert_Node(pNode pHead, int front,int data)
{
    int i = 0;
    pNode _node = pHead;
    pNode pSwap;                                //    用于交换
    if ((front < 1) && (NULL != _node))        //判断用户输入的数据是否大于等于1,及_node是否为空
    {
        return 0;
    }
    while (i < front - 1)                    //通过循环使指针指向要插入哪个节点前的节点。说的自己都不懂了，还是看下面的图吧。
    {
        _node = _node->pNext;
        ++i;
    }
    pNode pNew = (pNode)malloc(sizeof(Node));

    pNew->member = data;                        //    把输入的数据赋给要插入的节点
    pSwap = _node->pNext;                        //    把下一个节点的地址，给用于交换的pSwap
    _node->pNext = pNew;                        //    把要插入的节点的地址，给上个节点的指针域
    pNew->pNext = pSwap;                        //    把插入节点的下一个节点的地址，给插入节点的指针域
    return 1;

}

//    删除链表节点函数
//    第一个参数是头节点，第二个参数是要删除第几个节点·······和上面的插入函数是不是很像
int Del_Node(pNode pHead,int back)
{
    int i = 0;
    int data;
    pNode _node = pHead;
    pNode pSwap;
    if ((back < 1) && (NULL == _node->pNext))
    {
        printf("删除失败！\n");
        return 0;
    }
    while(i < back-1)
    {
        _node = _node->pNext;
        ++i;
    }
    pSwap = _node->pNext;
    data = pSwap->member;
    _node->pNext = _node->pNext->pNext;
    free(pSwap);
    return data;
}

pNode select_sort(pNode head)
{
    pNode begin=NULL,end=NULL;    //有序链表的首尾结点指针
    pNode p;
    pNode min,premin;    //最小结点及其前一个结点
    if(!head)return NULL;
    while(head)
    {
        //循环找出无序链表中的最小结点min及其前一个结点premin
        p=head;
        min=p;
        while(p->pNext)
        {
            if(min->member>p->pNext->member)
            {
                premin=p;
                min=p->pNext;
            }
            p=p->pNext;
        }
        //1. 将min接入有序链表
        //如果有序链表为NULL
        if(begin==NULL)
        {
            begin=end=min;
        }
        else
        {
            end->pNext=min;
            end=min;
        }
        //2. 在无序链表中删除结点min
        if(min==head)
        {
            head=min->pNext;
        }
        else
        {
            premin->pNext=min->pNext;
        }
    }
    end->pNext=NULL;
    return begin;
}
