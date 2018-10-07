#include<iostream>
#include<string>
using namespace std;

class Product // product Ŭ����
{
	int price;
	int abc;
	string comment;
	string maker;
public:
	Product() // Product ������
	{
		string comment;
		string maker;
		int price = 0;

		this->comment = comment;
		this->maker = maker;
		this->price = price;
	}

	void SetProduct() // Product ���� �Լ�
	{
		cout << "��ǰ���� >> ";
		getline(cin, comment);
		cout << "������ >> ";
		getline(cin, maker);
		cout << "���� >> ";
		cin >> price;
		cin.ignore(); // ���� ����
	}

	void ShowProduct() // Product �����ִ� �Լ�
	{
		cout << "��ǰ ���� : " << comment << endl;
		cout << "������ : " << maker << endl;
		cout << "���� : " << price << endl;
	}

	void setABC(int n) // ��ǰ�� ������ ���Ѵ�
	{
		abc= n;
	}
	int getABC(int n) // ��ǰ�� ������ int������ ��ȯ�Ѵ�
	{
		return abc;
	}
};

class Book :public Product // book Ŭ���� --> product ���
{
	string isbn;
	string auth;
	string title;
public:
	Book() // Book Ŭ���� ������
	{
		string title;
		string auth;
		string isbn;
		this->title = title;
		this->auth = auth;
		this->isbn = isbn;
	}

	void SetBook() // Book ���� �Լ�
	{
		SetProduct(); // ��� �̿� --> �θ� Ŭ������ SetProduct �Լ� ȣ��
		cout << "å ���� >> ";
		getline(cin, title);
		cout << "���� >> ";
		getline(cin, auth);
		cout << "ISBN >> ";
		getline(cin, isbn);
		setABC(1);
	}

	void ShowBook() // Book �����ִ� �Լ�
	{
		ShowProduct(); // ����̿� --> �θ� Ŭ������ ShowProduct �Լ� ȣ��
		cout << "å ���� : " << title << endl;
		cout << "���� : " << auth << endl;
		cout << "ISBN : " << isbn << endl;
	}
};

class CompactDisc :public Product // compactdisc Ŭ���� --> product ���
{
	string atitle;
	string singer;
public:
	CompactDisc() // Disc ������
	{
		string atitle;
		string singer;
		this->atitle = atitle;
		this->singer = singer;
	}

	void SetDisc() // Disc ���� �Լ�
	{
		SetProduct(); // ��� �̿� --> �θ� Ŭ������ SetProduct �Լ� ȣ��
		cout << "�ٹ� ���� >> ";
		getline(cin, atitle);
		cout << "���� >> ";
		getline(cin, singer);
		setABC(2);
	}

	void ShowDisc() // Disc �����ִ� �Լ�
	{
		ShowProduct(); // ��� �̿� --> �θ� Ŭ������ ShowProduct �Լ� ȣ��
		cout << "�ٹ� ���� : " << atitle << endl;
		cout << "���� : " << singer << endl;
	}
};

class ConversationBook :public Book // conversationbookŬ���� --> book ��� --> Product ���
{
	string langua;
public:
	ConversationBook() // conversationbook ������
	{
		this->langua = langua;
	}

	void SetCnvBook() // cnvbook ���� �Լ�
	{
		SetBook(); // ����̿� --> �θ� Ŭ������ SetBook �Լ� ȣ��
		cout << "��� >> ";
		getline(cin, langua);
		setABC(3);
	}

	void ShowCnvBook() //cnvbook �����ִ� �Լ�
	{
		ShowBook(); // ��� �̿� --> �θ� Ŭ������ ShowBook �Լ� ȣ�� --> ShowBook�Լ��� ShowProduct�� �̾���
		cout << "��� : " << langua << endl;
	}
};

int main()
{
	int i = 0;
	char sel;

	Product *pro[100];

	Book *book[100], bo[100]; // �ִ� 100���� ��ǰ���� ����
	
	ConversationBook *cnvBook[100], cnvbo[100]; // �ִ� 100���� ��ǰ���� ����

	CompactDisc *cmpDisc[100], disc[100]; // �ִ� 100���� ��ǰ���� ����


	cout << "***** ��ǰ ���� ���α׷��� �۵��մϴ� *****" << endl;
	while (1) // while���� �̿��Ͽ� ���Ḧ ���Ҷ����� ��� ����
	{
		cout << endl << endl << "��ǰ �߰�(1), ��� ��ǰ ��ȸ(2), ������(3) ? ";
		cin >> sel;
		cin.ignore(); // ���� ����

		switch (sel)
		{
		case '1': // ��ǰ �߰�
			cout << endl << "��ǰ ���� å(1), ����CD(2), ȸȭå(3) ? ";
			cin >> sel;
			cin.ignore(); // ���� ����
			switch (sel)
			{
			case '1': // å
				pro[i] = &bo[i]; // ��ĳ����
				book[i] = (Book *)pro[i]; // �ٿ�ĳ����
				book[i]->SetBook();
				i++;
				break;
			case '2': // ���� CD
				pro[i] = &disc[i]; // ��ĳ����
				cmpDisc[i] = (CompactDisc *)pro[i]; // �ٿ�ĳ����
				cmpDisc[i]->SetDisc();
				i++;
				break;
			case '3': // ȸȭå
				pro[i] = &cnvbo[i]; // ��ĳ����
				cnvBook[i] = (ConversationBook *)pro[i]; //�ٿ�ĳ����
				cnvBook[i]->SetCnvBook();
				i++;
				break;
			default:
				cout << endl << "�߸� �Է� �ϼ̽��ϴ�!" << endl << endl;
				break;
			}
			break;

		case '2': // ��ǰ ��ȸ
			for (int j = 0; j < i; j++)
			{
				cout << "--- ��ǰ ID : " << j << endl;
				int a = pro[j]->getABC(j); // ��ǰ ������ �޾ƿ�
				
				switch(a) // ��ǰ ������ ���� ���
				{
				case 1:
					book[j]->ShowBook(); 
					break;
				case 2:
					cmpDisc[j]->ShowDisc();
					break;
				case 3:
					cnvBook[j]->ShowCnvBook();
					break;
				}
				
			}
			break;

		case '3': // ����
			exit(0);

		default:
			cout << "�߸� �Է� �ϼ̽��ϴ�!" << endl;
			break;
		}
	}
}