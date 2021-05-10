#include <iostream>
using namespace std;
#include<string>
#define max 1000
struct person {
	string m_name;
	int m_sex;
	int m_age;
	string phone;
	string address;
};
struct member {
	person s1[max];
	int m_nu=0;
};
void showmenu() {
	cout<<"***************************"<<endl;
	cout<<"*****  1、增添联系人  *****"<<endl;
	cout<<"*****  2、显示联系人  *****"<<endl;
	cout<<"*****  3、删除联系人  *****"<<endl;
	cout<<"*****  4、查找联系人  *****"<<endl;
	cout<<"*****  5、修改联系人  *****"<<endl;
	cout<<"*****  6、清空联系人  *****"<<endl;
	cout<<"*****  0、退出通讯录  *****"<<endl;
	cout<<"***************************"<<endl;
}
void addperson(member* abs) {
	if (abs->m_nu == 1000) {
		cout << "通讯录已满" << endl;
	}
	else {
		string name;
		cout << "姓名：" << endl;
		cin >> name;
		abs->s1[abs->m_nu].m_name = name;

		int sex;
		cout << "性别：" << endl;
		cout << "1---男  2---女" << endl;
		while (true) {
			cin >> sex;
			if (sex==1||sex==2) {
				abs->s1[abs->m_nu].m_sex = sex;
				break;
			}
			else {
				cout << "输入有误,重新输入" << endl;//当输入除数字以外的 会导致这句话重复？？？
			}
		}

		int age;
		cout << "年龄：" << endl;
		cin >> age;
		abs->s1[abs->m_nu].m_age = age;

		string phone;
		cout << "电话：" << endl;
		cin >> phone;
		abs->s1[abs->m_nu].phone = phone;

		string address;
		cout << "地址：" << endl;
		cin >> address;
		abs->s1[abs->m_nu].address = address;

		abs->m_nu++;
		cout << "增添成功" << endl;
		//		system("pause");
		//      system("cls");
	}
	system("pause");//这两个放到这儿  我把上面if的东西可以省略break；
	system("cls");

}
int isexist(member* abs, string name) {
	for (int i = 0; i < abs->m_nu; i++) {
		if (abs->s1[i].m_name == name) {
			return i;
		}
		else {
			return -1;
		}
	}
}
void researchperson(member* abs) {
	cout << "请输入你要查询的人名" << endl;
	string name;
	cin>>name;
	int ret = isexist(abs, name);
	if (ret!=-1) {
		cout << "姓名：" << abs->s1[ret].m_name << '\t';
		cout << "性别：" << (abs->s1[ret].m_sex==1?"男":"女" )<< '\t';
		cout << "年龄：" << abs->s1[ret].m_age << '\t';
		cout << "电话：" << abs->s1[ret].phone << '\t';
		cout << "地址：" << abs->s1[ret].address << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}
void showperson(member* abs) {
	int i = 0;
	if (abs->m_nu == 0) {
		cout << "通讯录为空" << endl;

	}
	else {
		for (int i = 0; i < abs->m_nu; i++) {
			cout << "姓名：" << abs->s1[i].m_name << '\t';
			cout << "性别：" << (abs->s1[i].m_sex==1?"男":"女") << "\t";
			cout << "年龄：" << abs->s1[i].m_age << '\t';
			cout << "电话：" << abs->s1[i].phone << '\t';
			cout << "地址：" << abs->s1[i].address << endl;
		}
	}
	system("pause");
	system("cls");
}
void deleteperson(member* abs) {//经常性错误：不能用delete
	cout << "请输入你要删除的人：" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);//经常性错误：行参之间用逗号，不要用分号
	if (ret != -1) {
		for (int i = ret; i < abs->m_nu; i++)//当然for循环里可以用分号
		{
			abs->s1[i] = abs->s1[i + 1];
		}
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}
void modifyperson(member*abs) {
	cout << "请输入你要修改的人：" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "查无此人" << endl;
	}
	else {
		string name;
		cout << "姓名：" << endl;
		cin >> name;
		abs->s1[ret].m_name = name;

		int sex;
		cout << "性别：" << endl;
		while (true) {
			cin >> sex;
			if(sex==1||sex==2){
				abs->s1[ret].m_sex = sex;
			}
		}

		int age;
		cout << "年龄：" << endl;
		cin >> age;
		abs->s1[ret].m_age = age;

		string phone;
		cout << "电话：" << endl;
		cin >> phone;
		abs->s1[ret].phone = phone;

		string address;
		cout << "地址：" << endl;
		cin >> address;
		abs->s1[ret].address = address;


		cout << "修改完成" << endl;

	}
	system("pause");
	system("cls");
}
void emptyperson(member*abs) {
	abs->m_nu = 0;
	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}
int main() {
	member abs;

	//showmenu();  这个不能放这儿
	int t;
	while (true) {
		showmenu();//显示菜单放这儿
		cin >> t ;
		//showmenu();  这个不能放这儿
		switch (t) {
		case 1://增添
			addperson(&abs);
			break;
		case 2://显示
			showperson(&abs);
			break;
		case 3://删除
			deleteperson(&abs);
			break;
		case 4://查找
			researchperson(&abs);
			break;
		case 5://修改
			modifyperson(&abs);
			break;
		case 6://清空
			emptyperson(&abs);
			break;
		case 0://退出
			cout << "欢迎下次使用" << endl;
			return 0;
			system("pause");
			system("cls");
		default:
			break;
		}

	}
	return 0;
}