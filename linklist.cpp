#include <string>
#include <iostream>
using namespace std;

int myStoi(string s){
        int sum = 0;
        for(int i=0; i<s.size(); i++){
            sum = sum*10 + (s[i]-'0');
        }
        return sum;
    }
int main(){
    int a = myStoi("123243430");
    cout << a << endl;
    return 0;
}