#include <iostream>
#include <cstring>
using namespace std;

int C, N, a, fenwick[1000001];

void update(int n) {		// n == 0일 경우, 비트 연산을 통한 업데이트가 되지 않으므로
	while (n <= 1000000) {	// 펜윅트리의 최소 인덱스는 1임을 잊으면 안됨
		fenwick[n]++;
		n += n & (-n);		// 비트를 올려가며 탐색
	}
}

int pSum(int n) {			// 부분합을 구하는 과정
	int ret = 0;
	while (n > 0) {
		ret += fenwick[n];
		n &= n - 1;			// 비트를 낮은 비트부터 꺼가며 탐색
	}
	return ret;
}

int main() {
	cin.sync_with_stdio(false); cin.tie(NULL);
	cin >> C;
	while (C--) {
		memset(fenwick + 1, 0, sizeof(fenwick));
		cin >> N;
		long long ans = (long long)N * (N - 1) / 2;	// 전체 이동 경로로부터 이동하지
		while (N--) {									// 않는 경우들을 뺀다
			cin >> a;
			ans -= pSum(a + 1);
			update(a + 1);
		}
		cout << ans << '\n';
	}
}