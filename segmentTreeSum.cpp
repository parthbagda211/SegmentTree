#include "bits/stdc++.h"
using namespace std;
class SGTree {
	
public:
vector<long long> seg;
	SGTree(long long n) {
		seg.resize(4 * n + 1);
	}

	void build(long long ind, long long low, long long high, long long arr[]) {
		if (low == high) {
			seg[ind] = arr[low];
			return;
		}

		long long mid = (low + high) / 2;
		build(2 * ind + 1, low, mid, arr);
		build(2 * ind + 2, mid + 1, high, arr);
		seg[ind] = (seg[2 * ind + 1]+seg[2 * ind + 2]);
	}

	long long query(long long ind, long long low, long long high, long long l, long long r) {
		// no overlap
		// l r low high or low high l r
		if (r < low || high < l) return 0;

		// complete overlap
		// [l low high r]
		if (low >= l && high <= r) return seg[ind];

		long long mid = (low + high) >> 1;
		long long left = query(2 * ind + 1, low, mid, l, r);
		long long right = query(2 * ind + 2, mid + 1, high, l, r);
		return (left+ right);
	}
	void update(long long ind, long long low, long long high, long long i, long long val) {
		if (low == high) {
			seg[ind] = val;
			return;
		}

		long long mid = (low + high) >> 1;
		if (i <= mid) update(2 * ind + 1, low, mid, i, val);
		else update(2 * ind + 2, mid + 1, high, i, val);
		seg[ind] = seg[2 * ind + 1]+ seg[2 * ind + 2];
	}
};


int main(){
long long n,q;cin>>n>>q;
long long arr[n];
for(long long i=0;i<n;i++){
	cin>>arr[i];
}
SGTree sg1(n);

sg1.build(0,0,n-1,arr);

while(q--){
	long long type;cin>>type;
	if(type==1){
		long long i,val;cin>>i>>val;
		sg1.update(0,0,n-1,i,val);
	}
	else if(type==2){
		long long l,r;cin>>l>>r;
      
    int cnt = count(sg1.seg.begin(),sg1.seg.end(),sg1.query(0,0,n-1,l,r-1));
      cout << sg1.query(0,0,n-1,l,r-1) << " "  << cnt <<endl;
	}
	
}

}