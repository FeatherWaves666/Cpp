#include<iostream>
using namespace std;
struct S {
	const char* name;
	int age;
};
int cmp(const void* e1, const void* e2) {
	return ((struct S*)e1)->age - ((struct S*)e2)->age;
}
void swap(char* e1, char* e2, int nums) {
	for (int i = 0; i < nums; i++) {
		char temp = *e1;
		*e1 = *e2;
		*e2 = temp;
		e1++;
		e2++;
	}
}
void bubbleSort(void* p, int sz, int wth, int(*pfunc)(const void* e1, const void* e2)) {
	for (int i = 0; i < sz - 1; i++) {
		for (int j = 0; j < sz - 1 - i; j++) {
			if (cmp((char*)p + j * wth, (char*)p + (j + 1) * wth) > 0) {
				swap((char*)p + j * wth, (char*)p + (j + 1) * wth, wth);
			}
		}
	}
}
int main() {
	S arr[] = { {"zhangsan",10},{"lisi",6},{"wangwu",12} };
	bubbleSort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), cmp);
	for (int i = 0; i < 3; i++) {
		cout << arr[i].age << "  " << arr[i].name << endl;
	}
	return 0;
}
