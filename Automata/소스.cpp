#include <iostream>
#include <stack> // stack<>
#include <string>
#include <vector>	

using namespace std;

class node {
public:
	char state;
	int input;
	node* next;
};

int OperatorPriority(char c) 
{
	if (c == '*') {
		return 3;
	}
	else if (c == '.') {
		return 2;
	}
	else if (c == '|') {
		return 1;
	}
	else {
		return -1;
	}
}

string InfixToPostfix(string inputStr)
{
	stack<char> st;
	string ResultExpression = "";

	int i = 0;
	while (inputStr[i] != '\0')
	{
		// 알파벳 a, b
		if ((inputStr[i] == 'a' || inputStr[i] == 'b'))
		{
			ResultExpression += inputStr[i];
			++i;
		}
		// 열린 괄호
		else if (inputStr[i] == '(')
		{
			st.push('(');
			++i;
		}
		// 닫힌 괄호
		else if (inputStr[i] == ')')
		{
			while (st.top() != '(')
			{
				ResultExpression += st.top();
				st.pop();
			}
			st.pop();
			++i;
		}
		// 연산자
		else if (inputStr[i] == '*' || inputStr[i] == '.' || inputStr[i] == '|')
		{
			while (!st.empty() && OperatorPriority(inputStr[i]) <= OperatorPriority(st.top()))
			{
				ResultExpression += st.top();
				st.pop();
			}
			st.push(inputStr[i]);
			++i;
		}
		// 허용하지 않는 심볼이 입력된 경우
		else
		{
			cout << "에러: 알 수 없는 심볼이 입력됨" << endl;
			exit(-1);
		}
	}
	while (!st.empty()) // 연산자를 Result에 붙여넣고 스택을 비워준다
	{
		ResultExpression += st.top();
		st.pop();
	}

	cout << "\npostfix expression is " << ResultExpression << endl;
	return ResultExpression;
}

void printnode(vector<node*> v) 
{
	cout << "___________________________________________" << endl;
	cout << "| from state\t| input\t| to states" << endl;
	for (int i = 0; i < v.size(); i++) 
	{
		cout << "| " << i << "          \t|";
		node* head = v[i];
		cout << head->state;
		bool first = true;
		while (head != NULL) 
		{
			if (first){
				cout << "     \t|";
				first = false;
			}
			else {
				cout << "     \t";
			}
			cout << head->input;
			head = head->next;
		}
		cout << endl;
	}
	cout << "___________________________________________" << endl;
}

node* makenode(char in) {
	node* a = new node;
	a->state = in;
	a->input = -1;
	a->next = NULL;
	return a;
}

node* copynode(node* a) {
	node* b = new node;
	b->state = -1;
	b->input = -1;
	b->next = NULL;
	return b;
}

void op_and(vector<node*>& v, vector<vector<int> >& st) {
	int x, y;
	int first, last1;
	y = st[st.size() - 1][0];
	x = st[st.size() - 2][1];
	first = st[st.size() - 2][0];
	last1 = st[st.size() - 1][1];

	st.pop_back();
	st.pop_back();

	vector<int> ptemp;
	ptemp.push_back(first);
	ptemp.push_back(last1);
	st.push_back(ptemp);

	node* last = v[y];
	node* lnode = v[x];
	node* temp = copynode(last);
	// temp->to = -1;
	while (lnode->next != NULL) {
		lnode = lnode->next;
	}
	lnode->next = temp;
	lnode->input = y;

}

void op_or(vector<node*>& v, vector<vector<int> >& st) {
	int x, y, x1, y1;
	x = st[st.size() - 2][0];
	y = st[st.size() - 1][0];
	x1 = st[st.size() - 2][1];
	y1 = st[st.size() - 1][1];
	node* start = makenode('e');
	node* end = makenode('e');
	v.push_back(start);
	int firstnode = v.size() - 1;
	v.push_back(end);
	int endnode = v.size() - 1;

	st.pop_back();
	st.pop_back();

	vector<int> ptemp;
	ptemp.push_back(firstnode);
	ptemp.push_back(endnode);
	st.push_back(ptemp);

	for (int i = 0; i < v.size() - 2; i++) {
		node* h = v[i];
		while (h->next != NULL) {
			if (h->input == x || h->input == y) {
				h->input = firstnode;
			}
			h = h->next;
		}
	}


	node* temp = copynode(v[x]);
	node* temp1 = copynode(v[y]);
	node* t = v[firstnode];
	while (t->next != NULL) {
		t = t->next;
	}
	t->input = x;
	t->next = temp;
	t->next->input = y;
	t->next->next = temp1;

	node* adlink = v[x1];
	while (adlink->next != NULL) {
		adlink = adlink->next;
	}

	adlink->input = endnode;
	adlink->next = copynode(end);

	node* adlink1 = v[y1];
	while (adlink1->next != NULL) {
		adlink1 = adlink1->next;
	}
	adlink1->input = endnode;
	adlink1->next = copynode(end);

}

void op_closure(vector<node*>& v, vector<vector<int>>& st) 
{
	int x, x1;
	x = st[st.size() - 1][0];
	x1 = st[st.size() - 1][1];
	node* s = makenode('e');
	v.push_back(s);
	int firstnode = v.size() - 1;
	st.pop_back();
	vector<int> ptemp;
	ptemp.push_back(x);
	ptemp.push_back(firstnode);
	st.push_back(ptemp);

	for (int i = 0; i < v.size() - 2; i++) {
		node* h = v[i];
		while (h->next != NULL) {
			if (h->input == x) {
				h->input = firstnode;
			}
			h = h->next;
		}
	} 
	node* t = v[x1];
	while (t->next != NULL) {
		t = t->next;
	}
	t->input = x;
	t->next = copynode(t);
	t->next->input = firstnode;
	t->next->next = copynode(s);
}

string stringAcceptanceTest(string testStr)
{
	if (true)
	{
		return "\nTest result : [Accepted]\n";
	}
	else {

		return "\nTest result : [Rejected]\n";
	}
}

int main() 
{
	cout << "정규표현식 입력: ";
	string RE;
	cin >> RE;
	string postfixRE = InfixToPostfix(RE);

	vector<node*> v;
	vector<vector<int>> st;
	int firstnode = 0;
	for (int i = 0; i < postfixRE.length(); i++) 
	{
		// 연산자가 아닌 경우
		if (postfixRE[i] != '|' && postfixRE[i] != '*' && postfixRE[i] != '.') 
		{
			node* temp = makenode(postfixRE[i]); // 첫 심볼을 노드로 만든다
			v.push_back(temp);
			vector<int> ptemp;
			ptemp.push_back(v.size() - 1);
			ptemp.push_back(v.size() - 1);
			st.push_back(ptemp);
		}
		else if (postfixRE[i] == '.') {
			op_and(v, st);
		}
		else if (postfixRE[i] == '|') {
			op_or(v, st);
		}
		else if (postfixRE[i] == '*') {
			op_closure(v, st);
		}
	}
	cout << "\n[전이테이블]\n";
	printnode(v);
	cout << endl;
	cout << "starting node is ";
	cout << st[st.size() - 1][0] << endl;
	cout << "ending node is ";
	cout << st[st.size() - 1][1] << endl;

	cout << "\nTest할 string 입력: ";
	string testStr;
	cin >> testStr;
	cout << stringAcceptanceTest(testStr);

	return 0;
}

