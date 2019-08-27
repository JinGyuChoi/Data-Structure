#include <bits/stdc++.h>

using namespace std;
//Node class : bst를 위한 각 노드들의 class
class Node{
    public:
        string data; //string 값을 넣어줄 멤버변수
        int depth = 1; //각 노드들의 깊이, root의 깊이는 1이므로 초기값은 1로 초기화.
        Node* left; // 9~10 : 왼쪽노드와 오른쪽노드
        Node* right;
}; //end of Node class

// 노드를 추가하는 함수.
void add_data(Node* root,string name){
    if(root->data == "") { //root->data 가 ""일경우
        root->data = name; //해당 노드에 데이터를 추가.
        root->left = new Node(); // 17~24 : 데이터가 추가됨과 동시에 왼쪽노드, 오른쪽 노드를 할당하고,
        root->left->depth = root->depth; // 그 깊이를 이전의 노드의 깊이에 1 추가.
        root->right = new Node();
        root->right->depth = root->depth;
        root->left->depth++;
        root->right->depth++;
        return;
    }
    else{ //root->data 가 ""이 아닐경우 즉, 이미 다른 데이터가 있는경우, 왼쪽노드와 오른쪽 노드가 이미 할당돼 있을것이므로
        if(name < root->data){ // 26~31 : 왼쪽노드부터 차례로, 끝나면 오른쪽노드로 넘어가게끔 재귀함수로 데이터를 넣는다.
            add_data(root->left,name);
        }
        else {
            add_data(root->right,name);
        }
    }
}
//35~41 : 실습시간에 배운 함수를 사용했습니다.
void storeinorderInSet(Node* root, set<string>& s)  { //root 노드를 root로 가지는 bst의 원소를 set에 저장하는 함수.
	if (root->data=="") 	return; //해당 노드의 data가 없으면 함수종료.

	storeinorderInSet(root->left, s); // 38~40 : data가 있으면 왼쪽-root-오른쪽 순서대로 set에 저장.
	s.insert(root->data);
	storeinorderInSet(root->right, s);
}

Node* minnode(Node* root){ //최솟값을 가지는 노드를 반환하는 함수.
    while(root->left->data != "") root=root->left; //상대적으로 작은값은 왼쪽에 놓이므로, 왼쪽 데이터가 없을때까지 노드를 왼쪽으로 옮기고
    return root; //최소 노드를 반환. 
}

Node* maxnode(Node* root){ //최댓값을 가지는 노드를 반환하는 함수.
    while(root->right->data != "") root=root->right; //상대적으로 큰값은 오른쪽에 놓이므로, 오른쪽 데이터가 없을때까지 노드를 오른쪽으로 옮기고
    return root; //최대 노드를 반환.
}

bool is_leaf(Node* root){ //leaf node인지 판별하는 함수.
    if(root->left->data == "" && root->right->data == "") return true; //왼쪽노드 오른쪽노드 둘다 data 가 ""이면 참을 반환.
    else return false; //아니면 거짓을 반환.
}

