#include "PatriciaNode.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

PatriciaNode::PatriciaNode() {
	key = NULL;
	skip = 0;
	value = 0;
	left = NULL;
	right = NULL;
}

PatriciaNode::PatriciaNode(char *initKey, int initSkip, unsigned long long initValue, PatriciaNode *initLeft, PatriciaNode *initRight) {
	int leng = strlen(initKey);
	key = new char[leng + 1];

	key[leng] = '\0';
	strcpy(key, initKey);
	
	skip = initSkip;
	value = initValue;
	left = initLeft;
	right = initRight;
}

void PatriciaNode::SetNode(int s,char *k,unsigned long long v, PatriciaNode *l, PatriciaNode *r)
{
	key = k;
	skip = s;
	value = v;
	left = l;
	right = r;
}

PatriciaNode::~PatriciaNode() {
	delete [] key;
}


