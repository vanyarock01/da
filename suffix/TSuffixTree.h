#ifndef TSUFTREE_H
#define TSUFTREE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

class TSuffixArray;

class TNode
{
public:

    TNode (std::string::iterator start, std::string::iterator end);
    ~TNode() {};

    std::map<char, TNode *> vertex_list;
    std::string::iterator   start, end;
    TNode                  *suffixLink;

};

class TSuffixTree
{
public:

    TSuffixTree(std::string str);
    ~TSuffixTree();

    friend TSuffixArray;

private:

    std::string text;

    TNode *root;
    TNode *takeSuffLink;
    TNode *actNode;

    int remainder;
    int actLength;

    std::string::iterator actEdge;

    void Destroy         (TNode *node);
    void SuffixLinkAdd   (TNode *node);
    void DeepFirstSearch (TNode *node, std::vector<int> &result, int deep);
    void Construct       (std::string::iterator begin);
    bool Downhill        (std::string::iterator position, TNode *node);
};

class TSuffixArray
{
public:

    TSuffixArray          (TSuffixTree *tree);
    ~TSuffixArray         ( ) {};

    std::vector<int> Find (std::string &pattern);

private:

    int FindLeft (const std::string &pattern);
    int FindRight(const std::string &pattern);

    std::string text;
    std::vector<int> array;
};


#endif