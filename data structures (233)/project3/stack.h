/* @Author
 * Student Name: Muhammet Uçan * Student ID: 150140707
 * Date: 23.12.2016
 */
using namespace std;

struct StackNode {
	string data;
	StackNode *next;
};

struct Stack {
	StackNode *head;
	
	void create();
	void push(string);
	string pop();
	string top();
	bool isEmpty();
};

void Stack::create() {
	head = NULL;
}

void Stack::push(string s) {
	StackNode *temp = new StackNode;
	temp->data = s;
	temp->next = NULL;
	if (!head) {
		head = temp;
		return;
	}
	temp->next=head;
	head=temp;
}

string Stack::pop() {
	StackNode *temp = head;
	string s = temp->data;
	head = head->next;
	delete temp;
	return s;
}
string Stack::top() {
	return head->data;
}

bool Stack::isEmpty() {
	return head==NULL;
}
