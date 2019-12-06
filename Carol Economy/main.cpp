#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,k,pairs;
    cin>>n>>k;
    pairs=(n*(n-1))/2;
    cout<<pairs-k<<'\n';
    return 0;
}
/// xD
