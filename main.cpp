#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <map>
#include <math.h>
using namespace std;

// 7 100
// google.com gmail.com
// google.com maps.com
// facebook.com ufl.edu
// ufl.edu google.com
// ufl.edu gmail.com
// maps.com facebook.com
// gmail.com maps.com

// 0 0 0 1 0
// 0 0 0.5 0 0.5
// 0 0 0 0 0.5
// 0 1 0.5 0 0
// 1 0 0 0 0

class Graph
{
    map<string, vector<string>> adjacencyList;
    set<string> vertices;

    vector<vector<float>> adjacencyMatrix;

    vector<vector<float>> outDegrees;
    vector<vector<float>> inDegrees;

public:
    void Insert(string from, string to);
    void Print();
    void CreateAdjacencyMatrix();
    vector<vector<float>> GetOutDegrees();
    vector<vector<float>> GetInDegree();
    void PerformRotations(int numberOfRotations);

    bool isEdge(string from, string to);

};

// Inserts values into the graph:
void Graph::Insert(string from, string to)
{
    adjacencyList[from].push_back(to);
    vertices.insert(from);
    vertices.insert(to);
}

// Prints out the graph and everything that it's pointing to
void Graph::Print()
{
    cout << endl;
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

vector<vector<float>> InitializeMatrix(int n)
{
    vector<vector<float>> returnMatrix;

    for (int i = 0; i < n; i++)
    {
        returnMatrix.push_back(vector<float>());
        for (int j = 0; j < n; j++)
        {
            returnMatrix[i].push_back(0.0f);
        }
    }
    return returnMatrix;
}

void PrintMatrix(vector<vector<float>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

bool Graph::isEdge(string from, string to)
{
    vector<string> temp = adjacencyList[from];
    for (int i = 0; i < temp.size(); i++)
        if (temp[i] == to)
            return true;
    return false;
}

vector<vector<float>> Graph::GetOutDegrees()
{
    vector<vector<float>> outDegrees;
    auto it = vertices.begin();
    for (int i = 0; it != vertices.end(); i++, it++)
    {
        outDegrees.push_back(vector<float>());
        for (auto it2 = vertices.begin(); it2 != vertices.end(); it2++)
        {
            if (isEdge(*it, *it2))
                outDegrees[i].push_back(1);
            else
                outDegrees[i].push_back(0);
        }
    }
    return outDegrees;
}

vector<int> GetNumberOfOnes(vector<vector<float>> vec)
{
    vector<int> returnValue;
    int sumOfOnes;

    for (int i = 0; i < vec.size(); i++)
    {
        sumOfOnes = 0;
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec[i][j] == 1)
                sumOfOnes++;
        }
        returnValue.push_back(sumOfOnes);
    }
    return returnValue;
}

vector<vector<float>> Graph::GetInDegree()
{
    vector<vector<float>> inDegrees = InitializeMatrix(outDegrees.size());

    for (int i = 0; i < outDegrees.size(); i++)
    {
        for (int j = 0; j < outDegrees.size(); j++)
            inDegrees[i][j] = outDegrees[j][i];
    }

    vector<int> numberOfOnes = GetNumberOfOnes(outDegrees);
    for (int i = 0; i < outDegrees.size(); i++)
    {
        for (int j = 0; j < outDegrees.size(); j++)
        {
            inDegrees[i][j] = inDegrees[i][j] / numberOfOnes[j];
            if (isnan(inDegrees[i][j]))
                inDegrees[i][j] = 0.0f;

        }
    }

    return inDegrees;
}

void Graph::CreateAdjacencyMatrix()
{
    outDegrees = GetOutDegrees();
    inDegrees = GetInDegree();

    // cout << "Outdegree matrix: " << endl;
    // PrintMatrix(outDegrees);
    // cout << "Indegree matrix: " << endl;
    // PrintMatrix(inDegrees);
}

void Graph::PerformRotations(int numberOfRotations)
{
    adjacencyMatrix = InitializeMatrix(outDegrees.size());
    vector<float> resultVector;

    // Second rotation stuff:
    for (int i = 0; i < inDegrees.size(); i++)
    {
        float sum = 0.0f;
        for (int j = 0; j < inDegrees.size(); j++)
        {
            sum += inDegrees[i][j];
        }
        resultVector.push_back(sum * (1.0f / inDegrees.size()));
    }

    vector<float> tempVector;
    // cout << "Results vector: " << endl;
    for (int i = 0; i < resultVector.size(); i++)
        tempVector.push_back(resultVector[i]);
    // cout << endl;

    // Rest of the rotations stuff:
    numberOfRotations -= 2;
    if (numberOfRotations > 0)
    {
        for (int k = 0; k < numberOfRotations; k++)
        {
            for (int i = 0; i < inDegrees.size(); i++)
            {
                float sum = 0.0f;
                for (int j = 0; j < inDegrees.size(); j++)
                {
                    sum += inDegrees[i][j] * resultVector[j];
                }
                tempVector[i] = sum;
                // resultVector[i] = sum * (1.0f / inDegrees.size());
            }
            resultVector = tempVector;
        }
    }

    auto it = vertices.begin();
    cout << std::fixed << std::setprecision(2);
    for (int i = 0; it != vertices.end() ; i++, it++)
        if (isnan(resultVector[i]))
            cout << *it << " 0.00" << endl;
        else
            cout << *it << " " << resultVector[i] << endl;


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

    graph.CreateAdjacencyMatrix();

    graph.PerformRotations(numPowerIterations);

    return 0;
}
