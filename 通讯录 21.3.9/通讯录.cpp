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
	cout<<"*****  1��������ϵ��  *****"<<endl;
	cout<<"*****  2����ʾ��ϵ��  *****"<<endl;
	cout<<"*****  3��ɾ����ϵ��  *****"<<endl;
	cout<<"*****  4��������ϵ��  *****"<<endl;
	cout<<"*****  5���޸���ϵ��  *****"<<endl;
	cout<<"*****  6�������ϵ��  *****"<<endl;
	cout<<"*****  0���˳�ͨѶ¼  *****"<<endl;
	cout<<"***************************"<<endl;
}
void addperson(member* abs) {
	if (abs->m_nu == 1000) {
		cout << "ͨѶ¼����" << endl;
	}
	else {
		string name;
		cout << "������" << endl;
		cin >> name;
		abs->s1[abs->m_nu].m_name = name;

		int sex;
		cout << "�Ա�" << endl;
		cout << "1---��  2---Ů" << endl;
		while (true) {
			cin >> sex;
			if (sex==1||sex==2) {
				abs->s1[abs->m_nu].m_sex = sex;
				break;
			}
			else {
				cout << "��������,��������" << endl;//���������������� �ᵼ����仰�ظ�������
			}
		}

		int age;
		cout << "���䣺" << endl;
		cin >> age;
		abs->s1[abs->m_nu].m_age = age;

		string phone;
		cout << "�绰��" << endl;
		cin >> phone;
		abs->s1[abs->m_nu].phone = phone;

		string address;
		cout << "��ַ��" << endl;
		cin >> address;
		abs->s1[abs->m_nu].address = address;

		abs->m_nu++;
		cout << "����ɹ�" << endl;
		//		system("pause");
		//      system("cls");
	}
	system("pause");//�������ŵ����  �Ұ�����if�Ķ�������ʡ��break��
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
	cout << "��������Ҫ��ѯ������" << endl;
	string name;
	cin>>name;
	int ret = isexist(abs, name);
	if (ret!=-1) {
		cout << "������" << abs->s1[ret].m_name << '\t';
		cout << "�Ա�" << (abs->s1[ret].m_sex==1?"��":"Ů" )<< '\t';
		cout << "���䣺" << abs->s1[ret].m_age << '\t';
		cout << "�绰��" << abs->s1[ret].phone << '\t';
		cout << "��ַ��" << abs->s1[ret].address << endl;
	}
	else {
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}
void showperson(member* abs) {
	int i = 0;
	if (abs->m_nu == 0) {
		cout << "ͨѶ¼Ϊ��" << endl;

	}
	else {
		for (int i = 0; i < abs->m_nu; i++) {
			cout << "������" << abs->s1[i].m_name << '\t';
			cout << "�Ա�" << (abs->s1[i].m_sex==1?"��":"Ů") << "\t";
			cout << "���䣺" << abs->s1[i].m_age << '\t';
			cout << "�绰��" << abs->s1[i].phone << '\t';
			cout << "��ַ��" << abs->s1[i].address << endl;
		}
	}
	system("pause");
	system("cls");
}
void deleteperson(member* abs) {//�����Դ��󣺲�����delete
	cout << "��������Ҫɾ�����ˣ�" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);//�����Դ����в�֮���ö��ţ���Ҫ�÷ֺ�
	if (ret != -1) {
		for (int i = ret; i < abs->m_nu; i++)//��Ȼforѭ��������÷ֺ�
		{
			abs->s1[i] = abs->s1[i + 1];
		}
	}
	else {
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}
void modifyperson(member*abs) {
	cout << "��������Ҫ�޸ĵ��ˣ�" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret == -1) {
		cout << "���޴���" << endl;
	}
	else {
		string name;
		cout << "������" << endl;
		cin >> name;
		abs->s1[ret].m_name = name;

		int sex;
		cout << "�Ա�" << endl;
		while (true) {
			cin >> sex;
			if(sex==1||sex==2){
				abs->s1[ret].m_sex = sex;
			}
		}

		int age;
		cout << "���䣺" << endl;
		cin >> age;
		abs->s1[ret].m_age = age;

		string phone;
		cout << "�绰��" << endl;
		cin >> phone;
		abs->s1[ret].phone = phone;

		string address;
		cout << "��ַ��" << endl;
		cin >> address;
		abs->s1[ret].address = address;


		cout << "�޸����" << endl;

	}
	system("pause");
	system("cls");
}
void emptyperson(member*abs) {
	abs->m_nu = 0;
	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");
}
int main() {
	member abs;

	//showmenu();  ������ܷ����
	int t;
	while (true) {
		showmenu();//��ʾ�˵������
		cin >> t ;
		//showmenu();  ������ܷ����
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
			researchperson(&abs);
			break;
		case 5://�޸�
			modifyperson(&abs);
			break;
		case 6://���
			emptyperson(&abs);
			break;
		case 0://�˳�
			cout << "��ӭ�´�ʹ��" << endl;
			return 0;
			system("pause");
			system("cls");
		default:
			break;
		}

	}
	return 0;
}