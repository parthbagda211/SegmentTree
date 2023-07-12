#include "bits/stdc++.h"
using namespace std;
#define int long long 
const int N = 1e5+2;

int segTree[4*N];
int arr[N];
void build(int idx,int low , int high){
    if(low==high){
        segTree[idx]=arr[low];
        return ;
    }
    int mid = (low+high)/2;
    build(2*idx+1,low,mid);
    build(2*idx+2,mid+1,high);

    segTree[idx] = segTree[2*idx+1]+segTree[2*idx+2];
}
int kone(int idx,int low ,int high , int K){
    if(low==high){
        return low;
    }
    int mid = (low+high)/2;

    if(K<segTree[2*idx+1]){
        return kone(2*idx+1,low,mid,K);
    }else{
         return kone(2*idx+2,mid+1,high,K-segTree[2*idx+1]);
    }


}
void update(int idx,int low,int high,int index){
    if(low==high){
        if(arr[low]==1){
            arr[low]=0;
            segTree[idx]=arr[low];
        }else{
            arr[low]=1;
            segTree[idx]=arr[low];

        }
        return ;
    }
    int mid = (low+high)/2;

    if(index<=mid){
        update(2*idx+1,low,mid,index);
    }else{
        update(2*idx+2,mid+1,high,index);
    }

    segTree[idx] = segTree[2*idx+1]+segTree[2*idx+2];
}

signed main(){
 int n,m;cin>>n>>m;
 for(int i=0;i<n;i++) cin>>arr[i];
build(0,0,n-1);
while(m--){
    int type;cin>>type;
    if(type==1){
        int idx;cin>>idx;
        update(0,0,n-1,idx);
    }else{
        int k;cin>>k;
        cout << kone(0,0,n-1,k)<<endl;
    }
}
}