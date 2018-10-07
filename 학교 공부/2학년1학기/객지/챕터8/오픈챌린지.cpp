#include<iostream>
#include<string>
using namespace std;

class Product // product 클래스
{
	int price;
	int abc;
	string comment;
	string maker;
public:
	Product() // Product 생성자
	{
		string comment;
		string maker;
		int price = 0;

		this->comment = comment;
		this->maker = maker;
		this->price = price;
	}

	void SetProduct() // Product 셋팅 함수
	{
		cout << "상품설명 >> ";
		getline(cin, comment);
		cout << "생산자 >> ";
		getline(cin, maker);
		cout << "가격 >> ";
		cin >> price;
		cin.ignore(); // 버퍼 제거
	}

	void ShowProduct() // Product 보여주는 함수
	{
		cout << "상품 설명 : " << comment << endl;
		cout << "생산자 : " << maker << endl;
		cout << "가격 : " << price << endl;
	}

	void setABC(int n) // 상품을 종류를 정한다
	{
		abc= n;
	}
	int getABC(int n) // 상품의 종류를 int형으로 반환한다
	{
		return abc;
	}
};

class Book :public Product // book 클래스 --> product 상속
{
	string isbn;
	string auth;
	string title;
public:
	Book() // Book 클래스 생성자
	{
		string title;
		string auth;
		string isbn;
		this->title = title;
		this->auth = auth;
		this->isbn = isbn;
	}

	void SetBook() // Book 셋팅 함수
	{
		SetProduct(); // 상속 이용 --> 부모 클래스의 SetProduct 함수 호출
		cout << "책 제목 >> ";
		getline(cin, title);
		cout << "저자 >> ";
		getline(cin, auth);
		cout << "ISBN >> ";
		getline(cin, isbn);
		setABC(1);
	}

	void ShowBook() // Book 보여주는 함수
	{
		ShowProduct(); // 상속이용 --> 부모 클래스의 ShowProduct 함수 호출
		cout << "책 제목 : " << title << endl;
		cout << "저자 : " << auth << endl;
		cout << "ISBN : " << isbn << endl;
	}
};

class CompactDisc :public Product // compactdisc 클래스 --> product 상속
{
	string atitle;
	string singer;
public:
	CompactDisc() // Disc 생성자
	{
		string atitle;
		string singer;
		this->atitle = atitle;
		this->singer = singer;
	}

	void SetDisc() // Disc 셋팅 함수
	{
		SetProduct(); // 상속 이용 --> 부모 클래스의 SetProduct 함수 호출
		cout << "앨범 제목 >> ";
		getline(cin, atitle);
		cout << "가수 >> ";
		getline(cin, singer);
		setABC(2);
	}

	void ShowDisc() // Disc 보여주는 함수
	{
		ShowProduct(); // 상속 이용 --> 부모 클래스의 ShowProduct 함수 호출
		cout << "앨범 제목 : " << atitle << endl;
		cout << "가수 : " << singer << endl;
	}
};

class ConversationBook :public Book // conversationbook클래스 --> book 상속 --> Product 상속
{
	string langua;
public:
	ConversationBook() // conversationbook 생성자
	{
		this->langua = langua;
	}

	void SetCnvBook() // cnvbook 셋팅 함수
	{
		SetBook(); // 상속이용 --> 부모 클래스의 SetBook 함수 호출
		cout << "언어 >> ";
		getline(cin, langua);
		setABC(3);
	}

	void ShowCnvBook() //cnvbook 보여주는 함수
	{
		ShowBook(); // 상속 이용 --> 부모 클래스의 ShowBook 함수 호출 --> ShowBook함수는 ShowProduct로 이어짐
		cout << "언어 : " << langua << endl;
	}
};

int main()
{
	int i = 0;
	char sel;

	Product *pro[100];

	Book *book[100], bo[100]; // 최대 100개의 상품까지 관리
	
	ConversationBook *cnvBook[100], cnvbo[100]; // 최대 100개의 상품까지 관리

	CompactDisc *cmpDisc[100], disc[100]; // 최대 100개의 상품까지 관리


	cout << "***** 상품 관리 프로그램을 작동합니다 *****" << endl;
	while (1) // while문을 이용하여 종료를 원할때까지 계속 돌림
	{
		cout << endl << endl << "상품 추가(1), 모든 상품 조회(2), 끝내기(3) ? ";
		cin >> sel;
		cin.ignore(); // 버퍼 제거

		switch (sel)
		{
		case '1': // 상품 추가
			cout << endl << "상품 종류 책(1), 음악CD(2), 회화책(3) ? ";
			cin >> sel;
			cin.ignore(); // 버퍼 제거
			switch (sel)
			{
			case '1': // 책
				pro[i] = &bo[i]; // 업캐스팅
				book[i] = (Book *)pro[i]; // 다운캐스팅
				book[i]->SetBook();
				i++;
				break;
			case '2': // 음악 CD
				pro[i] = &disc[i]; // 업캐스팅
				cmpDisc[i] = (CompactDisc *)pro[i]; // 다운캐스팅
				cmpDisc[i]->SetDisc();
				i++;
				break;
			case '3': // 회화책
				pro[i] = &cnvbo[i]; // 업캐스팅
				cnvBook[i] = (ConversationBook *)pro[i]; //다운캐스팅
				cnvBook[i]->SetCnvBook();
				i++;
				break;
			default:
				cout << endl << "잘못 입력 하셨습니다!" << endl << endl;
				break;
			}
			break;

		case '2': // 상품 조회
			for (int j = 0; j < i; j++)
			{
				cout << "--- 상품 ID : " << j << endl;
				int a = pro[j]->getABC(j); // 상품 종류를 받아옴
				
				switch(a) // 상품 종류에 따라서 출력
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

		case '3': // 종료
			exit(0);

		default:
			cout << "잘못 입력 하셨습니다!" << endl;
			break;
		}
	}
}