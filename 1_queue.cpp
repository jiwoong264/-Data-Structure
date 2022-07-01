#include<iostream>
using namespace std;

template<typename T>
class Queue
{
	T arr[10]; // 각 원소가 저장될 배열
	int front; // 가장 먼저 들어온 원소를 가리기는 index
	int rear; // 가장 나중에 들어온 원소를 가리키는 index 
public:
	Queue(); // front와 rear를 초기화하기 위한 디폴트 생성자
	void Push(T element); // 매개변수로 받은 원소를 큐의 맨 뒤에 추가하는 함수
	T Pop(); // 가장 먼저 들어온 (앞에 있는) 원소를 삭제하고 리턴하는 함수
	void Print(); // 맨 뒤의 원소부터 순서대로 출력하는 함수
};

template<typename T>
Queue<T>::Queue()
{
	front = -1; // front의 초기값 -1로 설정
	rear = -1; // rear의 초기값을 -1로 설정
}


template<typename T>
void Queue<T>::Push(T element)
{
	if (rear >= 9) { // 큐가 꽉 찬 경우
        cout << "OVER FLOW" << endl; // over flow 발생
        return; // push 함수 종료
    }

	arr[++rear] = element; // rear의 값을 1 증가시키고 해당 인덱스에 원소를 추가
}

template<typename T>
T Queue<T>::Pop()
{
	if (rear <= front){ // 큐가 비어있을 경우
        cout << "UNDER FLOW" << endl; // under flow 발생
        return 0; // pop 함수 종료
    }

	return arr[++front]; // front의 값을 1 증가시키고 해당 인덱스의 원소를 반환
}

template<typename T>
void Queue<T>::Print()
{
	if (rear <= front) { // 큐가 비어있을 경우
        cout << "THE QUEUE IS EMPTY" << endl; // 큐가 비었음을 알림
        return; // print 함수 종료
    }

	for (int i = front + 1; i <= rear; i++)
		cout << arr[i] << '\t';
	cout << endl;
	
}

int main() {
    Queue<int> Q; // int형 큐 객체 생성
    int input = -1; // 사용자로부터 실행할 동작을 입력을 받기 위한 변수
    int ele; // 사용자로부터 push할 원소의 값을 입력받을 변수

    while (input) { // input == 0 이 되면 종료
        cout << "(1)push    (2)pop    (3)print    (0)END" << endl;
        cin >> input; // 사용자로부터 실행할 동작을 입력받음

        if (input == 1) { // push
            cout << "element : ";
            cin >> ele; // push할 원소를 입력받음
            Q.Push(ele); // 객체에서 push 함수 호출
        }
        else if (input == 2) { // pop
            Q.Pop(); // 객체에서 pop 함수 호출
        }
        else if (input == 3) { // print
            Q.Print(); // 객체에서 print 함수 호출
        }
    }
}