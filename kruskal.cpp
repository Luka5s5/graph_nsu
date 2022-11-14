#include <bits/stdc++.h>
#include "utils.cpp"
using namespace std;

// O (M log M + M*N)
vector<edge> kruskal_array(vector<edge> &g, int n, int m)
{
    int cost = 0;
    vector<edge> result;
    sort(g.begin(), g.end());
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++)
        tree_id[i] = i;
    for (int i = 0; i < m; i++)
    {
        int u = g[i].u, v = g[i].v, weight = g[i].weight;
        if (tree_id[u] != tree_id[v])
        {
            cost += weight;
            result.push_back(g[i]);
            int old_id = tree_id[u], new_id = tree_id[v];
            for (int j = 0; j < n; j++)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }
    return result;
}

// O (M log M)
vector<edge> kruskal_dsu(vector<edge> &g, int n, int m)
{
    int cost = 0;
    vector<edge> result;
    sort(g.begin(), g.end());
    dsu tree_id(n);
    for (int i = 0; i < m; i++)
    {
        int u = g[i].u, v = g[i].v, weight = g[i].weight;
        if (tree_id.leader(u) != tree_id.leader(v))
        {
            cost += weight;
            result.push_back(g[i]);
            tree_id.unite(v, u);
        }
    }
    return result;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<edge> g(m);
    for (int i = 0; i < m; i++)
        cin >> g[i];

    for (auto e : kruskal_dsu(g, n, m))
        cout << e << " ";
    cout << endl;

    for (auto e : kruskal_array(g, n, m))
        cout << e << " ";
    cout << endl;
}
