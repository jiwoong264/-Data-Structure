#include<iostream>
#include<stack>
using namespace std;

template<typename T>
class Queue
{
	stack<T> inStack; // Push 때 사용할, 각 원소가 저장될 배열
	stack<T> outStack; // Pop, Print시 사용할 임시 스택
public:
	void Push(T element); // 매개변수로 받은 원소를 큐의 맨 뒤에 추가하는 함수
	void Pop(); // 가장 먼저 들어온 (앞에 있는) 원소를 삭제하는 함수
	void Print(); // 맨 뒤의 원소부터 순서대로 출력하는 함수
};

template<typename T>
void Queue<T>::Push(T element)
{
    inStack.push(element); // inStack에 매개변수로 받은 element를 push
}

template<typename T>
void Queue<T>::Pop()
{
    if(inStack.empty()) // inStack이 빈 경우
        cout << "UNDER FLOW" << endl; // under frow 발생
        return; // pop을 할 수 없으므로 함수 종료
    
    while(!inStack.empty()) // inStack이 빌 때 까지 반복
    {
        outStack.push(inStack.top()); // outStack에 inStack의 top 원소를 push
        inStack.pop(); // inStack의 top 원소를 pop
    }    
    // while문이 종료되면 inStack은 비고, inStack에 있던 원소들은 역순으로 outStack에 들어감

    outStack.pop(); // outStack에서 pop을 하면 기존 inStack에 가장 처음으로 삽입된 원소가 삭제됨

    while(!outStack.empty()) // outStack이 빌 때 까지 반복
    {
        inStack.push(outStack.top()); // inStack에 outStack의 top 원소를 push
        outStack.pop(); // outStack의 top 원소를 pop
    }
    // while문이 종료되면 outStack은 비고, inStack에는 가장 아래 있던 원소만 삭제되고 원 상태로 돌아옴

}

template<typename T>
void Queue<T>::Print()
{
    while(!inStack.empty()) // inStack이 빌 때 까지 반복
    {
        outStack.push(inStack.top()); // outStack에 inStack의 top 원소를 push
        inStack.pop(); // inStack의 top 원소를 pop
    }    
    // while문이 종료되면 inStack은 비고, inStack에 있던 원소들은 역순으로 outStack에 들어감

    while(!outStack.empty()) // outStack이 빌 때 까지 반복
    {
        cout << outStack.top() << '\t'; // outStack의 top 원소를 출력
        inStack.push(outStack.top()); // inStack에 outStack의 top 원소를 push
        outStack.pop(); // outStack의 top 원소를 pop
    }
    // while문이 종료되면 outStack은 비고, inStack 원상복구 됨.
    // inStack에 있던 원소들은 아래 있던 원소부터 순서대로 출력됨

    cout << endl;

}


int main(void)
{
    Queue<int> SQ;
    SQ.Print();

    SQ.Push(1);
    SQ.Print();

    SQ.Push(2);
    SQ.Print();

    SQ.Push(3);
    SQ.Print();

    SQ.Push(4);
    SQ.Print();

    SQ.Pop();
    SQ.Print();

    SQ.Pop();
    SQ.Print();

    SQ.Push(5);
    SQ.Print();

    SQ.Pop();
    SQ.Print();

    SQ.Pop();
    SQ.Print();

    SQ.Pop();

    return 0;
}