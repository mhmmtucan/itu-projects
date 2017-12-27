//
//  queue.h
//  homework2
//	150140707
//	Muhammet UÇAN
//
#ifndef queue_h
#define queue_h
typedef struct applicant applicant;
typedef struct Node Node;
typedef struct Queue Queue;

struct applicant {
    int applicantID;
    int interviewTime;
    int trainingTime;
    int validForTrail;
    int validForJob;
    int isRegistered;
    int isInterviewed;
    int isTrained;
    int memoryID;
    int interviewID;
    int trainingID;
};

struct Node {
    struct applicant data;
    struct Node* next;
};

struct Queue {
    Node *front;
    Node *last;
    int size;
};

Node* createNode(applicant*);
Queue* createQueue();
void enqueue(Queue*,Node*);
Node* dequeue();
int isEmpty(Queue*);
void deleteNode(Node*);
void deleteQueue(Queue*);
#endif /* queue_h */
