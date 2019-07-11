#include <iostream>
using namespace std;

typedef pair<int, int> P;

int C, N, Q, h[100000];
P segA[100000 * 4];

P minmax(P a, P b) {	// 구간에서의 최소, 최대값 리턴을 위한 구조체(변수가 2개라서 pair를 사용해봄)
	P ret;	// first = min, second = max
	ret.first = a.first < b.first ? a.first : b.first;
	ret.second = a.second > b.second ? a.second : b.second;

	return ret;
}

P init(int node, int left, int right) {
	if (left == right) return segA[node] = P(h[left], h[left]);

	int mid = (left + right) / 2;
	P l = init(node * 2, left, mid);
	P r = init(node * 2 + 1, mid + 1, right);

	return segA[node] = minmax(l, r);
}

P query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || nodeRight < left) return P(20000, 0);	// 찾고자 하는 구간이 아닌 구간을 탐색할 때
	if (left <= nodeLeft && nodeRight <= right) return segA[node];	// 구간에 포함되는 구간일 때

	int mid = (nodeLeft + nodeRight) / 2;
	P l = query(left, right, node * 2, nodeLeft, mid);
	P r = query(left, right, node * 2 + 1, mid + 1, nodeRight);

	return minmax(l, r);
}
P query(int left, int right) { return query(left, right, 1, 0, N - 1); }

int main() {
	cin.sync_with_stdio(false); cin.tie(NULL);	// 입력이 많다

	cin >> C;
	while (C--) {
		cin >> N >> Q;
		for (int i = 0; i < N; i++) cin >> h[i];

		init(1, 0, N - 1);	// segment tree 초기화

		int a, b;
		while (Q--) {
			cin >> a >> b;
			P ans = query(a, b);
			cout << ans.second - ans.first << '\n';	// 쿼리를 통한 해답 출력
		}
	}
}