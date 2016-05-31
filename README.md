# libcompetitive

## 幾何ライブラリ
### 基本事項
頂点はcomplexクラスで管理。
+ 実数部分(x)取得 ```.real()```
+ 虚数部分(y)取得 ```.imag()```

+ 加減算はベクトルの加減算に相当
+ 乗除算は偏角の加減算、ベクトルの長さの積となる

+ ベクトルの長さはオーバーロードされた```abs(complex<T>)```で取得できる。
+ 誤差が怖ければ、長さの二乗を ```norm(complex<T>)```で取得可能。(ごめんなさい、テンプレート引数が整数だと未定義動作を起こすらしいので、これ嘘です)
+ 偏角は```arg(complex<T> z)```で得られる
+ ```std::polar(const T& rho, const T& theta=0)``` で大きさrho, 角度thetaのcomplex<T>が得られる

### 円について
#### 円と三角形
+ 外心の作図は各辺の垂直二等分線の交点
+ 内心の作図は各二等分線の交点

### 実装した関数リスト

|関数|意味| verify |
|:--:|:--:|:--:|
|```double dot_prod(VC a, VC b)```|aとbの内積 a・b||
|```double cross_prod(VC a, VC b)```|aとbの外戚 a x b||
|```VC get_vc_normal(VC a)```|ベクトルaの単位法線ベクトル取得|AOJ1132|
|```vector<LN> get_comm_tan(CIR c0, CIR c1)```|共通接線(common tangent) 同半径の円が重なると動かないので注意(無限個接線がある)|AOJ2201|
|```double dist_pts_line(PT p, LN l)```|点pと直線lの距離|AOJ2201|
