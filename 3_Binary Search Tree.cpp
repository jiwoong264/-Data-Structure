#include<iostream>
using namespace std;

template<class T>
class BST {
private:
    class Node {
    public:
        T data; //값을 저장할 변수
        Node* left; //왼쪽 자식노드를 가리킬 포인터
        Node* right; //오른쪽 자식노드를 가리킬 포인터
        Node(T n, Node* L = NULL, Node* R = NULL) : data(n), left(L), right(R) {}; //생성자
        int Get_Child(); //자식노드의 수를 반환하는 함수
    };
    Node* root; //트리의 맨 위에 있는 노드

    void Inorder(Node* ptr); //해당 노드를 중위순회
    void Preorder(Node* ptr); //해당 노드를 전위순회
    void Postorder(Node* ptr); //해당 노드를 후위순회

public:
    BST() : root(NULL) {}; //디폴트 생성자
    BST(T n); //n의 값을 갖는 root를 생성하는 생성자
    void Insert(T n); //n의 값을 갖는 노드를 적절한 위치에 삽입하는 함수
    void Delete(T n); //n의 값을 갖는 노드를 삭제하는 함수
    void Find(T n); //n의 값을 갖는 노드의 레벨을 출력하는 함수
    void Visit(Node* ptr); //순회에서 쓰일 해당 노드의 값을 출력하는 함수
    void Inorder(); //중위순회로 tree출력
    void Preorder(); //전위순회로 tree 출력
    void Postorder(); //후위순회로 tree 출력
    ~BST() { Delete(root); } //기본 소멸자
    void Delete(Node* ptr) //기본 소멸자에서 호출될 모든 노드를 삭제하기 위한 재귀함수
    {
        if(ptr != NULL)
        {
            Delete(ptr->left);
            Delete(ptr->right);
            delete ptr;
        }
    }
};

template<class T>
int BST<T>::Node::Get_Child() {
    int n = 0; //자식노드의 개수를 저장할 변수
    if (left != NULL) //왼쪽 자식노드가 있는 경우
        n++;
    if (right != NULL) //오른쪽 자식노드가 있는 경우
        n++;
    return n; //자식노드의 개수 반환
}

template<class T>
BST<T>::BST(T n) {
    Node* node = new Node(n); //n의 값을 갖는 노드 동적할당
    root = node; //root가 할당받은 노드를 가리킴
}

template<class T>
void BST<T>::Inorder(Node* ptr) {
    if (ptr) { //ptr이 NULL일 경우 함수 종료
        Inorder(ptr->left); //왼쪽 자식 노드를 중위순회
        Visit(ptr); //자신의 왼쪽 노드를 순회한 후 자신의 값 출력
        Inorder(ptr->right); //오른쪽 자식 노드를 중위순회
    }
}

template<class T>
void BST<T>::Preorder(Node* ptr) {
    if (ptr) {
        Visit(ptr); //자신의 값 출력
        Preorder(ptr->left); //왼쪽 자식 노드를 전위순회
        Preorder(ptr->right); //오른쪽 자식 노드를 전위순회
    }
}

template<class T>
void BST<T>::Postorder(Node* ptr) {
    if (ptr) {
        Postorder(ptr->left); //왼쪽 자식 노드를 후위순회
        Postorder(ptr->right); //오른쪽 자식 노드를 후위순회
        Visit(ptr); //자신의 값 출력
    }
}

