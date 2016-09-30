#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <set>
#include <string>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <functional> 
#include <assert.h>
//#include <bits/stdc++.h>
#define FOR(i, l, r) for (int i = int(l), __border_right##i = int(r); i < __border_right##i; i++)
#define STRUCT3(v1, v2, v3, name) struct name \
		{   \
			int v1, v2, v3; \
			name(int v1 = 0, int v2 = 0, int v3 = 0) : v1(v1), v2(v2), v3(v3) {} \
			friend bool operator < (const name& athis, const name& other) \
			{   \
				if (athis.v1 != other.v1) return athis.v1 < other.v1;   \
				if (athis.v2 != other.v2) return athis.v2 < other.v2;   \
				return athis.v3 < other.v3;   \
			}\
		}
#define PB push_back
#define LS (((k) << 1) + 1)
#define RS (((k) << 1) + 2)
#define LM ((l) + (r) >> 1)
#define RM (LM + 1)
//#define LOG(x) tb[(UI(x) * (UI)263572066) >> 27]
#define FST first
#define SCD second
#define retunr return
#define modp 1000000007
#define EPS 1e-7
#define INF 0x3f3f3f3f
#define MAX2 113
#define MAX3 1013
#define MAX4 10013
#define MAX5 100013
#define MAX6 1000013
#define MAXN 413
#define MANX MAXN
#define MAXLEN MAX5
using namespace std;
typedef long long LL;
typedef unsigned int UI;
typedef pair<int, int> PI;
typedef pair<PI, int> P;
STRUCT3(v, d1, d2, Edge);
STRUCT3(rem, d, v, Tri);

char buf[MAXLEN];
vector<string> lines;
map<string, int> l2i;
int head[MAXN], tail[MAXN];
string stationName[MAXN];
int stationNum;
int stationSplited[MAXN];
int stspn;
map<string, int> st2i;
vector<int> subPoint[MAXN];
int stsp2l[MAXN];
vector<int> G[MAXN];
vector<Edge> Gsp[MAXN];
int dis[MAXN][MAXN];;
PI dis2[MAXN];
int pre[MAXN];

