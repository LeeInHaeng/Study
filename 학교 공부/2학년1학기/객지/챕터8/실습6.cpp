#include<iostream>
using namespace std;

class BaseArray { // 책에 작성되어 있는 클래스
private:
	int capacity; // 배열의 크기
	int *mem; // 정수 배열을 만들기 위한 메모리의 포인터
protected:
	BaseArray(int capacity = 100) { // 스택의 디폴트 용량 100
		this->capacity = capacity;
		mem = new int[capacity]; // 사용자가 원하는 만큼의 용량을 할당받기 위한 new
	}
	~BaseArray() { // new를 반환
		delete[] mem;
	}
	void put(int index, int val) { // index에 val 값을 넣는 함수
		mem[index] = val;
	}
	int get(int index) { // index에 들어있는 val 값이 뭔지 알아오는 함수
		return mem[index];
	}
	int getCapacity() { // 스택의 용량을 알아내는 함수
		return capacity;
	}
};

class Mystack :public BaseArray // 상속
{
	int i;
	int len;
	int size;
public:
	Mystack(int size = 100) {
		this->size = size;
	}

	void push(int &n) // push 함수
	{
		static int i=0; // index가 초기화 되지 않도록 static으로 선언
		this->i = i;
		put(i, n); // 상속을 이용한 put 함수 호출 / mem의 index(i)에 val(n)을 넣음
		i++;
	}

	int capacity()
	{
		return getCapacity(); // 상속을 이용한 스택의 용량 확인 함수 호출
	}

	int length()
	{
		int len=0;
		this->len = len;
		len = i + 1;
		return len;
	}

	int pop()
	{
		i--;
		return get(i+1); // 상속을 이용한 get 함수 호출 / i+1은 len(스택의 길이)와 같음
	}
};

int main() // 책에 작성되어 있는 main 형태
{
	Mystack mStack(100);
	int n;
	cout << "스택에 삽입할 5개의 정수를 입력하라 >> ";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mStack.push(n);
	}

	cout << "스택 용량 : " << mStack.capacity() << ", 스택 크기 : " << mStack.length() << endl;
	cout << "스택의 모든 원소를 팝하여 출력한다 >> ";
	while (mStack.length() != 0) {
		cout << mStack.pop() << ' ';
	}
	cout << endl << "스택의 현재 크기 : " << mStack.length() << endl;
}