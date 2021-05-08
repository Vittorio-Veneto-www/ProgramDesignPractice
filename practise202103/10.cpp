#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

multiset<int> s;
int a[5000 + 5];

int main() {
	int n, T, k;
	scanf("%d", &T);
	while (T--) {
		s.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i ++) {
			scanf("%d", a + i);
			s.insert(a[i]);
		}
		bool flag = false;
		scanf("%d", &k);
		for (int i = 0; i < n; i ++) {
			for (int j = i + 1; j < n; j ++) {
				int target = k - a[i] - a[j], min_count = 1;
                int cnt = 0;
                for (auto k = s.lower_bound(target); k != s.upper_bound(target); k++) cnt++;
                if (target == a[i] && target == a[j])
                    min_count = 3;
                else
                    if (target == a[i] || target == a[j])
                        min_count = 2;
                if (cnt >= min_count)
                    flag = true;
}
			if (flag) break;
		}
		puts(flag? "Yes": "No");
	}
}