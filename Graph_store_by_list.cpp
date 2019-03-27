#include<bits/stdc++.h>
#include<vector>
#include<map>
#define mytype char

using namespace std;

struct node
{
    mytype vertex;
    struct node *next;
};

int main()
{
    int n;
    cout << "Nodes ? " << endl;
    cin >> n;

    map<mytype , int > od;
    map<mytype , int > id;
    vector < struct node* > var;
    vector < mytype > v(n);

    cout << "Enter " << n << " vertices : " << endl;
    for(int i = 0 ; i < n ; i++){
        cin >> v[i];
        od.insert(pair<mytype , int>(v[i] , 0));
        id.insert(pair<mytype , int>(v[i] , 0));
    }


    for(int i = 0 ; i < n ; i++){
        cout << "Enter number of Adjacence node of " << v[i] << " : \n";
        int e;
        cin >> e;
        struct node *head = new node();
        head->vertex = v[i];
        head->next = NULL;
        struct node *current = head;
        cout << "Enter Adjacence nodes of " << v[i] << " : \n";
        for(int j = 0 ; j < e ; j++){
            mytype val;
            cin >> val;
            struct node *neww = new node();
            neww->vertex = val;
            current->next = neww;
            neww->next = NULL;
            current = neww;
        }
        var.push_back(head);

    }

    //OutDegree
    for(int i = 0 ; i < n ; i++){
        struct node *temp = var[i];
        temp = temp->next;
        while(temp != NULL){
            //cout << temp->vertex << endl;
            od[var[i]->vertex] = od[var[i]->vertex] + 1;
            temp = temp->next;
        }
    }

    //InDegree
    for(int i = 0 ; i < n ; i++){
        struct node *temp = var[i];
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

    cout << "Outdegree : " << odeg << "\nIndegree :  " << ideg << endl;
    cout << od['B'] << endl;

}
