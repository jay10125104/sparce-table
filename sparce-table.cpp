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
