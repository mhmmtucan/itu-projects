/* @Author
 * Student Name: Muhammet Uçan * Student ID: 150140707
 * Date: 23.12.2016
 */
using namespace std;

struct QueueNode {
	long data;
	QueueNode *next;
};

struct Queue {
	QueueNode *front,*back;
	
	void create();
	void enqueue(long);
	long dequeue();
    long first();
	bool isEmpty();
    void print();
};

void Queue::create() {
	front = NULL;
	back = NULL;
}

void Queue::enqueue(long l) {
	QueueNode *temp = new QueueNode;
	temp->data = l;
	temp->next = NULL;
	if (!front) {
		front = temp;
		back = temp;
		return;
	}
	back->next = temp;
	back = temp;
}

long Queue::dequeue() {
	QueueNode *temp = front;
	front = front->next;
	long l = temp->data;
	delete temp;
	return l;
}

long Queue::first() {
    return front->data;
}

bool Queue::isEmpty() {
	return front==NULL;
}

void Queue::print() {
    QueueNode *temp = front;
    while (!temp) {
        cout << temp->data << "->";
        temp = temp->next;
    }
}
