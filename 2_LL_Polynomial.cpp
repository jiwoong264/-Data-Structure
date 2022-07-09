#include<iostream>
using namespace std;

class Polynomial
{
private:
    class Node
    {
    public:
        float coef; //계수
        int exp; //지수
        Node* link; //다음 노드를 가리킬 포인터
        Node(float c, int e = 0) { coef = c; exp = e; } //Node 생성자
    };
    Node* first;
public:
    Polynomial() { first = NULL; } //Polynomial 생성자
    void Get_Polynomial(); //다항식을 입력받을 함수
    void Insert(float c, int e); //계수c와 지수e를 갖는 항을 다항식에 추가
    Polynomial operator +(const Polynomial& b); //다항식 덧셈 결과 반환
    Polynomial operator -(const Polynomial& b); //다항식 뺄셈 결과 반환
    void Print(); //다항식을 내림차순으로 출력
};

void Polynomial::Get_Polynomial()
{
    float C; //계수를 입력받을 변수
    int E; //지수를 입력받을 변수
    
    cout << "다항식 생성 시작 (계수에 0을 입력하면 생성을 중단합니다)" << endl;

    while (1) //아래 조건문에 의해 중단되기 전까지 무한반복
    {
        cout << "추가할 항의 계수(실수)와 지수(정수)를 입력하세요 : ";
        cin >> C >> E; //계수와 지수 입력받음
        
        if (C == 0) //계수로 0을 입력받으면
            break; //함수 종료 (다항식 생성 중단)
        
        Insert(C,E); //계수C와 지수E를 갖는 항을 추가
    }
}

void Polynomial::Insert(float c, int e)
{
    Node* tmp = first; //각 노드를 돌며 계수가 중복된 항을 찾을 Node 포인터
    while (tmp) //tmp가 마지막 노드의 link인 NULL에 도달하면 반복 종료
    {
        if (e == tmp->exp) //생성할 노드의 지수와 같은 지수를 갖는 항이 존재할 경우
        {
            cout << "같은 지수를 갖는 항이 이미 존재합니다" << endl; //경고문 출력
            return; //함수 종료
        }
        tmp = tmp->link; //다음 노드를 가리킴
    }

    Node* node = new Node(c,e); //c와 e를 계수와 지수로 갖는 노드 생성

    if (!first) //다항식의 첫 번째 노드가 생성될 때
    {
        first = node; //first가 생성된 노드가 가리킴
        return; //함수 종료
    }

    //두 번째 이상 항이 생성될 때

    if (e > first->exp) //생성된 노드가 최고차항이라 삽입될 자리가 맨 앞인 경우
    {
          node->link = first; //생성된 노드의 link가 기존의 first 노드를 가리킴
          first = node; //first가 생성된 노드를 가리킴
          return; //함수 종료
    }

    //다항식의 중간이나 맨 끝에 항이 삽입되는 경우
    tmp = first; //삽입될 적절한 위치의 다음 노드를 찾을 Node 포인터
    Node* prev = NULL; //삽입될 적절한 위치의 직전 노드를 찾을 Node 포인터

    while (1) //아래 조건문에 의해 중단되기 전까지 무한반복
    {
        prev = tmp; //다음 노드를 가리킴
        tmp = tmp->link; //다음 노드를 가리킴

        if (!tmp) //LL의 맨 끝에 도달한 경우
            break; //반복 종료
        else if (prev->exp > e  && e > tmp->exp) //prev와 tmp 사이가 삽입될 적절한 위치인 경우
            break; //반복 종료
    }

    node->link = tmp; //생성된 노드가 tmp를 가리킴 (삽입될 위치가 맨 끝인 경우 NULL을 가리킴)
    prev->link = node; //prev가 생성된 노드를 가리킴
}

Polynomial Polynomial::operator +(const Polynomial& b)
{
    Polynomial result; //두 다항식의 합을 저장할 다항식
    Node* ai = this->first; //첫 번째 다항식의 노드를 가리킬 포인터
    Node* bi = b.first; //두 번째 다항식의 노드를 가리킬 포인터
    
    while (1) //아래 조건문에 의해 중단되기 전까지 무한반복
    {
        if (!ai) //ai가 NULL인 경우 (다항식 a에 더 이상 계산할 항이 없는 경우)
        {
            while(bi) //bi가 NULL에 도달하면 반복 종료 (다항식 b에도 더 이상 계산할 항이 없을 때)
            {
                result.Insert(bi->coef, bi->exp); //bi가 가리키는 항을 그래도 result에 추가
                bi = bi->link; //다음 항을 가리킴
            }
            break; //반복 종료
        }
        else if (!bi) //bi가 NULL인 경우 (다항식 b에 더 이상 계산할 항이 없는 경우)
        {
            while(ai) //ai가 NULL에 도달하면 반복 종료 (다항식 a에도 더 이상 계산할 항이 없을 때)
            {
                result.Insert(ai->coef, ai->exp); //ai가 가리키는 항을 그래도 result에 추가
                ai = ai->link; //다음 항을 가리킴
            }
            break; //반복 종료
        }


        if (ai->exp > bi->exp) //ai가 가리키는 항의 지수가 더 큰 경우
        {
            result.Insert(ai->coef, ai->exp); //ai가 가리키는 항을 그래도 result에 추가
            ai = ai->link; //다음 항을 가리킴
        }
        else if (ai->exp < bi->exp) //bi가 가리키는 항의 지수가 더 큰 경우
        {
            result.Insert(bi->coef, bi->exp); //bi가 가리키는 항을 그래도 result에 추가
            bi = bi->link; //다음 항을 가리킴
        }
        else //ai와 bi가 가리키는 두 항의 지수가 같은 경우
        {
            if (ai->coef + bi->coef) //두 항의 계수의 합이 0이 아닌 경우
                result.Insert(ai->coef + bi->coef, ai->exp); //두 항의 계수의 합, 두 항과 같은 지수를 같는 항을 result에 추가
            
            ai = ai->link; //다음 항을 가리킴
            bi = bi->link; //다음 항을 가리킴
            
        }
    }

    return result; //덧셈이 완료된 다항식을 return
}

