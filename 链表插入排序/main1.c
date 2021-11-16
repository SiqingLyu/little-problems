#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//    ���������еĽڵ�
typedef struct node
{
    int member;                //    �ڵ��еĳ�Ա
    struct node *pNext;        //    ָ����һ���ڵ��ָ��
} Node,*pNode;

//    ��������
pNode CreateList();                 //  ����������
pNode select_sort(pNode );
void TraverseList(pNode );            //  ����������
int Insert_Node(pNode ,int ,int);    //    ����ڵ���뺯��,��һ��������ͷ�ڵ㣬�ڶ���������Ҫ�ڵڼ����ڵ�ǰ���룬������������Ҫ���������
int Del_Node(pNode,int );        //    ɾ������ڵ�,��һ��������ͷ�ڵ㣬�ڶ���������ɾ���ڼ����ڵ㣬��������Ϊ
int main()
{
    pNode pHead = NULL;                //  �����ʼ��ͷ�ڵ㣬�ȼ��� struct Node *pHead == NULL
    int data;                        // ��ΪInsert_Node�����ĵ���������
    int num;                        //    ��ΪInset_Node�����ڶ�������
    char choose;
    int N,i;
    int return_val;
    printf("������N:");
     scanf("%d",&N);
               //  ����һ����ѭ�������������������ͷ���ĵ�ַ����pHead

    for(i=0; i<N*2; i++)
    {
       /* printf("�Ƿ�Ҫ�������²�����\n");
        printf("1.��������(A)      2.ɾ������(D)      3.�������(Q)\n");
        printf("�����룺");*/
        scanf("%c",&choose);
        switch (choose)
        {
        case 'A':
        {
            if(pHead==NULL)
                 pHead = CreateList();
            else
            {
            printf("������Ҫ�ڵڼ����ڵ�ǰ�������ݣ�");
            scanf("%d",&num);
            printf("������Ҫ��������ݣ�");
            scanf("%d",&data);
            if(Insert_Node(pHead,num,data) == 1)
            {
                printf("����ɹ�\n�����������ǣ�\n");
                TraverseList(pHead);
            }
            else
            {
                printf("����ʧ��\n");
            }
            printf("������ɺ�������ǣ�");
            TraverseList(pHead);

            }

        }continue;
        case 'D':
        {
            printf("������Ҫɾ���ڼ����ڵ�����ݣ�");
            scanf("%d",&num);
            return_val = Del_Node(pHead,num);
            if (return_val == 0)
            {
                printf("ɾ��ʧ�ܡ�\n");
            }
            else
            {
                printf("ɾ���ɹ���ɾ����Ԫ���ǣ�%d\n",return_val);
            }
            printf("������ɺ�������ǣ�");
            TraverseList(pHead);
        }continue;
        case 'Q':
            TraverseList(pHead);continue;
        }
    }

    return 0;
}

//    ����������
pNode CreateList()
{
                                          //    ��������ѭ��
                                         //    ���������Ч�ڵ������
    int val;                                        //    ������ʱ����û����������
    pNode pHead = (pNode)malloc(sizeof(Node));        //  ����һ���������Ч���ݵ�ͷ���
    pNode pTail = pHead;                            //    ��������һ���ڵ�
    pTail->pNext = NULL;                            //    ���һ���ڵ��ָ����Ϊ��


        printf("��ֵ��");
        scanf("%d",&val);
        pNode pNew = (pNode)malloc(sizeof(Node));    //    Ϊ�ڵ����ռ�
        pNew->member = val;                            //���û���������ݸ����ڵ�ĳ�Ա
        pTail->pNext = pNew;                        //�����һ���ڵ��ָ��ָ����һ���µĽڵ�
        pNew->pNext = NULL;                            //���½ڵ��е�ָ����Ϊ��
        pTail = pNew;                                //���½ڵ㸳������һ���ڵ�

    return pHead;                                    //����ͷ�ڵ�

}

//    ����������
void TraverseList(pNode pHead)
{
    //select_sort(pHead);
    pNode p = pHead->pNext;                            //��ͷ�ڵ��ָ�������ʱ�ڵ�p
    while(NULL != p)                                //�ڵ�p��Ϊ�գ�ѭ��
    {
        printf("%d ",p->member);
        p = p->pNext;
    }
    printf("\n");
    return ;
}

//    ����ڵ���뺯��
//    ��һ��������ͷ�ڵ㣬�ڶ���������Ҫ�ڵڼ����ڵ�ǰ���룬������������Ҫ���������
int Insert_Node(pNode pHead, int front,int data)
{
    int i = 0;
    pNode _node = pHead;
    pNode pSwap;                                //    ���ڽ���
    if ((front < 1) && (NULL != _node))        //�ж��û�����������Ƿ���ڵ���1,��_node�Ƿ�Ϊ��
    {
        return 0;
    }
    while (i < front - 1)                    //ͨ��ѭ��ʹָ��ָ��Ҫ�����ĸ��ڵ�ǰ�Ľڵ㡣˵���Լ��������ˣ����ǿ������ͼ�ɡ�
    {
        _node = _node->pNext;
        ++i;
    }
    pNode pNew = (pNode)malloc(sizeof(Node));

    pNew->member = data;                        //    ����������ݸ���Ҫ����Ľڵ�
    pSwap = _node->pNext;                        //    ����һ���ڵ�ĵ�ַ�������ڽ�����pSwap
    _node->pNext = pNew;                        //    ��Ҫ����Ľڵ�ĵ�ַ�����ϸ��ڵ��ָ����
    pNew->pNext = pSwap;                        //    �Ѳ���ڵ����һ���ڵ�ĵ�ַ��������ڵ��ָ����
    return 1;

}

//    ɾ������ڵ㺯��
//    ��һ��������ͷ�ڵ㣬�ڶ���������Ҫɾ���ڼ����ڵ㡤������������������Ĳ��뺯���ǲ��Ǻ���
int Del_Node(pNode pHead,int back)
{
    int i = 0;
    int data;
    pNode _node = pHead;
    pNode pSwap;
    if ((back < 1) && (NULL == _node->pNext))
    {
        printf("ɾ��ʧ�ܣ�\n");
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
    pNode begin=NULL,end=NULL;    //�����������β���ָ��
    pNode p;
    pNode min,premin;    //��С��㼰��ǰһ�����
    if(!head)return NULL;
    while(head)
    {
        //ѭ���ҳ����������е���С���min����ǰһ�����premin
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
        //1. ��min������������
        //�����������ΪNULL
        if(begin==NULL)
        {
            begin=end=min;
        }
        else
        {
            end->pNext=min;
            end=min;
        }
        //2. ������������ɾ�����min
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
