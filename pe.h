#pragma once

using namespace std;

// typedefs and defines

using li = long long;
using ld = long double;
using LI = __int128_t;

// [end] typedefs and defines

// Modular

template <int mod>
struct Modular {
	int val;

	Modular(long long _val = 0) {
		if (_val < 0 || _val >= mod) {
			val = _val % mod;
			if (val < 0) {
				val += mod;
			}
		} else {
			val = _val;
		}
	}

	Modular operator +(const Modular& ot) const {
		int res = val + ot.val;
		if (res >= mod) {
			res -= mod;
		}
		return {res};
	}

	Modular operator -(const Modular& ot) const {
		int res = val - ot.val;
		if (res < 0) {
			res += mod;
		}
		return {res};
	}

	Modular operator *(const Modular& ot) const {
		return {1ll * val * ot.val};
	}

	Modular& operator ++() {
		val += 1;
		if (val == mod) {
			val = 0;
		}
		return *this;
	}

	Modular operator ++(int) {
		Modular tmp(*this);
		operator ++();
		return tmp;
	}

	void operator +=(const Modular& ot) {
		val += ot.val;
		if (val >= mod) {
			val -= mod;
		}
	}

	void operator -=(const Modular& ot) {
		val -= ot.val;
		if (val < 0) {
			val += mod;
		}
	}

	void operator *=(const Modular& ot) {
		val = 1ll * val * ot.val % mod;
	}

	bool operator ==(const Modular& ot) const {
		return val == ot.val;
	}

	bool operator !=(const Modular& ot) const {
		return val != ot.val;
	}
};

template <int mod>
ostream& operator <<(ostream& ostr, const Modular<mod>& x) {
	return ostr << x.val;
}

// [end] Modular

// Matrix

template <typename T, int N>
struct Matrix {
	array<array<T, N>, N> a;

	Matrix(): a({}) {}
	Matrix(const array<array<T, N>, N>& _a): a(_a) {}

	Matrix operator +(const Matrix& ot) const {
		Matrix res;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				res[i][j] = a[i][j] + ot.a[i][j];
			}
		}
		return res;
	}

	Matrix operator -(const Matrix& ot) const {
		Matrix res;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				res[i][j] = a[i][j] - ot.a[i][j];
			}
		}
		return res;
	}

	Matrix operator *(const Matrix& ot) const {
		Matrix res;
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < N; ++k) {
				for (int j = 0; j < N; ++j) {
					res.a[i][j] += a[i][k] * ot.a[k][j];
				}
			}
		}
		return res;
	}

	void operator +=(const Matrix& ot) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				a[i][j] += ot.a[i][j];
			}
		}
	}

	void operator -=(const Matrix& ot) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				a[i][j] -= ot.a[i][j];
			}
		}
	}

	void operator *=(const Matrix& ot) {
		*this = *this * ot;
	}

	const array<T, N>& operator [](int index) const {
		return a[index];
	}

	array<T, N>& operator [](int index) {
		return a[index];
	}
};

template <typename T, int N>
Matrix<T, N> getId() {
	Matrix<T, N> res;
	for (int i = 0; i < N; ++i) {
		res[i][i] = 1;
	}
	return res;
}

template <typename T>
struct RectMatrix {
	int n, m;
	vector<vector<T>> a;

	RectMatrix(int _n, int _m): n(_n), m(_m), a(_n, vector<T>(_m)) {}

