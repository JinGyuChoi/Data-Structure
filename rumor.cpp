#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream ipf("rumor.inp");
    ofstream opf("rumor.out");

    int N,x,d;
    ipf>>N>>x>>d;
    vector <vector <int>> heard;
    int person;
    int day = 0;
    vector<int> friends;
    queue<int> spoiler;
    vector<int> gone;
    vector<int> :: iterator it;
    queue<int> dayheard;
    vector<int> spoiled;
    vector<int> fordayheard;
    spoiled.push_back(x);
    dayheard.push(x);
    spoiler.push(x);
    while(ipf>>person){
        if(person != 0) {
            friends.push_back(person);
        }
        else {
            heard.push_back(friends);
            friends.clear();
        }
    }
    sort(heard.begin(), heard.end());

    for(int i = 0; i < N; i++){
        sort(heard[i].begin()+1, heard[i].end());
    }

    while(day <= d && !(spoiler.empty())){
        for(int i = 0; i<N; i++){
            if(heard[i][0] == spoiler.front()){
                if(heard[i].size() == 1){
                    opf<<heard[i][0];
                    return 0;
                }

                else{
                    gone.push_back(spoiler.front());
                    spoiler.pop();
                    dayheard.pop();
                    for(auto it1 = heard[i].begin()+1; it1 != heard[i].end(); it1++){
                        auto it2 = find(spoiled.begin(), spoiled.end(), *it1);
                        if(it2 == spoiled.end()){
                            spoiler.push(*it1);
                            fordayheard.push_back(*it1);
                            spoiled.push_back(*it1);
                        }
                    }
                    if(dayheard.empty()){
                        day++;
                        if(!(fordayheard.empty())){
                            for(auto it3 = fordayheard.begin(); it3 != fordayheard.end(); it3++){
                                dayheard.push(*it3);
                            }
                            fordayheard.clear();
                        }
                        break;
                    }
                }
            }
        }
    }
    for(auto it2 = gone.begin(); it2 != gone.end(); it2++) opf<<*it2<<"\n";
    
    ipf.close();
    opf.close();
    return 0;
}