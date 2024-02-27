#include"RedBlackTree.h"
#include <iostream>
#include <utility>
#include "List.h"
#include"StackArray.h"

RedBlackTree::RedBlackTree() :
	root_()
{}

RedBlackTree::~RedBlackTree()
{
	deleteSubtree(root_);
}

RedBlackTree::RedBlackTree(const std::string& treeKey, const std::string& meaning)
{
	root_ = new NodeTree(std::make_pair(treeKey, new List(meaning)));
};


void RedBlackTree::deleteSubtree(NodeTree* node)
{
	if (!root_)
	{
		return;
	}
	if (node->left_)
	{
		deleteSubtree(node->left_);
	}
	if (node->right_)
	{
		deleteSubtree(node->right_);
	}
	delete node;
}

void RedBlackTree::insert(const std::string& treeKey, const std::string& meaning)
{

	if (treeKey.empty() || meaning.empty())
	{
		std::cerr << "Invalid input. Tree key and meaning must not be empty." << std::endl;
		return;
	}

	if (!root_)
	{
		root_ = new NodeTree(std::make_pair(treeKey, new List(meaning)));
		return;
	}
	NodeTree* parent = nullptr;
	NodeTree* current = root_;
	while (current)
	{
		if (treeKey == current->treeKey_.first)
		{	
			current->treeKey_.second->insertItem(meaning);
			return;
		}
		else if (treeKey > current->treeKey_.first)
		{
			parent = current;
			current = current->right_;
		}
		else
		{
			parent = current;
			current = current->left_;
		}
	}
	if (parent->treeKey_.first < treeKey)
	{
		parent->right_ = new NodeTree(std::make_pair(treeKey, new List(meaning)), NodeTree::Color_Black_Red::RED, parent);
		fixInsert(parent->right_);
	}
	else
	{
		parent->left_ = new NodeTree(std::make_pair(treeKey, new List(meaning)), NodeTree::Color_Black_Red::RED, parent);
		fixInsert(parent->left_);
	}
}

void RedBlackTree::fixInsert(NodeTree* node)
{
	while (node != root_ && node->p_->color_ == NodeTree::Color_Black_Red::RED)
	{
		if (node->p_ == node->p_->p_->left_)
		{
			NodeTree* uncle = node->p_->p_->right_;
			if (uncle && uncle->color_ == NodeTree::Color_Black_Red::RED)
			{
				node->p_->color_ = NodeTree::Color_Black_Red::BLACK;
				uncle->color_ = NodeTree::Color_Black_Red::BLACK;
				node->p_->p_->color_ = NodeTree::Color_Black_Red::RED;
				node = node->p_->p_;
			}
			else
			{
				if (node == node->p_->right_)
				{
					node = node->p_;
					leftRotation(node);
				}
				node->p_->color_ = NodeTree::Color_Black_Red::BLACK;
				node->p_->p_->color_ = NodeTree::Color_Black_Red::RED;
				rightRotation(node->p_->p_);
			}
		}
		else
		{
			NodeTree* uncle = node->p_->p_->left_;
			if (uncle && uncle->color_ == NodeTree::Color_Black_Red::RED)
			{
				node->p_->color_ = NodeTree::Color_Black_Red::BLACK;
				uncle->color_ = NodeTree::Color_Black_Red::BLACK;
				node->p_->p_->color_ = NodeTree::Color_Black_Red::RED;
				node = node->p_->p_;
			}
			else
			{
				if (node == node->p_->left_)
				{
					node = node->p_;
					rightRotation(node);
				}
				node->p_->color_ = NodeTree::Color_Black_Red::BLACK;
				node->p_->p_->color_ = NodeTree::Color_Black_Red::RED;
				leftRotation(node->p_->p_);
			}
		}
	}
	root_->color_ = NodeTree::Color_Black_Red::BLACK;
}
/// <Rec Search>
///added 
bool RedBlackTree::search(const std::string& treeKey)
{
	return (searchNodeTree(treeKey) != nullptr);
}