	RectMatrix operator +(const RectMatrix& ot) const {
		assert(tie(n, m) == tie(ot.n, ot.m));
		RectMatrix res(n, m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				res[i][j] = a[i][j] + ot.a[i][j];
			}
		}
		return res;
	}

	RectMatrix operator -(const RectMatrix& ot) const {
		assert(tie(n, m) == tie(ot.n, ot.m));
		RectMatrix res(n, m);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				res[i][j] = a[i][j] - ot.a[i][j];
			}
		}
		return res;
	}

	RectMatrix operator *(const RectMatrix& ot) const {
		assert(m == ot.n);
		RectMatrix res(n, ot.m);
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < ot.m; ++k) {
				for (int j = 0; j < m; ++j) {
					res.a[i][j] += a[i][k] * ot.a[k][j];
				}
			}
		}
		return res;
	}

	void operator +=(const RectMatrix& ot) {
		assert(tie(n, m) == tie(ot.n, ot.m));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				a[i][j] += ot.a[i][j];
			}
		}
	}

	void operator -=(const RectMatrix& ot) {
		assert(tie(n, m) == tie(ot.n, ot.m));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				a[i][j] -= ot.a[i][j];
			}
		}
	}

	void operator *=(const RectMatrix& ot) {
		*this = *this * ot;
	}

	const vector<T>& operator [](int index) const {
		return a[index];
	}

	vector<T>& operator [](int index) {
		return a[index];
	}
};

// [end] Matrix

// ostream operators

ostream& operator <<(ostream& ostr, __int128_t x) {
	const long long many = 1e18;
	if (x < many) {
		return ostr << (long long)x;
	} else {
		string s = to_string((long long)(x % many));
		while (s.length() < 18) {
			s = "0" + s;
		}
		return ostr << (long long)(x / many) << s;
	}
}

template <typename T, int N>
ostream& operator <<(ostream& ostr, const Matrix<T, N>& a) {
	for (const auto& v : a.a) {
		for (const auto& x : v) {
			ostr << x << " ";
		}
		ostr << "\n";
	}
	return ostr;
}

template <typename T>
ostream& operator <<(ostream& ostr, const RectMatrix<T>& a) {
	for (const auto& v : a.a) {
		for (const auto& x : v) {
			ostr << x << " ";
		}
		ostr << "\n";
	}
	return ostr;
}

template <typename T, typename U>
ostream& operator <<(ostream& ostr, const pair<T, U>& p) {
	return ostr << "(" << p.first << ", " << p.second << ")";
}

template <typename T>
ostream& operator <<(ostream& ostr, const vector<T>& v) {
	bool fp = true;
	ostr << "{";
	for (auto x : v) {
		if (fp) {
			fp = false;
		} else {
			ostr << ", ";
		}
		ostr << x;
	}
	return ostr << "}";
}

// [end] ostream operators

// prime number things

template <int N>
array<int, N> genErat() {
	array<int, N> erat;
	erat[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (erat[i] == 0) {
			erat[i] = i;
			if (1.0 * i * i < N + N) {
				for (int j = i * i; j < N; j += i) {
					if (erat[j] == 0) {
						erat[j] = i;
					}
				}
			}
		}
	}
	return erat;
}

template <int N>
array<int, N> genPhi(const array<int, N>& erat) {
	array<int, N> phi;
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		int p = erat[i];
		int j = i;
		phi[i] = 1;
		while (erat[j] == p) {
			j /= p;
			phi[i] *= p;
		}
		phi[i] = phi[i] / p * (p - 1) * phi[j];
	}
	return phi;
}

template <int N>
array<int, N> genMu(const array<int, N>& erat) {
	array<int, N> mu;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		mu[i] = (erat[i] == erat[i / erat[i]]) ? 0 : -mu[i / erat[i]];
	}
	return mu;
}

// [end] prime number things

// general stuff

template <typename T, int N>
Matrix<T, N> pw(Matrix<T, N> a, long long b) {
	Matrix<T, N> res = getId<T, N>();
	while (b) {
		if (b & 1ll) {
			res = res * a;
		}
		b >>= 1;
		a = a * a;
	}
	return res;
}

template <typename T>
T pw(T a, long long b) {
	T res = 1;
	while (b) {
		if (b & 1ll) {
			res = res * a;
		}
		b >>= 1;
		a = a * a;
	}
	return res;
}

long long inv(long long a, long long b) {
	return 1 < a ? b - inv(b % a, a) * b / a : 1;
}

pair<long long, long long> euc(long long x, long long y) {
	if (y == 0) {
		return {1, 0};
	}
	auto p = euc(y, x % y);
	return {p.second, p.first - x / y * p.second};
}

