#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<utility>
#include<algorithm>
#define mytype string
#define INF 10000000

using namespace std;

struct node
{
    mytype vertex;
    int weight;
    struct node *next;
};


int n;
vector < mytype > v;



void Dijkstra(map<mytype , node* > ver , mytype source){
    map < mytype , int > distance;
    priority_queue < pair<int , mytype> , vector < pair<int , mytype> > , greater< pair <int , mytype> > > pq;

    for(int i = 0 ; i < n ; i++){
        distance.insert(pair<mytype , int>(v[i] , INF));
    }
    distance[source] = 0;
    pq.push(make_pair(0 , source));

    while(!pq.empty()){
        mytype u = pq.top().second;
        pq.pop();
        node* adj = ver[u];
        adj = adj->next;
        while(adj != NULL){
            if(distance[adj->vertex] > distance[u] + adj->weight){
                distance[adj->vertex] = distance[u] + adj->weight;
                pq.push(make_pair(distance[adj->vertex] , adj->vertex));
            }
            adj = adj->next;
        }
    }
    map < mytype , int > :: iterator it;
    for(it = distance.begin() ; it != distance.end() ; it++){
        cout << "Distance[" << it->first << "] = " << it->second << endl;
    }
}



int main()
{
    cout << "Nodes ? " << endl;
    cin >> n;

    map<mytype , node* > ver;

    cout << "Enter " << n << " vertices : " << endl;
    for(int i = 0 ; i < n ; i++){
        mytype x;
        cin >> x;
        v.push_back(x);
    }

    for(int i = 0 ; i < n ; i++){
        cout << "Enter number of Adjacence node of " << v[i] << " : \n";
        int e;
        cin >> e;
        node *head = new node();
        head->vertex = v[i];
        head->next = NULL;
        node *current = head;
        cout << "Enter Adjacence nodes of " << v[i] << " : \n";
        for(int j = 0 ; j < e ; j++){
            mytype val;
            cin >> val;
            cout << "Enter weight of " << v[i] << " -> " << val << " :\n";
            int w;
            cin >> w;
            node *neww = new node();
            neww->vertex = val;
            neww->weight = w;
            current->next = neww;
            neww->next = NULL;
            current = neww;
        }
        ver.insert(pair < mytype , node* >(v[i] , head));

    }

    Dijkstra(ver , "s"); //Manually set the source in argument

}


/*
Input
5
s
u
v
x
y
2
u
10
x
5
2
v
1
x
2
1
y
4
3
u
3
v
9
y
2
2
s
7
v
6
*/

