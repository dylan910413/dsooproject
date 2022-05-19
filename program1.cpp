#include <bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<utility>
#include<vector>
#include<iomanip>
using namespace std;
using pii=pair<int,int>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
queue<int> takeoffqueue[5];
queue<pii> landingqueue[5];
queue<pii> emergency;
pii readyld[5];
int readyto[5];
int ldplaneid=1;                                                //landing planes id
int toplaneid=0;                                                //take off planes id        
int totalldplanes;
int totaltoplanes;
int towaitingtime;                                                //total waiting time
int ldwaitingtime;
int choose[5];   
int oil; 
int numofplaneld;
int numofplaneto;
int wtime[10005];  
int totale;    
int totalc;
int iter=0;
int iter2=0;

int rand_num1(){
    return uniform_int_distribution<int>(0, 3)(rng);
}  

int rand_num2(){
    return uniform_int_distribution<int>(0, 4)(rng);
}

void setting(){                                                    //將每單位時間要降落或起飛的飛機生成
    numofplaneld=rand_num2();
    numofplaneto=rand_num1();
    totalldplanes+=numofplaneld;
    totaltoplanes+=numofplaneto;
    for(int i=1;i<=numofplaneld;i++){
        int fuel=rand()%10+1;
        oil+=fuel;
        readyld[i].first=ldplaneid;
        readyld[i].second=fuel;
        ldplaneid+=2;
    }
    for(int i=1;i<=numofplaneto;i++){
        readyto[i]=toplaneid;
        wtime[toplaneid]=0;
        toplaneid+=2;
    }
}

void print(){
    for(int i=1;i<=4;i++){
        cout<<"Runway"<<i<<"("<<choose[i]<<")"<<endl;
        cout<<"L1:";
        int n=landingqueue[i].size();
        if(n>0){
            for(int j=0;j<n;j++){
                pii c=landingqueue[i].front();
                cout<<"("<<c.first<<", "<<c.second<<"), ";
                landingqueue[i].pop();
                landingqueue[i].push(c);
            }
        }
        cout<<endl;
        cout<<"L2:"<<endl;
        cout<<"T:";
        int m=takeoffqueue[i].size();
        if(m>0){
            for(int j=0;j<m;j++){
                int c=takeoffqueue[i].front();
                cout<<"("<<c<<"), ";
                takeoffqueue[i].pop();
                takeoffqueue[i].push(c);
            }
        }
        cout<<endl;
        cout<<endl;
    }
}

void checkemergency(){
    for(int i=2;i<=4;i++){
        int n=landingqueue[i].size();
        if(n>0){
            for(int j=0;j<n;j++){
                pii e=landingqueue[i].front();
                landingqueue[i].pop();
                if(e.second==0){
                    totale++;
                    emergency.push(e);
                    cout<<"("<<e.first<<"), ";
                }else landingqueue[i].push(e);
            }
        }else continue;
    }
}

void checkcrashed(){
    int m=emergency.size();
    if(m>0){
        totalc+=m;
        for(int i=0;i<m;i++){
        emergency.pop();
        }
    }else return;
}

void takeoffwaitingtime(){
    for(int i=1;i<=4;i++){
        int n=takeoffqueue[i].size();
        if(n>0){
            for(int j=0;j<n;j++){
                int id=takeoffqueue[i].front();
                takeoffqueue[i].pop();
                wtime[id]++;
                towaitingtime++;
                takeoffqueue[i].push(id);
            }
        }
    }
}

void landingwaitngtime(){
    for(int i=2;i<=4;i++){
        int n=landingqueue[i].size();
        if(n>0){
            for(int j=0;j<n;j++){
                pii id=landingqueue[i].front();
                landingqueue[i].pop();
                wtime[id.first]++;
                ldwaitingtime++;
                id.second--;
                landingqueue[i].push(id);
            }
        }  
    }
}

void step1(){
    cout<<"step1:"<<endl;
    cout<<"landing plane:";
    for(int i=1;i<=numofplaneld;i++){
        cout<<"("<<readyld[i].first<<", "<<readyld[i].second<<"), ";
    }
    cout<<endl;
    for(int i=1;i<=4;i++) choose[i]=-1;
    int s=iter+numofplaneld;
    int a=2;
    for(int i=iter;i<=s-1;i++){
        landingqueue[i%3+2].push(readyld[a-1]);
        a++;
        iter++;
    }
    cout<<endl;
    print();
}

void step2(){
    cout<<"step2: "<<endl;
    cout<<"takeoff plane:";
    for(int i=1;i<=numofplaneto;i++){
        cout<<"("<<readyto[i]<<"),";
    }
    cout<<endl;
    int s=iter2+numofplaneto;
    int a=1;
    iter2++;
    for(int i=1;i<=numofplaneto;i++){
        takeoffqueue[i].push(readyto[a]);
        a++;
    }
    print();
}

void step3(){
    cout<<"step3:"<<endl;
    cout<<"emergency plane:";
    checkemergency();
    int m=emergency.size();
    if(m>0){
        for(int i=1;i<=m;i++){
            choose[i]=emergency.front().first;
            emergency.pop();
        }
    }
    cout<<endl;
    print();
}

void step4(){
    cout<<"step4:"<<endl; 
    for(int i=1;i<=4;i++){
        int l=takeoffqueue[i].size();
        if(choose[i]==-1&&l>0){
            choose[i]=takeoffqueue[i].front();
            takeoffqueue[i].pop();
        }else{
            continue;
        }
    }
    for(int i=2;i<=4;i++){
        int n=landingqueue[i].size();
        if(choose[i]==-1&&n>0){
            for(int j=0;j<=n;j++){
                pii e2=landingqueue[i].front();
                if(e2.second<=2){
                    choose[i]=e2.first;
                    oil+=e2.second; 
                    landingqueue[i].pop();
                    break;
                }else{
                    landingqueue[i].pop();
                    landingqueue[i].push(e2);
                }
            }
        }
    } 
    for(int i=1;i<=4;i++){
        int l=takeoffqueue[i].size();
        if(choose[i]==-1&&l>0){
            choose[i]=takeoffqueue[i].front();
            takeoffqueue[i].pop();
        }else{
            continue;
        }
    }
    for(int i=2;i<=4;i++){
        int p=landingqueue[i].size();
        if(choose[i]==-1&&p>0){
            pii e3=landingqueue[i].front();
            choose[i]=e3.first;
            oil+=e3.second;
            landingqueue[i].pop();   
        }else{
            continue;
        }
    }
    print();
}
void all(){
    setting();
    step1();
    step2();
    step3();
    step4();
    checkcrashed();
    takeoffwaitingtime();
    landingwaitngtime();
}
int main(){
    int time=500;
    for(int i=1;i<=500;i++){
        cout<<"simulation time: "<<i<<endl;
        all();
    }
    cout<<"How Many time Unit You Want to Simulate: " <<time<<endl;
    cout<<"average landing waiting time: "<<setprecision(3)<<fixed<<(double)ldwaitingtime/totalldplanes<<"(s)"<<endl;
    cout<<"average takeoff waiting time: "<<setprecision(3)<<fixed<<(double)towaitingtime/totaltoplanes<<"(s)"<<endl;
    cout<<"average fuel saved: "<<setprecision(3)<<fixed<<(double)oil/totalldplanes<<"(s)"<<endl;
    cout<<"total plane in emergency:"<<totale<<endl;
    cout<<"total plane crashed:"<<totalc<<endl;
}