int read(FILE *fin)
{
	if (fgets(buf, MAXN, fin) == NULL) {
		return -1;
	}
	int n = strlen(buf);
	if (n > 0 && buf[n - 1] == '\n') {
		buf[--n] = 0;
	}
	if (n == 0) {
		return -1;
	}
	return n;
}
void addEdge(int u, int v, int d1, int d2)
{
	Gsp[u].PB(Edge(v, d1, d2));
	if (d2) {
		G[stationSplited[u]].PB(stationSplited[v]);
		dis[stationSplited[u]][stationSplited[v]] = 1;
	}
}
int init(FILE *fin)
{
	if (fin == NULL) {
		return -1;
	}
	int n;
	while ((n = read(fin)) != -1) {
		int type = 0;
		if (buf[n - 1] == '*') {
			type = 1;
			buf[--n] = 0;
		}
		else if (buf[n - 1] == '-') {
			type = 2;
			buf[--n] = 0;
		}
		if (n == 0) {
			return -1;
		}
		string s = string(buf);
		l2i[s] = lines.size();
		int he = (head[lines.size()] = stspn);
		lines.PB(s);
		if ((n = read(fin)) < 0) {
			return n;
		}
		FOR(i, 0, n) {
			if (buf[i] == ' ') {
				return -1;
			}
			int j = i + 1;
			while (j < n && buf[j] != ' ') {
				j++;
			}
			buf[j] = 0;
			string st = string(buf + i);
			int x = st2i[st];
			if (x == 0) {
				x = stationNum++;
				st2i[st] = x + 1;
				stationName[x] = st;
			}
			else {
				x--;
			}
			stsp2l[stspn] = lines.size() - 1;
			stationSplited[stspn] = x;
			FOR(k, 0, subPoint[x].size()) {
				addEdge(stspn, subPoint[x][k], 1, 0);
				addEdge(subPoint[x][k], stspn, 1, 0);
			}
			subPoint[x].PB(stspn++);
			i = j;
		}
		int ta = (tail[lines.size() - 1] = stspn);
		FOR(i, he, ta - 1) {
			addEdge(i, i + 1, 0, 1);
			if (type != 2) {
				addEdge(i + 1, i, 0, 1);
			}
		}
		if (type == 1) {
			addEdge(he, ta - 1, 0, 1);
			addEdge(ta - 1, he, 0, 1);
		}
		else if (type == 2) {
			vector<int> tmp;
			if ((n = read(fin)) < 0) {
				return n;
			}
			FOR(i, 0, n) {
				if (buf[i] == ' ') {
					return -1;
				}
				int j = i + 1;
				while (j < n && buf[j] != ' ') {
					j++;
				}
				buf[j] = 0;
				string st = string(buf + i);
				bool flag = false;
				int x = st2i[st] - 1;
				FOR(k, he, ta) {
					if (stationSplited[k] == x) {
						flag = true;
						tmp.PB(k);
						break;
					}
				}
				if (!flag) {
					return -1;
				}
				i = j;
			}
			FOR(i, 1, tmp.size()) {
				addEdge(tmp[i - 1], tmp[i], 0, 1);
			}
		}
	}
	return 0;
}
priority_queue<P, vector<P>, greater<P> > que;
int q[MAXN];
bool mark[MAXN];
void print(int t)
{
	vector<int> ans;
	cout << dis2[t].SCD + 1 << endl;
	while (t != -1) {
		ans.PB(t);
		t = pre[t];
	}
	for (int i = ans.size() - 1; i >= 0; i--) {
		cout << stationName[stationSplited[ans[i]]];
		if (i > 0 && dis2[ans[i]].SCD == dis2[ans[i - 1]].SCD) {
			cout << "换乘" << lines[stsp2l[ans[i - 1]]];
			i--;
		}
		cout << endl;
	}
}
void solvebc(int s, int t, char type)
{
	memset(dis2, 0x3f, sizeof(dis2));
	memset(mark, 0, sizeof(mark));
	memset(pre, -1, sizeof(pre));
	int head = 0, tail = 0;
	FOR(i, 0, subPoint[s].size()) {
		dis2[subPoint[s][i]] = PI(0, 0);
		que.push(P(PI(0, 0), subPoint[s][i]));
		pre[subPoint[s][i]] = -1;
	}
	FOR(i, 0, subPoint[t].size()) {
		mark[subPoint[t][i]] = true;
	}
	int T = 0;
	while (!que.empty()) {
		int u;
		P p;
		p = que.top();
		que.pop();
		u = p.SCD;
		if (dis2[u] < p.FST) {
			continue;
		}
		if (mark[u]) {
			T = u;
			break;
		}
		FOR(i, 0, Gsp[u].size()) {
			Edge &e = Gsp[u][i];
			int v = e.v;
			PI d = PI(type == 'b' ? 0 : dis2[u].FST + e.d1, dis2[u].SCD + e.d2);
			if (d < dis2[v]) {
				pre[v] = u;
				dis2[v] = d;
				que.push(P(d, v));
			}
		}
	}
	while (!que.empty()) {
		que.pop();
	}
	print(T);
}

