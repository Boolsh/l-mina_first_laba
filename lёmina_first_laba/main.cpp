#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

using Tinfo = char;
struct  NODE
{
	Tinfo info;
	NODE* next;
	NODE(Tinfo info, NODE* ptr = nullptr)
	{
		this->info = info;
		next = ptr;
	}
	~NODE()
	{
		next = nullptr;
	}
};
using ptrNode = NODE*;
struct StackL
{
private:
	ptrNode head;
	size_t count;
public:
	StackL()
	{
		head = nullptr;
	}
	bool empty()
	{
		return head == nullptr;
	}
	size_t size()
	{
		return count;
	}
	void push(Tinfo elem)
	{
		ptrNode newNode = new NODE(elem, head);
		head = newNode;
		count++;
	}
	void pop()
	{
		if (empty()) { std::cout << " Stack is empty \n"; }
		else
		{
			ptrNode tmp = head;
			head = head->next;
			delete tmp;
			count--;
		}
	}
	Tinfo top()
	{
		if (!empty())
			return head->info;
	}
	void view()
	{
		ptrNode tmp = head;
		while (tmp)
		{
			std::cout << tmp->info << ' ';
			tmp = tmp->next;
		}
	}
	void clear()
	{
		while (!empty())
		{
			pop();
		}
	}
	~StackL()
	{
		clear();
		delete head;
	}
};

// Функция для определения приоритета операторов
int getPriority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Функция для преобразования инфиксного выражения в постфиксное
string infixToPostfix(const string& expression) {
    StackL operators;
    string postfix;

    for (int i = 0; i < expression.length(); i++) {
        char token = expression[i];

        // Если символ - операнд, добавляем его в постфиксную строку
        if (isalnum(token)) {
            postfix += token;
        }

        else if (token == '(') {
            operators.push(token);
        }

        else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Удаляем '(' из стека
        }

        // Если нашли оператор
        else {
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(token)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(token);
        }
    }

    // Добавляем оставшиеся операторы из стека в постфиксную строку
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int main() {
    setlocale(LC_ALL, "RU");
    string expression;
    cout << "Введите математическое выражение: ";
    cin >> expression;

    string postfix = infixToPostfix(expression);
    cout << "Постфиксная форма: " << postfix << endl;

    return 0;
}
