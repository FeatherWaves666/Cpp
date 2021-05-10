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
	cout << "1��������ϵ��" << endl;
	cout << "2����ʾ��ϵ��" << endl;
	cout << "3��ɾ����ϵ��" << endl;
	cout << "4��������ϵ��" << endl;
	cout << "5���޸���ϵ��" << endl;
	cout << "6�������ϵ��" << endl;
	cout << "0���˳�ͨѶ¼" << endl;
	cout << "*************" << endl;
}
void addperson(personarr* abs) {
	if (abs->p_n == 1000) {
		cout << "ͨѶ¼����" << endl;
		return;
	}
	string name;
	cout << "������" << endl;
	cin >> name;
	abs->p[abs->p_n].p_name = name;
	
	int sex;
	cout << "�Ա�" << endl;
	cout << "1---�� 2---Ů" << endl;
	while (true) {
		cin >> sex;
		if (sex == 1 || sex == 2) {
			abs->p[abs->p_n].p_sex = sex;
			break;
		}
		cout << "��������" << endl;
	}

	int age;
	cout << "���䣺" << endl;
	cin >> age;
	abs->p[abs->p_n].p_age= age;

	string phone;
	cout << "�绰��" << endl;
	cin >> phone;
	abs->p[abs->p_n].p_phone = phone;

	string address;
	cout << "��ַ��" << endl;
	cin >> address;
	abs->p[abs->p_n].p_addrss = address;

	abs->p_n++;

	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
}
void showperson(personarr*abs) {
	if (abs->p_n == 0) {
		cout << "ͨѶ¼Ϊ��" << endl;
		//return;  ��Ҫ���������menu�ظ�����  ��Ϊû��cls������
	}
	else {
		for (int i = 0; i < abs->p_n; i++) {
			cout << "������" << abs->p[i].p_name << '\t';
			cout << "�Ա�" << (abs->p[i].p_sex == 1 ? "��" : "Ů") << '\t';
			cout << "���䣺" << abs->p[i].p_age << '\t';
			cout << "�绰��" << abs->p[i].p_phone << '\t';
			cout << "��ַ��" << abs->p[i].p_addrss << endl;
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
	cout << "��ɾ����Ҫ���ҵ��ˣ�" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "���޴���" << endl;
		return;
	}
	for (int i = ret; i < abs->p_n; i++) {
		abs->p[i] = abs->p[i + 1];
	}
	abs->p_n--;
	cout << "ɾ�����" << endl;
	system("pause");
	system("cls");
}
void findperson(personarr*abs) {
	string name;
	cout << "��������Ҫ���ҵ��ˣ�" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "���޴���" << endl;
		return;
	}
	cout << "������" << abs->p[ret].p_name << '\t';
	cout << "�Ա�" << (abs->p[ret].p_sex == 1 ? "��" : "Ů") << '\t';
	cout << "���䣺" << abs->p[ret].p_age << '\t';
	cout << "�绰��" << abs->p[ret].p_phone << '\t';
	cout << "��ַ��" << abs->p[ret].p_addrss << endl;

	cout << "�������" << endl;
	system("pause");
	system("cls");
}
void modifyperson(personarr* abs) {
	string name;
	cout << "��������Ҫ�޸ĵ��ˣ�" << endl;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "���޴���" << endl;
		return;
	}
	cout << "������" << endl;
	cin >> name;
	abs->p[ret].p_name = name;

	int sex;
	cout << "�Ա�" << endl;
	while (true) {
		cin >> sex;
		if (sex==1||sex==2) {
			abs->p[ret].p_sex = sex;
			break;
		}
		cout << "��������" << endl;
	}

	int age;
	cout << "���������䣺" << endl;
	cin >> age;
	abs->p[ret].p_age = age;

	string phone;
	cout << "������绰��" << endl;
	cin >> phone;
	abs->p[ret].p_phone = phone;

	string address;
	cout << "�������ַ��" << endl;
	cin >> address;
	abs->p[ret].p_addrss = address;

	cout << "�޸����" << endl;
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
		case 1://����
			addperson(&abs);
			break;
		case 2://��ʾ
			showperson(&abs);
			break;
		case 3://ɾ��
			deleteperson(&abs);
			break;
		case 4://����
			findperson(&abs);
			break;
		case 5://�޸�
			modifyperson(&abs);
			break;
		case 6://���
			abs.p_n = 0;
			break;
		case 0://�˳�
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		}
	}
	return 0;
}