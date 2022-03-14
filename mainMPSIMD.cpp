#include <iostream>
#include <vector>
#include <omp.h>
#include <x86intrin.h> // SSE (SIMD)

using namespace std;

int main() {	
	int M, N, K;
	// M - first matrix rows count
	// N - second matrix columns count
	// K - first matrix columns count = second matrix rows count
	
	cin >> M >> N >> K;
	
	vector<float> A(M*K);
	vector<float> B(K*N);
	vector<float> C(M*N, 0);
	
	for (int i = 0; i < M * K; ++i) {
		cin >> A[i];
	}
	for (int i = 0; i < K * N; ++i) {
		cin >> B[i];
	}
	
	#pragma omp parallel for shared(A, B, C, M, N, K)  // delete this line to do the loop in one thread
	for (int m = 0; m < M; ++m) {	
		int mN = m*N, mK = m*K, currentElem, k;
		__m128 float4ofTemp, nextF4ofA, nextF4ofB;
		for (int n = 0; n < N; ++n) {
			k = 0, currentElem = mN + n;
			float4ofTemp = _mm_set_ps(0, 0, 0, 0);

			for (; k < K - 4; k += 4) {
				nextF4ofA = _mm_set_ps(A[mK + k], A[mK + k + 1], A[mK + k + 2], A[mK + k + 3]);
				nextF4ofB = _mm_set_ps(B[k * N + n], B[(k + 1) * N + n], B[(k + 2) * N + n], B[(k + 3) * N + n]);
				float4ofTemp = _mm_add_ps(float4ofTemp, _mm_mul_ps(nextF4ofA, nextF4ofB));
			}
			float4ofTemp = _mm_hadd_ps(float4ofTemp, float4ofTemp);
			float4ofTemp = _mm_hadd_ps(float4ofTemp, float4ofTemp);
			C[currentElem] = _mm_cvtss_f32(float4ofTemp);

			for (; k < K; ++k) {
				C[currentElem] += A[mK + k] * B[k*N + n];
			}
		}
	}
	
	for (int m = 0; m < M; ++m) {
		int mN = m*N;
		for (int n = 0; n < N; ++n) {
			cout << C[mN + n] << " ";
		}
		cout << "\n";
	}
}