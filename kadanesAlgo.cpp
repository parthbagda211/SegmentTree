
#include "bits/stdc++.h"
using namespace std;
int main(){
    int n;cin>>n;
vector<int>arr(n);
for(int &i:arr){
    cin>>i;
}

int ans=INT_MIN;
int currsum=0;
for(int i=0;i<n;i++){
    currsum +=arr[i];
 
    if(currsum<0){
        currsum=0;
    }
    ans = max(ans,currsum);
   
}
cout << ans << endl;
}