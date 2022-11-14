#include <bits/stdc++.h>
#include "utils.cpp"
using namespace std;

#define INF 100500

// O(n*m)
pair<vector<int>, vector<int>> fb_or(vector<edge> &g, int m, int n, int s)
{
    vector<int> d(n, INF), p(n, -2);
    d[s] = 0, p[s] = -1;
    int t = n;
    while (n--)
        for (auto e : g)
            if (d[e.u] < INF && d[e.u] + e.weight < d[e.v])
            {
                p[e.v] = e.u;
                d[e.v] = d[e.u] + e.weight;
            }
    return {d, p};
}

pair<vector<int>, vector<int>> fb_unor(vector<edge> &g, int m, int n, int s)
{
    vector<int> d(n, INF), p(n, -2);
    d[s] = 0, p[s] = -1;
    int t = n;
    while (n--)
        for (auto e : g)
        {
            if (d[e.u] < INF && d[e.u] + e.weight < d[e.v])
            {
                p[e.v] = e.u;
                d[e.v] = d[e.u] + e.weight;
            }
            if (d[e.v] < INF && d[e.v] + e.weight < d[e.u])
            {
                p[e.u] = e.v;
                d[e.u] = d[e.v] + e.weight;
            }
        }
    return {d, p};
}

// O(n*log m)
pair<vector<int>, vector<int>> dijkstra_or(vector<edge> &g, int m, int n, int s)
{
    auto rg = reformat_graph(g, m, n);
    vector<int> d(n, INF), p(n, -2);
    d[s] = 0;
    p[s] = -1;
    set<pair<int, int>> q;
    q.insert({d[s], s});
    while (!q.empty())
    {
        int u = q.begin()->second;
        q.erase(q.begin());
        for (auto e : rg[u])
        {
            int to = e.v;
            int len = e.weight;
            if (d[u] + len < d[to])
            {
                q.erase({d[to], to});
                d[to] = d[u] + len;
                p[to] = u;
                q.insert({d[to], to});
            }
        }
    }
    return {d, p};
}

pair<vector<int>, vector<int>> dijkstra_unor(vector<edge> &g, int m, int n, int s)
{
    vector<edge> g_copy = g;
    for (int i = 0; i < m; i++)
        g_copy.push_back(edge(g_copy[i].v, g_copy[i].u, g_copy[i].weight));
    return dijkstra_or(g_copy, 2 * m, n, s);
}

int main()
{
    int is_or, n, m, s;
    cin >> is_or >> n >> m >> s;
    s--;

    vector<edge> g(m);
    for (int i = 0; i < m; i++)
    {
        cin >> g[i];
        g[i].u--;
        g[i].v--;
    }

    pair<vector<int>, vector<int>> ans_check = is_or ? fb_or(g, m, n, s) : fb_unor(g, m, n, s);
    pair<vector<int>, vector<int>> ans = is_or ? dijkstra_or(g, m, n, s) : dijkstra_unor(g, m, n, s);
    cout << "fb ans:\n";
    for (auto i : ans_check.first)
    {
        cout << i << " ";
    }
    cout << endl;

    cout << "dijkstra ans:\n";
    for (auto i : ans.first)
    {
        cout << i << " ";
    }
    cout << endl;

    auto p = ans.second;
    cout << "paths:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "path to " << i + 1 << ": ";
        vector<int> path;
        for (int nxt = i; nxt != s; nxt = p[nxt])
            path.push_back(nxt);
        path.push_back(s);
        reverse(path.begin(), path.end());
        for (auto i : path)
            cout << i + 1 << " ";
        cout << endl;
    }
}