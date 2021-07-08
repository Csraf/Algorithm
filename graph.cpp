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

/**G model
	0->2->4
    1->0->2
    2->3
    3->4
    4->3
**/



struct Node{
    int v; // 边的终点号
    int w; // 边权
    Node(int _v, int _w) : v(_v), w( _w) {}
};

void dfs(int u, int d, vector<vector<Node>>& aj, vector<bool> &vis){
    /**
     * u: 当前访问顶点号
     * d: 深度
     * aj: 图的邻接表
     * vis: 标记数组, 该顶点是否被访问过
     */
    for(int i=0; i<aj[u].size(); i++){
        int v = aj[u][i].v, w = aj[u][i].w;
        if(vis[v] == false){
            vis[v] = true;
            cout << "point " << u << " -> " << v << " w " << w << " d " << d << endl;
            dfs(v, d+1, aj, vis);
            vis[v] = false;
        }
    }
}


void bfs(int u, vector<vector<Node>>& aj, vector<bool> &vis){
    queue<int> q;
    cout << "point " << u << endl;
    q.push(u);
    vis[u] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0; i<aj[u].size(); i++){
            int v = aj[u][i].v, w = aj[u][i].w;
            if(vis[v] == false){
                cout << "point " << v << endl;
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

void dijkstra(int s, vector<vector<Node>>& aj, vector<bool> &vis, vector<int> &dis){ 
    /**
     * s: 起点
     * u: 中介点, 看做每一步的新起点
     * v: 终点, 看做这一步能访问到的点
     * aj: 邻接表
     * vis: 标记该顶点是否被访问
     * dis: 起点到当前点的最短距离
     */ 
    int n = aj.size();
    dis[s] = 0;
    for(int i=0; i<n; i++){
        int u = -1, mn = 0x7fffffff/3; 
        // [1]. 选取新的中介点 u, u 到 s 的距离最短, u 未被访问过
        for(int j=0; j<n; j++){
            if(vis[j] == false && dis[j] < mn){
                u = j;
                mn = dis[j];
            }
        }
        if(u == -1) return ;
        vis[u] = true;
        // [2]. 遍历中介点能访问到的所有顶点 v, 如果能让v更小, 则更新
        for(int j=0; j<aj[u].size(); j++){
            int v = aj[u][j].v, w = aj[u][j].w;
            if(vis[v] == false && dis[u] + w < dis[v]){
                    dis[v] = dis[u] + w;
            }
        }
    }
}

void floyd(vector<vector<int>>& graph){
    int n = graph.size();
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(graph[i][k] != 0x7fffffff/3 && graph[k][j] != 0x7fffffff/3 &&
                   graph[i][k] + graph[k][j] < graph[i][j]){
                       graph[i][j] = graph[i][k] + graph[k][j]; // 更短路径
                   }
            }
        }
    }
}


int main(){
    // 图的存储
    const int N = 5; 
    const int maxValue = 0x7fffffff/3; // 图的题目, 上限一般不是整数最大值

    // 邻接矩阵
    vector<vector<int>> graph(N, vector<int>(N, 0x7fffffff/3));
    graph[0][2] = 1;
    graph[0][4] = 1;
    graph[1][0] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][3] = 1;
    // graph[i][j] = k 顶点 i->j 的边权 k 


    // 邻接表 
    vector<vector<Node>> aj(N, vector<Node>());
    aj[0].push_back(Node(2, 1));
    aj[0].push_back(Node(4, 1));
    aj[1].push_back(Node(0, 1));
    aj[1].push_back(Node(2, 1));
    aj[2].push_back(Node(3, 1));
    aj[3].push_back(Node(4, 1)); 
    aj[4].push_back(Node(3, 1)); 
    // aj[i].push_back(Node(v, w)) 顶点 i->v 的边权 k 


    // 图的遍历 -- 深度遍历
    // 遍历每个节点, 遍历过的元素仍然能够遍历
    vector<bool> vis(N, false);
    for(int u=0; u<N; u++){
        if(vis[u] == false){
            vis[u] == true;
            dfs(u, 1, aj, vis);
            vis[u] == false;
        }
    }

    // 图的遍历 -- 广度遍历
    // 遍历每个节点, 遍历过的元素无法再次遍历
    for(int u=0; u<N; u++){
        if(vis[u] == false){
            bfs(u, aj, vis);
        }
    }

    // 单源最短路径 -- dijkstra 
    // 时间复杂度: O(n^2)
    // [1]. 每次选择一个未访问过的, 并且与起点 s 距离最短的顶点 u.
    // [2]. 顶点 v 表示顶点 u 能到达的所有点距离, 优化起点 s 到顶点 v 之间距离.


    for(int i=0;i<vis.size();i++){vis[i] = false;}
    vector<int> dis(N, 0x7fffffff/3); // 起点到达各点的最短路径长度
    dijkstra(0, aj, vis, dis);
    cout << dis[0] << " " << dis[1] << " " << dis[2] << " " << dis[3] << " " << dis[4] << endl; 


    // 全源最短路径 -- floyd 
    // 时间复杂度: O(n^3)
    // 题目中一般节点数不超过 200, 一般使用邻接矩阵存储.

    floyd(graph);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    // 最小生成树
    


    // 拓扑排序




    return 0;
}