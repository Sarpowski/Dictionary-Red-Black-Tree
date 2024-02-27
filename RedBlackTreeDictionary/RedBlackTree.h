#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include<exception>
#include <utility>
#include "List.h"
#include <string>


class RedBlackTree
{
public:

	RedBlackTree();
	~RedBlackTree();

	
	RedBlackTree(const std::string& treeKey, const std::string& meaning);

	void insert(const std::string& treeKey, const std::string& meaning);
	bool search(const std::string& treeKey);
	void deleteWord(const std::string& treeKey);
	void printWord(const std::string& treeKey, std::ostream& out);
	void printDictionary(std::ostream& out);
	int getHeight();

	//DOPE
	std::string translate(const std::string& sentence);



	RedBlackTree(const RedBlackTree& src) = delete;
	RedBlackTree(RedBlackTree&& src) noexcept = delete;
	RedBlackTree& operator=(const RedBlackTree& src) = delete;
	RedBlackTree& operator=(RedBlackTree&& src) noexcept = delete;


	bool isRedBlackTree();
	bool isRootBlack();
	bool isRedNodesHaveBlackChildren();
	
	bool isSameBlackNodeCount()
	{
		int blackNodeCount = -1;  // Initialized to -1 for the first node encountered
		return isSameBlackNodeCountHelper(root_, 0, blackNodeCount);
	}

	

private:

	struct NodeTree
	{
		enum class Color_Black_Red
		{
			BLACK,
			RED
		};
		NodeTree* left_;
		NodeTree* right_;
		NodeTree* p_;
		std::pair<std::string, List*> treeKey_;
		Color_Black_Red color_;

		NodeTree(std::pair<std::string, List*> treeKey = std::make_pair(std::string(), nullptr),
			Color_Black_Red color = Color_Black_Red::BLACK,
				 NodeTree* p = nullptr, 
			     NodeTree* left = nullptr, 
			     NodeTree* right = nullptr);
		
		~NodeTree();
		
			
		
	};
	NodeTree* root_;
	

	//tree operations 
	void deleteNode(NodeTree* node);
	void deleteSubtree(NodeTree* node);
	void fixInsert(NodeTree* son);
	void leftRotation(NodeTree* oldRoot);
	void rightRotation(NodeTree* oldRoot);
	void DeleteFixer(NodeTree* node);
	void swapData(NodeTree* node1, NodeTree* node2);

	NodeTree* findSuccessor(NodeTree* node);
	NodeTree* findSibling(const NodeTree* node);
	NodeTree* findReplacement(const NodeTree* node);
	NodeTree* searchNodeTree(const std::string& treeKey);

	bool isRedBlackTreeHelper(NodeTree* node);
	bool isRedNodesHaveBlackChildrenHelper(NodeTree* node);
	int getHeight(NodeTree* node); 
	
	bool isSameBlackNodeCountHelper(NodeTree* node, int currentBlackCount, int& blackNodeCount);
	
};



#endif 