#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<utility>
#include<algorithm>
#define mytype char
#define INF 100000

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
map<mytype , mytype > parent;
map<mytype , int > depth;
map<mytype , char > color;

vector < mytype > v;

void BFS_VISIT( map<mytype , node* > ver , mytype s){
    color[s] = 'G';
    depth[s] = 0;
    queue < mytype > q;
    q.push(s);
    while(!q.empty()){
        mytype current = q.front();
        q.pop();
        node *t = ver[current];
        while(t != NULL){
            if(color[t->vertex] == 'W'){
                q.push(t->vertex);
                color[t->vertex] = 'G';
                depth[t->vertex] = (depth[current] + 1);
                parent[t->vertex] = current;
            }
            t = t -> next;
        }
        color[current] = 'B';
    }

}

void BFS( map<mytype , node* > ver){
    for(int i = 0 ; i < n ; i++){
        parent.insert(pair < mytype , mytype >(v[i] , '*'));
        depth.insert(pair < mytype , int >(v[i] , 10000000));
        color.insert(pair < mytype , char >(v[i] , 'W'));
    }

    for(int i = 0 ; i < n ; i++){
        if(color[v[i]] == 'W'){
            BFS_VISIT(ver , v[i]);
        }
    }

}

void Shortest_path(mytype source , mytype destination){
    mytype d = destination;
    stack < mytype > s;
    s.push(destination);
    while(destination != source){
        destination = parent[destination];
        s.push(destination);
    }
    cout << "Shortest path from " << source << " to " << d << " :\n\n";
    while(!s.empty()){
        cout << s.top() << " -> ";
        s.pop();
    }
    cout << endl;

}

bool sortbyweight(edge a , edge b){
    return a.weight<b.weight;
}

map < mytype , mytype > par;

void make_set(mytype node){
    par.insert(pair<mytype,mytype>(node,node));
}

mytype find_set(mytype n){
    if(par[n] == n){
        return n;
    }
    par[n] = find_set(par[n]);
    return par[n];
}

void union_set(mytype a , mytype b){
    mytype u = find_set(a);
    mytype v = find_set(b);
    par[u] = v;
}

void Kruskals_MST(map<mytype , node* > ver){

    vector < edge > taken;
    vector < edge > edges;
    for(int i = 0 ; i < n ; i++){
        struct node* t = ver[v[i]];
        t = t->next;
        while(t != NULL){
            edge e;
            e.u = v[i];
            e.v = t->vertex;
            e.weight = t->weight;
            edges.push_back(e);
            t = t->next;
        }

    }
    sort(edges.begin() , edges.end() , sortbyweight);
    vector < edge >::iterator it;

    for(int i = 0 ; i < n ; i++){
        make_set(v[i]);
    }
    for(it = edges.begin() ; it != edges.end() ; it++){
        edge e = *it;
        //cout << it-> u << " ->" << it->v << "( " << it->weight << ")" << endl;
        mytype u = find_set(it->u);
        mytype v = find_set(it->v);
        if(u != v){
            union_set(u , v);
            edge e;
            e.u = it-> u;
            e.v = it-> v;
            e.weight = it->weight;
            taken.push_back(e);
        }
    }

    int sum = 0;
    for(int i = 0 ; i < taken.size() ; i++){
        edge e = taken[i];
        cout << e.u << " -> " << e.v << endl;
        sum += e.weight;
    }
    cout << "Cost : " << sum << endl;
}

void Prims_MST(map<mytype , node* > ver , mytype root){
    priority_queue < pair<int , mytype> , vector < pair<int , mytype> > , greater< pair <int , mytype> > > pq;
    map <mytype , int> key;
    map <mytype , bool> inqueue;
    map <mytype , mytype> par;
    for(int i = 0 ; i < n ; i++){
        key.insert(make_pair(v[i] , INF));
        inqueue.insert(make_pair(v[i] , false));
        par.insert(make_pair(v[i] , '*'));
    }
    pq.push(make_pair(0 , root));
    key[root] = 0;
    inqueue[root] = true;

    while(!pq.empty()){
        mytype u = pq.top().second;
        pq.pop();
        inqueue[u] = true;

        node* adj = ver[u];
        adj = adj->next;
        while(adj != NULL){
            if(adj->weight < key[adj->vertex] && inqueue[adj->vertex] == false){
                key[adj->vertex] = adj->weight;
                par[adj->vertex] = u;
                pq.push(make_pair(key[adj->vertex] , adj->vertex));
            }
            adj = adj->next;
        }
    }
    map <mytype , mytype>:: iterator it;
    int cost = 0;
    for(it = par.begin() ; it != par.end() ; ++it){
        cout << it->second << " -> " << it->first << endl;
        cost += key[it->first];
    }
    cout << "Cost : " << cost << endl;
}

int main()
{
    cout << "Nodes ? " << endl;
    cin >> n;

    map<mytype , int > od;
    map<mytype , int > id;
    map<mytype , node* > ver;


    cout << "Enter " << n << " vertices : " << endl;
    for(int i = 0 ; i < n ; i++){
        mytype x;
        cin >> x;
        v.push_back(x);
        od.insert(pair<mytype , int>(v[i] , 0));
        id.insert(pair<mytype , int>(v[i] , 0));
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

    //OutDegree
    for(int i = 0 ; i < n ; i++){
        node *temp = ver[v[i]];
        temp = temp->next;
        while(temp != NULL){
            od[ver[v[i]]->vertex] = od[ver[v[i]]->vertex] + 1;
            temp = temp->next;
        }
    }

    //InDegree
    for(int i = 0 ; i < n ; i++){
        node *temp = ver[v[i]];
        temp = temp->next;
        while(temp != NULL){
            id[temp->vertex] = id[temp->vertex] + 1;;
            temp = temp->next;
        }
    }

    map<mytype , int >::iterator it1,it2;
    int odeg = 0;
    for(it1 = id.begin() ; it1 != id.end() ; ++it1){
        odeg +=  it1->second;
    }
    int ideg = 0;
    cout << endl;
    for(it2 = od.begin() ; it2 != od.end() ; ++it2){
        ideg +=  it2->second;
    }

    cout << "Outdegree : " << odeg << "\nIndegree :  " << ideg << endl << endl;

    BFS(ver);


    map<mytype , int >::iterator it;
    for(it = depth.begin() ; it != depth.end() ; ++it){
        cout << "Depth of " << it->first << " is " << it->second << endl;
    }
    cout << endl;

    map<mytype , char >::iterator it3;
    for(it3 = color.begin() ; it3 != color.end() ; ++it3){
        cout << "color of " << it3->first << " is " << it3->second << endl;
    }
    cout << endl;

    map<mytype , mytype >::iterator it4;
    for(it4 = parent.begin() ; it4 != parent.end() ; ++it4){
        cout << "parent of " << it4->first << " is " << it4->second << endl;
    }
    cout << endl;

    Shortest_path('A' , 'D');

    cout << "\n(Prim's) Edges of Minimum Spanning tree : \n";
    Prims_MST(ver , 'G');
    cout << "\n(Kruskal's) Edges of Minimum Spanning tree : \n";
    Kruskals_MST(ver);




}


/*
8
r
s
t
u
v
w
x
y
2
s
v
2
r
w
3
w
x
u
2
t
y
1
r
3
s
t
x
3
w
t
y
2
x
u
*/

/*
8
A
B
C
D
E
F
G
H
2
B
4
H
6
4
H
5
A
4
C
9
E
2
1
B
9
1
E
15
3
F
8
B
2
D
15
3
G
3
H
10
E
8
2
H
14
F
3
4
A
6
B
5
F
10
G
14
*/

