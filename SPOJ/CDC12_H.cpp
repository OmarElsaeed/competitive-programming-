#include <bits/stdc++.h>

using namespace std;
const int MAX=262150;
int from,to;
long long tree[MAX],lazy[MAX];
void updateRange(int val,int s, int e, int p)
{
    if(lazy[p] != 0)
    {
        tree[p] += (e-s+1)*lazy[p];
        if(s!=e)
        {
            lazy[p*2]+= lazy[p];
            lazy[p*2+1]+= lazy[p];
        }
        lazy[p] = 0;
    }
    if(s>e||s>to||e<from)
        return;
    if(s>=from && e<= to)
    {
        tree[p] += (e-s+1)*val;
        if(s!=e)
        {
            lazy[p*2] += val;
            lazy[p*2+1] += val;
        }
        return;
    }
    int mid = (s + e) / 2;
    updateRange(val, s, mid,2*p);
    updateRange(val, mid+1, e,2*p+1);
    tree[p] = tree[p*2] + tree[p*2+1];
}

long long queryRange(int s,int e,int p)
{
    if(s>e||s>to||e<from)
        return 0;
    if(lazy[p] != 0)
    {
        tree[p] += (e-s+1)*lazy[p];
        if(s!=e)
        {
            lazy[p*2] += lazy[p];
            lazy[p*2+1] += lazy[p];
        }
        lazy[p] = 0;
    }
    if(s>=from&&e<= to)
        return tree[p];
    int mid = (s+ e) / 2;
    long long p1 = queryRange(s, mid,p*2);
    long long p2 = queryRange( mid + 1,e,p*2+1);
    return (p1 + p2);
}
int main()
{
    //freopen("out.txt","w",stdout);
    int t,n,q,x,y,k=1;
    char s[20];
    scanf("%d",&t);
    while(t--)
    {
        printf("Scenario #%d:\n",k++);
        scanf("%d %d",&n,&q);
        memset(tree,0,sizeof tree);
        memset(lazy,0,sizeof lazy);
        for(int i=0; i<q; i++)
        {
            scanf("%s",&s);
            if(s[0]=='a')
            {
                scanf("%d %d",&from,&to);
                printf("%lld\n",queryRange(0,n,1));
            }
            else
            {
                scanf("%d %d",&from,&to);
                printf("OK\n");
                updateRange(1,0,n,1);
            }
        }
    }
    return 0;
}