int alt[MAXN], stk[MAXN * 100], n;
int ans = INF;
int prevv[MAXN][MAXN];
int cnt;
//long start = clock();
void add(int s, int t, int loc)
{
	while (t != -1) {
		stk[loc + dis[s][t]] = t;
		t = prevv[s][t];
	}
}
bool dfs(int v, int d)
{
	if (cnt > 9137777) {
		return false;
	}
	cnt++;
	if (n == 0) {
		if (d + dis[v][0] < ans) {
			ans = d + dis[v][0];
			add(v, 0, d);
			//cout << "find at " << (clock() - start) / 1000. << "s, " << cnt << ": " << ans << endl;
			return true;
		}
		return false;
	}
	vector<int> bk;
	int md = INF;
	FOR(i, 0, n) {
		if (dis[v][alt[i]] < md) {
			md = dis[v][alt[i]];
			bk.clear();
			bk.PB(i);
		}
		else if (dis[v][alt[i]] == md) {
			bk.PB(i);
		}
	}
	bool flag = false;
	FOR(i, 0, bk.size()) {
		int tmp = alt[bk[i]];
		alt[bk[i]] = alt[--n];
		if (dfs(tmp, d + dis[v][tmp])) {
			add(v, tmp, d);
			flag = true;
		}
		alt[n++] = alt[bk[i]];
		alt[bk[i]] = tmp;
	}
	return flag;
}
void solvea()
{
	memset(dis, 0x3f, sizeof(dis));
	FOR(s, 0, stationNum) {
		memset(mark, 0, sizeof(mark));
		dis[s][s] = 0;
		prevv[s][s] = -1;
		int head = 0, tail = 0;
		q[tail++] = s;
		mark[s] = true;
		while (head < tail) {
			int v = q[head++];
			FOR(i, 0, G[v].size()) {
				if (!mark[G[v][i]]) {
					q[tail++] = G[v][i];
					prevv[s][G[v][i]] = v;
					mark[G[v][i]] = true;
					dis[s][G[v][i]] = dis[s][v] + 1;
				}
			}
		}
	}
	n = 0;
	FOR(i, 1, stationNum) {
		alt[n++] = i;
	}
	dfs(0, 0);
}

int main(int argc, char **argv)
{
	FILE *fin = fopen("beijing-subway.txt", "r");
	if (init(fin) < 0) {
		printf("文件错误\n");
		return 0;
	}
	fclose(fin);
	//solve();
	//cout << "end at " << (clock() - start) / 1000. << endl;
	//FOR(i, 0, ans) {
	//	printf("%d%c", stk[i], " \n"[i == ans - 1]);
	//}
	if (argc != 1) {
	/*while (1) {
		argc = 4;
		char argv[4][20];
		cin >> argv[1] >> argv[2] >> argv[3];*/
		if (argc == 4 && argv[1][0] == '-' && (argv[1][1] == 'b' || argv[1][1] == 'c')) {
			int s = st2i[string(argv[2])] - 1, t = st2i[string(argv[3])] - 1;
			if (s < 0 || t < 0) {
				printf("参数错误\n");
			}
			solvebc(s, t, argv[1][1]);
		}
		else if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'a') {
			int s = st2i[string(argv[2])] - 1;
			if (s < 0) {
				printf("参数错误\n");
			}
			else {
				solvea();
				int l = 0;
				FOR(i, 0, ans) {
					if (stk[i] == s) {
						l = i;
						break;
					}
				}
				FOR(i, 0, ans + 1) {
					cout << stationName[stk[(i + l) % ans]] << endl;
				}
			}
		}
		else {
			printf("参数错误\n");
		}
	}
	while (cin >> buf) {
		map<string, int>::iterator it = l2i.find(string(buf));
		if (it == l2i.end()) {
			printf("输入错误\n");
			continue;
		}
		FOR(i, head[it->SCD], tail[it->SCD]) {
			cout << stationName[stationSplited[i]] << endl;
		}
	}
	return 0;
}

#define _CRT_SECURE_NO_DEPRECATE
// #include <iostream>
// #include <cstdio>
// #include <cstdlib>
// #include <vector>
// #include <queue>
// #include <cmath>
// #include <map>
// #include <set>
// #include <set>
// #include <string>
// #include <ctime>
// #include <cstring>
// #include <algorithm>
// #include <regex>
// #include <functional> 
// #include <regex>
// #include <assert.h>
// //#include <bits/stdc++.h>
// #define FOR(i, l, r) for (int i = int(l), __border_right##i = int(r); i < __border_right##i; i++)
// #define STRUCT3(v1, v2, v3, name) struct name \
// 		{   \
// 			int v1, v2, v3; \
// 			name(int v1 = 0, int v2 = 0, int v3 = 0) : v1(v1), v2(v2), v3(v3) {} \
// 			friend bool operator < (const name& athis, const name& other) \
// 			{   \
// 				if (athis.v1 != other.v1) return athis.v1 < other.v1;   \
// 				if (athis.v2 != other.v2) return athis.v2 < other.v2;   \
// 				return athis.v3 < other.v3;   \
// 			}\
// 		}
// #define PB push_back
// #define LS (((k) << 1) + 1)
// #define RS (((k) << 1) + 2)
// #define LM ((l) + (r) >> 1)
// #define RM (LM + 1)
// //#define LOG(x) tb[(UI(x) * (UI)263572066) >> 27]
// #define FST first
// #define SCD second
// #define retunr return
// #define modp 1000000007
// #define EPS 1e-7
// #define INF 0x3f3f3f3f
// #define MAX2 113
// #define MAX3 1013
// #define MAX4 10013
// #define MAX5 100013
// #define MAX6 1000013
// #define MAXN 413
// #define MANX MAXN
// #define MAXLEN MAX5
// using namespace std;
// typedef long long LL;
// typedef unsigned int UI;
// typedef pair<int, int> PI;
// typedef pair<PI, int> P;
// STRUCT3(v, d1, d2, Edge);
// STRUCT3(rem, d, v, Tri);

