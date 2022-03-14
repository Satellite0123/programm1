#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
	
	int M, N, K;
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

	#pragma omp parallel for shared(A, B, C, M, N, K) // delete this line to do the loop in one thread
	for (int m = 0; m < M; ++m) {
		int mN = m*N, mK = m*K;
		for (int n = 0; n < N; ++n) {
			for (int k = 0; k < K; ++k) {
				C[mN + n] += A[mK + k] * B[k*N + n];
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