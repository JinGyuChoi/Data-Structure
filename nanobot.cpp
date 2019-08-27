#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream ipf("nanobot.inp");
    ofstream opf("nanobot.out");

	unsigned int n,m;
	ipf>>m>>n;  	// first m after n !!
	int** A;
	A = new int*[n];
	for(int r=0; r < n; r++){
		A[r]= new int[m];
	}
	if (n>=3 && n<=1000 && m>=3 && m<=1000)
	{
		int sz = n * m;
		int rnum=n, cnum=m, k=1, p=0, i;
		while(k<=sz)
		{
			for(i=rnum-1;i>=p;i--){        
				A[i][p]=k++;
			}
			if(k>sz) break;
			for(i=p+1;i<cnum;i++){    
				A[p][i]=k++;
			}
			if(k>sz) break;
			for(i=p+1;i<rnum;i++){     
				A[i][cnum-1]=k++;
			}
			if(k>sz) break;
			for(i=cnum-2;i>p;i--){     
				A[rnum-1][i]=k++;
			}
			p++, rnum=rnum-1, cnum=cnum-1;
		}
	}
	else opf<<"Error : out of range"<<endl;
	short x, y;
	ipf>>x>>y;	
	int a;
	ipf>>a;
	if(x>=1 && x<=m && y>=1 && y<=n) opf<<A[n-y][x-1];
	else opf<<"Error : out of range"<<endl;
	for(short i=0;i<n;i++) {
		for(short j=0;j<m;j++){
			if (A[i][j] == a) {
				opf << "\n" << j+1 << " " << n-i;
				break;
			}
		}
	}
	ipf.close();
    opf.close();
	return 0;
}