// char buf[MAXLEN];
// int read(FILE *fin, char buf[])
// {
// 	if (fgets(buf, MAXN, fin) == NULL) {
// 		return -1;
// 	}
// 	int n = strlen(buf);
// 	if (n > 0 && buf[n - 1] == '\n') {
// 		buf[--n] = 0;
// 	}
// 	if (n == 0) {
// 		return -1;
// 	}
// 	return n;
// }
// class Station
// {
// public:
// 	static map<string, int> st2i;
// 	static int num;
// 	static int pointNum;
// 	string name;
// 	int lineId;
// 	int id;
// 	int point;
// 	Station(const string& name, int lineId, int id) : name(name), lineId(lineId), id(id), point(pointNum++)
// 	{
// 		if (st2i.find(name) == st2i.end()) {
// 			Station::num++;
// 			Station::st2i[name] = id;
// 		}
// 	}
// };
// class Line
// {
// public:
// 	static vector<string> names;
// 	static map<string, int> line2id;
// 	static int nextId;
// 	int id;
// 	vector<Station*> stations;
// 	Line(const string& str, char *buf) : id(nextId++)
// 	{
// 		if (line2id.find(str) != line2id.end()) {
// 			throw "Repeated line\n";
// 		}
// 		/*regex pat("^(\\w+ \\d+\\(\\d+, +d+\\)[ \\n])*$");
// 		if (!regex_match(buf, pat)) {
// 			throw "Bad file\n";
// 		}*/
// 		line2id[str] = names.size();
// 		names.PB(str);
// 		int n = strlen(buf);
// 		FOR(i, 0, n) {
// 			int j = i + 1;
// 			while (j < n && buf[j] != ' ') {
// 				j++;
// 			}
// 			buf[j] = 0;
// 			string st = string(buf + i);
// 			i = j + 1;
// 			while (j < n && buf[j] != '(') {
// 				j++;
// 			}
// 			buf[j] = 0;
// 			int sid = atoi(buf + i);
// 			i = j + 1;
// 			while (j < n && buf[j] != ',') {
// 				j++;
// 			}
// 			buf[j] = 0;
// 			int x = atoi(buf + i);
// 			i = j + 1;
// 			while (j < n && buf[j] != ')') {
// 				j++;
// 			}
// 			buf[j] = 0;
// 			int y = atoi(buf + i);
// 			i = j;// +1;//yic

// 			stations.PB(new Station(st, id, sid));
// 		}
// 	}
// 	int getId(const string& name)
// 	{
// 		map<string, int>::iterator it = line2id.find(name);
// 		if (it == line2id.end()) {
// 			throw "No such line\n";
// 		}
// 		return (*it).SCD;
// 	}
// 	string getName(int id)
// 	{
// 		if (id < 0 || id >= (int)Line::names.size()) {
// 			throw "Wrong id of line\n";
// 		}
// 		return Line::names[id];
// 	}
// 	int getNum()
// 	{
// 		return Line::names.size();
// 	}
// 	Station* find(const string& name)
// 	{
// 		FOR(i, 0, stations.size()) {
// 			if (stations[i]->name == name) {
// 				return stations[i];
// 			}
// 		}
// 		return NULL;
// 	}
// };

