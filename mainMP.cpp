#include <iostream>
#include <ctime>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
	
	int M, N, K;
	cin>>M>>N>>K;
	vector<int> A(M*K);
	vector<int> B(K*N);
	vector<int> result(M*N, 0);
	for (int i = 0; i < M * K; i++) {
		A[i] = i % 3;
	}
	for (int i = 0; i < K * N; ++i) {
		B[i] = i % 3;
	}
//	for (int i = 0; i < M; ++i) {
//		for (int j = 0; j < K; ++j) {
//			cin>>A[i*K + j];
//		}
//	}
//	for (int i = 0; i < K; ++i) {
//		for (int j = 0; j < N; ++j) {
//			cin>>B[i*N + j];
//		}
//	}
	
	// 1000 1000 1000
    clock_t start;
    start = clock();
	#pragma omp parallel for shared(A, B, result) 
	for (int i = 0; i < M; i++) {
		int iN = i*N, iK = i*K;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < K; k++) {
				result[iN + j] += A[iK + k] * B[k*N + j];
			}
		}
	}
//	for (int m = 0; m < M; m++) {
//		for (int n = 0; n < N; n++) {
//			cout << result[m*N + n] << " ";
//		}
//		cout << "\n";
//	}
    cout<<"duration: "<< (clock() - start) / (double) CLOCKS_PER_SEC <<'\n';
}
