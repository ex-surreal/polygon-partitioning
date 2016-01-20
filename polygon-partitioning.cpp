#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#define START 0
#define END 1
#define SPLIT 2
#define MERGE 3
#define REGULAR 4
#define next(i) ((i+1)%n)
#define prev(i) ((i-1+n)%n)
#define x first
#define y second
#define pb push_back
#define mp make_pair
#include "Point.hpp"
using namespace std;

string names[5] = {"start", "end", "split", "merge", "regular"};

struct Edge {
	Point start, end;
	int id;
	Edge(Point a = Point(0, 0), Point b = Point(0, 0), int i = -1) {
		start = a;
		end = b;
		id = i;
	}
};

bool operator < (Edge a, Edge b) {
	double x1, x2;
	if (a.start.y > a.end.y) {
		x1 = a.start.x;
	} else {
		x1 = a.end.x;
	}
	if (b.start.y > b.end.y) {
		x2 = b.start.x;
	} else {
		x2 = b.end.x;
	}
	return x1 < x2;
}


class Partitioner {
public:
	vector <Point> poly;
	int n;
	int isComputed;
	vector<pair<int, int> > dia;
	set <Edge> active;
	vector<int> helper;
	vector<int> toRight;

	Partitioner(vector <Point> &p) {
		poly = p;
		n = p.size();
		isComputed = 0;
		helper = vector<int>(n);
		for (int i = 0; i < n; i++) {
			helper[i] = i;
		}
		toRight = vector<int>(n, 0);
	}

	int checkVertex(int i) {
		bool isAcute = false;
		int j = (i-1+n)%n;
		int k = (i+1)%n;
		if ((poly[i] - poly[j]) * (poly[k] - poly[j]) > 0) {
			isAcute = true;
		}
		if (isAcute && poly[j].y < poly[i].y && poly[k].y < poly[i].y) {
			return START;
		} else if (!isAcute && poly[j].y < poly[i].y && poly[k].y < poly[i].y) {
			return SPLIT;
		} else if (isAcute && poly[j].y >= poly[i].y && poly[k].y >= poly[i].y) {
			return END;
		} else if (!isAcute && poly[j].y >= poly[i].y && poly[k].y >= poly[i].y) {
			return MERGE;
		} else {
			return REGULAR;
		}
	}

	void sweep() {
		if (isComputed) {
			return;
		}

		vector <pair <Point, int> > event;

		for (int i = 0; i < n; i++) {
			event.push_back(make_pair(poly[i], i));
		}

		sort(event.begin(), event.end());

		for (int k = 0; k < n ; k++) {
			int i = event[k].y;
			int kind = checkVertex(i);
			cerr << i << " " << names[kind] <<endl;
			if (kind == START) {
				handleStart(i);
			} else if (kind == END) {
				handleEnd(i);
			} else if (kind == MERGE) {
				handleMerge(i);
			} else if (kind == SPLIT) {
				handleSplit(i);
			} else {
				handleRegular(i);
			}
		}

		isComputed = 1;
	}

	int search(int i) {
		__typeof(active.begin()) left = active.upper_bound(Edge(poly[i], poly[i], -1));
		if(left != active.begin()) {
			left --;
		}
		return left->id;
	}

	void erase(int i) {
		active.erase(Edge(poly[i], poly[next(i)], i));
	}

	void insert(int i) {
		active.insert(Edge(poly[i], poly[next(i)], i));
	}

	void handleStart(int i) {
		insert(i);
		helper[i] = i;
	}

	void handleEnd(int i) {
		if (checkVertex(helper[prev(i)]) == MERGE) {
			dia.pb(mp(i, helper[prev(i)]));
		}
		erase(prev(i));
	}

	void handleSplit(int i) {
		int j = search(i);
		dia.pb(mp(i, helper[j]));
		helper[j] = i;
		helper[i] = i;
		insert(i);
	}

	void handleMerge(int i) {
		if (checkVertex(helper[prev(i)]) == MERGE) {
			dia.pb(mp(i, helper[prev(i)]));
		}
		erase(prev(i));
		int j = search(i);
		if (checkVertex(helper[j]) == MERGE) {
			dia.pb(mp(i, helper[j]));
		}
		helper[j] = i;
	}

	void handleRegular(int i) {
		if (poly[next(i)].y <= poly[i].y) {
			if (checkVertex(helper[prev(i)]) == MERGE) {
				dia.pb(mp(i, helper[prev(i)]));
				erase(prev(i));
				helper[i] = i;
				insert(i);
			} else {
				int j = search(i);
				if (checkVertex(helper[j]) == MERGE) {
					dia.pb(mp(i, helper[j]));
				}
				helper[j] = i;
			}
		}
	}
};

int main () {
	freopen("input1.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int n;
	cin >> n;
	vector <Point> p(n);
	for (int i = 0; i < n ; i++) {
		cin >> p[i].x >> p[i].y;
	}
	reverse(p.begin(), p.end());
	Partitioner pt(p);
	pt.sweep();
	cout << pt.dia.size() << endl;
	for (int i = 0; i < (int) pt.dia.size(); i++) {
		cout << pt.poly[pt.dia[i].x].x << " " << pt.poly[pt.dia[i].x].y << " ";
		cout << pt.poly[pt.dia[i].y].x << " " << pt.poly[pt.dia[i].y].y << endl;
	}
	cout << n << endl;
	for (int i = 0; i < n ; i++) {
		cout << p[i].x << " " << p[i].y << endl;
	}
	return 0;
}
