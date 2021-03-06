#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <Windows.h>
#include "FSM.hpp"
#include "NFA.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include "ExpressionTree.hpp"
#include "DFA.hpp"

HANDLE hConsole;

int main()
{
	//system("Color F0");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int whiteColor = 15;
	int greyColor = 8;
	SetConsoleTextAttribute(hConsole, whiteColor);
	//Tree* newTree = build_tree_from_expression("[a-zA-Z]{3}e[a-zA-Z]{2}e");
	//Expression_Tree* newTree = new Expression_Tree("(A|B|C)*\\?D{3,15}[1-4]");
	std::string input;
	std::getline(std::cin, input);
	Expression_Tree* newTree = new Expression_Tree(input);
	/*
	Node* star1 = new Node(PLUS);
	Node* a1 = new Node(CHR, 'a');
	star1->left = a1;

	Tree* tree = new Tree(star1);
	*/
	/*
	NFA a = build_nfa_basic('a');
	NFA b = build_nfa_basic('b');
	NFA alt = build_nfa_alter(&a, &b);
	NFA str = build_nfa_star(&alt);
	NFA sa = build_nfa_concat(&str, &a);
	NFA sab = build_nfa_concat(&sa, &b);
	NFA sabb = build_nfa_concat(&sab, &b);
	*/
	NFA fin = *newTree->root->tree_to_nfa();
	DFA* finDFA = new DFA(&fin);
	/*
	std::vector<char>* char_vec = (*fin.transition_table)[fin.start];
	for (int i = 0; i < char_vec->size(); ++i)
	{
		if ((*char_vec)[i] != '\0')
		{
			if (DFA_Q.size() == 0)
			{
				DFA_Q.push(new DFA(i));
			}
			else {
				DFA_Q.front()->states.push_back(i);
			}
		}
	}
	
	while (!DFA_Q.empty())
	{
		DFA* curr_DFA = DFA_Q.front();
		DFA_Q.pop();
		while (!curr_DFA->states.empty())
		{
			int curr_state = curr_DFA->states.top();
			curr_DFA->states.pop();
			std::vector<char>* char_vec = (*fin.transition_table)[curr_state];
			for (int i = 0; i < char_vec->size(); ++i)
			{
				if ((*char_vec)[i] == eps)
				{
					curr_DFA->states.push(i);
				}
			}
		}
	}
	*/

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "Start: " << fin.start << std::endl << "End: " << fin.end << std::endl << *fin.regex << std::endl;

	SetConsoleTextAttribute(hConsole, whiteColor);
	std::cout << " ";
	if (fin.state_count >= 10)
		std::cout << " ";
	if (fin.state_count >= 100)
		std::cout << " ";
	for (int x = 0; x < fin.state_count; ++x) {
		std::cout << x << " ";
		if (x < 10 && fin.state_count >= 10)
			std::cout << " ";
		if (x < 100 && fin.state_count >= 100)
			std::cout << " ";
	}
	SetConsoleTextAttribute(hConsole, greyColor);
	std::cout << std::endl;
	for (int y = 0; y < fin.state_count; ++y)
	{
		SetConsoleTextAttribute(hConsole, whiteColor);
		std::cout << y;
		SetConsoleTextAttribute(hConsole, greyColor);
		if (fin.state_count >= 10 && y < 10)
			std::cout << " ";
		if (fin.state_count >= 100 && y < 100)
			std::cout << " ";
		for (int x = 0; x < fin.state_count; ++x)
		{
			if (fin.get_char(x, y) == '\0')
				std::cout << (char)197 << (char)196;
			else {
				SetConsoleTextAttribute(hConsole, whiteColor);
				std::cout << fin.get_char(x, y);
				SetConsoleTextAttribute(hConsole, 8);
				if (x < fin.state_count - 1)
					std::cout << (char)196;
			}
				
			if (fin.state_count >= 10 && x < fin.state_count-1)
				std::cout << (char)196;
			if (fin.state_count >= 100 && x < fin.state_count - 1)
				std::cout << (char)196;
		}
		std::cout << std::endl;
		if (fin.state_count >= 10)
		{
			if (y < fin.state_count - 1)
			{
				for (int x = 0; x < fin.state_count; ++x)
				{
					if (fin.state_count >= 10)
						std::cout << " ";
					if (fin.state_count >= 100)
						std::cout << " ";
					std::cout << " " << (char)179;

				}
			}
			std::cout << std::endl;
		}
	}
	while (1);
}