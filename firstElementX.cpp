#include "bits/stdc++.h"
using namespace std;
#define int long long 
const int N = 1e5+2;
int segTree[4*N];
int arr[N];
void build(int idx,int low, int high){
    if(low==high){
        segTree[idx]=arr[low];
        return ;
    }
    int mid = (low+high)/2;
    build(2*idx+1,low,mid);
    build(2*idx+2,mid+1,high);
    segTree[idx] = max(segTree[2*idx+1],segTree[2*idx+2]);

}
int query(int idx,int low,int high,int l,int r){
    if(low>r or high<l) return INT_MIN;
    if(l<=low and high<=r) return segTree[idx];
    
    int mid = (low+high)/2;
    int left = query(2*idx+1,low,mid,l,r);
    int right = query(2*idx+2,mid+1,high,l,r);

    return max(left ,right );
}
void update(int idx,int low,int high,int index,int val){
    if(low==high){
       arr[low]=val;
       segTree[idx]=arr[low];
       return ;
    }
    int mid = (low+high)/2;
    if(index<=mid){
        update(2*idx+1,low,mid,index,val);
    }else{
        update(2*idx+2,mid+1,high,index,val);

    }

    segTree[idx] = max(segTree[2*idx+1],segTree[2*idx+2]);
}
signed main(){
int n ,m;cin>>n>>m;
for(int i=0;i<n;i++) cin>>arr[i];
build(0,0,n-1);
while(m--){
    int type;cin>>type;
    if(type==1){
        int idx,val;cin>>idx>>val;
        update(0,0,n-1,idx,val);
    }else if(type==2){
        int x,l;cin>>x>>l;
        //binary search 
        int lo = l,hi = n-1;
        int ans=n;
        while(lo<=hi){
            int mid = (lo+hi)>>1;

            if(query(0,0,n-1,lo,mid)<x ){
                lo = mid+1;
            }else{
                hi = mid-1;
                ans = min(ans,mid);
            }

        }
        if(ans==n){
            cout << -1 << endl;
        }else{
            cout << ans<<endl;
        }
    }
}
// cout <<endl;
// for(int i=0;i<n;i++){
//     cout << segTree[i] << " ";
// }
}