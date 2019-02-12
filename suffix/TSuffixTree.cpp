#include "TSuffixTree.h"

TSuffixTree::TSuffixTree(std::string string):
    text(string), root(new TNode(text.end(), text.end())), remainder(0)
{
    actEdge          = text.begin();
    actNode          = root;
    root->suffixLink = root;
    takeSuffLink     = root;
    actLength        = 0;

    for (std::string::iterator suffix = text.begin(); suffix != text.end(); ++suffix)
        Construct(suffix);
}

TNode::TNode(std::string::iterator start, std::string::iterator end): 
    start(start), end(end), suffixLink(nullptr) {}

void TSuffixTree::Destroy(TNode *node)
{
    for (std::map<char, TNode *>::iterator it = node->vertex_list.begin(); it != node->vertex_list.end(); ++it)
        Destroy(it->second);

    delete node;
}

TSuffixTree::~TSuffixTree()
{
    Destroy(root);
}


void TSuffixTree::Construct(std::string::iterator begin)
{
    takeSuffLink = root;
    remainder++;

    while (remainder) {
        if (!actLength) actEdge = begin;
        
        std::map<char, TNode *>::iterator vertex = actNode->vertex_list.find(*actEdge);
        TNode *next;

        if (vertex == actNode->vertex_list.end()) {

            TNode *leaf = new TNode(begin, text.end());
            actNode->vertex_list[*actEdge] = leaf;
            SuffixLinkAdd(actNode);

        } else {
            next =  vertex->second;
            if (Downhill(begin, next)) continue;

            if (*(next->start + actLength) == *begin) {
                actLength++;
                SuffixLinkAdd(actNode);
                break;
            }

            TNode *split = new TNode(next->start, next->start + actLength);
            TNode *leaf  = new TNode(begin, text.end());

            actNode->vertex_list[*actEdge] = split;
            split->vertex_list[*begin]           = leaf;
            next ->start                        += actLength;
            split->vertex_list[*next->start]     = next;

            SuffixLinkAdd(split);
        }
        remainder--;
        if (actNode == root && actLength) {
            actLength--;
            actEdge = begin - remainder + 1;
        } else {
            actNode = (actNode->suffixLink) ? actNode->suffixLink : root;
        }
    }
}

bool TSuffixTree::Downhill(std::string::iterator position, TNode *node)
{
    int length;
    if (position + 1 < node->end)
        length = position + 1 - node->start;
    else
        length = node->end - node->start;

    if (actLength  >= length) {
        actEdge += length;
        actLength  -= length;
        actNode  = node;
        return true;
    }
    return false;
}

void TSuffixTree::SuffixLinkAdd(TNode *node)
{
    if (takeSuffLink != root) takeSuffLink->suffixLink = node;

    takeSuffLink = node;
}

void TSuffixTree::DeepFirstSearch(TNode *node, std::vector<int> &result, int deep)
{
    if (node->vertex_list.empty()) {
        result.push_back(text.size() - deep);
        return;
    }

    for (std::map<char, TNode *>::iterator it = node->vertex_list.begin(); 
                                            it != node->vertex_list.end();
                                                                     ++it) {
        int tmp = deep;
        tmp += it->second->end - it->second->start;
        DeepFirstSearch(it->second, result, tmp);
    }
}

TSuffixArray::TSuffixArray(TSuffixTree *tree):
    text(tree->text), array()
{
    tree->DeepFirstSearch(tree->root, array, 0);
}


int TSuffixArray::FindLeft(const std::string &pattern)
{
    int left   = 0;
    int right  = text.size() - 1;
    int length = pattern.size();

    while (left <= right) {
        int mid = (left + right) / 2;

        std::string tmp = text.substr(array[mid], length);

        if (pattern > tmp)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}

int TSuffixArray::FindRight(const std::string &pattern)
{
    int left   = 0;
    int right  = text.size() - 1;
    int length = pattern.size();

    while (left <= right) {
        int mid = (left + right) / 2;

        std::string tmp = text.substr(array[mid], length);

        if (pattern >= tmp)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return left;
}

std::vector<int> TSuffixArray::Find(std::string &pattern)
{
    int left  = FindLeft (pattern);
    int right = FindRight(pattern);

    std::vector<int> result;

    for (int i = left; i < right; ++i)
        result.push_back(array[i]);

    std::sort(result.begin(), result.end());
    return result;
}

