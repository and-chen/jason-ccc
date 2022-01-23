//
// CCC '18 J5 - Choose your own path
// https://dmoj.ca/problem/ccc18j5
//

#include <vector>
#include <iostream>
#include <queue>  
using namespace std;

class Node {
public:
    int id;
    bool visited;
    vector<Node*> Children;
    Node* Pred;
};


void bfs(Node** p, int n) {
    for (int i = 0; i < n; i++)
    {
        p[i]->visited = false;
        p[i]->Pred = nullptr;
    }

    queue<Node*> q;
    p[0]->visited = true;

    q.push(p[0]);

    while (q.size() != 0)
    {
        Node* cur = q.front();
        q.pop();
        for (int i = 0; i < cur->Children.size(); i++)
        {
            Node* next = cur->Children[i];
            if (next->visited == false) {
                next->visited = true;
                next->Pred = cur;
                q.push(next);
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;

    Node** Pages = new Node* [N];

    for (int i = 0; i < N; i++)
    {
        Node* pg = new Node();
        pg->id = i;
        Pages[i] = pg;
    }

    for (int i = 0; i < N; i++)
    {
        int Mi;
        cin >> Mi;
        for (int j = 0; j < Mi; j++) {
            int op;
            cin >> op;
            Pages[i]->Children.push_back(Pages[op - 1]);
        }
    }

    bfs(Pages, N);

    bool h = true;
    for (int i = 0; i < N; i++)
    {
        if (!Pages[i]->visited) {
            h = false;
            break;
        }
    }

    if (h) {
        cout << 'Y' << endl;
    }
    else {
        cout << 'N' << endl;
    }

    int shortest = 99999999;
    for (int i = 0; i < N; i++) {
        Node* cur = Pages[i];
        if (cur->Children.size() == 0) {
            //cout << "id: " << cur->id + 1 << endl;
            int count = 1;
            while (cur->Pred) {
                count++;
                cur = cur->Pred;    
                //cout << "\t next: " << cur->id + 1 << endl;
            }
            if (cur == Pages[0] && count < shortest) {
                shortest = count;
            }
        }
    }

    cout << shortest << endl;

    for (int i = 0; i < N; i++)
    {
        delete Pages[i];
    }
    delete[] Pages;
}