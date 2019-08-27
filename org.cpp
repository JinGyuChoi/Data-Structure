#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
        string data;
        int depth = 1;
        list<Node*> children;
        Node* parents = nullptr;
        ~Node(){
            data.clear();
            children.clear();
            parents -> ~Node();
        }
};

Node* find_root(list<Node*> &vnp){
    Node* root = new Node();
    for(auto it = vnp.begin(); it != vnp.end(); it++){
        if((*it)->parents == nullptr) {
            root = (*it);
            break;
        }
    }
    root->depth = 0;
    return root;
}

bool isMember(list<Node*> &vnp, Node* n)
{
    for(auto it = vnp.begin(); it != vnp.end(); it++){
        if((*it)->data == n -> data)  return true;
    }
    return false;
}

bool compare_node (Node* n1, Node* n2) {
    if (n1->children.size() > n2->children.size())
        return true;
    else if (n1->children.size() < n2->children.size())
        return false;
    else{
        if(n1->depth < n2->depth)
            return true;
        else if(n1->depth > n2->depth)
            return false;
        else{
            if(n1->data < n2->data)
                return true;
            else
                return false;
        }
    }
}

list<Node*> find_relation(list<Node*> &vnp){
    list<Node*> temp;
    for(auto it1 = vnp.begin(); it1 != vnp.end(); it1++){
        if(!(*it1)->children.empty()){
            auto it2 = it1;
            it2++;
            for(it2; it2 != vnp.end(); it2++){
                if((*it1)->data == (*it2)->data){
                    (*it1)->children.push_back((*it2)->children.front());
                    (*it2)->children.clear();
                }
            }
            temp.push_back(*it1);
        }
    }
    for(auto it = temp.begin(); it != temp.end(); it++){
        for(auto it2 = (*it)->children.begin(); it2 != (*it)->children.end(); it2++) (*it2)->parents = *it;
    }
    for(auto it = temp.begin(); it != temp.end(); it++){
        for(auto it2 = temp.begin(); it2 != temp.end(); it2++){
            if(it != it2){
                for(auto it3 = (*it2)->children.begin(); it3 != (*it2)->children.end(); it3++){
                    if((*it)->data == (*it3)->data) {
                        (*it)->parents = (*it2);
                        break;
                    }
                }
            }
        }
    }
    return temp;
}

void all_relation(list<Node*> &vnp,Node* root){
    for(auto it = root->children.begin(); it != root->children.end(); it++){
        if(!((*it)->children.empty())){
            for(auto it2 = (*it)->children.begin(); it2 != (*it)->children.end(); it2++) root->children.push_back(*it2);
        }
    }
}

void integrate(list<Node*> &vnp){
    for(auto it = vnp.begin(); it != vnp.end(); it++){
        if((*it)->parents != nullptr && !((*it)->children.empty())){
            for(auto it2 = (*it)->children.begin(); it2 != (*it)->children.end(); it2++){
                if(!isMember((*it)->parents->children,*it2)){
                    (*it2)->depth++;
                    (*it)->parents->children.push_back(*it2);
                }
            }
        }
    }
}

int main() {
    ifstream ipf("org.inp");
    ofstream opf("org.out");

    int N;
    ipf>>N;
    string name, boss;
    list<Node*> people;
    while(ipf>>name>>boss){
        Node* person1 = new Node();
        Node* person2 = new Node();
        person1 -> data = name;
        person2 -> data = boss;
        person2 -> children.push_back(person1);
        people.push_back(person2);
    }
    people = find_relation(people);
    Node* root = new Node();
    root = find_root(people);
    do{
        integrate(people);
    } while(root->children.size() < N-1);
    
    list<Node*> allpeople;
    allpeople.push_back(root);
    for(auto it = root->children.begin(); it != root->children.end(); it++) allpeople.push_back(*it);
    for(auto it = allpeople.begin(); it != allpeople.end(); it++) {
        for(auto it2 = people.begin(); it2 != people.end(); it2++){
            if((*it)->data == (*it2)->data){
                (*it2)->depth = (*it)->depth;
                *it = *it2;
            }
        }
    }
    allpeople.sort(compare_node);
    for(auto it = allpeople.begin(); it != allpeople.end(); it++){
        opf<<(*it)->data<<" ";
    }
    ipf.close();
    opf.close();
    return 0;
}