#include<iostream>
using namespace std;

template<typename T>
class Queue {
    private:
    class Node {
        public:
        T data; //단어를 저장할 변수
        Node* link; //다음 노드의 주소를 저장할 포인터
        Node(T element) { data = element; link = NULL;}; //element를 data로 가지는 Node를 생성하는 생성자
    };
    Node* first; //제일 앞의 노드를 가리킬 포인터
    Node* rear; //제일 뒤의 노드를 가리킬 포인터

public:
    Queue(T token); //생성자
    void Push(T token); //제일 뒤에 노드 삽입
    void Pop(); //제일 앞의 노드 삭제
    void Front(); //제일 앞의 노드 출력, 없는 경우 예외처리
    void Print(); //제일 앞의 노드부터 순서대로 마지막 노드의 data까지 출력
};

template<typename T>
Queue<T>::Queue(T token) {
    rear = new Node(token); //매개변수로 받은 token를 data로 가지는 Node를 생성, rear가 가리키게 함
    first = rear;
}

template<typename T>
void Queue<T>::Push(T token) {
    Node* node = new Node(token); //token를 data로 갖는 삽입할 노드 생성 

    if (!first) //큐가 비어있는 경우
    {
        rear = node; //rear가 생성된 노드를 가리킴
        first = node; //first도 생성된 노드를 가리킴
        return; //함수 종료
    }

    //큐가 비어있지 않아 맨 뒤에 노드를 추가하는 경우
    rear->link = node; //기존의 마지막 노드가 생성된 노드를 가리킴
    rear = node; //rear가 생성된 노드를 가리킴
    
}

template<typename T>
void Queue<T>::Pop() {
    if (!first) //큐가 빈 경우
    {
        cout << "Empty Queue" << endl; //경고문 출력
        return; //함수 종료
    }
    //큐가 비어있지 않아 맨 앞의 노드를 삭제하는 경우
    Node* tmp = first->link; //기존의 두 번째 노드의 주소를 저장할 포인터 생성
    first->link = NULL; //반환 전 first의 link 초기화
    delete first; //기존의 첫 번째 노드 반환
    first = tmp; //first가 기존의 두 번째 노드를 가리킴
}

template<typename T>
void Queue<T>::Front() {
    if (!rear) //큐가 빈 경우
    {
        cout << "Empty Queue" << endl; //경고문 출력
        return; //함수 종료
    }

    cout << "Data of front Node : " << first->data << endl; //first가 가리키는 맨 앞 노드의 data 출력
}

template<typename T>
void Queue<T>::Print() {
    if (!first) //큐가 빈 경우
    {
        cout << "Empty Linkes List" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = first; //처음부터 끝까지 각 노드를 탐색할 포인터

    while (tmp != NULL) //tmp가 마지막 노드까지 가리킨 후 반복 종료
    {
        cout << tmp->data << '\t'; //해당 노드의 data 출력
        tmp = tmp->link; //다음 노드를 가리킴
    }
    cout << endl;
}

int main(void)
{
    Queue<int> queue(3);
    queue.Print();

    queue.Push(1);
    queue.Front();
    queue.Print();

    queue.Push(2);
    queue.Front();
    queue.Print();

    queue.Push(3);
    queue.Front();
    queue.Print();

    queue.Push(4);
    queue.Front();
    queue.Print();

    queue.Pop();
    queue.Front();
    queue.Print();

    queue.Pop();
    queue.Front();
    queue.Print();

    queue.Push(5);
    queue.Front();
    queue.Print();

    queue.Pop();
    queue.Front();
    queue.Print();

    queue.Pop();
    queue.Front();
    queue.Print();

    queue.Pop();
    queue.Front();

    return 0;
}