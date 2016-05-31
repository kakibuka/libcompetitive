#include <complex>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
using namespace std;

#define X real()
#define Y imag()

#define fi first
#define se second

// ----- debug macro -----
#define DMPPT(p) (p).X << "," << (p).Y
// ----- ----- ----- -----

// 同じデータ構造だが、意味を区別する為にベクトルと点を分ける
typedef complex<double> PT;
typedef complex<double> VC;
// 直線，線分のデータ構造．意味の区別で別々のtypedef
typedef pair<PT,PT> LN;
typedef pair<PT,PT> SG;
// 円のデータ構造
typedef pair<PT,double> CIR;

// paramater
const double EPS = 1e-8;

double dot_prod(VC a, VC b) {
	return a.X * b.X + a.Y * b.Y;
}
double cross_prod(VC a, VC b) {
	return a.X * b.Y - a.Y * b.X;
}

// 直線 or 線分の単位法線ベクトル取得
VC get_vc_normal(VC a) {
	a = a * PT(0,-1);
	return a / abs(a);
}

// 共通接線(common tangent) 同半径の円が重なると動かないので注意(無限個接線がある)
vector<LN> get_comm_tan(CIR c0, CIR c1) {
	vector<LN> res;
	VC v, n;
	double d;
	double theta, phi, psi;
	const int sign[] = {1,-1};

	if(c0.se > c1.se)
		swap(c0,c1);
	v = c1.fi-c0.fi;
	n = get_vc_normal(v);
	d = abs(v);
	theta = arg(v);
	// 共通接線なし
	if(d < abs(c1.se-c0.se) + EPS)
		return res;
	// 共通接線 (2円の外で交差)
	if(abs(abs(c1.se-c0.se)-d) < EPS || d < abs(c1.se-c0.se)) {
		// 円が接する
		assert(abs(c1.se-c0.se) > EPS);
		v *= c0.se / (c1.se - c0.se);
		res.push_back(LN(c0.fi + v, c0.fi + v + n));
	}
	else {
		phi = asin((c1.se-c0.se)/d) + M_PI / 2.0;
		for(int i = 0; i < 2; i++) {
			psi = theta + sign[i] * phi;
			res.push_back(SG(c0.fi + polar(c0.se, psi),
					c1.fi + polar(c1.se, psi)));
		}
	}
	// 共通接線 (2円の間で交差)
	if(abs(c0.se + c1.se - d) < EPS) {
		// 円が接する
		v *= c0.se / (c0.se + c1.se);
		res.push_back(LN(c0.fi + v, c0.fi + v + n));
	}
	else if(c0.se + c1.se < d) {
		phi = acos((c0.se+c1.se)/d);
		for(int i = 0; i < 2; i++) {
			psi = theta + sign[i] * phi;
			res.push_back(SG(c0.fi + polar(c0.se, psi),
						c1.fi + polar(c1.se, psi + M_PI)));
		}
	}
	return res;
}

double dist_pts_line(PT p, LN l) {
	VC a, b;
	a = l.fi - p;
	b = l.se - p;
	return abs(cross_prod(a,b)) / abs(l.fi-l.se);
}

// rest code
