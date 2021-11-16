#include <stdio.h>
#include <stdlib.h>
#define MAX2 1000
#define MAX 10     //石板模板最大限制
typedef struct stone
{
    float width;
    float height;
    float s;
} Stone,*pStone;
typedef struct curplan
{
    float cs[MAX2];//存储不同方案的面积
} Curplan,*pCurp;
//int Cursum=0;
int quan;    // 全局变量，与Cursum共同作用
pCurp StoneCutter(pStone st,Stone remainst, int n,pCurp CurS,float S,int Cursum) //递归循环，枚举所有可能的方法，最后在主函数取最优
{
    int i,j;
    float temp;   //用于暂存数据
    int flag=0;  //flag用于标志枚举中是否第一次进行本次循环
    for(i=0; i<n; i++)    //下面分为五种情况
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
        printf("请输入石板原料高和宽：\n");
        scanf("%f %f",&remainst.height,&remainst.width);
        remainst.s=remainst.height*remainst.width;
        n=MAX+1;
        while(n>MAX)
        {
            printf("共有几块石板样板？\n");
            scanf("%d",&n);
            if(n>MAX) printf("超过最大限制，请重新输入：\n");
        }

        printf("请输入高和宽\n");
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
        printf("最大面积为  %f\n最大利用率为  %.4f",max,rate);
        printf("是否继续？（否输入0）\n");
        scanf("%d",&swi);
    }

    return 0;
}
