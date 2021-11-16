/*

  1.packing����������и�M��N��ԭ�ϣ���n���ز�ģ��
    �иʽ��һ���У�����и����ʹ��ʯ�����������
  2.ʹ��DP˼·��ѭ��M��N�Σ�ÿ�εĽ�����������֣���ǰģ��+�е�������ģ�塣


*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <queue>
#include <string>

#define MAX 10001
#define thisMAX 100001
using namespace std;

//queue<int> nowModels;
//queue<int> nowDirecs;
int nowModels[MAX][MAX];
int nowDirecs[MAX][MAX];
typedef struct stone{
    int w;
    int h;
    int area;
}st1s,*St;
queue<int> Mod;
queue<string> Cut;

//struct plan{
//    int Num;
//    string direction;
//}plans[100][100];



st1s models[MAX];
//models[0].h = -1;
//models[0].w = -1;
//models[0].area = -1;
int W,H;
int n;
int thisArea[MAX][MAX];
//int thisDirec[MAX][MAX];
//int thisModel[MAX][MAX];


//void trans(){
//    float m = min(W,H);
//     for(int j = 1 ; j <= n ; j ++){
//        m = min(m,models[j].h);
//        m = min(m,models[j].w);
//    }
//    int i = m;
//    m = m - i;
//    bool a = (m*10>0);
//    bool b = (m*100>0);
//    bool c = (m*1000>0);
//    if(c){
//        W = W*1000;
//        H = H*1000;
//        for(int j = 1 ; j <= n ; j ++){
//        models[j].w*=1000;
//        models[j].h*=1000;
//    }
//    }
//   else{
//        if(b){
//            W = W*100;
//            H = H*100;
//             for(int j = 1 ; j <= n ; j ++){
//                models[j].w*=100;
//                models[j].h*=100;
//            }
//        }
//        else{
//            if(a){
//                W = W*10;
//                H = H*10;
//                for(int j = 1 ; j <= n ; j ++){
//                    models[j].w*=10;
//                    models[j].h*=10;
//                }
//            }
//        }
//   }
//}
//

void initial(){
    cout<<"������ԭ�Ͽ� �� �ߣ�";
    cin>>W>>H;
    cout<<"������ģ��������";
    cin>>n;

    for(int j = 1 ; j <= n ; j ++){
        cout<<"�������"<<j<<"��ģ��Ŀ�͸ߣ�";
        cin>>models[j].w>>models[j].h;
        models[j].area = models[j].h*models[j].w;
    }
//    trans();

}

void disp(int a,int b){
    if(a == 0 || b == 0){
//        Mod.push(-1);
//        Cut.push("���������");
        return;
    }
    if(nowDirecs[a][b] == 1){
            Mod.push(nowModels[a][b]);
            Cut.push("��������");
            disp(0,0);

    }
    if(nowDirecs[a][b] == 2){
        int a1=a,b1=b;
        Mod.push(nowModels[a1][b1]);
        Cut.push("����");
        a = a - models[nowModels[a1][b1]].w;
        disp(a,b);
        b = b - models[nowModels[a1][b1]].h;
        disp(models[nowModels[a1][b1]].w,b);
    }
    if(nowDirecs[a][b] == 3){
        int a1=a,b1=b;
        Mod.push(nowModels[a1][b1]);
        Cut.push("����");
        b = b - models[nowModels[a1][b1]].h;
        disp(a,b);
        a = a - models[nowModels[a1][b1]].w;
        disp(a,models[nowModels[a1][b1]].h);
    }


}

int curMaxArea(int cur_w,int cur_h){
    int max_flag = 0, max_direc = 0;
    int max_now = 0 ;
    if(cur_w == 0 || cur_h == 0 ){
        return 0;
    }

    else{
        for(int i = 1 ; i <= n ; i ++){
            if(cur_h == models[i].h && cur_w == models[i].w){
//                plans[cur_w][cur_h].Num = i;
//                plans[cur_w][cur_h].direction = "��������";

                nowDirecs[cur_w][cur_h] = 1;
                nowModels[cur_w][cur_h] = i;
                return models[i].area;
            }
            if(cur_h == models[i].h && cur_w > models[i].w ){

                //�������ֻ������(2)
//                thisDirec[cur_w][cur_h] =  thisDirec[cur_w-models[i].w][cur_h]
                if(models[i].area+thisArea[cur_w-models[i].w][cur_h] > max_now){
                    max_now = models[i].area+thisArea[cur_w-models[i].w][cur_h];
                    max_direc = 2;
                    max_flag = i;
                }
//                max_now = max( models[i].area+thisArea[cur_w-models[i].w][cur_h] , max_now );
//                plans[cur_w][cur_h].Num = i;
//                plans[cur_w][cur_h].direction = "����";
            }
            if(cur_h > models[i].h && cur_w == models[i].w ){
                //ֻ�ܺ���
//                max_now = max( models[i].area+thisArea[cur_w][cur_h-models[i].h] , max_now );
//                plans[cur_w][cur_h].Num = i;
//                plans[cur_w][cur_h].direction = "����";
                if(models[i].area+thisArea[cur_w][cur_h-models[i].h] > max_now){
                    max_now = models[i].area+thisArea[cur_w][cur_h-models[i].h];
                    max_direc = 3;
                    max_flag = i;
                }

            }
            if( cur_h > models[i].h && cur_w > models[i].w ){
                //�������
                int heng = models[i].area + thisArea[cur_w-models[i].w][models[i].h]+thisArea[cur_w][cur_h - models[i].h];
                //�������
                int shu = models[i].area + thisArea[cur_w - models[i].w][cur_h]+thisArea[models[i].w][cur_h - models[i].h];
                if(shu > max_now){
                    max_now = shu;
                    if(heng > max_now){
                        max_now = heng;
                        max_direc = 3;
                        max_flag  = i;
                    }
                    else{
                        max_direc = 2;
                        max_flag  = i;
                    }
                }
                else{
                    if(heng > max_now){
                        max_now = heng;
                        max_direc = 3;
                        max_flag  = i;
                    }
                }
//                max_now = max(shu,max_now);
//                max_now = max(heng,max_now);
//                if(max_now == shu ){
//                    plans[cur_w][cur_h].Num = i;
//                    plans[cur_w][cur_h].direction = "�������ٺ���";
//
//                }
//                else{
//                    plans[cur_w][cur_h].Num = i;
//                    plans[cur_w][cur_h].direction = "�Ⱥ���������";
//
//                }
            }

        }
        nowDirecs[cur_w][cur_h] = max_direc;
        nowModels[cur_w][cur_h] = max_flag;
//        cout<<"nowDirec["<<cur_w<<"] "<<"["<<cur_h<<"]= "<<max_direc<<"  nowModels["<<cur_w<<"] "<<"["<<cur_h<<"]= "<<max_flag<<endl;
//        if(cur_w  == W && cur_h == H){
//            cout<<"now is W��H situation"<<endl;
//        }
//        cout<<"��ǰ������"<<max_now<<endl;
        return max_now;

    }
}




double Dpack(){
    for(int i = 0 ; i <= W ; i ++){
        for(int j = 0 ; j <= H ; j ++){
            thisArea[i][j] = curMaxArea(i,j);
        }
    }
    double all_area = W*H;
    double rate = thisArea[W][H]/all_area;
    return rate;
}



int main()
{
    int go_on = 1;
    while(go_on){
        initial();
        cout<<"���������Ϊ��"<<Dpack()<<"\n";
        cout<<"�и��Ϊ��"<<endl;
        disp(W,H);
        while(!Cut.empty()){
            cout<<"�и�ģ�壺"<<Mod.front()<<"��  �и����"<<Cut.front()<<endl;
            Cut.pop();
            Mod.pop();
        }
        cout<<"�Ƿ������������������0����������1����";
        cin>>go_on;

//        fscanf(fopen("data.txt","r"),"%d",&go_on);
    }

    return 0;
}
