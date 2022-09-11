#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define for0(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>
#define pb push_back
#define sz(x) sizeof(x)
#define vec(n, x) vector<int> v(n, x)
const ll INF = 1e18;
const ll MOD = 1000000007;
#define hi        \
    ll tests;     \
    cin >> tests; \
    while (tests--)
#define all(x) x.begin(), x.end()
#define readv(vec)      \
    for (auto &x : vec) \
    {                   \
        cin >> x;       \
    }
#define PHI M_PI
#define graph                   \
    int V;                      \
    cin >> V;                   \
    vector<int> adj[V];         \
    int e;                      \
    for (int i = 0; i < e; i++) \
    {                           \
        int u, v;               \
        cin >> u >> v;          \
        adj[u].push_back(v);    \
        adj[v].push_back(u);    \
    }
#define printv(vec)       \
    for (auto x : vec)    \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl;
#define sortasc(vec) sort(all(vec));
#define sortdes(vec) sort(vec.rbegin(), vec.rend());
#define setpre(x) cout << fixed << setprecision(10) << x << endl
#define kick cout << 'C' << 'a' << 's' << 'e' << ' ' << '#' << k << ':' << ' '
vector<ll> sieve(int n)
{
    int *arr = new int[n + 1]();
    vector<ll> vect;
    for (int i = 2; i <= n; i++)
        if (arr[i] == 0)
        {
            vect.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                arr[j] = 1;
        }
    return vect;
}
bool pal(string s)
{
    int i = 0;
    int j = s.size() - 1;
    while (i < j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
ll op1(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a + b) % m) + m) % m;
}
ll op2(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a * b) % m) + m) % m;
}
ll op3(ll a, ll b, ll m)
{
    a = a % m;
    b = b % m;
    return (((a - b) % m) + m) % m;
}
int powerexpo(int x, int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
        {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll C(ll a, ll b) { return (a + b - 1) / b; }
struct unionfind
{
    int n;
    vector<int> rank;
    vector<int> parent;
    unionfind(int n)
    {
        rank.resize(n);
        fill(rank.begin(), rank.end(), 0);
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int node)
    {
        if (node == parent[node])
        {
            return node;
        }
        else
        {
            return parent[node] = find(parent[node]);
        }
    }
    bool Union(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
        {
            return false;
        }
        if (rank[u] < rank[v])
        {
            parent[u] = v;
        }
        else if (rank[u] > rank[v])
        {
            parent[v] = u;
        }
        else
        {
            parent[v] = u;
            rank[u]++;
        }
        return true;
    }
};
// code by CasioFx-69
struct sparce
{
    vector<int>v;
    int n;
    int k;
    vector<vector<int>>table;
    sparce(vector<int>&arr){
        v=arr;
        n = v.size();
        k = log2(n); //max segment that 2^k can be form;
        // E.G.-> 9 -> log2(9)->3
        // 2 3 9 2 4 16 9 12 15
        // rows are 
        //2^0 -> 2 3 9 2 4 16 9 12 15 
        //2^1 -> 2 3 2 2 4 6 9 12
        //2^2 -> 2 2 2 2 4 6 
        //2^3 -> 2 2
        vector<vector<int>>s(k+1,vector<int>(n,0));
        table = s;
    }

    void build()
    {
        table[0] = v;
        for(int row = 1;row<=k;row++){
            //for each 2^1 , 2^2 ..... , 2^k;
            for(int col =0;(col+((1<<row)-1))<n;col++){
                // col should be col + (row^2 - 1) < n 
                //e.g -> we are at col 5 [val==16] and row is 3->2^2 , we have to start 5,6,7,8 min val
                //    -> 5 + pow(2^2) - 1  is less than 10.
                table[row][col] = min(table[row-1][col],table[row-1][col+(1<<(row-1))]);
                // uprowcol + (uprowcol + pow(uprow^2); or  
                // uprowcol + (uprowcol + pow((currrow-1)^2);  
            }
        }
    }
    int query(int l,int r){
        int range = r-l+1;
        int k = log2(range);
        //2^0 -> 2 3 9 2 4 16 9 12 15 
        //2^1 -> 2 3 2 2 4 6 9 12
        //2^2 -> 2 2 2 2 4 6 
        //2^3 -> 2 2
        // query-> [0-8];
        // range - > 8 - 0 + 1= 9;
        // k = 3;
        // min(min[2,3,9,2,4,16,9,12],min[3,9,2,4,16,9,12,15]);
        // min(table[k][l] , table[k][r - (pow(2,k) + 1)])
        // min(table[3][0],table[3][8 - 8 + 1])
        // min(table[3][0],table[3][1]) -> 2;
        return min(table[k][l],table[k][r-(1<<k)+1]);

    }
};
int main()
{
    int n;
    cin >> n;
    vector<int>v(n);
    readv(v);
    sparce se = sparce(v);
    se.build();
    int q;
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        cout<<se.query(a,b)<<endl;
    }

    return 0;
}