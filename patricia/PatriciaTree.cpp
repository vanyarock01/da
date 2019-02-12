#include "PatriciaTree.h"
#include "PatriciaNode.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>


int PatriciaTree::GetBit(char *key, register int idx)
{
    if (idx < 0) return -1;

    register int bit_pos = 7 - (idx & 7);
    register int bit = key[idx >> 3];
    bit = (bit >> bit_pos) & 1U;

    return bit;
}

void NodeDebugPrint(PatriciaNode *tree, PatriciaNode *node, int32_t idx)
{
    if ((node->left->skip >= node->skip) &&
            (node->left != node) &&
            (node->left != tree))
        NodeDebugPrint(tree, node->left, idx + 1);
    for (int j = 0; j < idx; ++j)
        putchar('\t');
    printf("%s, %d |  %s < > %s\n", node->key, node->skip, node->left->key, node->right->key);
    if ((node->right->skip >= node->skip) &&
            (node->right != node) && (node->right != tree))
        NodeDebugPrint(tree, node->right, idx + 1);
}

void PatriciaTree::Print()
{
    if (root != NULL) {
        NodeDebugPrint(root, root, 0);
    }
}



int PatriciaTree::EqualKey(char *x, char *y)
{
    if (x == NULL || y == NULL)
        return 0;
    return !strcmp(x, y);
}


PatriciaNode* PatriciaTree::SearchI(char *key)
{
    if (root == NULL) return NULL;
    PatriciaNode*  parent = root;
    PatriciaNode*  x = root->left;

    while (parent->skip < x->skip) {
        parent = x;
        x = (GetBit(key, x->skip) ? x->right : x->left);
    }

    if (!EqualKey(key, x->key))
        return NULL;

    return x;

}

PatriciaNode* PatriciaTree::Search(char *key)
{
    //PatriciaNode *res = SearchI(key);

    if (root == NULL) return NULL;
    
    PatriciaNode*  parent = root;
    PatriciaNode*  x = root->left;


    while (parent->skip < x->skip) {
        parent = x;
        x = (GetBit(key, x->skip) ? x->right : x->left);
    }

    return (EqualKey(key, x->key)) ? x : NULL;
}


int PatriciaTree::FirstDifferentBit(char *x, char *y)
{
    int n = 0;
    int d = 0;

    int max = (strlen(x) > strlen(y)) ? strlen(y) : strlen(x);
    while (*x == *y && n < max) {
        x++; y++; n++;
    }
    while (GetBit(x, d) == GetBit(y, d)) d++;

    return ((n << 3) + d);
}


RetToken PatriciaTree::Insert(char *key, unsigned long long val)
{
    if (root == NULL) {
        root = new PatriciaNode(key, 0, val, NULL, NULL);
        root->left = root;
        root->right = root;
        size++;
        return SUCCESS;
    }
    PatriciaNode *parent, *tmp, *x;

    parent = root;
    tmp = parent->left;

    while (parent->skip < tmp->skip) {
        parent = tmp;
        tmp = (GetBit(key, tmp->skip) ? tmp->right : tmp->left);
    }

    if (EqualKey(key, tmp->key)) return SKIP;

    int i = FirstDifferentBit(key, tmp->key);

    parent = root;
    x = parent->left;

    while ( ( parent->skip < x->skip ) && ( x->skip < i) ) {
        parent = x;
        x = (GetBit(key, x->skip) ? x->right : x->left);
    }

    tmp = new PatriciaNode(key, i, val, NULL, NULL);
    tmp->left = (GetBit(key, i) ? x : tmp);
    tmp->right = (GetBit(key, i) ? tmp : x);

    if (GetBit(key, parent->skip))
        parent->right = tmp;
    else
        parent->left = tmp;
    size++;
    return SUCCESS;

}

RetToken PatriciaTree::Delete(char *key)
{
    if (root == NULL) return SKIP;

    if ((root == root->left) && (EqualKey(root->key, key))) {
        delete root;
        root = NULL;
        size--;
        return SUCCESS;
    }

    PatriciaNode *sire;
    PatriciaNode *parent = root;
    PatriciaNode *child = parent->left;



    while (parent->skip < child->skip) {
        sire = parent;
        parent = child;
        child = GetBit(key, child->skip) ? child->right : child->left;
    }

    if (!EqualKey(child->key, key)) return SKIP;

    if (child != parent) {

        if (parent->key == NULL) {
            child->key = NULL;
        }
        else {
            delete [] child->key;
            child->key = new char[strlen(parent->key) + 1];
            
            child->key[strlen(parent->key)] = '\0';
            strcpy(child->key, parent->key);
        }
        child->value = parent->value;
    }

    if ((parent->left->skip > parent->skip) || (parent->right->skip > parent->skip)) {
        if (parent != child) {
            PatriciaNode *leaf = parent;
            PatriciaNode *tmp = GetBit(parent->key, parent->skip) ? parent->right : parent->left;

            while (leaf->skip < tmp->skip) {
                leaf = tmp;
                tmp = GetBit(parent->key, tmp->skip) ? tmp->right : tmp->left;
            }

            if (!EqualKey(parent->key, tmp->key)) return SKIP;

            if (GetBit(parent->key, leaf->skip))
                leaf->right = child;
            else
                leaf->left = child;
        }

        if (sire != parent) {
            PatriciaNode *child = GetBit(key, parent->skip) ? parent->left : parent->right;

            if (GetBit(key, sire->skip))
                sire->right = child;
            else
                sire->left = child;
        }
    } else {
        if (sire != parent) {
            PatriciaNode *item;

            if ((parent->left == parent->right) && (parent->left == parent))
                item = sire;
            else
                item = (parent->left == parent) ? parent->right : parent->left;

            if (GetBit(key, sire->skip))
                sire->right = item;
            else
                sire->left = item;
        }
    }
    delete parent;
    size--;
    return SUCCESS;
}


