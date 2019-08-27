#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream ipf("function.inp");
    ofstream opf("function.out");
    int N,k1,k2;
    ipf>>N>>k1>>k2;
    vector <vector <string>> func;
    string element;
    stack <int> x_pos;
    stack <int> y_pos;
    vector<string> temp;
    while(ipf>>element){
        temp.push_back(element);
        if(element == "$") {
            func.push_back(temp);
            temp.clear();
        }
    }

    int i = 0, j = 1;
    int c;
    int count=0, deadcount=0;
    int x[2]={-1,-1}, y[2]={-1,-1};
    while(1){
        if(func[i][j] == "$"){
            deadcount--;//갓준석... 당신은 도덕책...
            if(x_pos.empty()) break;
            i = x_pos.top();
            j = y_pos.top() + 1;
            x_pos.pop();
            y_pos.pop();

        }
        else if((bool)isupper(func[i][j][0])){
            deadcount++;
            if(deadcount > 300) {
                opf<<"DEADLOCK";
                return 0;
            }
            x_pos.push(i);
            y_pos.push(j);
            for(c=0; c<N; c++){
                if(func[i][j] == func[c][0]){
                    break;
                }
            }
            i=c;
            j=1;
        }

        else{
            count++;
            if(count == k1){
                x[0] = i;
                y[0] = j;
            }

            else if(count == k2){
                x[1] = i;
                y[1] = j;
            }
            j++;
        }
    }

    if(x[0] == -1) opf<<"NONE\n";
    else opf<<func[x[0]][0]<<'-'<<func[x[0]][y[0]]<<'\n';

    if(x[1] == -1) opf<<"NONE";
    else opf<<func[x[1]][0]<<'-'<<func[x[1]][y[1]];

    ipf.close();
    opf.close();

    return 0;
}
