#include "bits/stdc++.h"
using namespace std;
#define int long long 
const int N = 1e5+2,MOD = 1e9+7;
struct grp
{
    int sum,pref,suff,ans;

};
grp segmentTree[4*N];
int arr[N];
void build(int idx , int low , int high){
    if(low==high){
       if(arr[low]<=0){
        segmentTree[idx].sum = arr[low];
        segmentTree[idx].pref  = segmentTree[idx].suff = segmentTree[idx].ans=0;
       }
       else{
        segmentTree[idx].sum = segmentTree[idx].pref = segmentTree[idx].suff = segmentTree[idx].ans = arr[low];
       }
       return ;

    }

    int mid = (low+high)/2;
    build(2*idx+1,low,mid);
    build(2*idx+2,mid+1,high);

    segmentTree[idx].sum = segmentTree[2*idx+1].sum + segmentTree[2*idx+2].sum ;

    segmentTree[idx].pref = max(segmentTree[2*idx+1].pref,segmentTree[2*idx+1].sum + segmentTree[2*idx+2].pref);

    segmentTree[idx].suff = max(segmentTree[2*idx+2].suff,segmentTree[2*idx+2].sum + segmentTree[2*idx+1].suff);

    segmentTree[idx].ans = max(segmentTree[2*idx+1].suff+segmentTree[2*idx+2].pref,max(segmentTree[2*idx+2].ans , segmentTree[2*idx+1].ans));

}
void update(int idx,int low,int high,int index,int val){
   if(low==high){
    arr[low]=val;
     if(arr[low]<=0){
        segmentTree[idx].sum = arr[low];
        segmentTree[idx].pref  = segmentTree[idx].suff = segmentTree[idx].ans =0;
       }
       else{
        segmentTree[idx].sum = segmentTree[idx].pref = segmentTree[idx].suff = segmentTree[idx].ans = arr[low];
       }
       return ;
}

int mid = (low+high)/2;
if(index<=mid){
    update(2*idx+1,low,mid,index,val);
}
else{
     update(2*idx+2,mid+1,high,index,val);
}

    segmentTree[idx].sum = segmentTree[2*idx+1].sum + segmentTree[2*idx+2].sum ;

    segmentTree[idx].pref = max(segmentTree[2*idx+1].pref,segmentTree[2*idx+1].sum + segmentTree[2*idx+2].pref);

    segmentTree[idx].suff = max(segmentTree[2*idx+2].suff,segmentTree[2*idx+2].sum + segmentTree[2*idx+1].suff);

    segmentTree[idx].ans = max(segmentTree[2*idx+1].suff+segmentTree[2*idx+2].pref,max(segmentTree[2*idx+2].ans , segmentTree[2*idx+1].ans));

}

signed  main(){
    int n,m;cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    build(0,0,n-1);
    cout << segmentTree[0].ans << endl;

    while(m--){
        int idx,val;cin>>idx>>val;
        update(0,0,n-1,idx,val);
        cout << segmentTree[0].ans << endl;
    }
    return 0;
}