// class Graph
// {
// public:
// 	vector<int> G[MAXN];
// 	vector<Edge> Gsp[MAXN];
// 	vector<int> mainPoint;
// 	int dis[MAXN][MAXN];
// 	int alt[MAXN], stk[MAXN * 100], n;
// 	PI dis2[MAXN];
// 	int pre[MAXN];
// 	bool mark[MANX];
// 	int q[MANX];
// 	int prevv[MAXN][MAXN];
// 	int cnt;
// 	int ans;
// 	Graph()
// 	{
// 		memset(dis, 0x3f, sizeof(dis));
// 		memset(mark, 0, sizeof(mark));
// 	}
// 	void addEdge(const Station* u, const Station* v, int d1, int d2)
// 	{
// 		Gsp[u->point].PB(Edge(v->point, d1, d2));
// 		if (d2) {
// 			if (!mark[u->id]) {
// 				mark[u->id] = true;
// 				mainPoint.PB(u->id);
// 			}
// 			if (!mark[v->id]) {
// 				mark[v->id] = true;
// 				mainPoint.PB(v->id);
// 			}
// 			G[u->id].PB(v->id);
// 			dis[u->id][v->id] = 1;
// 		}
// 	}
// 	vector<int> getRoute(const vector<int>& s, const vector<int>& t, char type)
// 	{
// 		priority_queue<P, vector<P>, greater<P> > que;
// 		memset(dis2, 0x3f, sizeof(dis2));
// 		memset(mark, 0, sizeof(mark));
// 		memset(pre, -1, sizeof(pre));
// 		int head = 0, tail = 0;
// 		FOR(i, 0, s.size()) {
// 			dis2[s[i]] = PI(0, 0);
// 			type == 'b' ? q[tail++] = s[i] : que.push(P(PI(0, 0), s[i]));
// 			pre[s[i]] = -1;
// 		}
// 		FOR(i, 0, t.size()) {
// 			mark[t[i]] = true;
// 		}
// 		int T = 0;
// 		while (type == 'b' ? head < tail : !que.empty()) {
// 			int u;
// 			P p;
// 			if (type == 'b') {
// 				u = q[head++];
// 			}
// 			else {
// 				p = que.top();
// 				que.pop();
// 				u = p.SCD;
// 				if (dis2[u] < p.FST) {
// 					continue;
// 				}
// 			}
// 			if (mark[u]) {
// 				T = u;
// 				break;
// 			}
// 			FOR(i, 0, Gsp[u].size()) {
// 				Edge &e = Gsp[u][i];
// 				int v = e.v;
// 				PI d = PI(type == 'b' ? 0 : dis2[u].FST + e.d1, dis2[u].SCD + e.d2);
// 				if (d < dis2[v]) {
// 					pre[v] = u;
// 					dis2[v] = d;
// 					type == 'b' ? q[tail++] = v : que.push(P(d, v));
// 				}
// 			}
// 		}
// 		vector<int> ans;
// 		while (T != -1) {
// 			ans.PB(T);
// 			T = pre[T];
// 		}
// 		return ans;
// 	}
// 	//long start = clock();
// 	void add(int s, int t, int loc)
// 	{
// 		while (t != -1) {
// 			stk[loc + dis[s][t]] = t;
// 			t = prevv[s][t];
// 		}
// 	}
// 	bool dfs(int v, int d)
// 	{
// 		if (cnt > 9137777) {
// 			return false;
// 		}
// 		cnt++;
// 		if (n == 0) {
// 			if (d + dis[v][0] < ans) {
// 				ans = d + dis[v][0];
// 				add(v, 0, d);
// 				//cout << "find at " << (clock() - start) / 1000. << "s, " << cnt << ": " << ans << endl;
// 				return true;
// 			}
// 			return false;
// 		}
// 		vector<int> bk;
// 		int md = INF;
// 		FOR(i, 0, n) {
// 			if (dis[v][alt[i]] < md) {
// 				md = dis[v][alt[i]];
// 				bk.clear();
// 				bk.PB(i);
// 			}
// 			else if (dis[v][alt[i]] == md) {
// 				bk.PB(i);
// 			}
// 		}
// 		bool flag = false;
// 		FOR(i, 0, bk.size()) {
// 			int tmp = alt[bk[i]];
// 			alt[bk[i]] = alt[--n];
// 			if (dfs(tmp, d + dis[v][tmp])) {
// 				add(v, tmp, d);
// 				flag = true;
// 			}
// 			alt[n++] = alt[bk[i]];
// 			alt[bk[i]] = tmp;
// 		}
// 		return flag;
// 	}
// 	vector<int> getCycle()
// 	{
// 		memset(dis, 0x3f, sizeof(dis));
// 		FOR(s, 0, mainPoint.size()) {
// 			memset(mark, 0, sizeof(mark));
// 			dis[s][s] = 0;
// 			prevv[s][s] = -1;
// 			int head = 0, tail = 0;
// 			q[tail++] = s;
// 			mark[s] = true;
// 			while (head < tail) {
// 				int v = q[head++];
// 				FOR(i, 0, G[v].size()) {
// 					if (!mark[G[v][i]]) {
// 						q[tail++] = G[v][i];
// 						prevv[s][G[v][i]] = v;
// 						mark[G[v][i]] = true;
// 						dis[s][G[v][i]] = dis[s][v] + 1;
// 					}
// 				}
// 			}
// 		}
// 		n = 0;
// 		FOR(i, 1, mainPoint.size()) {
// 			alt[n++] = i;
// 		}
// 		dfs(0, 0);
// 		vector<int> res;
// 		FOR(i, 0, ans) {
// 			res.PB(stk[ans - i - 1]);
// 		}
// 		return res;
// 	}

