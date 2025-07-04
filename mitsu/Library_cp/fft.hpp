#include <vector>
#include <complex>
#include <cassert>
using namespace std;

constexpr double TAU = 6.28318530717958647692528676655900577;

//逆変換：inv==-1
void fft(std::vector<std::complex<double>> &x, const unsigned bit, const int inv=1){
	std::size_t n = x.size();
	assert(n == 1 << bit);
	std::size_t mask1 = n - 1; // k が数列の長さを超えたときに割った余りをとるマスク
	std::vector<std::complex<double>> zeta(n);
	for(std::size_t i = 0; i < n; ++i){
		zeta[i] = std::polar(1., - inv * TAU * i / n); // ゼータの -i 乗
	}
	for(unsigned i = 0; i < bit; ++i){
		std::size_t mask2 = mask1 >> i + 1; // イオタの部分を得るマスク
		std::vector<std::complex<double>> tmp(n);
		for(std::size_t j = 0; j < n; ++j){
			std::size_t lower = j & mask2; // イオタの部分
			std::size_t upper = j ^ lower; // k の部分
			std::size_t shifted = upper << 1 & mask1;
			tmp[j] = x[shifted | lower] + zeta[upper] * x[shifted | mask2 + 1 | lower];
		}
		x = std::move(tmp);
	}
    if(inv==-1)for(auto &v:x)v/=n;
}

template<typename T>
vector<T> prod(vector<T> &a,vector<T> &b){
    vector<complex<double>> A(a.size()),B(b.size());
    rep(i,a.size())A[i].real(a[i]);
    rep(i,b.size())B[i].real(b[i]);
    int bit=1;
    while((1<<bit)<A.size()+B.size())bit++;
    A.resize(1<<bit);
    B.resize(1<<bit);
    fft(A,bit);
    fft(B,bit);
    rep(i,1<<bit)A[i]*=B[i];
    fft(A,bit,-1);
    vector<T> res(A.size()+B.size()-1);
    rep(i,A.size()+B.size()-1)res[i]=A[i].real();/////////////////////////////Tが整数型なら+0.5を挟む
    return res;
}