Polynomial Polynomial::operator -(const Polynomial& b)
{
    Polynomial result; //두 다항식의 차를 저장할 다항식
    Node* ai = this->first; //첫 번째 다항식의 노드를 가리킬 포인터
    Node* bi = b.first; //두 번째 다항식의 노드를 가리킬 포인터
    
    while (1) //아래 조건문에 의해 중단되기 전까지 무한반복
    {
        if (!ai) //ai가 NULL인 경우 (다항식 a에 더 이상 계산할 항이 없는 경우)
        {
            while(bi) //bi가 NULL에 도달하면 반복 종료 (다항식 b에도 더 이상 계산할 항이 없을 때)
            {
                result.Insert(-(bi->coef), bi->exp); //bi가 가리키는 항의 계수의 부호를 바꾼 후 result에 추가
                bi = bi->link; //다음 항을 가리킴
            }
            break; //반복 종료
        }
        else if (!bi) //bi가 NULL인 경우 (다항식 b에 더 이상 계산할 항이 없는 경우)
        {
            while(ai) //ai가 NULL에 도달하면 반복 종료 (다항식 a에도 더 이상 계산할 항이 없을 때)
            {
                result.Insert(ai->coef, ai->exp); //ai가 가리키는 항을 그래도 result에 추가
                ai = ai->link; //다음 항을 가리킴
            }
            break; //반복 종료
        }


        if (ai->exp > bi->exp) //ai가 가리키는 항의 지수가 더 큰 경우
        {
            result.Insert(ai->coef, ai->exp); //ai가 가리키는 항을 그래도 result에 추가
            ai = ai->link; //다음 항을 가리킴
        }
        else if (ai->exp < bi->exp) //bi가 가리키는 항의 지수가 더 큰 경우
        {
            result.Insert(-(bi->coef), bi->exp); //bi가 가리키는 항의 계수의 부호를 바꾼 후 result에 추가
            bi = bi->link; //다음 항을 가리킴
        }
        else //ai와 bi가 가리키는 두 항의 지수가 같은 경우
        {
            if (ai->coef - bi->coef) //두 항의 계수의 차가 0이 아닌 경우
                result.Insert(ai->coef - bi->coef, ai->exp); //두 항의 계수의 차, 두 항과 같은 지수를 같는 항을 result에 추가
            
            ai = ai->link; //다음 항을 가리킴
            bi = bi->link; //다음 항을 가리킴
            
        }
    }

    return result; //뺄셈이 완료된 다항식을 return
}

void Polynomial::Print()
{
    if (!first) //LL이 빈 경우
    {
        cout << "Empty Linkes List" << endl; //경고문 출력
        return; //함수 종료
    }

    Node* tmp = first; //LL의 처음부터 끝까지 각 노드를 탐색할 포인터

    while (tmp != NULL) //tmp가 마지막 노드까지 가리킨 후 반복 종료
    {
        if (tmp->exp == 0) //지수가 0인 상수항의 경우
        {
            if (tmp->coef > 0) //계수가 양수일 경우
                cout << '+'; //'+' 출력
            cout << tmp->coef; //계수(상수)만 출력
            break; //마지막 항이 출력되었으므로 반복 종료
        }

        //상수항이 아닌 경우

        if (tmp->coef > 0) //계수가 양수인 경우
            cout << '+' << tmp->coef << "x^"; //'+'와 계수 출력
        else if (tmp->coef < 0) //계수가 음수인 경우
            cout << tmp->coef << "x^"; //계수만 출력
            
        cout << tmp->exp; //지수 출력
        tmp = tmp->link; //다음 노드를 가리킴
    }
    cout << endl;
}

int main()
{
    Polynomial A, B;

    cout << "[A] ";    
    A.Get_Polynomial();
    cout << "[B] ";
    B.Get_Polynomial();

    cout << "[A] = ";
    A.Print();
    cout << "[B] = ";
    B.Print();

    Polynomial C = A + B;
    Polynomial D = A - B;

    cout << "[A] + [B] = ";
    C.Print();
    cout << "[A] - [B] = ";
    D.Print();

    return 0;   
}