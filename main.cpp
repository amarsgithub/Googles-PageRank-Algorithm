#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

// 7 2
// google.com gmail.com
// google.com maps.com
// facebook.com ufl.edu
// ufl.edu google.com
// ufl.edu gmail.com
// maps.com facebook.com
// gmail.com maps.com

class Graph
{
    map<string, vector<string>> adjacencyList;
    set<string> vertices;
public:
    void Insert(string from, string to);
    void Print();

};

void Graph::Insert(string from, string to)
{
    adjacencyList[from].push_back(to);
    vertices.insert(from);
    vertices.insert(to);
}

void Graph::Print()
{
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        cout << *it << " points to: " << endl;
        vector<string> temp = adjacencyList[*it];
        for (int i = 0; i < temp.size(); i++)
        {
            cout << temp[i] << endl;
        }
        cout << endl;
    }
}

int main(void)
{
    int numLines, numPowerIterations;
    cin >> numLines;
    cin >> numPowerIterations;
    string to, from, temp, temp2;
    Graph graph;

    for (int i = 0; i < numLines; i++)
    {
        cin >> from;
        cin >> to;
        graph.Insert(from, to);
    }

    cout << endl; 
    graph.Print();

    return 0;
}
