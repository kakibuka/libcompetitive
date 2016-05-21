#include <complex>
#include <cmath>
#include <iostream>
using namespace std;

#define X real()
#define Y imag()

// ----- debug macro -----
#define DMPPT(p,stream) stream << (p).X << "," << (p).Y
// ----- ----- ----- -----

// 同じデータ構造だが、意味を区別する為にベクトルと点を分ける
typedef complex<double> PT;
typedef complex<double> VC;

// 直線 or 線分の単位法線ベクトル取得
VC get_vc_normal(VC a) {
	a = a * PT(0,-1);
	return a / abs(a);
}

// rest code
int main() {
	PT a(10,10);
	a = get_vc_normal(a);
	DMPPT(a,cout);
	return 0;
}
