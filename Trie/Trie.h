#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class trie {
private:
	class TrieNode {
	public:
		bool is_end = false;
		vector<TrieNode*> children;
	};

	int size_t = 0;
	int children_size = 256;
	TrieNode *root = nullptr;

public:
	/* Constructor */
	trie() {
		size_t = 0;
		root = nullptr;
	}

	/* Destructor */
	~trie() {
		delete root;
		root = nullptr;
		size_t = 0;
	}

	/* Add */
	/* Add key */
	void put(string key, bool is_end);

	/* Delete */
	/* Remove key and is_endue */
	void remove(string key);

	/* Search */
	/* Check trie has is_endue of key */
	bool get(string key);

	/* Check trie contains key */
	bool containsKey(string key);

	/* The shortest prefix of query */
	string shortestPrefix(string query);

	/* The longest prefix of query */
	string longestPrefix(string query);

	/* All the keys have the secific prefix */
	vector<string> keyWithPrefix(string prefix);

	/* Check if trie contains key of the specific prefix */
	bool hasKeyWithPrefix(string prefix);

	/* Search for all matching keys */
	vector<string> keysWithPattern(string pattern);

	/* Check whether a matching key exists */
	bool hasKeyWithPattern(string pattern);

	/* The key in trie */
	int size();

private:
	TrieNode* getNode(TrieNode *node, string key);
	void traverse(TrieNode *node, string path, vector<string>& res);
	void traverse(TrieNode *node, string path, string pattern, int i, vector<string> &res);
	bool hasKeyWithPattern(TrieNode *node, string pattern, int i);
	TrieNode* put(TrieNode *node, string key, bool is_end, int i);
	TrieNode* remove(TrieNode *node, string key, int i);
};