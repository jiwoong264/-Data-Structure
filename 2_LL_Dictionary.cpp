#include<iostream>
using namespace std;

class Dictionary {
    private:
    class Node {
        public:
        string data; //단어를 저장할 변수
        Node* link; //다음 노드의 주소를 저장할 포인터
        Node(string word) { data = word; link = NULL;}; //word를 data로 가지는 Node를 생성하는 생성자
    };
    Node* first; //첫 번째 노드를 가리킬 포인터

public:
    Dictionary(string word); //생성자
    void Find(string word); //word가 몇 번째 위치에 있는 지 출력, 없으면 없다고 출력
    void Insert(string word); //단어 적절한 위치에 삽입(알파벳 순)
    void Delete(string word); //word를 리스트에서 삭제, 없는 경우도 예외처리 해야 함
    void Display();
};

Dictionary::Dictionary(string word) {
    first = new Node(word); //매개변수로 받은 word를 data로 가지는 Node를 생성, first가 가리키게 함
}

void Dictionary::Find(string word) { //몇 번째? 없으면 없다
    if (!first) //LL이 빈 경우
    {
        cout << "Empty Linkes List" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = first; //LL의 처음부터 끝까지 각 노드를 탐색할 포인터
    int count = 1; //찾는 word가 몇 번째 노드인지 저장할 변수

    while (1) //tmp가 마지막 노드까지 가리킨 후 반복 종료
    {
        if (!tmp) //LL의 맨 끝에 도달한 경우
        {
            cout << '\"' << word << "\" isn't exist in this Dictionary" << endl; //경고문 출력
            return; //함수 종료
        }
        else if (tmp->data == word) //tmp가 찾는 word를 가진 노드일 경우
        {
            cout << "The sequence of \"" << word << "\" : " << count << endl; //몇 번째 노드인지 출력
            return; //함수 종료
        }

        tmp = tmp->link; //다음 노드를 가리킴
        count++;
    }
}

void Dictionary::Insert(string word) {
    Node* node = new Node(word); //word를 data로 갖는 삽입할 노드 생성 

    if (!first) //LL이 비어있는 경우
    {
        first = node; //first가 생성한 노드를 가리킴
        return; //함수 종료
    }
    else if (first->data > word) //생성된 노드가 삽입될 자리가 맨 앞인 경우
    {
          node->link = first; //생성된 노드의 link가 기존의 first 노드를 가리킴
          first = node; //first가 생성된 노드를 가리킴
          return; //함수 종료
    }

    //LL의 중간이나 맨 끝에 단어가 삽입되는 경우
    Node* tmp = first; //삽입될 적절한 위치의 다음 노드를 찾을 Node 포인터
    Node* prev = NULL; //삽입될 적절한 위치의 직전 노드를 찾을 Node 포인터

    while (1)
    {
        prev = tmp; //다음 노드를 가리킴
        tmp = tmp->link; //다음 노드를 가리킴

        if (!tmp) //LL의 맨 끝에 도달한 경우
            break; //반복 종료
        else if (prev->data <= word && tmp->data >= word) //prev와 tmp 사이가 삽입될 적절한 위치인 경우
            break; //반복 종료
    }

    node->link = tmp; //생성된 노드가 tmp를 가리킴 (삽입될 위치가 맨 끝인 경우 NULL을 가리킴)
    prev->link = node; //prev가 생성된 노드를 가리킴
}

void Dictionary::Delete(string word) {
    if (!first) //LL이 빈 경우
    {
        cout << "Empty Linkes List" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = first; //삭제할 word를 data로 갖는 노드를 찾을 포인터
    Node* prev = NULL; //tmp 이전의 노드를 찾을 포인터
    while (1)
    {
        if (!tmp) //LL의 맨 끝에 도달한 경우
            break; //반복 종료
        else if (tmp->data == word) //tmp가 삭제할 word를 가진 노드를 가리킬 경우
            break; //반복 종료
            
        prev = tmp; //다음 노드를 가리킴
        tmp = tmp->link; //다음 노드를 가리킴
    }

    if (!tmp) //삭제할 word를 가진 노드가 없는 경우
    {
         cout << "삭제하려는 Data가 없습니다" << endl; //경고문 출력
    }
    else if (tmp == first) //첫 번째 노드가 삭제할 word를 가진 경우
    {
        prev = first->link; //prev가 두 번째 노드를 가리킴
        tmp->link = NULL; //반환하기 전 link 초기화
        delete tmp; //삭제한 노드의 메모리 반환
        first = prev; // first를 기존의 두번 째 노드를 가리킴
    }
    else //삭제할 word를 가진 노드가 마지막 노드이거나 두 노드 사이인 경우
    {
        prev->link = tmp->link; //prev가 다음 노드가 가리키던 노드를 가리킴(마지막 노드인 경우 NULL을 가리킴)
        tmp->link = NULL; //반환하기 전 link 초기화
        delete tmp; //삭제한 노드의 메모리 반환
    }
}

void Dictionary::Display() {
    if (!first) //LL이 빈 경우
    {
        cout << "Empty Linkes List" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = first; //LL의 처음부터 끝까지 각 노드를 탐색할 포인터

    while (tmp != NULL) //tmp가 마지막 노드까지 가리킨 후 반복 종료
    {
        cout << tmp->data << '\t'; //해당 노드의 data 출력
        tmp = tmp->link; //다음 노드를 가리킴
    }
    cout << endl;
}

int main() {
    Dictionary Dt("ABC");
    int input = 1;
    string word;

    while (input) {
        cout << "(1)Insert    (2)Delete    (3)Display    (4)Find    (0)END" << endl;
        cin >> input;

        if (input == 1) {
            cout << "Word to insert : ";
            cin >> word;
            Dt.Insert(word);
        }
        else if (input == 2) {
            cout << "Word to Delete : ";
            cin >> word;
            Dt.Delete(word);
        }
        else if (input == 3) {
            Dt.Display();
        }
        else if (input == 4) {
            cout << "Word to Find : ";
            cin >> word;
            Dt.Find(word);
        }
    } 
}
