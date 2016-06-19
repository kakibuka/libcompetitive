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

vector<PT> intersec_line_line(LN a, LN b) {
	vector<PT> res;
	if(abs(cross_prod(a.fi-a.se, b.fi-b.se)) < EPS)
		return res;
	if(abs(cross_prod(b.fi-a.fi, b.se-a.fi)) < EPS)
		swap(a.fi, a.se);

	VC va, vb, vc;
	double s, t;
	va = b.fi-a.fi;
	vb = b.se-a.fi;
	vc = a.se-a.fi;
	s = cross_prod(va,vc) / cross_prod(va,vb);
	t = cross_prod(vc,vb) / cross_prod(va,vb);
	res.push_back(a.fi + (t * va + s * vb) / (s+t));
	return res;
}

bool on_seg(PT p, SG a) {
	VC b, c;
	b = a.fi - p;
	c = a.se - p;
	return dot_prod(b,c) < EPS && abs(cross_prod(b,c)) < EPS;
}

vector<PT> intersec_seg_seg(SG a, SG b) {
	vector<PT> tmp, res;
	tmp = intersec_line_line(a,b);
	for(int i = 0; i < tmp.size(); i++) {
		if(on_seg(tmp[i],a) && on_seg(tmp[i],b))
			res.push_back(tmp[i]);
	}
	return res;
}

vector<PT> intersec_circle_circle(CIR a, CIR b) {
	vector<PT> res;
	double d = abs(a.fi-b.fi);
	if(abs(a.se+b.se-d) < EPS || abs(abs(a.se-b.se)-d) < EPS) {
		res.push_back(a.fi + polar(a.se, arg(b.fi-a.fi)));
		return res;
	}
	if(a.se+b.se < d || d < abs(a.se-b.se))
		return res;
	double theta;
	double aa, bb, cc;
	aa = b.se;
	bb = a.se;
	cc = d;
	// 余弦定理
	theta = acos((bb*bb + cc*cc - aa*aa)/ (2.0*bb*cc));
	for(int i = 0; i < 2; i++) {
		res.push_back(a.fi + polar(a.se, theta + arg(b.fi-a.fi)));
		theta *= -1;
	}
	return res;
}

// test code
