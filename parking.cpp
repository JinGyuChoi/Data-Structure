#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream ipf("parking.inp");
    ofstream opf("parking.out");

    int K, N;
    ipf>>K>>N;
    vector <int> slot;
    int cars;
    slot.reserve(K);

    /* 해당 값 지우는 코드
    while( iter != vecNum.end( ) )
		{
			if( iter->nCount == nInput )
			{ 
				iter = vecNum.erase( iter );				
			} 
			else 
			{ 
				++iter; 
			}
		}*/

    vector<int> :: iterator it;
    int count_0 = 0;
    while(ipf>>cars){
        if(cars > 0) {
            it = find(slot.begin(),slot.end(),0);
            if (it != slot.end()) {
                *it = cars;
                count_0--;
                for(it; it!=slot.end(); it++){
                    if (*it != 0) break;
                    if (it == slot.end()) count_0++;
                }
            }
            else {
                if(slot.size()<K){
                    slot.push_back(cars);
                }
                else {
                    slot.resize(2 * slot.size());
                    count_0 += slot.size()/2;
                    it = find(slot.begin(),slot.end(),0);
                    if (it != slot.end()) {
                        *it = cars;
                        count_0--;
                    }
                }
            }
        }
        else{
            it = slot.begin();
            while( it != slot.end( ) ){
			    if( *it == -cars ){ 
                    *it = 0;
                    count_0++;
                    break;		
			    } 
			    else it++;   
            }//end of deleting car
            if( (slot.size() - count_0) <= slot.size()/3 ){
                vector<int>::iterator it2;
                vector<int>::iterator it3;
                while(1){
                    for(it2=slot.begin();it2!=slot.end();it2++){
                        if(*it2 == 0){
                            for(it3=it2; it3!=slot.end(); it3++){
                                if(*it3 != 0){
                                    int temp = *it3;
                                    *it3 = 0;
                                    *it2 = temp;
                                    break;
                                }
                        
                            }
                        }
                    }
                    if(it3 == slot.end()) break;
                }
                slot.resize(slot.size()/2);
                if(slot.size()<K) slot.resize(K);
                count_0 = 0;
                for(it = slot.begin();it!=slot.end(); it++){
                    if (*it == 0) count_0 ++;
                }
            }
        }
    }
    for(int i = 0; i<slot.size(); i++){
        if(slot[i] != 0){
            opf<<i+1<<" "<<slot[i]<<"\n";
        }
    }

    ipf.close();
    opf.close();
    return 0;
}