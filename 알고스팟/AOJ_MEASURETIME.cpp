#include <iostream>
#include <cstring>
using namespace std;

int C, N, a, fenwick[1000001];

void update(int n) {		// n == 0�� ���, ��Ʈ ������ ���� ������Ʈ�� ���� �����Ƿ�
	while (n <= 1000000) {	// ����Ʈ���� �ּ� �ε����� 1���� ������ �ȵ�
		fenwick[n]++;
		n += n & (-n);		// ��Ʈ�� �÷����� Ž��
	}
}

int pSum(int n) {			// �κ����� ���ϴ� ����
	int ret = 0;
	while (n > 0) {
		ret += fenwick[n];
		n &= n - 1;			// ��Ʈ�� ���� ��Ʈ���� ������ Ž��
	}
	return ret;
}

int main() {
	cin.sync_with_stdio(false); cin.tie(NULL);
	cin >> C;
	while (C--) {
		memset(fenwick + 1, 0, sizeof(fenwick));
		cin >> N;
		long long ans = (long long)N * (N - 1) / 2;	// ��ü �̵� ��ηκ��� �̵�����
		while (N--) {									// �ʴ� ������ ����
			cin >> a;
			ans -= pSum(a + 1);
			update(a + 1);
		}
		cout << ans << '\n';
	}
}