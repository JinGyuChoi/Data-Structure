#include <bits/stdc++.h>

using namespace std;

void Cut(list<int> &lt,int first, int last){
    list<int>::iterator it1 = lt.begin();
    list<int>::iterator it2 = lt.begin();
    for(int i = 0; i < first-1; i++){
        it1++;
    }
    for(int j = 0; j < last; j++){
        it2++;
    }
    lt.splice(lt.end(),lt,it1,it2);
}

int main() {
    ifstream ipf("card.inp");
    ofstream opf("card.out");

    int n_card,n_working;
    ipf>>n_card>>n_working;
    list<int> cards;
    for(int i = 1; i <= n_card; i++){
        cards.push_back(i);
    }
    vector <int> works;
    string working;
    while(ipf>>working){
        if(working == "Shuffle") {
            works.push_back(-1);
        }
        else if (working == "Cut"){
            works.push_back(-2);
        }
        else {
            works.push_back(stoi(working));
        }
    }
    // Shuffle : -1 , Cut : -2
    for(auto it = works.begin(); it != works.end(); it++){
        if(*it == -2) Cut(cards,*(it+1),*(it+2));

        else if (*it == -1){
            list<int> anotherDeck;
            list<int>::iterator where = cards.begin();
            float idx = (float)cards.size()/2;
            for(int i = 0; i < round(idx); i++){
                where++;
            }
            anotherDeck.splice(anotherDeck.begin(),cards,where,cards.end());
            list<int>::iterator A_it = cards.begin();
            list<int>::iterator B_it = anotherDeck.begin();
            for(int i = 0; i < n_card/2; i++){
                A_it++;
                cards.insert(A_it,*B_it);
                B_it++;
            }
        }
    }
    list<int>::iterator start = cards.begin();
    list<int>::iterator center = cards.begin();
    list<int>::reverse_iterator last = cards.rbegin();
    for(int i = 1; i < n_card/2; i++) center++;
    opf<<*start<<" "<<*center<<" "<<*last;

    ipf.close();
    opf.close();
    return 0;
}