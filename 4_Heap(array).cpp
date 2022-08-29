#include<iostream>
using namespace std;

//우선순위 큐 크기는 최대 15개까지만
template <typename T>
class PriorityQueue
{
    T arr[16]; //원소들을 저장할 배열
    int amt; //현재 원소들의 개수를 저장할 변수
public:
    PriorityQueue() : amt(0) { arr[0] = 0; } //생성자
    void Insert(T data); //data를 적절한 위치에 삽입하는 함수
    T Pop(); //우선순위가 가장 높은 원소를 반환하고 삭제하는 함수
    void Print(); //우선순위가 가장 높은 원소부터 차례대로 모든 원소를 출력하는 함수
};

template<typename T>
void PriorityQueue<T>::Insert(T data)
{
    if (amt >= sizeof(arr) / sizeof(arr[0]) - 1) //우선순위 큐가 가득 찼다면
    {
        cout << "Over Flow" << endl; //경고문 출력
        return; //함수 종료
    }
    
    arr[++amt] = data; //amt를 증가시키고 우선순위가 가장 낮은 위치에 data 삽입

    if (amt == 1) //우선순위 큐가 비어있었다면
       return; //함수 종료
    
    int id = amt; //적절한 위치를 찾기 위해 인덱스를 기억할 변수
    int tmp; //데이터 교환에 필요한 변수

    while (arr[id/2] > arr[id]) //부모 노드보다 삽입할 노드의 우선순위가 높은 동안 반복
    {
        //삽입할 노드의 부모 노드와 위치 변경
        tmp = arr[id/2]; 
        arr[id/2] = arr[id];
        arr[id] = tmp;
        id /= 2; //id값도 변경된 위치에 맞게 변경
    }
}

template<typename T>
T PriorityQueue<T>::Pop()
{
    if (amt == 0) //우선순위 큐가 비어있다면
    {
        cout << "Under Flow" << endl; //경고문 출력
        return 0; //함수 종료
    }

    int Will_Return = arr[1]; //반환할 값을 기억할 변수

    arr[1] = arr[amt--]; //우선순위가 가장 낮은 값을 루트로 이동
    int id = 1; //가장 낮은 곳에 있던 노드의 적절한 위치를 찾기 위해 인덱스를 기억할 변수
    int tmp; //데이터 교환에 필요한 변수

/////////////
    while (id * 2 <= amt) //가장 낮은 곳에 있던 노드가 왼쪽 자식노드를 갖는 경우 반복
    {
        if (amt == id * 2) //가장 낮은 곳에 있던 노드가 왼쪽 자식노드만 갖는 경우
        {
            if (arr[id] > arr[id*2]) //가장 낮은 곳에 있던 노드가 자신보다 우선순위가 높은 자식노드를 가질 경우
            {
                //가장 낮은 곳에 있던 노드의 왼쪽 자식노드와 위치 변경
                tmp = arr[id];
                arr[id] = arr[id*2];
                arr[id*2] = tmp;
                id *= 2; //id 값도 변경된 위치에 맞게 변경
            }
            break;
        }
        
        //가장 낮은 곳에 있던 노드가 왼쪽, 오른쪽 자식 노드를 다 갖는 경우
        if (arr[id] > arr[id*2] || arr[id] > arr[id*2+1]) //가장 낮은 곳에 있던 노드가 자신보다 우선순위가 높은 자식노드를 가질 경우
        {
            if (arr[id*2] < arr[id*2+1]) //왼쪽 자식노드가 오른쪽 자식노드보다 우선순위가 높은 경우
            {
                //가장 낮은 곳에 있던 노드의 왼쪽 자식노드와 위치 변경
                tmp = arr[id];
                arr[id] = arr[id*2];
                arr[id*2] = tmp;
                id *= 2; //id 값도 변경된 위치에 맞게 변경
            }
            else if (arr[id*2] > arr[id*2+1]) //오른쪽 자식노드가 왼쪽 자식노드보다 우선순위가 높은 경우
            {
                //가장 낮은 곳에 있던 노드의 오른쪽 자식노드와 위치 변경
                tmp = arr[id];
                arr[id] = arr[id*2+1];
                arr[id*2+1] = tmp;
                id = id * 2 + 1; //id 값도 변경된 위치에 맞게 변경
            }
        }
        else //가장 낮은 곳에 있던 노드의 우선순위가 가장 높은 경우
            break; //반복 종료
        
    }

    cout << "Pop " << Will_Return << endl;
    return Will_Return;
}

template<typename T>
void PriorityQueue<T>::Print()
{
    if (amt == 0) //우선순위 큐가 비어있다면
    {
        cout << "Empty Priority Queue" << endl; //경고문 출력
        return; //함수 종료
    }

    for (int i = 1; i <= amt; i++)
            cout << arr[i] << '\t';
    cout << endl;
}


int main () {
    
    PriorityQueue<int> PQ;
    int input = 1;
    int data;

    while (input) {
        cout << "(1)Insert    (2)Pop    (3)Print    (0)End" << endl;
        cin >> input;

        if (input == 1) {
            cout << "Word to insert : ";
            cin >> data;
            PQ.Insert(data);
        }
        else if (input == 2) {
            PQ.Pop();
        }
        else if (input == 3) {
            cout << "<Print>" << endl;
            PQ.Print();
        }
        else
            break;
    }
    
    return 0;
}