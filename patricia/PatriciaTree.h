#ifndef PATRICIATREE_H_
#define PATRICIATREE_H_

#include <cstdlib>
#include <iostream>

#include "PatriciaNode.h"


enum RetToken {
	SUCCESS,
	FILE_OPEN,
	FILE_I,
	FILE_O,
	ALLOC,
	FREE,
	SKIP
};

void StringInit(char *data, size_t l);

const static int bit = 8;

class PatriciaTree {
public:
	PatriciaTree(){
		size = 0;
		root = NULL;
	}
	~PatriciaTree(){};
	void Print();
	int GetBit(char *key, int idx);
	int EqualKey(char *x, char *y);

	PatriciaNode* Search(char *key);
	RetToken Insert(char *key, unsigned long long val);
	RetToken Load(char *path);
	RetToken Save(char *path);
	void Clear();
	RetToken Delete(char *key);

	PatriciaNode *root;
	int size;

private:
	int FirstDifferentBit(char *x, char *y);
	PatriciaNode* SearchI(char *key);
	//PatriciaNode* SearchI(PatriciaNode *link, char *key, int d);
	void ClearR(PatriciaNode *node);
	int GetArray(PatriciaNode *node, PatriciaNode **a, int idx);
	RetToken SetArray(PatriciaNode **a, FILE *ofs);

};



#endif /* PATRICIATREE_H_ */