pair<long long, long long> crt(const vector<long long>& rems, const vector<long long>& mods) {
	long long m = 1, r = 0;
	for (int i = 0; i < (int)rems.size(); ++i) {
		auto g = gcd(m, mods[i]);
		if (r % g != rems[i] % g) {
			return {-1, -1};
		}
		auto p = euc(m / g, mods[i] / g);
		r += m * (p.first * (rems[i] - r) / g % mods[i] + mods[i]);
		m *= mods[i] / g;
		r %= m;
		if (r < 0) {
			r += m;
		}
	}
	return {r, m};
}

// [end] general stuff

// prime counting function

namespace prime_counting {

const int N = 111111111;
vector<int> primes;
int erat[N];

struct Query {
	long long ans;
	int n, k;
};

struct Fenwick {
	int n;
	vector<int> a;

	Fenwick(int _n): n(_n), a(_n) {}

	void add(int pos, int x) {
		while (pos < n) {
			a[pos] += x;
			pos |= pos + 1;
		}
	}

	int get(int pos) {
		int res = 0;
		while (pos >= 0) {
			res += a[pos];
			pos = (pos & (pos + 1)) - 1;
		}
		return res;
	}
};

void memoizeQueries(long long n, int k, int K, vector<Query>& qrs) {
	if (n == 0) {
		return;
	}
	if (k == 0) {
		return;
	}
	if (n < K) {
		qrs.push_back({0, (int)n, k});
	} else if (1ll * primes[k - 1] * primes[k - 1] > n) {
		memoizeQueries(n, upper_bound(all(primes), sqrtl(n)) - primes.begin(), K, qrs);
	} else {
		memoizeQueries(n, k - 1, K, qrs);
		memoizeQueries(n / primes[k - 1], k - 1, K, qrs);
	}
}

long long calcPi(long long n, int k, int K, vector<Query>& qrs) {
	if (n == 0) {
		return 0;
	}
	if (k == 0) {
		return n;
	}
	if (n < K) {
		long long res = qrs.back().ans;
		qrs.pop_back();
		return res;
	} else if (1ll * primes[k - 1] * primes[k - 1] > n) {
		int j = upper_bound(all(primes), sqrtl(n)) - primes.begin();
		long long res = calcPi(n, j, K, qrs) + j - k;
		return res;
	} else {
		long long res = calcPi(n, k - 1, K, qrs);
		res -= calcPi(n / primes[k - 1], k - 1, K, qrs);
		return res;
	}
}

long long Pi(long long n) {
	if (n < N) {
		return upper_bound(all(primes), n) - primes.begin();
	}
	const int K = powl(n / logl(n), 2.0 / 3);
	// cerr << K << "\n";
	int k = upper_bound(all(primes), sqrtl(n)) - primes.begin();
	vector<Query> qrs;
	memoizeQueries(n, k, K, qrs);
	if (K <= 2) {
		return upper_bound(all(primes), n) - primes.begin();
	}
	vector<int> all_guys(K - 2);
	iota(all(all_guys), 2);
	sort(all(all_guys), [&](int i, int j) {
		return erat[i] > erat[j];
	});
	vector<int> qids(qrs.size());
	iota(all(qids), 0);
	sort(all(qids), [&](int i, int j) {
		return qrs[i].k > qrs[j].k;
	});
	Fenwick f(K);
	for (int i = 0, j = 0; i < (int)qids.size(); ++i) {
		while (j < (int)all_guys.size() && erat[all_guys[j]] >= primes[qrs[qids[i]].k]) {
			f.add(all_guys[j], 1);
			++j;
		}
		qrs[qids[i]].ans = f.get(qrs[qids[i]].n) + 1;
	}
	reverse(all(qrs));
	return calcPi(n, k, K, qrs) + k - 1;
}

void init() {
	erat[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (erat[i] == 0) {
			erat[i] = i;
			primes.push_back(i);
		}

		for (int p : primes) {
			if (p > erat[i] || p * i >= N) {
				break;
			}
			erat[i * p] = p;
		}
	}
}

} // namespace prime_counting