#include <map>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#ifndef TBOHR_H_
#define TBOHR_H_

typedef std::string TLetter;

typedef struct TBohrItem {
	std::map<TLetter, TBohrItem*> path;
	TBohrItem* sufflink = nullptr;
	std::vector<int> success; //pattern id
} TBohrItem;

class TBohr {
public:
	TBohr();
	TBohrItem* Next(TBohrItem* item, TLetter letter);
	TBohrItem* Move(TBohrItem* item, TLetter letter);
	void Parse(const std::string&);
	void Push(const std::vector<TLetter>&);
	void PushLetter(TBohrItem *node, TLetter let, int patid);
	TBohrItem* FindSufflink(TBohrItem* child, TBohrItem* parent,
			const TLetter letter);
	void Search(std::vector<TLetter>&,
			std::vector<std::pair<int, int> >&);

	void Linkate();
	std::vector<int> pieceIndex;
private:
	TBohrItem* root;
	int patternSize;
	int pieces;
	
};

#endif /* TBOHR_H_ */