template<class T>
void BST<T>::Insert(T n) {
    Node* node = new Node(n); //n을 data로 갖는 삽입할 노드 생성
    
    if (root == NULL) { //tree가 비어있는 경우
        root = node; //root에 노드 삽입
        return; //함수 종료
    }
    //트리가 비어있지 않은 경우
    Node* tmp = root; //삽입할 적절한 위치를 가리킬 포인터
    Node* prev = NULL; //삽입할 적절한 위치의 부모노드를 가리킬 포인터

    while (tmp) //tmp가 NULL을 가리키면 (삽입할 적절한 위치) 반복 종료
    {
        if (n == tmp->data) //삽입할 n이 이미 tree에 있는 경우
        {
            cout << "해당 값을 가진 node가 존재합니다" << endl; //경고문 출력
            return; //함수 종료
        }
        else if (n < tmp->data) //삽입할 n이 tmp의 data보다 작을 경우
        {
            prev = tmp;
            tmp = tmp->left; //tmp가 왼쪽 자식노드로 이동
        }
        else if (n > tmp->data) //삽입할 n이 tmp의 data보다 클 경우
        {
            prev = tmp;
            tmp = tmp->right; //tmp가 오른쪽 자식노드로 이동
        }
    }

    if (n < prev->data) //삽입할 n이 prev의 data보다 작을 경우
        prev->left = node; //prev의 왼쪽에 삽입
    else if (n > prev->data) //삽입할 n이 prev의 data보다 클 경우
        prev->right = node; //prev의 오른쪽에 삽입
}

template<class T>
void BST<T>::Delete(T n) {
    if (!root) { //tree가 비어있는 경우
        cout << "Empty Tree" << endl; //경고문 출력
        return; //함수 종료
    }

    //트리가 비어있지 않은 경우
    Node* del = root; //삭제할 n을 data로 갖는 노드를 찾을 포인터
    Node* delParent = NULL; //del의 주소를 파악하기 위한 포인터

    while (del != NULL) //del이 NULL을 가리키면 반복 종료
    {
        if (n == del->data) //del이 삭제할 n을 data로 갖는 경우
        {
            break; //반복 종료
        }
        else if (n < del->data) //삭제할 n이 del의 data보다 작을 경우
        {
            delParent = del;
            del = del->left; //del이 왼쪽 자식노드로 이동
        }
        else if (n > del->data) //삭제할 n이 del의 data보다 클 경우
        {
            delParent = del;
            del = del->right; //del이 오른쪽 자식노드로 이동
        }
    }


    //예외처리 1
    if (del == NULL) //del == NULL인 경우 (삭제할 n이 tree에 없는 경우)
    {
        cout << n << " doesn't exist in this tree" << endl; //경고문 출력
        return; //함수 종료
    }
    //예외처리 2
    if (del == root) //삭제할 노드가 root인 경우
        delParent = new Node(0,root, root); //임의로 delParent 노드 생성

    //자식노드 개수에 따른 삭제
    if (del->Get_Child() == 0) //del이 leaf 노드인 경우
    {
        if (del == delParent->left) //del이 delParent의 왼쪽 자식노드인 경우
            delParent->left = NULL; //del을 가리키던 포인터 초기화
        else if (del == delParent->right) //del이 delParent의 오른쪽 자식노드인 경우
            delParent->right = NULL; //del을 가리키던 포인터 초기화

        delete del; //del 삭제
    }
    else if(del->Get_Child() == 1) //del이 자식노드를 1개 가질 경우
    {
        if (del == delParent->left) //del이 delParent의 왼쪽 자식노드인 경우
        {
            if (del->left != NULL) //del이 왼쪽 자식노드를 가질 경우
                delParent->left = del->left; //del의 자식노드를 delParent에게 연결
            else if (del->right != NULL) //del이 오른쪽 자식노드를 가질 경우
                delParent->left = del->right; //del의 자식노드를 delParent에게 연결
        }
        else if (del == delParent->right) //del이 delParent의 오른쪽 자식노드인 경우
        {
            if (del->left != NULL) //del이 왼쪽 자식노드를 가질 경우
                delParent->right = del->left; //del의 자식노드를 delParent에게 연결
            else if (del->right != NULL) //del이 오른쪽 자식노드를 가질 경우
                delParent->right = del->right; //del의 자식노드를 delParent에게 연결
        }
        
        delete del; //del 삭제
    }
    else if (del->Get_Child() == 2) //del이 자식노드를 2개 가질 경우
    {
        Node* tmp = del->left; //del의 왼쪽 자식노드 중 가장 큰 값을 가진 노드를 찾을 포인터
        Node* tmpParent = del; //tmp의 주소를 파악하기 위한 포인터

        while (tmp->right != NULL) //더 이상 오른쪽 자식노드가 없는 노드에 도달하면 반복 종료
        {
            tmpParent = tmp;
            tmp = tmp->right; //tmp가 오른쪽 자식노드로 이동
        }

        if (del == tmpParent) //예외처리 필요한 케이스
        {
            tmp->right = del->right; //tmp가 del의 오른쪽 자식노드를 가리킴
        }
        else //위의 경우 외 모든 경우
        {
            tmpParent->right = tmp->left; //tmp의 자식노드를 tmp 자리로 대치
            tmp->left = del->left; //tmp가 del의 자식노드를 가리킴
            tmp->right = del->right; //tmp가 del의 자식노드를 가리킴
        }
        
        
        if (del == delParent->left) //del이 delParent의 왼쪽 자식노드인 경우
            delParent->left = tmp; //delParent의 왼쪽 자식노드를 tmp로 대치
        else if (del == delParent->right) //del이 delParent의 오른쪽 자식노드인 경우
            delParent->right = tmp; //delParent의 오른쪽 자식노드를 tmp로 대치

        delete del; //del 삭제
    }

    if (delParent->right == root) //root 노드를 삭제한 경우
    {
        root = delParent->left; //root 변경
        delete delParent; //임의로 생성했던 delParent 삭제
    }

}

