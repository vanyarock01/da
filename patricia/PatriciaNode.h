#ifndef PATRICIANODE_H_
#define PATRICIANODE_H_



class PatriciaNode {
public:
	PatriciaNode();
	PatriciaNode(char *initKey, int initSkip, unsigned long long initValue, PatriciaNode *initLeft, PatriciaNode *initRight);
	~PatriciaNode();


	void SetNode(int s,char *k,unsigned long long v, PatriciaNode *l, PatriciaNode *r);

	char *key;
	int skip;
	int idx;
	unsigned long long value;

	PatriciaNode *left;
	PatriciaNode *right;

};

#endif /* PATRICIANODE_H_ */
