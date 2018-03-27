#include <iostream>
#include <string.h>
#include <deque>
#include <stack>
using namespace std;

class node
{
public:
	node()
	{
		cur_X = 0;
		cur_Y = 0;
		type = 0;
		depth = 0;
		parent = NULL;
		
		for(int i = 0; i < 5; i++)
		{
			child[i] = NULL;
		}
	};
	
	int cur_X;
	int cur_Y;
	int type;
	int depth;
	node* parent;
	node* child[5];
};

void BFS(void);
void IDS(void);
node* DLS(node*, int);
node* expand(node*, node*, int);
void printResult(node*, node*);

int X, Y;
int sequence[100] = {0};

int main()
{
	while(1)
	{
		int i = 0;
		char order[3];
		
		// input
		cin >> order >> X >> Y;
		
		while(1)
		{
			char tmp = getchar();
			
			if(tmp == '\n')
			{
				break;
			}
			else if(tmp != ' ')
			{
				sequence[i] = tmp - 48;
				i++;
			}
		}
		
		if(!strcmp(order, "BFS")) BFS();
		else if(!strcmp(order, "IDS")) IDS();
		
		X = Y = 0;
		for(int i = 0; i < 100; i++)
		{
			sequence[i] = 0;
		}
	}
} 

void BFS(void)
{
	node* root = new node;
	deque<node*> frontier;
	deque<node*>::iterator it;
	int flag = 0;
	
	frontier.push_back(root);
	
	while(1)
	{
		it = frontier.begin();
		
		for(int i = 1; i <= 5; i++)
		{
			node* tmp = new node;
			node* target = expand(*it, tmp, i);
			
			if(target != NULL)
			{
				flag = 1;
				printResult(root, target);
				break;
			}
			
			frontier.push_back(tmp);
		}
		
		frontier.pop_front();
		
		if(flag == 1) break;
	}
}

void IDS(void)
{
	node* root = new node;
	
	for(int i = 0; ; i++)
	{
		node* target = DLS(root, i);
		
		if(target != NULL)
		{
			printResult(root, target);
			break;
		}
	}
}

node* DLS(node* root, int depth)
{
	stack<node*> s;
	s.push(root);
	int flag = 0;
	node* target = NULL;
	
	while(1)
	{
		node* tmp_parent = s.top();
		s.pop();
		
		if(tmp_parent->depth == depth)
		{
			for(int i = 1; i <= 5; i++)
			{
				node* tmp_child = new node;
				target = expand(tmp_parent, tmp_child, i);
				
				if(target != NULL)
				{
					flag = 1;
					break;
				}
			}
		}
		else
		{
			for(int i = 4; i >= 0; i--)
			{
				s.push(tmp_parent->child[i]);
			}
		}
		
		if(flag == 1) // find target
		{
			return target;
		}
		
		if(s.empty()) // do not find target, this depth is not enough
		{
			return NULL;
		}
		
	}
	
}

node* expand(node* parent, node* child, int type)
{
	node* target;
	child->type = type;
	child->depth = parent->depth + 1;
	child->parent = parent;
	parent->child[type-1] = child;
	
	if(type == 1) // x+
	{
		child->cur_X = parent->cur_X + sequence[child->depth-1];
		child->cur_Y = parent->cur_Y;
	}
	else if(type == 2) // x-
	{
		child->cur_X = parent->cur_X - sequence[child->depth-1];
		child->cur_Y = parent->cur_Y;
	}
	else if(type == 3) // y+
	{
		child->cur_X = parent->cur_X;
		child->cur_Y = parent->cur_Y + sequence[child->depth-1];
	}
	else if(type == 4) // y-
	{
		child->cur_X = parent->cur_X;
		child->cur_Y = parent->cur_Y - sequence[child->depth-1];
	}
	else //S
	{
		child->cur_X = parent->cur_X;
		child->cur_Y = parent->cur_Y;
	}
	
	if(child->cur_X == X && child->cur_Y == Y)
	{
		target = child;
		return target;
	} 
	
	return NULL;
}

void printResult(node* root, node* target)
{
	deque<int> route;
	deque<int>::iterator itr;
	int depth = 0;
	int cur_X = 0;
	int cur_Y = 0;
	
	while(1)
	{
		route.push_front(target->type);
		
		if(target->parent != root)	
			target = target->parent;
		else 
			break;
	}
	
	cout << "(initial)     (0, 0)\n";
	for(itr = route.begin(); itr != route.end(); itr++)
	{
		switch(*itr)
		{
			case 1:
				cur_X += sequence[depth];
				cout << "(x+) " << sequence[depth] << "        (" << cur_X << ", " << cur_Y << ")\n";
				break;
			case 2:
				cur_X -= sequence[depth];
				cout << "(x-) " << sequence[depth] << "        (" << cur_X << ", " << cur_Y << ")\n";
				break;
			case 3:
				cur_Y += sequence[depth];
				cout << "(y+) " << sequence[depth] << "        (" << cur_X << ", " << cur_Y << ")\n";
				break;
			case 4:
				cur_Y -= sequence[depth];
				cout << "(y-) " << sequence[depth] << "        (" << cur_X << ", " << cur_Y << ")\n";
				break;
			case 5:
				cout << "(S)  " << sequence[depth] << "        (" << cur_X << ", " << cur_Y << ")\n";
				break;
		}
		
		depth++;
	}
}
