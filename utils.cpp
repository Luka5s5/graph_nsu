#include <bits/stdc++.h>
using namespace std;

struct dsu
{
    vector<int> parent, size;

    dsu() : dsu(0) {}

    dsu(int n)
    {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i, size[i] = 1;
    }

    int leader(int v)
    {
        return (parent[v] == v) ? v : parent[v] = leader(parent[v]);
    }

    void unite(int a, int b)
    {
        a = leader(a), b = leader(b);
        if (size[a] > size[b])
            swap(a, b);
        size[b] += size[a];
        parent[a] = b;
    }
};

struct edge
{
    int u, v, weight;

    edge(int _u, int _v, int _weight) : u{_u}, v{_v}, weight{_weight} {}
    edge() : edge(0, 0, 0) {}

    bool operator<(const edge &other)
    {
        return this->weight < other.weight;
    }

    friend ostream &operator<<(ostream &os, const edge &e)
    {
        os << "(" << e.u << ", " << e.v << ", " << e.weight << ")";
        return os;
    }

    friend istream &operator>>(istream &is, edge &e)
    {
        is >> e.u >> e.v >> e.weight;
        return is;
    }
};
