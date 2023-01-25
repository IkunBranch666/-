#ifndef __LINK_STACK_H__
#define __LINK_STACK_H__

typedef int Data;
struct Node
{
	Data data;
	struct Node* next;
};

struct LinkStack
{
	int size;
	Node* front;
	Node* bottom;
};

void createLinkStack();
void Push(LinkStack* s, Data val);
Data top(LinkStack* s);
int size(LinkStack* s);
bool empty(LinkStack* s);



#endif // !__LINK_STACK_H__
