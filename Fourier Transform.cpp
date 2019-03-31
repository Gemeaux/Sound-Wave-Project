#include <bits/stdc++.h>
using namespace std;
using vType = complex<double>;
constexpr double PI = acos(-1);
constexpr size_t MAXN = 1024;
vType arr[MAXN], w[MAXN];
void bitrev(vType *a, int n) {
	int j = n >> 1;
	for (int i = 1; i < n - 1; ++i) {
		if (i < j) swap(a[i], a[j]);
		int k = n >> 1;
		while (j >= k) j -= k, k >>= 1;
		if (j < k) j += k;
	}
}
void prep(int n) {
	for (int i = 0; i < n; ++i) {
		w[i] = vType(cos(2 * PI * i / n), sin(2 * PI * i / n));
	}
}
void fft(vType *a, int n, bool inv = false) {
	bitrev(a, n), prep(n);
	for (int i = 2; i <= n; i <<= 1) {
		for (int j = 0; j < n; j += i) {
			for (int k = j; k < j + (i >> 1); ++k) {
				vType u = a[k], v = a[k + (i >> 1)] * w[n / i * (k - j)];
				a[k] = u + v, a[k + (i >> 1)] = u - v;
			}
		}
	}
	for (int i = 0; i < n; ++i) a[i] /= n / 2;
	if (inv) {
		for (int i = 1; i < (n >> 1); ++i) swap(a[i], a[n - i]);
		for (int i = 0; i < n; ++i) a[i] *= 2;
	}
}
double in[MAXN], out1[MAXN], out2[MAXN];
void proc(int n) {
	assert(n <= MAXN);
	for (int i = 0; i < n; ++i) arr[i] = vType(in[i], 0);
	fft(arr, n);
	for (int i = 0; i < n; ++i) out1[i] = arr[i].real(), out2[i] = arr[i].imag();
}
void proc2(int n) {
	assert(n <= MAXN);
	for (int i = 0; i < n; ++i) arr[i] = vType(out1[i], out2[i]);
	fft(arr, n, true);
	for (int i = 0; i < n; ++i) in[i] = arr[i].real();
}
int main () {
	int n;
	cin >> n;
	double amp = -1;
	for (int i = 0; i < n; ++i) cin >> in[i], amp = max(amp, abs(in[i]));
	proc(n);
	cout << fixed << setprecision(5);
	cout << amp << endl;
	cout << endl;
	cout << "cos: ";
	for (int i = 0; i < n; ++i) {
		cout << out1[i] / amp;
		if (i < n - 1) cout << " , ";
	}
	cout << endl;
	cout << endl;
	cout << "sin: ";
	for (int i = 0; i < n; ++i) {
		cout << out2[i] / amp;
		if (i < n - 1) cout << " , ";
	}
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}