// };
// class CityMap
// {
// public:
// 	vector<Line*> lines;
// 	vector<Station*> stations;
// 	vector<int> subPoint[MAXN];
// 	Graph graph;
// 	void init(FILE *fin, char *buf)
// 	{
// 		if (fin == NULL) {
// 			throw "Invalid file\n";
// 		}
// 		int n;
// 		while ((n = read(fin, buf)) != -1) {
// 			int type = 0;
// 			if (buf[n - 1] == '*') {
// 				type = 1;
// 				buf[--n] = 0;
// 			}
// 			else if (buf[n - 1] == '-') {
// 				type = 2;
// 				buf[--n] = 0;
// 			}
// 			if (n == 0) {
// 				throw "Bad file\n";
// 			}
// 			string s = string(buf);
// 			if (read(fin, buf) < 0) {
// 				throw "Bad file\n";
// 			}
// 			Line* li = new Line(s, buf);
// 			lines.PB(li);
// 			FOR(i, 0, li->stations.size() - 1) {
// 				graph.addEdge(li->stations[i], li->stations[i + 1], 0, 1);
// 				if (type != 2) {
// 					graph.addEdge(li->stations[i + 1], li->stations[i], 0, 1);
// 				}
// 			}
// 			if (type == 1) {
// 				graph.addEdge(li->stations[0], li->stations[li->stations.size() - 1], 0, 1);
// 				graph.addEdge(li->stations[li->stations.size() - 1], li->stations[0], 0, 1);
// 			}
// 			else if (type == 2) {
// 				vector<Station*> tmp;
// 				if ((n = read(fin, buf)) < 0) {
// 					throw "Bad file\n";
// 				}
// 				FOR(i, 0, n) {
// 					if (buf[i] == ' ') {
// 						throw "Bad file\n";
// 					}
// 					int j = i + 1;
// 					while (j < n && buf[j] != ' ') {
// 						j++;
// 					}
// 					buf[j] = 0;
// 					string name = string(buf + i);
// 					Station* st = li->find(name);
// 					if (st == NULL) {
// 						throw "Bad file\n";
// 					}
// 					tmp.PB(st);
// 					i = j;
// 				}
// 				FOR(i, 1, tmp.size()) {
// 					graph.addEdge(tmp[i - 1], tmp[i], 0, 1);
// 				}
// 			}
// 			stations.insert(stations.end(), li->stations.begin(), li->stations.end());
// 		}
// 		FOR(i, 0, stations.size()) {
// 			subPoint[stations[i]->id].PB(stations[i]->point);
// 		}
// 		FOR(i, 0, stations.size()) {
// 			if (stations[i]->point == subPoint[stations[i]->id][0]) {
// 				FOR(j, 0, subPoint[stations[i]->id].size()) {
// 					FOR(k, 0, subPoint[stations[i]->id].size()) {
// 						if (k == j) {
// 							continue;
// 						}
// 						graph.addEdge(stations[subPoint[stations[i]->id][j]], stations[subPoint[stations[i]->id][k]], 1, 0);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	vector<int> getRoute(int s, int t, char type)
// 	{
// 		vector<int> res = graph.getRoute(subPoint[s], subPoint[t], type);
// 		vector<int> ans;
// 		for (int i = res.size() - 1; i >= 0; i--) {
// 			if (ans.size() == 0 || stations[ans.back()]->id != stations[res[i]]->id) {
// 				ans.PB(res[i]);
// 			}
// 		}
// 		return ans;

