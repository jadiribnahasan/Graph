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

struct edge
{
    mytype u , v;
    int weight;
};


int n;
vector < mytype > v;
vector < edge > E;

map < mytype , int > secdistance;

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
                edge e;
                e.u = u;
                e.v = adj->vertex;
                e.weight = adj->weight;
                E.push_back(e);
            }
            adj = adj->next;
        }
    }
    map < mytype , int > :: iterator it;
    for(it = distance.begin() ; it != distance.end() ; it++){
        cout << "Distance[" << it->first << "] = " << it->second << endl;
    }

}


void SDijkstra(edge e , map<mytype , node* > ver , mytype source){
    priority_queue < pair<int , mytype> , vector < pair<int , mytype> > , greater< pair <int , mytype> > > pq;
    map < mytype , int > distance;
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
            if((distance[adj->vertex] > distance[u] + adj->weight)){
                if(!((u == e.u && adj->vertex == e.v) || (u == e.v && adj->vertex == e.u))){
                    distance[adj->vertex] = distance[u] + adj->weight;
                    pq.push(make_pair(distance[adj->vertex] , adj->vertex));
                }

            }
            adj = adj->next;
        }
    }
    for(int i = 0 ; i < n ; i++){
        secdistance[v[i]] = min(secdistance[v[i]] , distance[v[i]]);
        cout << secdistance[v[i]] << " " << distance[v[i]] << endl;
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

    Dijkstra(ver , "c"); //Manually set the source in argument

    for(int i = 0 ; i < n ; i++){
        secdistance[v[i]] = INF;
    }
    vector < edge > :: iterator t;
    for(t = E.begin() ; t != E.end() ; t++){
        cout << t->u << " -> " << t->v << " - " << t->weight << endl;
        SDijkstra(*t , ver , "c");
    }
    map < mytype , int > :: iterator it;
    for(it = secdistance.begin() ; it != secdistance.end() ; it++){
        cout << "Sec_Distance[" << it->first << "] = " << it->second << endl;
    }


}




