#include<iostream>
using namespace std;

template<typename T>
class CircularQueue
{
	T arr[10]; // 각 원소가 저장될 배열
	int front; // 가장 먼저 들어온 원소를 가리기는 index
	int rear; // 가장 나중에 들어온 원소를 가리키는 index 
public:
	CircularQueue(); // front와 rear를 초기화하기 위한 디폴트 생성자
	void Push(T element); // 매개변수로 받은 원소를 큐의 맨 뒤에 추가하는 함수
	void Pop(); // 가장 먼저 들어온 (앞에 있는) 원소를 삭제하는 함수
	void Print(); // 큐의 맨 뒤의 원소부터 순서대로 출력하는 함수
};

template<typename T>
CircularQueue<T>::CircularQueue()
{
	front = 0; // front의 초기값 설정
	rear = 0; // rear의 초기값을 설정
}


template<typename T>
void CircularQueue<T>::Push(T element)
{
	if ((rear + 1) % 10 == front % 10) { // 큐가 꽉 찬 경우
        cout << "OVER FLOW" << endl; // over flow 발생
        return; // push 함수 종료
    }

	arr[(++rear) % 10] = element; // rear의 값을 1 증가시키고 해당 인덱스에 원소를 추가
}

template<typename T>
void CircularQueue<T>::Pop()
{
	if (rear == front){ // 큐가 비어있을 경우
        cout << "UNDER FLOW" << endl; // under flow 발생
        return; // pop 함수 종료
    }

	front++; // front 값 1 증가
}

template<typename T>
void CircularQueue<T>::Print()
{
	if (rear == front) { // 큐가 비어있을 경우
        cout << "THE QUEUE IS EMPTY" << endl; // 큐가 비었음을 알림
        return; // print 함수 종료
    }

	for (int i = front + 1; i <= rear; i++)
		cout << arr[i % 10] << '\t';
	cout << endl;
}

int main(void)
{
    CircularQueue<int> CQ;
    CQ.Print();

    CQ.Push(1);
    CQ.Print();

    CQ.Push(2);
    CQ.Print();

    CQ.Push(3);
    CQ.Print();

    CQ.Push(4);
    CQ.Print();

    CQ.Pop();
    CQ.Print();

    CQ.Pop();
    CQ.Print();

    CQ.Push(5);
    CQ.Print();

    CQ.Pop();
    CQ.Print();

    CQ.Pop();
    CQ.Print();

    CQ.Pop();

    return 0;
}
