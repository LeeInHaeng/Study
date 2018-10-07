#include<iostream>
using namespace std;

class BaseArray { // å�� �ۼ��Ǿ� �ִ� Ŭ����
private:
	int capacity; // �迭�� ũ��
	int *mem; // ���� �迭�� ����� ���� �޸��� ������
protected:
	BaseArray(int capacity = 100) { // ������ ����Ʈ �뷮 100
		this->capacity = capacity;
		mem = new int[capacity]; // ����ڰ� ���ϴ� ��ŭ�� �뷮�� �Ҵ�ޱ� ���� new
	}
	~BaseArray() { // new�� ��ȯ
		delete[] mem;
	}
	void put(int index, int val) { // index�� val ���� �ִ� �Լ�
		mem[index] = val;
	}
	int get(int index) { // index�� ����ִ� val ���� ���� �˾ƿ��� �Լ�
		return mem[index];
	}
	int getCapacity() { // ������ �뷮�� �˾Ƴ��� �Լ�
		return capacity;
	}
};

class Mystack :public BaseArray // ���
{
	int i;
	int len;
	int size;
public:
	Mystack(int size = 100) {
		this->size = size;
	}

	void push(int &n) // push �Լ�
	{
		static int i=0; // index�� �ʱ�ȭ ���� �ʵ��� static���� ����
		this->i = i;
		put(i, n); // ����� �̿��� put �Լ� ȣ�� / mem�� index(i)�� val(n)�� ����
		i++;
	}

	int capacity()
	{
		return getCapacity(); // ����� �̿��� ������ �뷮 Ȯ�� �Լ� ȣ��
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
		return get(i+1); // ����� �̿��� get �Լ� ȣ�� / i+1�� len(������ ����)�� ����
	}
};

int main() // å�� �ۼ��Ǿ� �ִ� main ����
{
	Mystack mStack(100);
	int n;
	cout << "���ÿ� ������ 5���� ������ �Է��϶� >> ";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mStack.push(n);
	}

	cout << "���� �뷮 : " << mStack.capacity() << ", ���� ũ�� : " << mStack.length() << endl;
	cout << "������ ��� ���Ҹ� ���Ͽ� ����Ѵ� >> ";
	while (mStack.length() != 0) {
		cout << mStack.pop() << ' ';
	}
	cout << endl << "������ ���� ũ�� : " << mStack.length() << endl;
}