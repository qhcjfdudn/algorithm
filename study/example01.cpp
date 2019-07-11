#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10000	// MAX = N 이상의 가장 가까운 2의 제곱수 * 2. 편의상 N * 4를 사용.
int N;
int segA[MAX];

// segment Tree 초기화. 현재는 RMQ(Range Minimum Query)를 구현했기에 return값이 minimum. 이는 문제에 따라 수정 필요.
int init(int node, int left, int right) {
	if (left == right) return segA[node] = left;	// 값의 구간이 1개의 구간만 포함할 때

	int mid = (left + right) / 2;
	int l = init(left, mid, node * 2);
	int r = init(mid + 1, right, node * 2 + 1);

	return segA[node] = min(l, r);
}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {	// 찾고자 하는 구간 [left, right]에서 node의 구간 [nodeLeft, nodeRight] 탐색
	if (right < nodeLeft || nodeRight < left) return 999;	// 찾고자 하는 구간과 node의 구간의 교집합이 공집합일 때
	if (left <= nodeLeft && nodeRight <= right) return segA[node];	// node의 구간이 찾고자 하는 구간에 포함될 때

	int mid = (nodeLeft + nodeRight) / 2;
	int l = query(left, right, node * 2, nodeLeft, mid);
	int r = query(left, right, node * 2 + 1, mid + 1, nodeRight);

	return min(l, r);
}
int query(int left, int right) { return query(left, right, 1, 0, N - 1); }	// 쿼리 연산의 간편화

int update(int index, int value, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || nodeRight < index) return segA[node];	// 찾는 index가 구간 [nodeLeft, nodeRight]에 포함되지 않을 경우
	if (nodeLeft == nodeRight) return segA[node] = value;	// index가 구간에 포함되면서, 구간이 1개의 구간일 경우
	
	int mid = (nodeLeft + nodeRight) / 2;
	int l = update(index, value, node * 2, nodeLeft, mid);
	int r = update(index, value, node * 2 + 1, mid + 1, nodeRight);

	return segA[node] = min(l, r);
}
int update(int index, int value) { return update(index, value, 1, 0, N - 1); }	// update 연산의 간편화
