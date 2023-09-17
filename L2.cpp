#define NAN -2e9;
#define type char
struct Node {
	Node* next;
	Node* prev;
	type val;
};

struct L2 {
	Node* head = NULL;
	Node* tail = NULL;
};

Node* make_node(type key) {
	Node* res = new Node;
	res->next = NULL; // (*res).next = NULL;
	res->val = key; // (*res).val = key; 
	res->prev = NULL;
	return res;
}
type front(const L2& list) {
	return list.head ? list.head->val : NULL;
}
type back(const L2& list) {
	return list.tail ? list.tail->val : NULL;
}
int size(const L2& list) {
	if (list.head == NULL) return 0;
	Node* run = list.head;
	int size = 1;
	while (run->next != NULL) {
		run = run->next;
		size++;
	}
	return size;
}
void clear(L2& list) {
	if (list.head == NULL) return;
	Node* run = list.head;
	Node* tmp;
	while (run->next != NULL) {
		tmp = run->next;
		delete run;
		run = tmp;
	}
	delete run;
	list.head = NULL;
	list.tail = NULL;
	return;
}

void push_front(L2& list, type key) {
	Node* p = make_node(key);
	if (list.head && list.head == list.tail) {
		p->next = list.head;
		list.head = p;
		list.tail->prev = p;
	}
	else if (list.head) {
		p->next = list.head;
		list.head->prev = p;
		list.head = p;
	}
	else {
		list.head = p;
		list.tail = p;
	}
}
void pop_front(L2& list) {
	if (list.head == NULL) return;
	else if (list.head == list.tail) {
		list.head = NULL;
		list.tail = NULL;
	}
	else {
		Node* p = list.head;
		list.head = list.head->next;
		delete p;
		list.head->prev = NULL;
	}
}
void push_back(L2& list, type key) {
	Node* p = make_node(key);
	if (!list.head) {
		list.head = p;
		list.tail = p;
	}
	else if (list.head == list.tail && list.head) {
		list.tail = p;
		list.tail->prev = list.head;
		list.head->next = list.tail;
	}
	else {
		list.tail->next = p;
		p->prev = list.tail;
		list.tail = p;
	}
}
void pop_back(L2& list) {
	if (list.head == NULL) return;
	else if (list.tail == list.head) {
		list.head = NULL;
		list.tail = NULL;
	}
	else {
		Node* p = list.tail;
		list.tail = list.tail->prev;
		list.tail->next = NULL;
		delete p;
	}
}
void insert(Node* p, type key) {
	Node* p1 = make_node(key);
	p1->next = p->next;
	p1->prev = p;
	p->next->prev = p1;
	p->next = p1;
}
void print(const L2& list) {
	Node* run = list.head;
	while (run) {
		cout << run->val << " ";
		run = run->next;
	}
}