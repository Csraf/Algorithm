#include<iostream>
#include<string>
#include<vector>

using namespace std;

bool hashTable[11]={false};
void dfs(int index, int n, string &item, string str, vector<string> &vs){
    if(index == n){
        vs.push_back(item);
        cout<< "##### " << item << endl; 
        return ;
    }
    for(int i=0; i<n; i++){
        cout << "index " << index << " i " << i << endl;
        for(int j=0; j<2; j++){
            cout << "hashTable[i] " << hashTable[j] << " ";
        }
        if(hashTable[i] == false){
            hashTable[i] = true;
            item.push_back(str[i]);
            cout<< "before " << item << endl;
            dfs(index+1, n, item, str, vs);
            cout<< "after " << item << endl;
            item.pop_back();
            hashTable[i] = false;
            cout << hashTable[i] << endl;
        }
    }
}

vector<string> Permutation(string str) {
    vector<string> vs;
    // for(int i=0; i<1001; i++){
    //     hashTable.push_back(false);
    // }
    string item="";
    if(str.size() == 0) return vs;
    dfs(0, str.size(), item, str, vs);
    return vs;
}

int main(){
    string str = "ab";
    vector<string> v = Permutation(str);
    for(int i=0; i<v.size(); i++){
        cout << v[i] << endl;
    }

    return 0;
}