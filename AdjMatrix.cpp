// Code written by: Amar Suchak
// Code written on: 11/29/2018
// The code below uses solely an adjacency matrix to implement a very simple
// version of Google's pagerank algorithm.

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <map>
#include <math.h>
using namespace std;

bool isEdge(string from, string to, vector<pair<string, string>> input)
{
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].first == from)
            if (input[i].second == to)
                return true;
    }
    return false;
}

vector<vector<float>> GetInDegrees(
    map<string, int> outDegrees,
    vector<pair<string, string>> input,
    set<string> websites)
{
    vector<vector<float>> outDegrees2D;
    vector<vector<float>> inDegrees;

    auto it = websites.begin();
    for (int i = 0; it != websites.end(); i++, it++)
    {
        outDegrees2D.push_back(vector<float>());
        for (auto it2 = websites.begin(); it2 != websites.end(); it2++)
        {
            if (isEdge(*it, *it2, input))
                outDegrees2D[i].push_back(1);
            else
                outDegrees2D[i].push_back(0);
        }
    }

    auto it2 = outDegrees.begin();
    for (int i = 0; it2 != outDegrees.end(); i++, it2++)
    {
        inDegrees.push_back(vector<float>());
        auto it3 = outDegrees.begin();
        for (int j = 0; it3 != outDegrees.end() ; j++, it3++)
        {
            float temp;
            temp = outDegrees2D[j][i];
            temp = temp / outDegrees[it3->first];
            if (isnan(temp)) temp = 0.0f;
            inDegrees[i].push_back(temp);
        }
    }

    return inDegrees;
}

vector<vector<float>> InitializeGraph(int numEdges)
{
    vector<vector<float>> graphOfZeroes;
    for (int i = 0; i < numEdges; i++)
    {
        graphOfZeroes.push_back(vector<float>());
        for (int j = 0; j < numEdges; j++)
            graphOfZeroes[i].push_back(0);
    }
    return graphOfZeroes;
}

vector<float> PerformRotations(
    vector<vector<float>> graph,
    int numPowerIterations,
    set<string> websites)
{
    vector<float> resultVector, tempVector;

    auto it = websites.begin();
    for (int i = 0; it != websites.end(); i++, it++)
        resultVector.push_back(1.0f/graph.size());

    if (numPowerIterations <= 1)
        return resultVector;

    numPowerIterations--;

    for (int i = 0; i < resultVector.size(); i++)
        tempVector.push_back(resultVector[i]);

    for (int i = 0; i < numPowerIterations; i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < graph.size(); k++)
            {
                sum += graph[j][k] * resultVector[k];
            }
            tempVector[j] = sum;
        }
        resultVector = tempVector;
    }

    return resultVector;
}

int main(void)
{
    int numLines, numPowerIterations;
    cin >> numLines;
    cin >> numPowerIterations;
    vector<pair<string, string>> input;
    set<string> websites;
    map<string, int> outDegrees;
    vector<vector<float>> graph;

    for (int i = 0; i < numLines; i++)
    {
        pair<string, string> temp;
        // temp.first is from, temp.two is to
        cin >> temp.first;
        cin >> temp.second;
        websites.insert(temp.first);
        websites.insert(temp.second);
        input.push_back(temp);
        outDegrees[temp.first]++;
    }

    graph = GetInDegrees(outDegrees, input, websites);

    vector<float> resultVector = PerformRotations(graph, numPowerIterations, websites);

    auto it = websites.begin();
    cout << std::fixed << std::setprecision(2);
    for (int i = 0; it != websites.end(); i++, it++)
    {
        if (isnan(resultVector[i]))
            cout << *it << " 0.00" << endl;
        else
            cout << *it << " " << resultVector[i] << endl;
    }

    return 0;
}
