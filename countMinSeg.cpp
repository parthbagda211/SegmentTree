#include "bits/stdc++.h"
using namespace std;
class SEGTree {
    vector<int> segment;
    vector<int> count;  // New vector to store count of minimum elements

public:
    SEGTree(int n) {
        segment.resize(4 * n);
        count.resize(4 * n);  // Initialize count vector
    }

    void build(int idx, int low, int high, int arr[]) {
        if (low == high) {
            segment[idx] = arr[low];
            count[idx] = 1;  // Initialize count as 1 for leaf nodes
            return;
        }
        int mid = (low + high) / 2;
        build(2 * idx + 1, low, mid, arr);
        build(2 * idx + 2, mid + 1, high, arr);
        segment[idx] = min(segment[2 * idx + 1], segment[2 * idx + 2]);

        // Update count based on the minimum value
        if (segment[idx] == segment[2 * idx + 1])
            count[idx] += count[2 * idx + 1];
        if (segment[idx] == segment[2 * idx + 2])
            count[idx] += count[2 * idx + 2];
    }

    pair<int, int> query(int idx, int low, int high, int l, int r) {
        // NO OVERLAP
        if (l > high || r < low)
            return {INT_MAX, 0};

        // COMPLETE OVERLAP
        if (l <= low && r >= high)
            return {segment[idx], count[idx]};

        // PARTIAL OVERLAP
        int mid = (low + high) / 2;
        pair<int, int> left = query(2 * idx + 1, low, mid, l, r);
        pair<int, int> right = query(2 * idx + 2, mid + 1, high, l, r);

        if (left.first < right.first)
            return left;
        if (right.first < left.first)
            return right;

        // If minimum values are equal, combine the counts
        return {left.first, left.second + right.second};
    }

    void update(int idx, int low, int high, int i, int val) {
        if (low == high) {
            segment[idx] = val;
            return;
        }

        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * idx + 1, low, mid, i, val);
        else
            update(2 * idx + 2, mid + 1, high, i, val);

        segment[idx] = min(segment[2 * idx + 1], segment[2 * idx + 2]);

        // Update count based on the minimum value
        count[idx] = 0;  // Reset count
        if (segment[idx] == segment[2 * idx + 1])
            count[idx] += count[2 * idx + 1];
        if (segment[idx] == segment[2 * idx + 2])
            count[idx] += count[2 * idx + 2];
    }
};

int main(){
int n,q;cin>>n>>q;
int arr[n];
for(int i=0;i<n;i++){
	cin>>arr[i];
}
SEGTree sg1(n);

sg1.build(0,0,n-1,arr);

while(q--){
	int type;cin>>type;
	if(type==1){
		int i,val;cin>>i>>val;
		sg1.update(0,0,n-1,i,val);
	}
	else if(type==2){
		int l,r;cin>>l>>r;
      pair<int,int>p = sg1.query(0,0,n-1,l,r-1);
      cout << p.first << " " << p.second  <<endl;
	}
	
}

}