#include <bits/stdc++.h>

using namespace std;

enum AntihashMethod {
	Birthday,
	Tree,
	Multitree,
};

mt19937 rr;

void show_help_and_exit() {
	printf("usage: antitest [-h] -l LEN -p MODULO -a BASE (--lower | --upper | --binary) (--birthday | --tree | --multitree) [--multitree-cnt MTCNT]\n\n");
	printf("Construct two different strings of given length with the same rolling hash.\n\n");
	printf("optional arguments:\n");
	printf("  -h, --help                  show this help message and exit\n");
	printf("  -l LEN, --length LEN        length of the strings\n");
	printf("  -p MODULO, --modulo MODULO  the modulo\n");
	printf("  -a BASE, --base BASE        the base\n");
	printf("  --lower                     construct lowercase latin strings\n");
	printf("  --upper                     construct uppercase latin strings\n");
	printf("  --binary                    construct binary strings\n");
	printf("  --birthday                  use birthday paradox attack (default)\n");
	printf("  --tree                      use tree attack\n");
	printf("  --multitree                 use multitree attack\n");
	printf("  --multitree-cnt MTCNT       if the multitree attack is chosen, the number of values to store (default = 100)\n");
	printf("\nexample:\n  $ antitest -p 1000000007 -a 228 -l 10\n  jgonqhanim\n  nyjsbzetvg\n");
	exit(0);
}

string random_string(int len, char from = 'a', int alphabet_size = 26) {
	string res(len, 0);
	for (int i = 0; i < len; ++i) {
		res[i] = from + rr() % alphabet_size;
	}
	return res;
}

long long fmamod(long long h, long long a, long long b, long long p) {
	// returns (h * a + b) % p
	if (p < (1ll << 32)) {
		return (h * a + b) % p;
	} else {
		return ((__int128)h * a + b) % p;
	}
}

long long get_hash(const string& s, long long p, long long a) {
	long long h = 0;
	for (char c : s) {
		h = fmamod(h, a, c, p);
	}
	return h;
}

void run_birthday(uint32_t p, uint32_t a, int len, char first_letter, int alphabet_size) {
	if (len == 0) {
		fprintf(stderr, "len must be positive\n");
		exit(4);
	}
	map<uint32_t, string> M;
	while (true) {
		auto s = random_string(len, first_letter, alphabet_size);
		auto h = get_hash(s, p, a);
		if (M.count(h)) {
			auto t = M[h];
			if (t == s) {
				continue;
			}
			cout << s << "\n" << t << "\n";
			return;
		}
		M[h] = s;
	}
}

struct TreeCluster {
	long long value;
	int sons[2];
	int signs[2];

	explicit TreeCluster(long long val = 0): value(val) {
		memset(sons, -1, sizeof(sons));
		memset(signs, 0, sizeof(signs));
	}

	bool operator <(const TreeCluster& ot) const {
		return abs(value) < abs(ot.value);
	}
};

void run_tree(long long p, long long a, int len, char first_letter, int alphabet_size) {
	vector<TreeCluster> clusters(len);
	{
		long long h = 1;
		for (int i = len - 1; i >= 0; --i) {
			clusters[i] = TreeCluster(h);
			if (clusters[i].value > p - clusters[i].value) {
				clusters[i].value -= p;
			}
			h = fmamod(h, a, 0, p);
		}
	}

	vector<int> coeffs(len, 1);
	for (int i = 0; i < len; ++i) {
		long long v = clusters[i].value;
		int opt = 1;
		long long cur = v;
		for (int j = 2; j < alphabet_size; ++j) {
			cur += clusters[i].value;
			if (cur <= -p) {
				cur += p;
			}
			if (cur >= p) {
				cur -= p;
			}
			if (abs(cur + p) < abs(cur)) {
				cur += p;
			}
			if (abs(cur - p) < abs(cur)) {
				cur -= p;
			}
			if (abs(cur) < abs(v)) {
				v = cur;
				opt = j;
			}
		}
		coeffs[i] = opt;
		clusters[i].value = v;
	}

	auto output_solution = [&](int idx) {
		vector<int> solution(len);
		function<void(int, int)> rec = [&](int idx, int sign) {
			if (idx < len) {
				solution[idx] = sign;
				return;
			}
			for (int j : {0, 1}) {
				rec(clusters[idx].sons[j], sign * clusters[idx].signs[j]);
			}
		};
		rec(idx, 1);
		for (int x : {1, -1}) {
			string s(len, first_letter);
			for (int i = 0; i < len; ++i) {
				if (solution[i] == x) {
					s[i] += coeffs[i];
				}
			}
			cout << s << "\n";
		}
	};

	vector<int> ids(len);
	iota(ids.begin(), ids.end(), 0);
	while ((int)ids.size() > 1) {
		vector<int> nids;
		sort(ids.begin(), ids.end(), [&](int a, int b) {
			return clusters[a] < clusters[b];
		});
		if (ids.size() % 2) {
			nids.push_back(ids[0]);
		}
		for (int i = ids.size() % 2; i < (int)ids.size(); i += 2) {
			int x = ids[i], y = ids[i + 1];
			clusters.emplace_back(clusters[x].value + ((clusters[x].value > 0) == (clusters[y].value > 0) ? -1 : 1) * clusters[y].value);
			clusters.back().sons[0] = x;
			clusters.back().sons[1] = y;
			clusters.back().signs[0] = 1;
			clusters.back().signs[1] = ((clusters[x].value > 0) == (clusters[y].value > 0) ? -1 : 1);
			if (clusters.back().value == 0) {
				output_solution((int)clusters.size() - 1);
				return;
			}
			nids.push_back((int)clusters.size() - 1);
		}
		ids.swap(nids);
	}
	fprintf(stderr, "Didn't find a collision\n");
	exit(5);
}

