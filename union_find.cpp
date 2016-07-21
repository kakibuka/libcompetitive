#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
#define rep(i,n) for(ll i = 0; i < (n); i++)

struct UnionFind {
	vector<int> uf;
	vector<int> rk;
	int sz;

	UnionFind(int n) {
		sz = n;
		uf.resize(n);
		rk.resize(n);
		this->init();
	}

	void init() {
		rep(i,sz) {
			uf[i] = i;
			rk[i] = 0;
		}
	}

	int find(int a) {
		return uf[a] == a ? a : (uf[a] = this->find(uf[a]));
	}

	bool same(int a, int b) {
		return find(a) == find(b);
	}

	void merge(int a, int b) {
		int aa, bb;
		aa = find(a);
		bb = find(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) {
			uf[bb] = aa;
		}
		else {
			if(rk[aa] == rk[bb]) rk[bb]++;
			uf[aa] = bb;
		}
	}
};