void RedBlackTree::deleteWord(const std::string& treeKey)
{
	NodeTree* current = root_;
	while (current)
	{
		if (current->treeKey_.first < treeKey)
		{
			current = current->right_;
		}
		else if (current->treeKey_.first > treeKey)
		{
			current = current->left_;
		}
		else
		{
			std::cout << "key deleted \n";
			break;
		}
	}
	if (!current)
	{
		std::cout << "you cant delete because key is not exists \n";

		return;
	}
	deleteNode(current);
}

void RedBlackTree::deleteNode(NodeTree* node)
{
	NodeTree* replaceNode = findReplacement(node);
	bool bothBlack = ((replaceNode == nullptr || replaceNode->color_ == NodeTree::Color_Black_Red::BLACK)
		&& (node->color_ == NodeTree::Color_Black_Red::BLACK));
	NodeTree* parent = node->p_;
	if (replaceNode == nullptr)
	{
		if (node == root_)
		{
			root_ = nullptr;
		}
		else
		{
			if (bothBlack)
			{
				DeleteFixer(node);
			}
			else
			{
				if (findSibling(node))
				{
					findSibling(node)->color_ = NodeTree::Color_Black_Red::RED;
				}
			}
			if (node == node->p_->left_)
			{
				parent->left_ = nullptr;
			}
			else
			{
				parent->right_ = nullptr;
			}
		}
		delete node;
		return;
	}
	if (node->left_ == nullptr || node->right_ == nullptr)
	{
		if (node == root_)
		{
			swapData(replaceNode, node);
			node->left_ = node->right_ = nullptr;
			delete replaceNode;
		}
		else
		{
			if (node == node->p_->left_)
			{
				parent->left_ = replaceNode;
			}
			else
			{
				parent->right_ = replaceNode;
			}
			delete node;
			replaceNode->p_ = parent;
			if (bothBlack)
			{
				DeleteFixer(replaceNode);
			}
			else
			{
				replaceNode->color_ = NodeTree::Color_Black_Red::BLACK;
			}
		}
		return;
	}
	swapData(replaceNode, node);
	deleteNode(replaceNode);
}

void RedBlackTree::DeleteFixer(NodeTree* node)
{
	if (node == root_)
	{
		return;
	}
	NodeTree* sibling = findSibling(node);
	NodeTree* parent = node->p_;
	if (sibling == nullptr)
	{
		DeleteFixer(parent);
	}
	else
	{
		if (sibling->color_ == NodeTree::Color_Black_Red::RED)
		{
			parent->color_ = NodeTree::Color_Black_Red::RED;
			sibling->color_ = NodeTree::Color_Black_Red::BLACK;
			if (sibling == sibling->p_->left_)
			{
				rightRotation(parent);
			}
			else
			{
				leftRotation(parent);
			}
			DeleteFixer(node);
		}
		else
		{
			if ((sibling->left_ != nullptr && sibling->left_->color_ == NodeTree::Color_Black_Red::RED) ||
				(sibling->right_ != nullptr && sibling->right_->color_ == NodeTree::Color_Black_Red::RED))
			{
				if (sibling == sibling->p_->left_)
				{
					if (sibling->left_ != nullptr && sibling->left_->color_ == NodeTree::Color_Black_Red::RED)
					{
						sibling->left_->color_ = sibling->color_;
						sibling->color_ = parent->color_;
						rightRotation(parent);
					}
					else
					{
						sibling->right_->color_ = parent->color_;
						leftRotation(sibling);
						rightRotation(parent);
					}
				}
				else
				{
					if (sibling->right_ != nullptr && sibling->right_->color_ == NodeTree::Color_Black_Red::RED)
					{
						sibling->right_->color_ = sibling->color_;
						sibling->color_ = parent->color_;
						leftRotation(parent);
					}
					else
					{
						sibling->left_->color_ = parent->color_;
						rightRotation(sibling);
						leftRotation(parent);
					}
				}
				parent->color_ = NodeTree::Color_Black_Red::BLACK;
			}
			else
			{
				sibling->color_ = NodeTree::Color_Black_Red::RED;
				if (parent->color_ == NodeTree::Color_Black_Red::BLACK)
				{
					DeleteFixer(parent);
				}
				else
				{
					parent->color_ = NodeTree::Color_Black_Red::BLACK;
				}
			}
		}
	}
}


