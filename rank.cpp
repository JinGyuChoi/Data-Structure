#include <bits/stdc++.h>

using namespace std;
static bool SOX(vector <int> v1, vector <int> v2){
    if(v1.size()-1 > v2.size()-1) return true;
    else if(v1.size()-1 < v2.size()-1) return false;
    else{
        for(int i=0; i<v1.size()-1; i++){
            if(v1[i] < v2[i]) return false;
            else if(v1[i] > v2[i]) return true;
        }
        vector<int> :: iterator it1;
        vector<int> :: iterator it2;
        it1=v1.end()-1;
        it2 = v2.end() - 1;
        if(*it1 > *it2) return false;
        else return true;
    }
}
int main() {
    ifstream ipf("rank.inp");
    ofstream opf("rank.out");

    int N;
    ipf>>N;
    vector <vector <int>> report;
    int grade;
	vector < vector<int> >::iterator ri;
    vector<int> temp;
    vector <int>::iterator gi;
    int id = 1;
    while(ipf>>grade){
        if(grade != -1) {
            temp.push_back(grade);
        }
        else {
            temp.push_back(id);
            report.push_back(temp);
            temp.clear();
            id++;
        }
    }
    for(int i = 0; i<N; i++){
        sort(report[i].begin(),report[i].end()-1);
    }
    sort(report.begin(), report.end(),&SOX);
    /*for( ri = report.begin(); ri != report.end(); ++ri) {
        cout <<(ri-report.begin()) << "==>  " ;
		for( gi = ri->begin(); gi != ri->end(); ++gi) {
			// jt is now a pointer to an integer.
			cout << *gi << " ";
		}
		cout << endl;
	}*/
    for(int i = 0; i<N; i++){
        gi = report[i].end()-1;
        opf<<*gi<<"\n";
    }

    ipf.close();
    opf.close();
    return 0;
}
