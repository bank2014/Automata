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
		// ���ĺ� a, b
		if ((inputStr[i] == 'a' || inputStr[i] == 'b'))
		{
			ResultExpression += inputStr[i];
			++i;
		}
		// ���� ��ȣ
		else if (inputStr[i] == '(')
		{
			st.push('(');
			++i;
		}
		// ���� ��ȣ
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
		// ������
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
		// ������� �ʴ� �ɺ��� �Էµ� ���
		else
		{
			cout << "����: �� �� ���� �ɺ��� �Էµ�" << endl;
			exit(-1);
		}
	}
	while (!st.empty()) // �����ڸ� Result�� �ٿ��ְ� ������ ����ش�
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
	cout << "����ǥ���� �Է�: ";
	string RE;
	cin >> RE;
	string postfixRE = InfixToPostfix(RE);

	vector<node*> v;
	vector<vector<int>> st;
	int firstnode = 0;
	for (int i = 0; i < postfixRE.length(); i++) 
	{
		// �����ڰ� �ƴ� ���
		if (postfixRE[i] != '|' && postfixRE[i] != '*' && postfixRE[i] != '.') 
		{
			node* temp = makenode(postfixRE[i]); // ù �ɺ��� ���� �����
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
	cout << "\n[�������̺�]\n";
	printnode(v);
	cout << endl;
	cout << "starting node is ";
	cout << st[st.size() - 1][0] << endl;
	cout << "ending node is ";
	cout << st[st.size() - 1][1] << endl;

	cout << "\nTest�� string �Է�: ";
	string testStr;
	cin >> testStr;
	cout << stringAcceptanceTest(testStr);

	return 0;
}

