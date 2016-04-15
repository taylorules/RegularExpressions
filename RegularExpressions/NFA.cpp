#include <iostream>
#include "NFA.hpp"

NFA::NFA(int states)
{
	transition_table = new std::vector<std::vector<char>*>(states);
	for (int x = 0; x < states; ++x)
	{
		(*(transition_table))[x] = new std::vector<char>(states);
		for (int y = 0; y < states; ++y)
		{
			(*(*(transition_table))[x])[y] = '\0';
		}
	}
	state_count = states;
}

void NFA::set_char(int from, int to, char c)
{
	if (from >= state_count || to >= state_count || from < 0 || to < 0)
		return;
	(*(*(transition_table))[from])[to] = c;
	return;
}

const char NFA::get_char(int from, int to)
{
	if (from >= state_count || to >= state_count || from < 0 || to < 0)
		return '\0';
	return (*(*(transition_table))[from])[to];
}

void NFA::append()
{
	transition_table->insert(transition_table->end(), new std::vector<char>(state_count, '\0'));
	state_count++;
	for (int i = 0; i < state_count; ++i)
	{
		(*(transition_table))[i]->insert((*(transition_table))[i]->end(),'\0');
	}
}

void NFA::shift(int count)
{
	for (int i = 0; i < count; ++i)
	{
		transition_table->insert(transition_table->begin(), new std::vector<char>(state_count, '\0'));
		state_count++;
		for (int j = 0; j < state_count; ++j)
		{
			(*(transition_table))[j]->insert((*(transition_table))[j]->begin(), '\0');
		}
		start++;
		end++;
	}
}

void NFA::fill(NFA* other)
{
	for (int from = 0; from < other->state_count; ++from)
	{
		for (int to = 0; to < other->state_count; ++to)
		{
			set_char(from, to, other->get_char(from, to));
		}
	}
}

NFA::~NFA(){}

NFA build_nfa_basic(char c)
{
	NFA* basic = new NFA(2);
	basic->start = 0;
	basic->end = 1;
	basic->set_char(0, 1, c);
	return (*basic);
}

NFA build_nfa_alter(NFA* nfa1, NFA* nfa2)
{
	NFA* one = new NFA(nfa1->state_count);
	one->fill(nfa1);
	one->start = nfa1->start;
	one->end = nfa1->end;

	NFA* two = new NFA(nfa2->state_count);
	two->fill(nfa2);
	two->start = nfa2->start;
	two->end = nfa2->end;

	one->shift(1);
	two->shift(one->state_count);
	NFA* new_nfa = new NFA(two->state_count);
	new_nfa->fill(two);
	new_nfa->start = two->start;
	new_nfa->end = two->end;

	new_nfa->fill(one);
	new_nfa->set_char(0, one->start, *(u8"\u03F5"));
	new_nfa->set_char(0, two->start, *(u8"\u03F5"));
	new_nfa->start = 0;
	new_nfa->append();
	new_nfa->end = new_nfa->state_count - 1;
	new_nfa->set_char(one->end, new_nfa->end, *(u8"\u03F5"));
	new_nfa->set_char(two->end, new_nfa->end, *(u8"\u03F5"));
	//*(u8"\u03F5")
	
	/*new_nfa->fill(&nfa2);
	new_nfa->fill(&nfa1);
	new_nfa->set_char(0, nfa1.start, '?');
	new_nfa->set_char(0, nfa2.start, '?');
	new_nfa->start = 0;
	new_nfa->append();
	new_nfa->end = new_nfa->state_count - 1;
	new_nfa->set_char(nfa1.end, new_nfa->end, '?');
	new_nfa->set_char(nfa2.end, new_nfa->end, '?');*/
	return (*new_nfa);
}

NFA build_nfa_star(NFA* nfa)
{
	NFA* new_nfa = new NFA(nfa->state_count);
	new_nfa->fill(nfa);
	new_nfa->start = nfa->start;
	new_nfa->end = nfa->end;

	new_nfa->shift(1);
	new_nfa->append();
	new_nfa->set_char(new_nfa->end, new_nfa->start, *(u8"\u03F5"));
	new_nfa->set_char(0, new_nfa->start, *(u8"\u03F5"));
	new_nfa->set_char(new_nfa->end, new_nfa->state_count - 1, *(u8"\u03F5"));
	new_nfa->set_char(0, new_nfa->state_count - 1, *(u8"\u03F5"));
	new_nfa->start = 0;
	new_nfa->end = new_nfa->state_count - 1;
	return *new_nfa;
}

NFA build_nfa_concat(NFA* nfa1, NFA* nfa2)
{
	NFA* one = new NFA(nfa1->state_count);
	one->fill(nfa1);
	one->start = nfa1->start;
	one->end = nfa1->end;

	NFA* two = new NFA(nfa2->state_count);
	two->fill(nfa2);
	two->start = nfa2->start;
	two->end = nfa2->end;

	two->shift(one->state_count - 1);
	NFA* new_nfa = new NFA(two->state_count);
	new_nfa->fill(two);
	new_nfa->start = two->start;
	new_nfa->end = two->end;
	new_nfa->fill(one);
	new_nfa->start = one->start;
	return (*new_nfa);
}