// 	}
// };

// map<string, int> Station::st2i;
// int Station::num = 0;
// int Station::pointNum = 0;
// vector<string> Line::names;
// map<string, int> Line::line2id;
// int Line::nextId = 0;
// int main(int argc, char **argv)
// {
// 	/*string sss("asd %d %c", 2, '3');
// 	cout << sss + string("asd") << endl;
// 	while (1);*/
// 	FILE *fin = fopen("beijing-subway_points.txt", "r");
// 	CityMap *cm = new CityMap();
// 	try
// 	{
// 		cm->init(fin, buf);
// 	}
// 	catch (const char* s)
// 	{
// 		fclose(fin);
// 		printf("%s", s);
// 		while (1);
// 		return 0;
// 	}
// 	fclose(fin);
// 	//solve();
// 	//cout << "end at " << (clock() - start) / 1000. << endl;
// 	//FOR(i, 0, ans) {
// 	//	printf("%d%c", stk[i], " \n"[i == ans - 1]);
// 	//}
// 	//if (argc != 1) {
// 	while (1) {
// 		argc = 4;
// 		char argv[4][20];
// 		cin >> argv[1] >> argv[2] >> argv[3];
// 		if (argc == 4 && argv[1][0] == '-' && (argv[1][1] == 'b' || argv[1][1] == 'c')) {
// 			map<string, int>::iterator s = Station::st2i.find(string(argv[2])), t = Station::st2i.find(string(argv[3]));
// 			if (s == Station::st2i.end() || t == Station::st2i.end()) {
// 				printf("参数错误\n");
// 			}
// 			vector<int> res = cm->getRoute(s->SCD, t->SCD, argv[1][1]);
// 			FOR(i, 0, res.size()) {
// 				Station* s = cm->stations[res[i]];
// 				cout << s->name;
// 				if (i < res.size() - 1 && cm->stations[res[i + 1]]->lineId != s->lineId) {
// 					cout << "换乘地铁" << Line::names[cm->stations[res[i + 1]]->lineId];
// 				}
// 				cout << endl;
// 			}
// 		}
// 		else if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'a') {
// 			map<string, int>::iterator s = Station::st2i.find(string(argv[2]));
// 			if (s == Station::st2i.end()) {
// 				printf("参数错误\n");
// 			}
// 			else {
// 				vector<int> res = cm->graph.getCycle();
// 				int l = 0;
// 				FOR(i, 0, res.size()) {
// 					if (res[i] == s->SCD) {
// 						l = i;
// 						break;
// 					}
// 				}
// 				FOR(i, 0, res.size() + 1) {
// 					cout << 1 << endl;
// 					cout << cm->stations[res[(i + l) % res.size()]]->name << endl;
// 				}
// 			}
// 		}
// 		else {
// 			printf("参数错误\n");
// 		}
// 	}
// 	while (cin >> buf) {
// 		map<string, int>::iterator li = Line::line2id.find(string(buf));
// 		if (li == Line::line2id.end()) {
// 			printf("输入错误\n");
// 			continue;
// 		}
// 		FOR(i, 0, cm->lines[li->SCD]->stations.size()) {
// 			cout << cm->lines[li->SCD]->stations[i]->name << endl;
// 		}
// 	}
// 	return 0;
// }
