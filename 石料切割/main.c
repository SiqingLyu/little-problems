#include <stdio.h>
#include <stdlib.h>
#define MAX2 1000
#define MAX 10     //ʯ��ģ���������
typedef struct stone
{
    float width;
    float height;
    float s;
} Stone,*pStone;
typedef struct curplan
{
    float cs[MAX2];//�洢��ͬ���������
} Curplan,*pCurp;
//int Cursum=0;
int quan;    // ȫ�ֱ�������Cursum��ͬ����
pCurp StoneCutter(pStone st,Stone remainst, int n,pCurp CurS,float S,int Cursum) //�ݹ�ѭ����ö�����п��ܵķ����������������ȡ����
{
    int i,j;
    float temp;   //�����ݴ�����
    int flag=0;  //flag���ڱ�־ö�����Ƿ��һ�ν��б���ѭ��
    for(i=0; i<n; i++)    //�����Ϊ�������
    {
        if(remainst.height<st[i].height || remainst.width<st[i].width)
            continue;
        if(remainst.height == st[i].height && remainst.width == st[i].width)
        {
            if(flag!=0)
            {
                Cursum++;
                quan++;
                CurS->cs[quan]+=st[i].s;
            }
            else
            {
                CurS->cs[Cursum]+=st[i].s;
            }
            return CurS;
        }
        if(remainst.height>st[i].height&&remainst.width==st[i].width)
        {
            if(flag!=0)
            {
                Cursum++;
                quan++;
                CurS->cs[quan]=S+st[i].s;
                temp=remainst.height;
                remainst.height-=st[i].height;

                StoneCutter(st,remainst,n,CurS, CurS->cs[quan],quan);
                remainst.height=temp;
            }
            else{
                 CurS->cs[Cursum]=S+st[i].s;
                temp=remainst.height;
                remainst.height-=st[i].height;

                StoneCutter(st,remainst,n,CurS, CurS->cs[Cursum],Cursum);
                remainst.height=temp;
            }


            flag=1;
        }
        if(remainst.height == st[i].height&&remainst.width>st[i].width)
        {
            if(flag!=0){
                Cursum++;
                quan++;
            temp=remainst.width;
            remainst.width-=st[i].width;
            CurS->cs[quan]=S+st[i].s;
            StoneCutter(st,remainst,n,CurS, CurS->cs[quan],quan);
            remainst.width=temp;
            }
            else{
                temp=remainst.width;
            remainst.width-=st[i].width;
            CurS->cs[Cursum]=S+st[i].s;
            StoneCutter(st,remainst,n,CurS, CurS->cs[Cursum],Cursum);
            remainst.width=temp;
            }

            flag=1;
        }
        if(remainst.height > st[i].height&&remainst.width > st[i].width)
        {
            if(flag!=0){
                Cursum++;
                quan++;
            CurS->cs[quan]=S+st[i].s;
            remainst.width-=st[i].width;
            StoneCutter(st,remainst,n,CurS, CurS->cs[quan],quan);

            remainst.height-=st[i].height;
            temp=remainst.width;
            remainst.width=st[i].width;
            StoneCutter(st,remainst,n,CurS, CurS->cs[quan],quan);
            remainst.width=temp+st[i].width;
            remainst.height+=st[i].height;
            }
            else{
                CurS->cs[Cursum]=S+st[i].s;
            remainst.width-=st[i].width;
            StoneCutter(st,remainst,n,CurS, CurS->cs[Cursum],Cursum);

            remainst.height-=st[i].height;
            temp=remainst.width;
            remainst.width=st[i].width;
            StoneCutter(st,remainst,n,CurS, CurS->cs[Cursum],Cursum);
            remainst.width=temp+st[i].width;
            remainst.height+=st[i].height;
            }



            Cursum++;
            quan++;
            CurS->cs[quan]=S+st[i].s;
            remainst.height-=st[i].height;
            StoneCutter(st,remainst,n,CurS, CurS->cs[quan],quan);

            remainst.width-=st[i].width;
            temp=remainst.height;
            remainst.height=st[i].height;
            StoneCutter(st,remainst,n,CurS,CurS->cs[quan],quan);
            remainst.height=temp+st[i].height;
            remainst.width+=st[i].width;


            flag=1;
        }

    }
    return CurS;
}


int main()
{
    int i,n,swi=1;
    float max=0,rate;
    Stone st[MAX];
    Stone remainst;
    pCurp cp;
    cp=(pCurp)malloc(sizeof(Curplan));
    cp->cs[MAX2]=0;
    for(i=0; i<MAX; i++)
    {
        st[i].height=0;
        st[i].width=0;
        st[i].s=0;
    }
    while(swi)
    {
        printf("������ʯ��ԭ�ϸߺͿ�\n");
        scanf("%f %f",&remainst.height,&remainst.width);
        remainst.s=remainst.height*remainst.width;
        n=MAX+1;
        while(n>MAX)
        {
            printf("���м���ʯ�����壿\n");
            scanf("%d",&n);
            if(n>MAX) printf("����������ƣ����������룺\n");
        }

        printf("������ߺͿ�\n");
        for(i=0; i<n; i++)
        {
            scanf("%f %f",&st[i].height,&st[i].width);
            st[i].s=st[i].height*st[i].width;
        }
        i=0;
        StoneCutter(st,remainst,n,cp,0,0);
        for(i=0; i<=quan; i++)
        {
            if(max<cp->cs[i])
            {
                max=cp->cs[i];
            }
        }
        rate=max/remainst.s;
        printf("������Ϊ  %f\n���������Ϊ  %.4f",max,rate);
        printf("�Ƿ��������������0��\n");
        scanf("%d",&swi);
    }

    return 0;
}