struct MultiTreeCluster {
	struct Node {
		long long value;
		int signs[2];
		int ids[2];

		explicit Node(long long v = 0): value(v) {
			signs[0] = signs[1] = -1;
			ids[0] = ids[1] = -1;
		}

		bool operator <(const Node& ot) const {
			return abs(value) < abs(ot.value);
		}
	};
	int sons[2];
	vector<Node> nodes;

	MultiTreeCluster() {
		sons[0] = sons[1] = -1;
	}
	MultiTreeCluster(int x, int y) {
		sons[0] = x;
		sons[1] = y;
	}

	void add(long long val, int sign1 = 0, int sign2 = 0, int inner1 = -1, int inner2 = -1) {
		nodes.emplace_back(val);
		nodes.back().signs[0] = sign1;
		nodes.back().signs[1] = sign2;
		nodes.back().ids[0] = inner1;
		nodes.back().ids[1] = inner2;
	}

	void sort() {
		std::sort(nodes.begin(), nodes.end());
	}

	void shrink(int cnt) {
		if ((int)nodes.size() > cnt) {
			nodes.resize(cnt);
		}
	}
};

void run_multitree(long long p, long long a, int len, int cnt_values, char first_letter, int alphabet_size) {
	vector<MultiTreeCluster> clusters(len);
	{
		long long h = 1;
		for (int i = len - 1; i >= 0; --i) {
			long long cur = h;
			for (int j = 1; j < alphabet_size; ++j) {
				if (cur <= -p) {
					cur += p;
				}
				if (cur >= p) {
					cur -= p;
				}
				if (abs(cur + p) < abs(cur)) {
					cur += p;
				}
				if (abs(cur - p) < abs(cur)) {
					cur -= p;
				}
				clusters[i].add(cur, 0, 0, j, 0);
				cur += h;
			}
			clusters[i].sort();
			clusters[i].shrink(cnt_values);
			h = fmamod(h, a, 0, p);
		}
	}

	auto output_solution = [&](int idx) {
		vector<int> solution(len);
		function<void(int, int, int)> rec = [&](int idx, int sign, int inner_idx) {
			if (idx < len) {
				solution[idx] = clusters[idx].nodes[inner_idx].ids[0] * sign;
				return;
			}
			for (int j : {0, 1}) {
				rec(clusters[idx].sons[j], sign * clusters[idx].nodes[inner_idx].signs[j], clusters[idx].nodes[inner_idx].ids[j]);
			}
		};
		rec(idx, 1, 0);
		for (int x : {1, -1}) {
			string s(len, first_letter);
			for (int i = 0; i < len; ++i) {
				if ((solution[i] > 0) == (x > 0)) {
					s[i] += abs(solution[i]);
				}
			}
			cout << s << "\n";
		}
	};

	auto merge = [&](int i, int j) -> MultiTreeCluster {
		priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
		set<pair<int, int>> was;
		const auto& ci = clusters[i], cj = clusters[j];
		auto upd = [&](int l, int r) {
			if (!was.count({l, r})) {
				pq.push({abs(abs(ci.nodes[l].value) - abs(cj.nodes[r].value)), l, r});
				was.insert({l, r});
			}
		};
		MultiTreeCluster res(i, j);
		{
			int l = 0, r = 0;
			while (l < (int)ci.nodes.size() && r < (int)cj.nodes.size()) {
				auto value = abs(ci.nodes[l].value) - abs(cj.nodes[r].value);
				upd(l, r);
				if (value < 0) {
					++l;
				} else {
					++r;
				}
			}
		}
		for (int it = 0; it < cnt_values && !pq.empty(); ++it) {
			auto [value, l, r] = pq.top();
			pq.pop();
			res.add(
				ci.nodes[l].value + ((ci.nodes[l].value > 0) == (cj.nodes[r].value > 0) ? -1 : 1) * cj.nodes[r].value,
				1,
				(ci.nodes[l].value > 0) == (cj.nodes[r].value > 0) ? -1 : 1,
				l, r
			);
			if (abs(ci.nodes[l].value) > abs(cj.nodes[r].value)) {
				if (l + 1 < (int)ci.nodes.size()) {
					upd(l + 1, r);
				}
				if (r > 0) {
					upd(l, r - 1);
				}
			} else {
				if (r + 1 < (int)cj.nodes.size()) {
					upd(l, r + 1);
				}
				if (l > 0) {
					upd(l - 1, r);
				}
			}
		}
		return res;
	};

	vector<int> ids(len);
	iota(ids.begin(), ids.end(), 0);
	while ((int)ids.size() > 1) {
		vector<int> nids;
		sort(ids.begin(), ids.end(), [&](int a, int b) {
			return abs(clusters[a].nodes[0].value) < abs(clusters[b].nodes[0].value);
		});
		if (ids.size() % 2) {
			nids.push_back(ids[0]);
		}
		for (int i = ids.size() % 2; i < (int)ids.size(); i += 2) {
			int x = ids[i], y = ids[i + 1];
			auto nw = merge(x, y);
			clusters.push_back(nw);
			if (clusters.back().nodes[0].value == 0) {
				output_solution((int)clusters.size() - 1);
				return;
			}
			nids.push_back((int)clusters.size() - 1);
		}
		ids.swap(nids);
	}
	fprintf(stderr, "Didn't find a collision\n");
	exit(6);
}

