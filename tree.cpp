#include<stdio.h>
#include<iostream>
#include<utility>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;

/* 
 * 0. 创建
 * 1. dfs
 * 2. bfs
 * 3. 最短路径: dijkstra, floyd
 * 4. 最小生成树
 * 5. 拓扑排序 
 */

// typedef struct TreeNode{
//     int val; 
//     TreeNode *left, *right;
// }TreeNode;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


int main(){
    // 树
    TreeNode *root = new TreeNode(0);
    cout << root->val;
    cout << root->left;
    cout << root->right;
    return 0;
}