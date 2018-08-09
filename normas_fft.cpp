const int L = 21;
const int N = 1 << L;

long long bit_rev[N];

using ld = long double;
using Poly = vector<long long>;
using base = complex<ld>;
const int mod = 1000000007;
const ld pi = acosl(-1);

int revBit(int x, int k) {
	int y = 0;
	while (k--) {
		y = y * 2 + x % 2;
		x >>= 1;
	}
	return y;
}

void pre() {
	for (int i = 0; i < N; ++i) {
		bit_rev[i] = revBit(i, L);
	}
}

void fft(vector<base>& a) {
	int n = a.size();
	assert(!(n & (n - 1)));

	for (int i = 0; i < n; ++i) {
		int j = bit_rev[i] / (N / n);
		if (i < j) {
			swap(a[i], a[j]);
		}
	}

	for (int len = 1; len < n; len *= 2) {
		base w, dw(cosl(pi / len), sinl(pi / len));
		for (int start = 0; start < n; start += 2 * len) {
			for (int i = 0; i < len; ++i) {
				if (!(i & 31)) {
					w = {cosl(pi * i / len), sinl(pi * i / len)};
				}
				auto u = a[start + i], v = a[start + i + len] * w;
				a[start + i] = u + v;
				a[start + i + len] = u - v;
				w *= dw;
			}
		}
	}
}

const int shift = 15;

vector<base> getSmall(Poly a) {
	vector<base> res(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		res[i] = a[i] & (1 << shift) - 1;
	}
	return res;
}

vector<base> getLarge(Poly a) {
	vector<base> res(a.size());
	for (int i = 0; i < (int)a.size(); ++i) {
		res[i] = a[i] >> shift;
	}
	return res;
}

Poly multiply(Poly a, Poly b) {
	int n = 1;
	while (n < (int)a.size() || n < (int)b.size()) {
		n *= 2;
	}
	n *= 2;
	a.resize(n, 0);
	b.resize(n, 0);
	auto a_l = getLarge(a);
	auto a_s = getSmall(a);
	auto b_l = getLarge(b);
	auto b_s = getSmall(b);
	auto a_c = a_s;
	auto b_c = b_s;
	for (int i = 0; i < n; ++i) {
		a_c[i] += a_l[i] * base(0, 1);
		b_c[i] += b_l[i] * base(0, 1);
	}
	fft(a_c);
	fft(b_c);
	vector<base> fst(n), snd(n);
	for (int i = 0; i < n; ++i) {
		int j = i ? n - i : 0;
		base a_l = (a_c[i] + conj(a_c[j])) / base(2, 0);
		base a_s = (a_c[i] - conj(a_c[j])) / base(0, 2);
		base b_l = (b_c[i] + conj(b_c[j])) / base(2 * n, 0);
		base b_s = (b_c[i] - conj(b_c[j])) / base(0, 2 * n);
		fst[j] = a_l * b_l + a_s * b_s * base(0, 1);
		snd[j] = a_l * b_s + a_s * b_l;
	}
	fft(fst);
	fft(snd);
	Poly res(n);
	for (int i = 0; i < n; ++i) {
		long long s = roundl(real(fst[i]));
		long long m = roundl(real(snd[i]));
		long long l = roundl(imag(fst[i]));
		s %= mod;
		m %= mod;
		l %= mod;
		res[i] = s + (m << shift) + (l << (2 * shift));
		res[i] %= mod;
	}
	return res;
}
