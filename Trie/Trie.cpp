#include "Trie.h"

trie::TrieNode* trie::getNode(TrieNode* node, string key) {
	TrieNode *p = node;
	for (int i = 0; i < key.size(); ++i) {
		if (p == nullptr)
			return nullptr;
		char ch = key[i];
		p = p->children[ch];
	}
	return p;
}

bool trie::get(string key) {
	TrieNode *x = getNode(root, key);
	if (x == nullptr || x->is_end)
		return false;
	return x->is_end;
}

bool trie::containsKey(string key) {
	return get(key);
}

bool trie::hasKeyWithPrefix(string prefix) {
	return getNode(root, prefix) != nullptr;
}

string trie::shortestPrefix(string query) {
	TrieNode *p = root;
	for (int i = 0; i < query.size(); ++i) {
		if (p == nullptr)
			return "";
		if (p->is_end)
			return query.substr(0, i + 1);

		char ch = query[i];
		p = p->children[ch];
	}

	if (p != nullptr && p->is_end)
		return query;

	return "";
}

string trie::longestPrefix(string query) {
	TrieNode *p = root;
	int max_len = 0;

	for (int i = 0; i < query.size(); ++i) {
		if (p == nullptr)
			break;
		if (p->is_end)
			max_len = i;

		char ch = query[i];
		p = p->children[ch];
	}

	if (p != nullptr && p->is_end)
		return query;

	return query.substr(0, max_len + 1);
}

vector<string> trie::keyWithPrefix(string prefix) {
	vector<string> res;
	TrieNode *x = getNode(root, prefix);
	if (x == nullptr)
		return res;

	traverse(x, prefix, res);
	return res;
}

void trie::traverse(TrieNode *node, string path, vector<string>& res) {
	if (node == nullptr)
		return;

	if (node->is_end)
		res.push_back(path);

	for (int c = 0; c < children_size; ++c) {
		path.push_back((char)(c));
		traverse(node->children[c], path, res);
		path.pop_back();
	}
}

vector<string> trie::keysWithPattern(string pattern) {
	vector<string> res;
	string path;
	traverse(root, path, pattern, 0, res);
	return res;
}

void trie::traverse(TrieNode *node, string path, string pattern, int i, vector<string> &res) {
	if (node == nullptr)
		return;
	if (i == pattern.size()) {
		if (node->is_end)
			res.push_back(path);
		return;
	}

	char c = pattern[i];
	if (c == '.') {
		for (int j = 0; j < children_size; ++j) {
			path.push_back((char)(j));
			traverse(node->children[i], path, pattern, i + 1, res);
			path.pop_back();
		}
	}
	else {
		path.push_back(c);
		traverse(node->children[c], path, pattern, i + 1, res);
		path.pop_back();
	}
}

bool trie::hasKeyWithPattern(string pattern) {
	return hasKeyWithPattern(root, pattern, 0);
}

bool trie::hasKeyWithPattern(TrieNode *node, string pattern, int i) {
	if (node == nullptr)
		return false;
	if (i == pattern.size())
		return node->is_end;

	char c = pattern[i];
	if (c != '.')
		return hasKeyWithPattern(node->children[c], pattern, i + 1);

	// meet '.'
	for (int j = 0; j < children_size; ++j) {
		if (hasKeyWithPattern(node->children[j], pattern, i + 1))
			return true;
	}

	return false;
}

void trie::put(string key, bool is_end) {
	if (!containsKey(key))
		size_t++;
	root = put(root, key, is_end, 0);
}

trie::TrieNode* trie::put(TrieNode *node, string key, bool is_end, int i) {
	if (node == nullptr)
		node = new TrieNode();
	if (i == key.size()) {
		node->is_end = true;
		return node;
	}
	char c = key[i];
	node->children[c] = put(node->children[c], key, is_end, i + 1);
	return node;
}

void trie::remove(string key) {
	if (!containsKey(key))
		return;
	root = remove(root, key, 0);
	size_t--;
}

trie::TrieNode* trie::remove(TrieNode *node, string key, int i) {
	if (node == nullptr)
		return nullptr;

	if (i == key.size())
		return node;
	else {
		char c = key[i];
		node->children[i] = remove(node->children[c], key, i + 1);
	}

	if (node->is_end)
		return node;

	for (int c = 0; c < children_size; ++c)
		if (node->children[c] != nullptr)
			return node;
	return nullptr;
}

int trie::size() {
	return size_t;
}