void del_data(Node* root,string name){ //대망의..... 값을 빼는 함수.
    set<string> s; // 59~67 : name이 해당되는 data가 없으면 그대로 함수를 종료.
	storeinorderInSet(root, s);
    set<string>::const_iterator it;
    for(it = s.begin(); it != s.end(); it++){
        if(*it == name){
            break;
        }
    }
    if(it == s.end()) return;

    if(root->data == name) { //name이 해당 노드의 data일때
        if(root->left->data == "" && root->right->data == "") {//해당 노드가 leaf 라면
            root->data=""; //해당 노드의 data를 지운다.
        }
        else if (root->left->data == "" && root->right->data != ""){ //해당 노드의 왼쪽 부트리가 없다면
            while(!is_leaf(root)){ // 74~85 : root가 leaf node 가 될때까지 오른쪽 부트리의 최솟값을 data에 넣고 최솟값을 가진 노드의 data를 지운다.
                for(auto it2 = s.begin(); it2 != s.end(); it2++){
                    if(*it2 == name){
                        it2++;
                        root->data = *it2;
                        break;
                    }
                }
                root = minnode(root->right);
                name = root->data;
            }
            root->data="";
        }
        else{ //해당 노드의 왼쪽 부트리가 있다면
            while(!is_leaf(root)){ // 88~100 : root가 leaf node 가 될때까지 왼쪽 부트리의 최댓값을 data에 넣고 최댓값을 가진 노드의 data를 지운다.
                for(auto it2 = s.begin(); it2 != s.end(); it2++){
                    if(*it2 == name){
                        it2--;
                        root->data = *it2;
                        break;
                    }
                }
                root = maxnode(root->left);
                name = root->data;
            }
            root->data="";
        }
        return; //위의 경우중 하나의 작업이 끝나면 함수를 종료한다.
    }
    else{ // name이 bst에 있지만 root->data 가 name이 아닌경우
        del_data(root->left,name); //104~105 : 왼쪽에서 오른쪽으로 해당 함수를 실행하며 지운다.
        del_data(root->right,name);
    }
}

void find_leaf(Node* root, vector<string> &leaf_node){//leafnode를 찾아서 벡터에 저장하는 함수.
    if (root->data == "")   return; //data가 없으면 함수종료.
    if(is_leaf(root))  { // 111~117 : 해당 노드가 leaf node 이면 벡터에 값을 저장하고 함수를 종료. 이 작업을 왼쪽부터 오른쪽으로 반복.
        leaf_node.push_back(root->data);
        return;
    }
    find_leaf(root->left,leaf_node);
    find_leaf(root->right,leaf_node);
}

void same_depth(Node* root,string k, vector<string> &depsame){ //깊이가 같은 노드를 벡터에 저장하는 함수.
    int num = stoi(k); //명령을 string으로 입력받았으므로, depth의 동일여부를 판단하기 위해 int로 변환한다.
    if (root->data == "")   return; //data가 없으면 함수종료.
    if(root->depth == num)  { // 122~128 : 해당 노드의 깊이가 num과 같으면 벡터에 값을 저장하고 함수를 종료. 이 작업을 왼쪽부터 오른쪽으로 반복.
        depsame.push_back(root->data);
        return;
    }
    same_depth(root->left, k,depsame);
    same_depth(root->right, k,depsame);
}

int main() {
    ifstream ipf("bst.inp");
    ofstream opf("bst.out");
    int N;
    ipf>>N;
    string command;
    vector<string> allcom;//input file 로 부터 받을 명령을 저장할 벡터
    vector<string> leaf;//leafnode들을 저장할 벡터
    vector<string> samedep;//같은 깊이의 노드들을 저장할 벡터.
    while(ipf>>command){
        allcom.push_back(command);
    }
    Node* root = new Node();
    for(auto it = allcom.begin(); it != allcom.end(); it++){
        if(*it == "+") {
            add_data(root,*(it+1)); //명령이 "+" 이면 add_data 실행.
        }
        else if(*it == "-") {
            del_data(root,*(it+1)); //명령이 "-" 이면 del_data 실행.
        }
        else if(*it == "leaf") { // 150~155 : 명령이 "leaf" 이면 기존의 leaf벡터는 초기화하고 find_leaf 실행후 leaf벡터 출력.
            leaf.clear();
            find_leaf(root,leaf);
            for(auto it : leaf) opf<<it<<" ";
            opf<<"\n";
        }
        else if(*it == "depth"){ // 156~164 : 명령이 "depth" 이면 기존의 samedep벡터는 초기화하고 same_dapth 실행후 
            samedep.clear(); //벡터가 비어있으면 "NO" 를 출력하고 원소가 있으면 원소를 출력.
            same_depth(root,*(it+1),samedep);
            if(!samedep.empty()){
                for(auto it : samedep) opf<<it<<" ";
            }
            else opf<<"NO";
            opf<<"\n";
        }
    }

    ipf.close();
    opf.close();
    return 0;
}