bool RedBlackTree::isRedBlackTree() {
	if (root_ == nullptr) {
		return true;
	}
	int blackCount = 0; 

	
	//  some recursive stuff 
	return isRedBlackTreeHelper(root_) && isRootBlack() && isRedNodesHaveBlackChildren() && isSameBlackNodeCount();
}

bool RedBlackTree::isRootBlack()
{
	
		return (root_->color_ == NodeTree::Color_Black_Red::BLACK);
	
}

bool RedBlackTree::isRedNodesHaveBlackChildren()
{
	
	return isRedNodesHaveBlackChildrenHelper(root_);
	
}

void RedBlackTree::leftRotation(NodeTree* oldR)
{
	if (!oldR->right_)
	{
		return;
	}
	NodeTree* newRoot = oldR->right_;
	oldR->right_ = newRoot->left_;
	if (newRoot->left_)
	{
		newRoot->left_->p_ = oldR;
	}
	newRoot->p_ = oldR->p_;
	if (oldR->p_)
	{
		if (oldR == oldR->p_->left_)
		{
			oldR->p_->left_ = newRoot;
		}
		else
		{
			oldR->p_->right_ = newRoot;
		}
	}
	else
	{
		root_ = newRoot;
	}
	newRoot->left_ = oldR;
	oldR->p_ = newRoot;
}

void RedBlackTree::rightRotation(NodeTree* oldR)
{
	if (!oldR->left_)
	{
		return;
	}
	NodeTree* newRoot = oldR->left_;
	oldR->left_ = newRoot->right_;
	if (newRoot->right_)
	{
		newRoot->right_->p_ = oldR;
	}
	newRoot->p_ = oldR->p_;
	if (oldR->p_)
	{
		if (oldR == oldR->p_->right_)
		{
			oldR->p_->right_ = newRoot;
		}
		else
		{
			oldR->p_->left_ = newRoot;
		}
	}
	else
	{
		root_ = newRoot;
	}
	newRoot->right_ = oldR;
	oldR->p_ = newRoot;
}





void RedBlackTree::swapData(NodeTree* node1, NodeTree* node2)
{
	std::swap(node1->treeKey_, node2->treeKey_);
}

void RedBlackTree::printWord(const std::string& treeKey, std::ostream& out)
{
	NodeTree* current = root_;
	while (current != nullptr)
	{
		if (treeKey < current->treeKey_.first)
		{
			current = current->left_;
		}
		else if (treeKey > current->treeKey_.first)
		{
			current = current->right_;
		}
		else
		{
			std::cout << treeKey << "\n";
			current->treeKey_.second->print(out);
			return;
		}
	}

	std::cout << treeKey << " : there is no word with  that  key in the dictionary\n";
}

void RedBlackTree::printDictionary(std::ostream& out)//DONE
{
	if (root_==nullptr)
	{
		out << "The dictionary is empty." << std::endl;
		return;
	}

	StackArray<NodeTree*> stack(getHeight());
	NodeTree* curr = root_;
	while (!stack.isEmpty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left_;
		}
		else
		{
			curr = stack.pop();
			out << curr->treeKey_.first << "\n";
			curr->treeKey_.second->print(out);
			curr = curr->right_;
		}
	}
		
}

int RedBlackTree::getHeight()
{
	return getHeight(root_);
}


std::string RedBlackTree::translate(const std::string& sentence)
{
	
		std::string translation;
		std::string word;
		size_t sentenceLength = sentence.length();

		for (size_t i = 0; i < sentenceLength; i++)
		{
			char c = sentence[i];
			if (c == ' ' || i == sentenceLength - 1)
			{
				if (i == sentenceLength - 1)
				{
					word += c;
				}
				if (word == "is" || word == "the" || word == "to" || word == "a" || word== "am" || word == "are" )//In russian basicly there is a none corresponding for the "is"
				{																
					word.clear();
				}
				NodeTree* node = searchNodeTree(word);
				if (node != nullptr) {
					translation += node->treeKey_.second->getFirstItem() + ' ';
				}
				else
				{
					translation += word + ' ';
				}
				word.clear();
			}
			else {
				word += c;
			}
		}

		return translation;
	
}

