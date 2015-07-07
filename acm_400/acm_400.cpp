#include <string>   
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include "stdio.h"

struct TreeNode
{
	std::string data; 
	std::vector<TreeNode *> children;
	int skip;
	TreeNode* parent;
};

enum ERelationShip
{
	EChild = 0,		//儿子
	EAncestor = 1,	//祖先
	ESibling = 2,		//兄弟
	EParent = 3,		//双亲
	EDescendant = 4,	//后代
};

struct WordStruct
{
	std::string preName;
	std::string nextName;
	ERelationShip relatiopShip;
};

int split(const std::string& str, std::vector<std::string>& ret_, std::string sep = ",");
int getSkip(std::string str);
WordStruct parserWord(std::string str);
bool judge(TreeNode* globalTree, std::string str);
TreeNode* getByName(TreeNode* globalTree, std::string name);


int main()
{
	int personNum = 0;
	int wordsNum = 0;
	std::cin >> personNum >> wordsNum;
	TreeNode* tree = new TreeNode();
	std::vector<std::string> questions;
	std::map<int, TreeNode*> mapTree;
	for (int i = 0; i <= personNum; ++i)
	{
		char str[100];
		gets_s(str);
		std::string temp = str;
		//getline(std::cin, temp);
		int currentSkip = getSkip(temp);
		if (currentSkip == 0)
		{
			tree->data = temp;
			tree->skip = currentSkip;
			tree->parent = nullptr;
			mapTree[currentSkip] = tree;
		}
		else
		{
			TreeNode* child = new TreeNode();
			child->data = temp.substr(currentSkip, temp.size());
			child->skip = currentSkip;
			mapTree[currentSkip - 2]->children.push_back(child);
			mapTree[currentSkip] = child;
			child->parent = mapTree[currentSkip - 2];
		}
	}

	for (int j = 0; j < wordsNum; ++j)
	{
		char str[100];
		gets_s(str);
		std::string temp = str;
		questions.push_back(temp);
	}

	for (int i = 0; i < questions.size(); ++i)
	{
		std::cout <<( judge(tree, questions[i]) ? "True" : "False")<< std::endl;
	}

	system("pause");
	return 0;
}

int getSkip(std::string str)
{
	int skip = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		if (str.c_str()[i] == ' ')
		{
			++skip;
		}
		else
		{
			break;
		}
	}
	return skip;
}

bool judge(TreeNode* globalTree, std::string str)
{
	WordStruct wordStruct = parserWord(str);
	TreeNode* preTree = getByName(globalTree, wordStruct.preName);
	TreeNode* nextTree = getByName(globalTree, wordStruct.nextName);
	if (nullptr == preTree || nextTree ==nullptr)
	{
		std::cout << "name error" << std::endl;
		return false;
	}
	switch (wordStruct.relatiopShip)
	{
	case EParent:
	{
					return nextTree->parent == preTree;
	}
		break;
	case ESibling:
	{
					 return nextTree->parent == preTree->parent;
	}
		break;
	case EDescendant:
	{
						//后代
						TreeNode* tempNode = preTree->parent;
						while (tempNode)
						{
							if (tempNode == nextTree)
							{
								return true;
							}
							else
							{
								tempNode = tempNode->parent;
							}
						}
						return false;
	}
		break;
	case EChild:
	{
				   return preTree->parent == nextTree;
	}
		break;
	case  EAncestor:
	{
					   //祖先
					   TreeNode * tempNode = nextTree->parent;
					   while (tempNode)
					   {
						   if (tempNode == preTree)
						   {
							   return true;
						   }
						   else
						   {
							   tempNode = tempNode->parent;
						   }
					   }
					   return false;
	}
		break;
	}
	return false;
}

WordStruct parserWord(std::string str)
{
	WordStruct wordStruct;
	std::vector<std::string> strs;
	split(str, strs, " ");
	wordStruct.preName = strs[0];
	wordStruct.nextName = strs[strs.size() - 1];
	if (str.find("child") != std::string::npos)
	{
		wordStruct.relatiopShip = EChild;
	}
	else if (str.find("ancestor") != std::string::npos)
	{
		wordStruct.relatiopShip = EAncestor;
	}
	else if (str.find("sibling") != std::string::npos)
	{
		wordStruct.relatiopShip = ESibling;
	}
	else if (str.find("parent") != std::string::npos)
	{
		wordStruct.relatiopShip = EParent;
	}
	else
	{
		wordStruct.relatiopShip = EDescendant;
	}
	return wordStruct;
}

int split(const std::string& str, std::vector<std::string>& ret_, std::string sep)
{
	if (str.empty())
	{
		return 0;
	}

	std::string tmp;
	std::string::size_type pos_begin = str.find_first_not_of(sep);
	std::string::size_type comma_pos = 0;

	while (pos_begin != std::string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

TreeNode* getByName(TreeNode* globalTree, std::string name)
{
	if (globalTree->data == name)
	{
		return globalTree;
	}
	else
	{
		for (int i = 0; i < globalTree->children.size(); ++i) 
		{
			TreeNode* tempPtr = getByName(globalTree->children[i], name);
			if (nullptr != tempPtr)
			{
				return tempPtr;
			}
		}
	}
	return nullptr;
}