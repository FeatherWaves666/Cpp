#include"SequeList.h"
using namespace std;
void initSL(SL& s) {
	s.a = NULL;
	s.size = 0;
	s.capacity = 0;
}

void destory(SL& s) {
	free(s.a);
	s.a = NULL;
	s.capacity = 0;
	s.size = 0;
}

void print(SL& s) {
	for (int i = 0; i < s.size; i++) {
		cout << s.a[i] << ' ';
	}
}

void SLCheckCapacity(SL& s) {
	if (s.capacity == s.size) {
		int newSpace = s.capacity == 0 ? 4 : s.capacity * 2;
		SLDATETYPE* p = (SLDATETYPE*)realloc(s.a, s.capacity * sizeof(SLDATETYPE));
		if (p == NULL) {
			cout << "FAIL" << endl;
			exit(-1);
		}
		else {
			s.a = p;
			s.capacity = newSpace;
		}
	}
}

void pushBack(SL& s, SLDATETYPE x) {
	/*SLCheckCapacity(s);
	s.a[s.size] = x;
	s.size++;*/
	insert(s, s.size, x);
}

void pushFront(SL& s, SLDATETYPE x) {
	/*SLCheckCapacity(s);
	int end = s.size - 1;
	while (end >= 0) {
		s.a[end + 1] = s.a[end];
		end--;
	}
	s.a[0] = x;
	s.size++;*/
	insert(s, 0, x);
}

void popBack(SL& s, SLDATETYPE x) {
	assert(s.size > 0);

	//s.size--;
	erase(s, s.size - 1);
}

void popFront(SL& s, SLDATETYPE x) {
	assert(s.size > 0);

	/*int end = 1;
	while (end <= s.size) {
		s.a[end - 1] = s.a[end];
		end++;
	}

	s.size--;*/
	erase(s, 0);
}

void insert(SL& s, int pos, SLDATETYPE x) {
	assert(pos < s.size);
	SLCheckCapacity(s);

	int end = s.size - 1;
	while (end>=pos) {
		s.a[end + 1] = s.a[end];
		end--;
	}

	s.a[pos] = x;
	s.size--;
}

void erase(SL& s, int pos) {
	assert(pos < s.size);

	int end = pos + 1;
	while (end <= s.size) {
		s.a[end - 1] = s.a[end];
	}

	s.size--;
}

int find(SL& s, SLDATETYPE x) {
	for (int i = 0; i < s.size; i++) {
		if (s.a[i] == x) {
			return i;
		}
	}
	return -1;
}

void modify(SL& s, int pos, SLDATETYPE x) {
	assert(pos < s.size);
	s.a[pos] = x;
}

