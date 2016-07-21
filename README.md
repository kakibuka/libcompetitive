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
|```vector<PT> intersec_line_line(LN a, LN b)```|直線と直線の交点|AOJ1183|
|```vector<PT> intersec_seg_seg(SG a, SG b)```|線分と線分の交点|AOJ1183|
|```vector<PT> intersec_circle_circle(CIR a, CIR b)```|円と円の交点|AOJ1183|
|```bool has_intersec_seg_seg(SG a, SG b)```|線分と線分の交差判定。平行だった場合は無条件にfalseが帰る|AOJ2402|
|```double dist_pts_seg(PT p, SG a)```|点と線分の距離|AOJ2402|
|```double dist_seg_seg(SG a, SG b)```|線分と線分の距離|AOJ2402|


## クエリ処理系データ構造
### 実装したデータ構造

|データ構造|内容|verify|
|:--:|:--:|:--:|
|```UpdateDelayedRMQ```|更新遅延付きセグ木によるRMQ実装|CF52C|
|```UnionFind```|ふつうのUF|AOJ2224|

### データ構造使用法
#### ```UpdateDelayedRMQ```
|メンバ関数|内容|
|:--:|:--:|
|```UpdateDelayedRMQ(int sz, T init_dat, T sentinel)```|コンストラクタ。szにセグ木が持つべき区間の大きさを、init_datに初期化用の値を、sentinelに考えられる最大値を入れる|
|```T ref_dat(k)```|外から呼ぶ必要なし。ノードを参照する際に必要な更新を行い、ノードが持つ値を返す|
|```T inner_query(int a, int b, int k, int l, int r, bool update, T info)```|半開区間[a,b)の最小値を返す。 k,l,rにはノード番号kが[l,r)の区間の情報を持つような値を引数として与える。 アップデートクエリではupdate=true,info=(加算する値)を設定し、 最小値クエリではupdate=false,info=0を設定する。|
|```T query(int a, int b)```|半開区間[a,b)の最小値クエリ。 inner_queryを適切な形で呼び出す|
|```T update(int a, int b, T v)```|半開区間[a,b)への加算クエリ。 inner_queryを適切な形で呼び出す|

#### ```UnionFind```
|メンバ関数|内容|
|:--:|:--:|
|```UnionFind(int n)```|コンストラクタ。UFのサイズを指定。|
|```void init()```|UFの初期化を行う。コンストラクタの中でも呼ばれるから、使いまわさなければ呼ぶ必要なし。|
|```int find(int a)```|根を見つける。|
|```bool same(int a, int b)```|同じ集合に含まれるかどうか。|
|```void merge(int a, int b)```|aが含まれる集合とbが含まれる集合のマージ。|