int PatriciaTree::GetArray(PatriciaNode *node, PatriciaNode **a, int idx)
{
    a[idx] = node;
    node->idx = idx;

    if (node->left->skip > node->skip) {
        idx = GetArray(node->left, a, ++idx);
    }

    if (node->right->skip > node->skip) {
        idx = GetArray(node->right, a, ++idx);
    }
    return idx;
}


RetToken PatriciaTree::SetArray(PatriciaNode **a, FILE *ofs)
{
    int len;
    int skip, idx, idxL, idxR;
    unsigned long long val;
    char *key;

    while (fread(&len, sizeof(len), 1, ofs) == 1) {

        key = new char[len + 1];
        key[len] = '\0';
        if (key == NULL) return ALLOC;

        bool ex = true;
        ex &= (bool)fread(&skip, sizeof(skip), 1, ofs);
        ex &= (bool)fread(key, sizeof(char), len, ofs);
        ex &= (bool)fread(&val, sizeof(val), 1, ofs);
        ex &= (bool)fread(&idx, sizeof(idx), 1, ofs);
        ex &= (bool)fread(&idxL, sizeof(idxL), 1, ofs);
        ex &= (bool)fread(&idxR, sizeof(idxR), 1, ofs);

        if (!ex) return FILE_I;

        a[idx]->SetNode(skip, key, val, a[idxL], a[idxR]);
        a[idx]->idx = 0;
        key = NULL;
    }

    return SUCCESS;
}

RetToken PatriciaTree::Load(char *path)
{

    FILE *ofs = fopen(path, "rb");
    if (ofs == NULL) return FILE_OPEN;

    if (!(bool)fread(&size, sizeof(size), 1, ofs)) return FILE_I;

    if (size == 0) return SKIP;


    PatriciaNode **a = (PatriciaNode**)malloc(size * sizeof(PatriciaNode));
    if (a == NULL) return ALLOC;

    for (int i = 0; i < size; i++) {
        a[i] = new PatriciaNode();
    }
    RetToken res = SetArray(a, ofs);
    root = *a;

    free(a);
    fclose(ofs);

    return res;

}

RetToken PatriciaTree::Save(char *path)
{

    FILE *ofs = fopen(path, "wb");
    if (ofs == NULL) return FILE_OPEN;

    PatriciaNode **a = (PatriciaNode **) malloc(size * sizeof(PatriciaNode*));
    if (a == NULL) return ALLOC;

    bool ex = true;
    ex &= (bool)fwrite(&size, sizeof(size), 1, ofs);
    if (size) GetArray(root, a, 0);


    for (int i = 0; i < size; ++i) {
        int len = strlen(a[i]->key);

        ex &= (bool)fwrite(&len, sizeof(int), 1, ofs);
        ex &= (bool)fwrite(&(a[i]->skip), sizeof(a[i]->skip), 1, ofs);
        ex &= (bool)fwrite(a[i]->key, sizeof(char), len, ofs);
        ex &= (bool)fwrite(&(a[i]->value), sizeof(a[i]->value), 1, ofs);
        ex &= (bool)fwrite(&(a[i]->idx), sizeof(a[i]->idx), 1, ofs);
        ex &= (bool)fwrite(&(a[i]->left->idx), sizeof(a[i]->left->idx), 1, ofs);
        ex &= (bool)fwrite(&(a[i]->right->idx), sizeof(a[i]->left->idx), 1, ofs);

        if (!ex) return FILE_O;
    }
    free(a);
    fclose(ofs);
    return SUCCESS;
}

void PatriciaTree::ClearR(PatriciaNode *node)
{
    if ((node->left->skip >= node->skip) && (node->left != node) && (node->left != root))
        ClearR(node->left);

    if ((node->right->skip >= node->skip) && (node->right != node) && (node->right != root))
        ClearR(node->right);

    delete node;

}
void PatriciaTree::Clear()
{
    if (size > 0 && root != NULL) ClearR(root);
}



