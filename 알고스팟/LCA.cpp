#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 100000;

vector<int> child[MAX_N], trip;
int no2serial[MAX_N], serial2no[MAX_N];	// �Է¹��� ��带 ���׸�Ʈ Ʈ���� �ذ��ϱ� ���� ��迭
int depth[MAX_N], locInTrip[MAX_N];	// ���׸�Ʈ Ʈ������ �� ��尡 ó�� �����ϴ� location
int nextNode;
int C, N, Q;
int segA[8 * MAX_N];

void traverse(int here, int d) {	// �Է� ����� ��迭
	no2serial[here] = nextNode;
	serial2no[nextNode] = here;
	depth[here] = d;
	locInTrip[here] = trip.size();	// ���� ��尡 Ʈ������ ó�� ���� ���� �ε���
	nextNode++;

	trip.push_back(no2serial[here]);	// ���׸�Ʈ Ʈ���� �����ϱ� ���� trip �迭
	for (int i = 0; i < child[here].size(); i++) {
		trip.push_back(no2serial[here]);	// trip �迭�� ��ü Ʈ���� ������ȸ�� ����̴�.
		traverse(child[here][i], d + 1);	// �� �� 1 - 2 - 1�� ���� ��ȸ �������� �ٽ� ���ƿ� ��쿡��
											// ��忡 �߰��Ѵ�.

	}
}

int init(int node, int left, int right) {	// ���׸�Ʈ Ʈ�� �ʱ�ȭ
	if (left == right) return segA[node] = trip[left];

	int mid = (left + right) / 2;
	int l = init(node * 2, left, mid);
	int r = init(node * 2 + 1, mid + 1, right);
	return segA[node] = min(l, r);
}

int lca(int left, int right, int node, int nodeLeft, int nodeRight) {	// Ʈ�� Ž��
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

int solve(int u, int v) {	// �ּ� ���� ���� ã��
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