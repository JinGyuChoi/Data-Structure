#include <bits/stdc++.h>

using namespace std;

class Graph{
    public:
        vector<vector<int>> adj;
        Graph(vector<char> &vhead, vector<char> &vloc){
            adj.resize(vhead.size());
            int i = 0;
            int idx;
            while(1){
                if(i == 0){
                    for(int j = 0; j < vhead.size(); j++){
                        if(vhead[j] == vloc[i]){
                            idx = j;
                            break;
                        }
                    }
                    i++;
                    while(vloc[i] != '$'){
                        for(int j = 0; j < vhead.size(); j++){
                            if(vhead[j] == vloc[i]){
                                adj[idx].push_back(j);
                            }
                        }
                        i++;
                    }
                }

                else if(vloc[i] == '$'){
                    i++;
                    if(i == vloc.size()) break;
                    for(int j = 0; j < vhead.size(); j++){
                        if(vhead[j] == vloc[i]){
                            idx = j;
                            break;
                        }
                    }
                    i++;
                    while(vloc[i] != '$'){
                        for(int j = 0; j < vhead.size(); j++){
                            if(vhead[j] == vloc[i]){
                                adj[idx].push_back(j);
                            }
                        }
                        i++;
                    }
                }
            }
        }
        void DFS(int start, vector<int> &visitOrder);
        void BFS(int start, vector<int> &visitOrder);
};

void Graph::DFS(int start, vector<int> &visitOrder){
    unordered_set<int> visited;
    stack<int> S;
    visited.insert(start);
    S.push(start);
    while(!S.empty()){
        start = S.top();
        vector<int>::iterator it;
        for(it = adj[start].begin(); it != adj[start].end(); it++){
            auto didvisit = visited.find(*it);
            if(didvisit == visited.end()) break;
        }
        if(it != adj[start].end()){
            visited.insert(*it);
            S.push(*it);
            visitOrder.push_back(*it);
        }
        else S.pop();
    }
}

void Graph::BFS(int start, vector<int> &visitOrder){
    queue<int> q;
    q.push(start);
    unordered_set<int> visited;
    visited.insert(start);
    while(!q.empty()){
        start = q.front();
        q.pop();
        for(auto it = adj[start].begin(); it != adj[start].end(); it++){
            auto didvisit = visited.find(*it);
            if(didvisit == visited.end()){
                q.push(*it);
                visited.insert(*it);
                visitOrder.push_back(*it);
            }
        }
    }
}

int distance(Graph G, int src, int dest) {
    if(src == dest) return 0;
    int dist = 1;
    vector<int> visited;
    queue<int> nodes;
    vector<int> forsame;
    queue<int> same_dist;
    nodes.push(src);
    visited.push_back(src);
    same_dist.push(src);
    while(!nodes.empty()){
        int x = nodes.front();
        nodes.pop();
        same_dist.pop();
        for(int i = 0; i < G.adj[x].size(); i++){
            if(G.adj[x][i] == dest) return dist;
            auto it = find(visited.begin(), visited.end(), G.adj[x][i]);
            if(it == visited.end()){
                nodes.push(G.adj[x][i]);
                visited.push_back(G.adj[x][i]);
                forsame.push_back(G.adj[x][i]);
            }
        }
        if(same_dist.empty()){
            dist++;
            if(!forsame.empty()){
                for(auto it = forsame.begin(); it != forsame.end(); it++){
                    same_dist.push(*it);
                }
                forsame.clear();
            }
        }
    }
    return 0;
}
int main(){
    ifstream ipf("meeting.inp");
    ofstream opf("meeting.out");
    int N;
    char f1,f2,f3;
    int idx1, idx2, idx3;
    int maxdist, minIndex=0;
    char location;
    vector<int> dist;
    vector<char> vloc;
    vector<char> vhead;
    vector<int> visitOrderDFS;
    vector<int> visitOrderBFS;
    ipf>>N;
    ipf>>f1>>f2>>f3;
    while(ipf>>location){
        vloc.push_back(location);
    }
    vhead.push_back(vloc[0]);
    for(auto it = vloc.begin(); it != vloc.end(); it++){
        if(*it == '$' && it+1 != vloc.end()){
            vhead.push_back(*(it+1));
        }
    }
    sort(vhead.begin(),vhead.end());
    Graph g(vhead,vloc);
    for(int i = 0; i < vhead.size(); i++){
        if(vhead[i] == f1){
            idx1 = i;
            break;
        }
    }
    for(int i = 0; i < vhead.size(); i++){
        if(vhead[i] == f2){
            idx2 = i;
            break;
        }
    }
    for(int i = 0; i < vhead.size(); i++){
        if(vhead[i] == f3){
            idx3 = i;
            break;
        }
    }
    vector<int> distances1;
    vector<int> distances2;
    vector<int> distances3;
    vector<int> Mdistances;
    for(int i = 0; i < N; i++){
        distances1.push_back(distance(g,idx1,i));
    }
    for(int i = 0; i < N; i++){
        distances2.push_back(distance(g,idx2,i));
    }
    for(int i = 0; i < N; i++){
        distances3.push_back(distance(g,idx3,i));
    }
    for(int i = 0; i < N; i++){
        if(distances1[i] >= distances2[i]){
            if(distances3[i] > distances1[i]) maxdist = distances3[i];
            else maxdist = distances1[i];
        }
        else if(distances2[i] >= distances3[i]){
            if(distances1[i] > distances2[i]) maxdist = distances1[i];
            else maxdist = distances2[i];
        }
        else if(distances3[i] >= distances1[i]){
            if(distances2[i] > distances3[i]) maxdist = distances2[i];
            else maxdist = distances3[i];
        }
        Mdistances.push_back(maxdist);
    }
    for(int i = 0; i < Mdistances.size(); i++){
        if(Mdistances[minIndex] > Mdistances[i] && Mdistances[i] > 0){
            minIndex = i;
        }
    }
    opf<<vhead[minIndex]<<"\n"<<Mdistances[minIndex]+2*(Mdistances[minIndex]-1);
    g.DFS(2,visitOrderDFS);
    for(auto it : visitOrderDFS) cout<<it<<" "; //주석처리 할것.
    g.BFS(2,visitOrderBFS);
    cout<<endl;
    for(auto it : visitOrderBFS) cout<<it<<" "; //주석처리 할것.

    ipf.close();
    opf.close();
    return 0;
}
