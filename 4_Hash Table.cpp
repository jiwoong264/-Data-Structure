#include<iostream>
using namespace std;

class HT {
private:
    class Node {
    public:
        char data[3]; 
        Node *next;
        Node(char data[3]);
    };
    Node* bucket[17]; //key값에 따라 분류된 연결리스트의 첫 노드들을 담을 배열

public:
    HT(); //생성자
    void Insert(char *str); //str을 갖는 노드를 생성해 해당하는 bucket의 맨 뒤에 삽입하는 함수
    void Delete(char *str); //str을 갖는 노드를 찾아 삭제하는 함수
    void Find(char *str); //str이 몇 번째 bucket의 몇 번째 원소인지 출력하는 함수
    void Print(int key); //해당 key의 bucket에 있는 모든 원소를 출력하는 함수
private:
    inline int GetKey(char str[3]) //str의 key값을 계산해 반환하는 함수
    {
        return ((str[0] - 'a') * 26 * 26 + (str[1] - 'a') * 26 + str[2] - 'a') % 17;
        //세 자리의 소문자 문자열을 26진수 수로 환산
    }
};

HT::HT()
{
    for (int i = 0; i < 17; i++)
        bucket[i] = NULL; //연결리스트의 fisrt를 모두 NULL로 초기화
}

HT::Node::Node(char *str)
{
    for (int i = 0; i < 3; i++)
        data[i] = str[i];
    next = NULL;
}

void HT::Insert(char *str)
{
    Node* node = new Node(str); //삽입할 str을 data로 갖는 삽입할 새 노드 생성
    int key = GetKey(str); //삽입할 str의 key값 구하기

    if (bucket[key] == NULL) //해당 key의 bucket이 비어있다면
    {
        bucket[key] = node; //node를 해당 bucket의 첫 원소로 저장
        return; //함수 종료
    }
    
    Node* tmp = bucket[key]; //해당 bucket의 마지막 노드를 찾을 변수
    while(tmp->next != NULL) //tmp가 bucket의 마지막 노드에 도달하면 반복 종료
        tmp = tmp->next; //tmp가 다음 노드를 가리킴

    tmp->next = node; //삽입할 node를 해당 bucket의 마지막 노드로 연결
}

void HT::Delete(char *str){
    int key = GetKey(str); //삭제할 str의 key값 구하기

    if (bucket[key] == NULL) //해당 key의 bucket이 비어있다면
    {
        cout << str << " doesn't exist in this Hash Table" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = bucket[key]; //삭제할 str을 갖는 노드를 찾을 변수
    Node* prev = NULL; //tmp의 이전 노드를 기억할 변수

    while (1)
    {
        if (tmp == NULL) //tmp가 해당 bucket의 마지막 노드를 지나쳤다면
            break; //반복 종료
        else if (string(tmp->data) == str) //tmp가 삭제할 str을 가진 노드를 찾은 경우
            break; //반복 종료

        //위 조건문을 통과했다면
        prev = tmp; //prev가 다음 노드를 가리킴
        tmp = tmp->next; //tmp가 다음 노드를 가리킴
    }

    if (tmp == NULL) //삭제할 str을 가진 노드가 없는 경우
    {
        cout << str << " doesn't exist in it's bucket" << endl; //경고문 출력
    }
    else if (tmp == bucket[key]) //해당 bucket의 첫 노드가 삭제할 str을 갖는 경우
    {
        bucket[key] = bucket[key]->next; //해당 bucket의 첫 노드를 다음 노드로 변경
        tmp->next = NULL; //반환 전 next 초기화
        delete tmp; //삭제한 노드의 메모리 반환
    }
    else //삭제할 str을 가진 노드가 마지막 노드이거나 두 노드 사이인 경우
    {
        prev->next = tmp->next; //prev가 tmp의 다음 노드를 가리킴 (tmp가 마지막 노드인 경우 NULL)
        tmp->next = NULL; //반환 전 next 초기화
        delete tmp; //삭제한 노드의 메모리 반환
    }

}

void HT::Find(char *str){
    int key = GetKey(str); //찾을 str의 key값 구하기
    int count = 1; //찾을 str이 해당 bucket의 몇 번째 노드인지 기억할 변수

    if (bucket[key] == NULL) //해당 key의 bucket이 비어있다면
    {
        cout << str << " doesn't exist in this Hash Table" << endl; //경고문 출력
        return; //함수 종료
    }
    
    Node* tmp = bucket[key]; //해당 bucket의 마지막 노드를 찾을 변수
    while (1)
    {
        if (tmp == NULL) //tmp가 해당 bucket의 마지막 노드를 지나쳤다면
        {
            cout << str << " doesn't exist in it's bucket" << endl; //경고문 출력
            return; //함수 종료
        }
        else if (string(tmp->data) == str) //tmp가 삭제할 str을 가진 노드를 찾은 경우
            break; //반복 종료

        //위 조건문을 통과했다면
        tmp = tmp->next; //tmp가 다음 노드를 가리킴
        count++; //몇 번째 노드인지 기억
    }

    //해당 노드가 몇 번 bucket의 몇 번째 노드인지 출력
    cout << str << " is in bucket[" << key << "] with " << count << "th" << endl;
}

void HT::Print(int key){
    if (bucket[key] == NULL) //해당 key의 bucket이 비어있다면
    {
        cout << "bucket[" << key << "] is empty" << endl; //경고문 출력
        return; //함수 종료
    }
    
    Node* tmp = bucket[key]; //해당 bucket의 마지막 노드를 찾을 변수

    cout << "bucket[" << key << ']' << endl;
    while (tmp != NULL) //tmp가 해당 bucket의 마지막 노드를 지나쳤다면 반복 종료
    {
        cout << tmp->data << '\t'; //tmp가 가리키는 노드의 data 출력
        tmp = tmp->next; //tmp가 다음 노드를 가리킴
    }
    cout << endl;
}

int main () {
    
    HT ht;
    int input = 1;
    char str[3];
    int key;

    while (input != -1) {
        cout << "(1)Insert    (2)Delete    (3)Find    (4)Print    (-1)End" << endl;
        cin >> input;

        if (input == 1) {
            cout << "Word to insert : ";
            cin >> str;
            ht.Insert(str);
        }
        else if (input == 2) {
            cout << "Word to Delete : ";
            cin >> str;
            ht.Delete(str);
        }
        else if (input == 3) {
            cout << "Word to Find : ";
            cin >> str;
            ht.Find(str);
        }
        else if (input == 4) {
            cout << "Key of bucket to Print (0~16) : ";
            cin >> key;
            ht.Print(key);
        }
        else
            break;
    }
    
    return 0;
}