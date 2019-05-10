#include "solution.h"

#define CLASS_NAME LollipopHoney
#define METHOD_NAME count

// template <typename... Input, typename Output>
// bool testOne(Input... input, Output output) {
// 	return CLASS_NAME().METHOD_NAME(input...) == output;
// }

int test_num = 1;

ostream& operator <<(ostream& ostr, const vector<int>& a) {
	ostr << "{";
	for (int i = 0; i < (int)a.size(); ++i) {
		if (i) {
			ostr << ", ";
		}
		ostr << a[i];
	}
	ostr << "}";
	return ostr;
}

#define test(x, ...) {\
	cerr << "Test #" << test_num++ << ": "; \
	auto res = CLASS_NAME().METHOD_NAME(__VA_ARGS__); \
	if (res == (x)) \
		cerr << "ok\n"; \
	else { \
		cerr << "fail returned " << res << " while should have returned " << (x) << "\n"; \
	} \
}

#define check_stupid(...) {\
	auto x = CLASS_NAME().METHOD_NAME(__VA_ARGS__); \
	auto y = CLASS_NAME().stupid(__VA_ARGS__); \
	if (x != y) { \
		cerr << "fail returned " << x << " while should have returned " << y << "\n"; \
	} else { \
		cerr << "ok\n"; \
	} \
}

int main() {
	test((vector<int>{60, 1}), 1, vector<int>{1, 1, 2, 2}, vector<int>{10, 20, 30, 40});
	test((vector<int>{60, 9}), 2, vector<int>{1, 1, 1, 2, 2, 2}, vector<int>{10, 10, 10, 20, 20, 20});
	test((vector<int>{}), 2, vector<int>{1, 1, 1, 1, 1, 2}, vector<int>{10, 20, 30, 40, 50, 60});
	test((vector<int>{48, 2}), 3, vector<int>{48,33,22,9,37,44,5,49,24,14,45,1}, vector<int>{9,1,7,10,7,10,5,1,3,3,4,5});
	test((vector<int>{20, 846527861}), 10, vector<int>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40}, vector<int>{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});

	return 0;
}
