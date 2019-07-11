#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10000	// MAX = N �̻��� ���� ����� 2�� ������ * 2. ���ǻ� N * 4�� ���.
int N;
int segA[MAX];

// segment Tree �ʱ�ȭ. ����� RMQ(Range Minimum Query)�� �����߱⿡ return���� minimum. �̴� ������ ���� ���� �ʿ�.
int init(int node, int left, int right) {
	if (left == right) return segA[node] = left;	// ���� ������ 1���� ������ ������ ��

	int mid = (left + right) / 2;
	int l = init(left, mid, node * 2);
	int r = init(mid + 1, right, node * 2 + 1);

	return segA[node] = min(l, r);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {	// ã���� �ϴ� ���� [left, right]���� node�� ���� [nodeLeft, nodeRight] Ž��
	if (right < nodeLeft || nodeRight < left) return 999;	// ã���� �ϴ� ������ node�� ������ �������� �������� ��
	if (left <= nodeLeft && nodeRight <= right) return segA[node];	// node�� ������ ã���� �ϴ� ������ ���Ե� ��

	int mid = (nodeLeft + nodeRight) / 2;
	int l = query(left, right, node * 2, nodeLeft, mid);
	int r = query(left, right, node * 2 + 1, mid + 1, nodeRight);

	return min(l, r);
}
int query(int left, int right) { return query(left, right, 1, 0, N - 1); }	// ���� ������ ����ȭ

int update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || nodeRight < index) return segA[node];	// ã�� index�� ���� [nodeLeft, nodeRight]�� ���Ե��� ���� ���
	if (nodeLeft == nodeRight) return segA[node] = value;	// index�� ������ ���ԵǸ鼭, ������ 1���� ������ ���
	
	int mid = (nodeLeft + nodeRight) / 2;
	int l = update(index, value, node * 2, nodeLeft, mid);
	int r = update(index, value, node * 2 + 1, mid + 1, nodeRight);

	return segA[node] = min(l, r);
}
int update(int index, int value) { return update(index, value, 1, 0, N - 1); }	// update ������ ����ȭ
