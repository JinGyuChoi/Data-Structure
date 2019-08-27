#include <bits/stdc++.h>

using namespace std;

int N,M,k;
int BFS(vector<vector<int>> &germs, int x, int y){
    queue<pair<int,int>> q;
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,1,0,-1};
    int count = 0;
    q.push(pair<int,int>(x,y));
    while(!q.empty()){
        int x2 = q.front().first;
        int y2 = q.front().second;
        q.pop();
        if(germs[x2][y2] == 1){
            count++;
            germs[x2][y2] = 0;
            for(int i = 0; i < 4; i++){
                int nextX = x2 + dx[i];
                int nextY = y2 + dy[i];
                if(nextX >= 0 && nextX < M && nextY >= 0 && nextY < N){
                    if(germs[nextX][nextY] == 1) q.push(pair<int,int>(nextX,nextY));
                }
            }     
        }
    }
    return count;
}

int main() {
    ifstream ipf("micro.inp");
    ofstream opf("micro.out");
    ipf>>N>>M>>k;
    string location;
    vector<int> germ;
    vector<vector<int>> germs;
    int n, r = 0, w = 0;
    list<int> size;
    while(ipf>>location){
        if(location == "#") germ.push_back(1);
        else if(location == "_") germ.push_back(0);
        r++;
        if(r == N){
            germs.push_back(germ);
            germ.clear();
            r = 0;
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(germs[i][j] == 1){
                n = BFS(germs,i,j);
                size.push_back(n);
                if(n >= k) w++;
            }
        }
    }
    size.sort();
    list<int>::reverse_iterator ri = size.rbegin();
    if(w > 0)   opf<<w<<" "<<*ri;
    else opf<<w<<" "<<0;

    ipf.close();
    opf.close();
    
    return 0;
}
