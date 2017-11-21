# Список проебонов на контесте

## Всегда выводим ответ на запрос!

Неправильно:

```c++
while (q--) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    if (!dsu.merge(u, v)) {
        // ниче ж не поменялось)))))) можно сделать continue))))))
        continue;
    }
    make_some_logic(u, v);
    cout << get_cur_ans() << "\n";
}
```

Правильно:

```c++
while (q--) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    if (dsu.merge(u, v)) {
        make_some_logic(u, v);
    }
    cout << get_cur_ans() << "\n";
}
```

## `m` рёбер, а не `n`.

Неправильно:

```c++
int n, m;
cin >> n >> m;
vector<vector<int>> a(n);
for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    a[u].push_back(v);
    a[v].push_back(u);
}
```

Правильно:

```c++
int n, m;
cin >> n >> m;
vector<vector<int>> a(n);
for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    a[u].push_back(v);
    a[v].push_back(u);
}
```

## Лучше `struct` с понятными названиями полей, а не `std::pair`.

Неправильно:

```c++
set<pair<int, int>> a;
for (int i = 0; i < n; ++i) {
    int pos, val;
    cin >> pos >> val;
    a.insert({pos, val});
}
sort(all(a));

int q;
cin >> q;
while (q--) {
    int pos, val;
    cin >> pos >> val;
    auto it = a.lower_bound({pos, 0});
    if (it != a.end() && it->first > val) { // эээ ну в сете же по first сортим в 1ю очередь
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
```

Правильно:

```c++
struct Shit {
    int pos;
    int val;
    
    bool operator <(const Shit& ot) const {
        return make_pair(pos, val) < make_pair(ot.pos, ot.val);
    }
}

set<Shit> a;
for (int i = 0; i < n; ++i) {
    int pos, val;
    cin >> pos >> val;
    a.insert({pos, val});
}
sort(all(a));

int q;
cin >> q;
while (q--) {
    int pos, val;
    cin >> pos >> val;
    auto it = a.lower_bound({pos, 0});
    if (it != a.end() && it->val > val) {   // хуй проебёшься
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
```

## Перенумерация в эйлеровом обходе.

## `vector<char>` хранит числа до 255.

Неправильно:

```c++
vector<char> used(n), num_comp(n);
int cur = 0;
for (int i = 0; i < n; ++i) {
    if (!used[i]) {
        dfs(i, cur++);
    }
}
```

Правильно:

```c++
vector<char> used(n);
vector<int> num_comp(n);
int cur = 0;
for (int i = 0; i < n; ++i) {
    if (!used[i]) {
        dfs(i, cur++);
    }
}
```

## `bool f()` возвращает `bool`.

Неправильно:

```c++
bool occurs(const string& s, const string& t) {
    for (int i = 0; i + (int)s.length() <= (int)t.length(); ++i) {
        // падажжи ебана
        // если содержится, то нужен индекс
        if (t.substr(i, s.length()) == s) {
            return i;
        }
    }
    // иначе пускай будет -1
    return -1;
}
```

Правильно:

```c++
int occurs(const string& s, const string& t) {
...
```

## Не используются `push_val[v]` после `push(v)` в ДО.

## Индексы в `dsu` до `n`, а не до `num_comps`.

## В `merge` `push_val = UNDEFINED`.