template<class T>
void BST<T>::Find(T n) {
    int level = 0;

    if (!root) { //tree가 비어있는 경우
        cout << "Empty Tree" << endl; //경고문 출력
        return; //함수 종료
    }
    //트리가 비어있지 않은 경우
    Node* tmp = root; //찾는 n을 data로 갖는 노드를 찾을 포인터

    while (tmp) //tmp가 NULL을 가리키면 (삽입할 적절한 위치) 반복 종료
    {
        if (n == tmp->data) //tmp가 찾는 n을 data로 갖는 경우
        {
            break; //반복 종료
        }
        else if (n < tmp->data) //찾는 n이 tmp의 data보다 작을 경우
        {
            tmp = tmp->left; //tmp가 왼쪽 자식노드로 이동
            level++;
        }
        else if (n > tmp->data) //찾는 n이 tmp의 data보다 클 경우
        {
            tmp = tmp->right; //tmp가 오른쪽 자식노드로 이동
            level++;
        }
    }
    if (!tmp) //tmp == NULL인 경우 (찾는 n이 tree에 없는 경우)
        cout << n << " doesn't exist this tree" << endl; //경고문 출력
    else if (tmp) //tmp가 찾는 n을 data로 갖는 경우
        cout << "Level of " << n << " is " << level << endl; //해당 노드의 level 출력
}

template<class T>
void BST<T>::Visit(Node* ptr) {
    cout << ptr->data << '\t'; //노드가 갖는 data 출력
}

template<class T>
void BST<T>::Inorder() {
    Inorder(root); //재귀로 root부터 중위순회
}

template<class T>
void BST<T>::Preorder() {
    Preorder(root); //재귀로 root부터 전위순회
}

template<class T>
void BST<T>::Postorder() {
    Postorder(root); //재귀로 root부터 후위순회
}

int main () {
    BST<int> tree;
    int input = 1;
    int n;

    while (input) {
        cout << "(1)Insert    (2)Delete    (3)Find    (4)Print    (0)End" << endl;
        cin >> input;

        if (input == 1) {
            cout << "Word to insert : ";
            cin >> n;
            tree.Insert(n);
        }
        else if (input == 2) {
            cout << "Word to Delete : ";
            cin >> n;
            tree.Delete(n);
        }
        else if (input == 3) {
            cout << "Word to Find : ";
            cin >> n;
            tree.Find(n);
        }
        else if (input == 4) {
            cout << "<1>Inoreder    <2>Preorder    <3>Postorder" << endl;
            cin >> input;

            if (input == 1)
                tree.Inorder();
            else if (input == 2)
                tree.Preorder();
            else if (input == 3)
                tree.Postorder();
            
            cout << endl;
        }
        else
            continue;
        
    }

    return 0;
}