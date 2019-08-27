#include <bits/stdc++.h>

using namespace std;
using ll = long long;

typedef struct{
    list<int> id;
    ll start;
    ll end;
} User;

list <User> loglist;

bool compare_login (User &u1, User &u2) {
    if (u1.start<u2.start)
        return true;
    else if (u1.start>u2.start)
        return false;
    else{
        if(u1.end <= u2.end)
            return true;
        else
            return false;
    }

    return (u1.start<u2.start);
} // end

int main() {
    ifstream ipf("log.inp");
    ofstream opf("log.out");

    int N,K;
    ipf>>N>>K;
    int u_id;
    ll in,out;
    int count = 0;
    User user;
    while(ipf>>u_id>>in>>out){
        user.id.push_back(u_id);
        user.start = in;
        user.end = out;
        loglist.push_back(user);
        user.id.clear();
        count++;
        if(count == N) break;
    }

    loglist.sort(compare_login);
    ll Q;
    list<int> logid;
    while(ipf >> Q){
        for(auto it = loglist.begin(); it != loglist.end(); it++){
            if((*it).start <= Q && (*it).end >= Q) {
                for(auto it2 = (*it).id.begin(); it2 != (*it).id.end(); it2++) {
                    logid.push_back(*it2);
                }
            }
        }
        logid.sort();
        //logid.unique();
        if(logid.empty()) opf<<"0";
        else {
            for(auto it3 = logid.begin(); it3 != logid.end(); it3++) {
                opf<<*it3<<" ";
            }
            logid.clear();
        }
        opf<<"\n";
    }

    ipf.close();
    opf.close();
    return 0;
}