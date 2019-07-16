#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 100000;

vector<int> child[MAX_N], trip;
int no2serial[MAX_N], serial2no[MAX_N];	// 입력받은 노드를 세그먼트 트리로 해결하기 위해 재배열
int depth[MAX_N], locInTrip[MAX_N];	// 세그먼트 트리에서 각 노드가 처음 등장하는 location
int nextNode;
int C, N, Q;
int segA[8 * MAX_N];

void traverse(int here, int d) {	// 입력 노드의 재배열
	no2serial[here] = nextNode;
	serial2no[nextNode] = here;
	depth[here] = d;
	locInTrip[here] = trip.size();	// 현재 노드가 트리에서 처음 나올 때의 인덱스
	nextNode++;

	trip.push_back(no2serial[here]);	// 세그먼트 트리를 구현하기 위한 trip 배열
	for (int i = 0; i < child[here].size(); i++) {
		trip.push_back(no2serial[here]);	// trip 배열은 전체 트리를 전위순회한 결과이다.
		traverse(child[here][i], d + 1);	// 이 때 1 - 2 - 1과 같이 순회 과정에서 다시 돌아온 경우에도
											// 노드에 추가한다.

	}
}

int init(int node, int left, int right) {	// 세그먼트 트리 초기화
	if (left == right) return segA[node] = trip[left];

	int mid = (left + right) / 2;
	int l = init(node * 2, left, mid);
	int r = init(node * 2 + 1, mid + 1, right);
	return segA[node] = min(l, r);
}

int lca(int left, int right, int node, int nodeLeft, int nodeRight) {	// 트리 탐색
	if (right < nodeLeft || nodeRight < left) return 5e5;
	if (left <= nodeLeft && nodeRight <= right) return segA[node];

	int mid = (nodeLeft + nodeRight) / 2;
	int l = lca(left, right, node * 2, nodeLeft, mid);
	int r = lca(left, right, node * 2 + 1, mid + 1, nodeRight);

	return min(l, r);
}
int lca(int left, int right) {
	return lca(left, right, 1, 0, trip.size() - 1);
}

int solve(int u, int v) {	// 최소 공통 조상 찾기
	int lu = locInTrip[u];
	int lv = locInTrip[v];

	if (lv < lu) swap(lu, lv);

	return depth[u] + depth[v] - 2 * depth[serial2no[lca(lu, lv)]];
}

int main() {
	cin.sync_with_stdio(false); cin.tie(NULL);
	cin >> C;
	while (C--) {
		nextNode = 0;
		trip.clear();
		int a, b;
		cin >> N >> Q;
		for (int i = 0; i < N; i++) child[i].clear();
		for (int i = 1; i < N; i++) {
			cin >> a;
			child[a].push_back(i);
		}

		traverse(0, 0);

		init(1, 0, trip.size() - 1);
		while (Q--) {
			cin >> a >> b;
			cout << solve(a, b) << '\n';
		}
	}
}