int main(int argc, char** argv) {
	int len = 0;
	vector<long long> ps;
	vector<long long> as;
	char first_letter = 'a';
	int alphabet_size = 26;
	int multitree_cnt = 100;
	AntihashMethod method = AntihashMethod::Birthday;
	{
		int i = 1;
		while (i < argc) {
			if (strcmp(argv[i], "--length") == 0 || strcmp(argv[i], "-l") == 0) {
				++i;
				assert(i < argc);
				len = atoi(argv[i++]);
			} else if (strcmp(argv[i], "--modulo") == 0 || strcmp(argv[i], "-p") == 0) {
				++i;
				assert(i < argc);
				ps.push_back(atoll(argv[i++]));
			} else if (strcmp(argv[i], "--base") == 0 || strcmp(argv[i], "-a") == 0) {
				++i;
				assert(i < argc);
				as.push_back(atoll(argv[i++]));
			} else if (strcmp(argv[i], "--multitree-cnt") == 0) {
				++i;
				assert(i < argc);
				multitree_cnt = atoi(argv[i++]);
			} else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
				show_help_and_exit();
			} else if (strcmp(argv[i], "--lower") == 0) {
				++i;
			} else if (strcmp(argv[i], "--upper") == 0) {
				first_letter = 'A';
				++i;
			} else if (strcmp(argv[i], "--binary") == 0) {
				first_letter = '0';
				alphabet_size = 2;
				++i;
			} else if (strcmp(argv[i], "--birthday") == 0) {
				method = AntihashMethod::Birthday;
				++i;
			} else if (strcmp(argv[i], "--tree") == 0) {
				method = AntihashMethod::Tree;
				++i;
			} else if (strcmp(argv[i], "--multitree") == 0) {
				method = AntihashMethod::Multitree;
				++i;
			} else {
				fprintf(stderr, "Unrecognized parameter: %s\n", argv[i]);
				exit(1);
			}
		}
	}

	if (ps.size() != as.size()) {
		fprintf(stderr, "Unequal number of bases and modulos\n");
		exit(2);
	}
	if (ps.empty()) {
		fprintf(stderr, "No bases/modulos are given\n");
		exit(3);
	}

	for (int i = 0; i < (int)ps.size(); ++i) {
		as[i] %= ps[i];
		if (as[i] < 0) {
			as[i] += ps[i];
		}
	}

	if ((int)ps.size() == 1) {
		if (method == AntihashMethod::Birthday) {
			assert(ps[0] < (1ll << 32));
			run_birthday(ps[0], as[0], len, first_letter, alphabet_size);
		} else if (method == AntihashMethod::Tree) {
			run_tree(ps[0], as[0], len, first_letter, alphabet_size);
		} else if (method == AntihashMethod::Multitree) {
			run_multitree(ps[0], as[0], len, multitree_cnt, first_letter, alphabet_size);
		} else {
			assert(false);
		}
		return 0;
	} else {
		// TODO
	}

	return 0;
}