RedBlackTree::NodeTree::NodeTree(std::pair<std::string, List*> treeKey, Color_Black_Red color, NodeTree* p, NodeTree* left, NodeTree* right):
	left_(left),
	color_(color),
	p_(p),
	right_(right),
	treeKey_(treeKey)
{}

RedBlackTree::NodeTree::~NodeTree()
{
	delete treeKey_.second;
}
RedBlackTree::NodeTree* RedBlackTree::findSibling(const NodeTree* node)
{
	
		if (node->p_ == nullptr)
		{
			return nullptr;

		}
		if (node == node->p_->left_)
		{
			return node->p_->right_;
		}
		return node->p_->left_;
	
}
RedBlackTree::NodeTree* RedBlackTree::findSuccessor(NodeTree* node)
{
	NodeTree* temp = node;
	while (temp->left_ != nullptr)
	{
		temp = temp->left_;
	}
	return temp;
}
RedBlackTree::NodeTree* RedBlackTree::findReplacement(const NodeTree* node)
{
	if ((node->left_ != nullptr) && (node->right_ != nullptr))
	{
		return findSuccessor(node->right_);

	}
	if ((node->left_ == nullptr) && (node->right_ == nullptr))
	{
		return nullptr;
	}
	if (node->left_ != nullptr)
	{
		return node->left_;

	}
	else
	{
		return node->right_;

	}


}

RedBlackTree::NodeTree* RedBlackTree::searchNodeTree(const std::string& treeKey)
{
	NodeTree* current = root_;
	while (current != nullptr)
	{
		if (treeKey < current->treeKey_.first)
		{
			current = current->left_;
		}
		else if (treeKey > current->treeKey_.first)
		{
			current = current->right_;
		}
		else
			break;


	}
	return current;

}

bool RedBlackTree::isRedBlackTreeHelper(NodeTree* node)
{
	if (node == nullptr)
	{
		return true;
	}

	if (node->color_ == NodeTree::Color_Black_Red::RED)
	{
		if (node->left_ != nullptr && node->left_->color_ == NodeTree::Color_Black_Red::RED) 
		{
			return false;
		}
		if (node->right_ != nullptr && node->right_->color_ == NodeTree::Color_Black_Red::RED) 
		{
			return false;
		}
	}

	return isRedBlackTreeHelper(node->left_) && isRedBlackTreeHelper(node->right_);

}

bool RedBlackTree::isRedNodesHaveBlackChildrenHelper(NodeTree* node)
{
	if (node == nullptr) 
	{
		return true;
	}

	if (node->color_ == NodeTree::Color_Black_Red::RED)
	{
		if ((node->left_ != nullptr && node->left_->color_ == NodeTree::Color_Black_Red::RED) ||
			(node->right_ != nullptr && node->right_->color_ == NodeTree::Color_Black_Red::RED)) {
			return false;
		}
	}
	return isRedNodesHaveBlackChildrenHelper(node->left_) && isRedNodesHaveBlackChildrenHelper(node->right_);

}

int RedBlackTree::getHeight(NodeTree* node)
{
	if (node == nullptr) {
		//leaf node
		return 0;
	}


	int leftHeight = getHeight(node->left_);
	int rightHeight = getHeight(node->right_);

	// +  1 for the current node
	return std::max(leftHeight, rightHeight) + 1;
}

bool RedBlackTree::isSameBlackNodeCountHelper(NodeTree* node, int currentBlackCount, int& blackNodeCount)
{
	
		if (node == nullptr) {
			if (blackNodeCount == -1) {
				blackNodeCount = currentBlackCount;  // Set blackNodeCount for the first time
			}
			else {
				if (currentBlackCount != blackNodeCount) {
					return false;
				}
			}
			return true;
		}

		if (node->color_ == NodeTree::Color_Black_Red::BLACK) {
			currentBlackCount++;
		}

		return isSameBlackNodeCountHelper(node->left_, currentBlackCount, blackNodeCount) &&
			isSameBlackNodeCountHelper(node->right_, currentBlackCount, blackNodeCount);
	
		
}
