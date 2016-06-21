#include <vector>
#include <algorithm>
using namespace std;

template<class T>
struct UpdateDelayedRMQ {
	int size, cap;
	T sentinel_dat;
	vector<T> dat;
	vector<char> dirty;
	vector<T> buf;

	UpdateDelayedRMQ(int sz, T init_dat, T sentinel) {
		size = sz;
		cap = 1;
		while(cap < sz)
			cap *= 2;
		cap *= 2;
		dat = vector<T>(cap,init_dat);
		dirty = vector<char>(cap,0);
		buf = vector<T>(cap,0);
		sentinel_dat = sentinel;
	}

	// dat[k]を参照する．
	T ref_dat(int k) {
		if(dirty[k]) {
			// ノードを更新
			dat[k] = min(dat[k] + buf[k], sentinel_dat);
			// 子ノードに更新情報を伝搬
			for(int i = 1; i <= 2; i++) {
				if(k*2+i < cap) {
					buf[k*2+i] += buf[k];
					dirty[k*2+i] = 1;
				}
			}
			buf[k] = 0;
			dirty[k] = 0;
		}
		return dat[k];
	}

	// 値取得クエリと区間アップデートクエリは一体化させる．
	T query(int a, int b, int k, int l, int r, bool update, T info) {
		if(r <= a || b <= l) {
			return update ? ref_dat(k) : sentinel_dat;
		}

		if(a <= l && r <= b) {
			dirty[k] = 1;
			buf[k] = buf[k] + info;
			return ref_dat(k);
		}
		else {
			ref_dat(k);
			T vl = query(a, b, k*2 + 1, l, (l+r) / 2, update, info);
			T vr = query(a, b, k*2 + 2, (l+r) / 2, r, update, info);
			if(update)
				dat[k] = min(vl, vr);
			return min(vl, vr);
		}
	}
};

