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
    segTree[idx] = (segTree[2*idx+1]+segTree[2*idx+2]);

}
int query(int idx,int low,int high,int l,int r){
    if(low>r or high<l) return 0;
    if(l<=low and high<=r) return segTree[idx];
    
    int mid = (low+high)/2;
    int left = query(2*idx+1,low,mid,l,r);
    int right = query(2*idx+2,mid+1,high,l,r);

    return (left+right);
}
void update(int idx,int low,int high,int index,int val){
    if(low==high){
       
       segTree[idx]=val;
       return ;
    }
    int mid = (low+high)/2;
    if(index<=mid){
        update(2*idx+1,low,mid,index,val);
    }else{
        update(2*idx+2,mid+1,high,index,val);

    }

    segTree[idx] = segTree[2*idx+1]+segTree[2*idx+2];
}
signed main(){
for(int i=0;i<4*N;i++){
	segTree[i]=0;
}    int n;cin>>n;
    int x;
    build(0,0,n-1);
 
    for(int i=0;i<n;i++){
       cin>>x;
     cout << query(0,1,n,x,n)<<endl;
     update(0,1,n,x,1);
    }
}