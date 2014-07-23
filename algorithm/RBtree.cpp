#include <stdio.h>
#include <stdlib.h>

struct RBnode
{
	int key, value;
	RBnode *l, *r;
	int color;
};

class RBtree
{
public:
	RBtree(){ root = NULL; }
	~RBtree(){}

	void Insert(int key, int value){}
	void Remove(int key){}
	int GetValue(int key){}

private:
	RBnode *root;

	void LRotation(RBnode *node){
		RBnode *tmp = node->l;
		node->l = tmp->r;
		tmp->r = node;
		node = tmp;
	}
	void RRotation(RBnode *node){}
	void RLRotation(RBnode *node){}
	void LRRotation(RBnode *node){}
};

int main(){

}