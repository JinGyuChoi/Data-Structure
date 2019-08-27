#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream ipf("shopping.inp", ios::binary);
    ofstream opf("shopping.out", ios::binary);
    int N,k;
    ipf>>N>>k;
    int user,item;
    vector<int> time;
    vector<int> sorted_time;
    vector<int> times(k);
    vector<int> users;
    queue<int> cart[k];
    vector<int> out;
    stack<int> sameindex;

    while(ipf>>user>>item){
        users.push_back(user);
        time.push_back(item);
    }
    int j = 0;
    int minIndex;
    while(out.size() != N){
        if(users.size() > k){
            for(int x = 0; x < k; x++){
                if(cart[x].empty()) {
                    if(j == N) break;
                    cart[x].push(users[j]);
                    times[x] += time[j];
                    j++;
                }
            }
            minIndex = min_element(times.begin(),times.end()) - times.begin();
            for(int i = 0; i < k; i++){
                if(times[minIndex] == times[i]) sameindex.push(i);
            }
            if(sameindex.size() == 1){
                if(!(cart[minIndex].empty())){
                    out.push_back(cart[minIndex].front());
                    cart[minIndex].pop();
                    sameindex.pop();
                }
                else{
                    times[minIndex] = 5000;
                    sameindex.pop();
                }
            }
            else if(sameindex.size() >= 2){
                if(!(cart[minIndex].empty())){
                    while(!(sameindex.empty())){
                        out.push_back(cart[sameindex.top()].front());
                        cart[sameindex.top()].pop();
                        sameindex.pop();
                    }
                }
                else{
                    while(!(sameindex.empty())){
                        times[minIndex] = 5000;
                        sameindex.pop();
                    }
                }
            }
        }
        else{
            /*sorted_time = time;
            sort(sorted_time.begin(), sorted_time.end());
            for(int m = 0; m < sorted_time.size(); m++){
                for(int n = 0; n < time.size(); n++){
                    if(sorted_time[m] == time[n]) out.push_back(users[n]);
                }
            }*/
            minIndex = min_element(time.begin(),time.end()) - time.begin();
            for(int i = 0; i < time.size(); i++){
                if(time[minIndex] == time[i]) sameindex.push(i);
            }
            if(sameindex.size() == 1){
                out.push_back(users[minIndex]);
                time[sameindex.top()] = 5000;
                sameindex.pop();
            }
            else if(sameindex.size() >= 2){
                while(!(sameindex.empty())){
                    out.push_back(users[sameindex.top()]);
                    time[sameindex.top()] = 5000;
                    sameindex.pop();
                }
            }
        }
    }
    for(auto it:out) opf<<it<<"\n";

    return 0;
}