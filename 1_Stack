#include<iostream>
using namespace std;

template<typename T>
class Stack
{
	T* arr; // 각 원소가 저장될 배열의 주소를 가리킬 포인터
	int length; // 스택의 크기
	int top; // 스택의 가장 위의 원소를 가리키는 index
public:
	Stack(int size); // size를 매개변수로 받아 해당 크기만큼 배열을 동적할당 받을 생성자
	void Push(T element); // 매개변수로 받은 원소를 스택의 가장 위에 추가하는 함수
	void Pop(); // 스택의 가장 위의 원소를 삭제하는 함수
	void Print(); // 스택의 가장 아래 원소부터 순서대로 출력하는 함수
	~Stack() {delete[] arr;} // 스택이 소멸될 때 동적할당받은 메모리를 반환하기 위한 소멸자
};

template<typename T>
Stack<T>::Stack(int size)
{
    length = size;
	arr = new T[length]; // size만큼 T타입의 배열 동적할당
    top = -1; // top 값 초기화
}


template<typename T>
void Stack<T>::Push(T element)
{
	if (top >= length - 1) { // 스택이 꽉 찬 경우
        cout << "OVER FLOW" << endl; // over flow 발생
        return; // push 함수 종료
    }

    arr[++top] = element; // top을 1 증가시킨 후 해당 인덱스에 매개변수로 받은 값 넣음
}

template<typename T>
void Stack<T>::Pop()
{
	if (top <= -1){ // 스택이 비어있을 경우
        cout << "UNDER FLOW" << endl; // under flow 발생
        return; // pop 함수 종료
    }

    top--; // top 1 감소
}

template<typename T>
void Stack<T>::Print()
{
	if (top <= -1) { // 스택이 비어있을 경우
        cout << "THE STACK IS EMPTY" << endl; // 스택이 비었음을 알림
        return; // print 함수 종료
    }

    for (int i = 0; i < top+1; i++) // 스택의 원소의 개수만큼 반복
        cout << arr[i] << '\t'; // 인덱스 0 부터 스택의 원소 출력
    cout << endl;
}


int main(void)
{
	Stack<int> stack(3);
	stack.Print();

	stack.Push(1);
	stack.Print();

	stack.Push(2);
	stack.Print();

	stack.Push(3);
	stack.Print();

	stack.Push(4);
	stack.Print();

	stack.Pop();
	stack.Print();

	stack.Pop();
	stack.Print();

	stack.Push(5);
	stack.Print();

	stack.Pop();
	stack.Print();

	stack.Pop();
	stack.Print();

	stack.Pop();

	return 0;
}
