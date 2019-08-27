#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(void){
    ifstream ipf("log.inp");
    ofstream opf("log.out");
    ifstream txf("syslog.txt");

    vector<int> elements;
    int N, n;
    txf >> n;
    ipf >> N;
    int *days, *index;
    days = new int[n+2];
    index = new int[n+2];
    days[0] = 0;
    index[0] = 0;
    int today = 1; 
    int count;
    int num;

    while(!txf.eof()){
            count = 0;
            txf >> num;
            days[today] = num;
            while(1){
                txf>>num;
                if(num == 0)
                    break;
                count++;
                elements.push_back(num);
            }
            index[today] = index[today-1] + count;
            today++;
    }

    days[n+1] = 100000;
    index[n+1] = 0;
    int dayStart,timeStart, dayEnd,timeEnd;
    for(int m=0; m<N; m++){
        ipf>>dayStart>>timeStart>>dayEnd>>timeEnd;
        int n_element = 0;
        today = 0;
        count = 0;
        for(int i=0; i<n+1; i++)
            if(days[i+1]>=dayStart){
                today = i;
                break;
            }
        for(int i=today; i<n+1; i++)
            if(days[i+1]>dayEnd){
                count = i;
                break;
            }

        if(days[today+1] == dayStart)
            for(int i=index[today]; i<index[today+1]; i++)
                if(timeStart>elements[i])
                    n_element--;
        if(days[count] == dayEnd)
            for(int i=index[count-1]; i<index[count]; i++)
                if(timeEnd<elements[i])
                    n_element--;

        n_element += index[count]-index[today];
        opf<<n_element<<'\n';
    }
    ipf.close();
    txf.close();
    opf.close();
    return 0;
}