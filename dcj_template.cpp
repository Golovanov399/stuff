#include <bits/stdc++.h>
#include "message.h"
#include "baby_blocks.h" // problem library

#define itn int
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())

using namespace std;

namespace NMyPutAndGet {
	// Put
	void Put(int target, char value) {
		PutChar(target, value);
	}

	void Put(int target, int value) {
		PutInt(target, value);
	}

	void Put(int target, long long value) {
		PutLL(target, value);
	}

	void Put(int target, const string& value) {
		PutInt(target, value.size());
		for (char x : value) {
			Put(target, x);
		}
	}

	template <typename T, typename U>
	void Put(int target, const pair<T, U>& value);
	template <typename T>
	void Put(int target, const vector<T>& value);

	template <typename T, typename U>
	void Put(int target, const pair<T, U>& value) {
		Put(target, value.first);
		Put(target, value.second);
	}

	template <typename T>
	void Put(int target, const vector<T>& value) {
		PutInt(target, value.size());
		for (const T& x : value) {
			Put(target, x);
		}
	}

	// Get
	void Get(int source, char& value) {
		value = GetChar(source);
	}

	void Get(int source, int& value) {
		value = GetInt(source);
	}

	void Get(int source, long long& value) {
		value = GetLL(source);
	}

	void Get(int source, string& value) {
		value.resize(GetInt(source));
		for (char& x : value) {
			Get(source, x);
		}
	}

	template <typename T, typename U>
	void Get(int source, pair<T, U>& value);
	template <typename T>
	void Get(int source, vector<T>& value);

	template <typename T, typename U>
	void Get(int source, pair<T, U>& value) {
		Get(source, value.first);
		Get(source, value.second);
	}

	template <typename T>
	void Get(int source, vector<T>& value) {
		value.resize(GetInt(source));
		for (T& x : value) {
			Get(source, x);
		}
	}

	template <typename T>
	T Get(int source) {
		T value;
		Get(source, value);
		return value;
	}
} // namespace NMyPutAndGet
using namespace NMyPutAndGet;

inline int GetLeft(int id) {
	return 1ll * GetNumberOfBlocks() * (id - 1) / (NumberOfNodes() - 1);
}

inline int GetRight(int id) {
	return 1ll * GetNumberOfBlocks() * id / (NumberOfNodes() - 1);
}

void Rule() {
	int n = NumberOfNodes();

	// type your code here
}

void Obey(int id) {
	int l = GetLeft(id);
	int r = GetRight(id);

	// type your code here
}

int main() {
	if (MyNodeId() == 0) {
		Rule();
	} else {
		Obey(MyNodeId());
	}

	return 0;
}
