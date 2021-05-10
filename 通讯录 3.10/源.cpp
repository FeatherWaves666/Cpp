#include<iostream>
using namespace std;
#include<string>
#define max 1000
struct person {
	string p_name;
	int p_sex;
	int p_age;
	string p_phone;
	string p_addrss;
};
struct personarr {
	int p_n=0;
	person p[max];
};
void showmenu(){
	cout << "*************" << endl;
	cout << "1、增添联系人" << endl;
	cout << "2、显示联系人" << endl;
	cout << "3、删除联系人" << endl;
	cout << "4、查找联系人" << endl;
	cout << "5、修改联系人" << endl;
	cout << "6、清空联系人" << endl;
	cout << "0、退出通讯录" << endl;
	cout << "*************" << endl;
}
void addperson(personarr* abs) {
	if (abs->p_n == 1000) {
		cout << "通讯录已满" << endl;
		return;
	}
	string name;
	cout << "姓名：" << endl;
	cin >> name;
	abs->p[abs->p_n].p_name = name;
	
	int sex;
	cout << "性别：" << endl;
	cout << "1---男 2---女" << endl;
	while (true) {
		cin >> sex;
		if (sex == 1 || sex == 2) {
			abs->p[abs->p_n].p_sex = sex;
			break;
		}
		cout << "重新输入" << endl;
	}

	int age;
	cout << "年龄：" << endl;
	cin >> age;
	abs->p[abs->p_n].p_age= age;

	string phone;
	cout << "电话：" << endl;
	cin >> phone;
	abs->p[abs->p_n].p_phone = phone;

	string address;
	cout << "地址：" << endl;
	cin >> address;
	abs->p[abs->p_n].p_addrss = address;

	abs->p_n++;

	cout << "添加成功" << endl;
	system("pause");
	system("cls");
}
void showperson(personarr*abs) {
	if (abs->p_n == 0) {
		cout << "通讯录为空" << endl;
		//return;  不要放这里，导致menu重复出现  因为没有cls清屏了
	}
	else {
		for (int i = 0; i < abs->p_n; i++) {
			cout << "姓名：" << abs->p[i].p_name << '\t';
			cout << "性别：" << (abs->p[i].p_sex == 1 ? "男" : "女") << '\t';
			cout << "年龄：" << abs->p[i].p_age << '\t';
			cout << "电话：" << abs->p[i].p_phone << '\t';
			cout << "地址：" << abs->p[i].p_addrss << endl;
		}
	}
	system("pause");
	system("cls");
}
int isexist(personarr* abs, string name) {
	for (int i = 0; i < abs->p_n; i++) {
		if (abs->p[i].p_name==name) {
			return i;
		}
		return -1;
	}
}
void deleteperson(personarr*abs) {
	string name;
	cout << "请删除你要查找的人：" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "查无此人" << endl;
		return;
	}
	for (int i = ret; i < abs->p_n; i++) {
		abs->p[i] = abs->p[i + 1];
	}
	abs->p_n--;
	cout << "删除完成" << endl;
	system("pause");
	system("cls");
}
void findperson(personarr*abs) {
	string name;
	cout << "请输入你要查找的人：" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "查无此人" << endl;
		return;
	}
	cout << "姓名：" << abs->p[ret].p_name << '\t';
	cout << "性别：" << (abs->p[ret].p_sex == 1 ? "男" : "女") << '\t';
	cout << "年龄：" << abs->p[ret].p_age << '\t';
	cout << "电话：" << abs->p[ret].p_phone << '\t';
	cout << "地址：" << abs->p[ret].p_addrss << endl;

	cout << "查找完毕" << endl;
	system("pause");
	system("cls");
}
void modifyperson(personarr* abs) {
	string name;
	cout << "请输入你要修改的人：" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "查无此人" << endl;
		return;
	}
	cout << "姓名：" << endl;
	cin >> name;
	abs->p[ret].p_name = name;

	int sex;
	cout << "性别：" << endl;
	while (true) {
		cin >> sex;
		if (sex==1||sex==2) {
			abs->p[ret].p_sex = sex;
			break;
		}
		cout << "重新输入" << endl;
	}

	int age;
	cout << "请输入年龄：" << endl;
	cin >> age;
	abs->p[ret].p_age = age;

	string phone;
	cout << "请输入电话：" << endl;
	cin >> phone;
	abs->p[ret].p_phone = phone;

	string address;
	cout << "请输入地址：" << endl;
	cin >> address;
	abs->p[ret].p_addrss = address;

	cout << "修改完毕" << endl;
	system("pause");
	system("cls");

}
int main() {
	int t;
	personarr abs;
	while (true) {
		showmenu();
		cin >> t;
		switch (t) {
		case 1://增加
			addperson(&abs);
			break;
		case 2://显示
			showperson(&abs);
			break;
		case 3://删除
			deleteperson(&abs);
			break;
		case 4://查找
			findperson(&abs);
			break;
		case 5://修改
			modifyperson(&abs);
			break;
		case 6://清空
			abs.p_n = 0;
			break;
		case 0://退出
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		}
	}
	return 0;
}