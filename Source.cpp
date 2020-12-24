#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "rules.h"

using namespace std;

int main()
{
	//Read all strings from file
	ifstream fin("input.txt");
	vector<string> data;
	string current;
	while (getline(fin, current)) {
		data.push_back(current);
	}

	char delim = ' ';
	//read and prepare first table data
	vector<char> terminals1;
	for (auto terminal : data[2])
	{
		if (terminal != delim && terminal != '~')
		{
			terminals1.push_back(terminal);
		}
	}
	int count = 3;
	vector<rule> rules1;
	while (data[count].size() != 0 && count < data.size())
	{
		string current = data[count];
		rule r;
		r.from = current[0];
		r.is_ending = current[1] == '.';
		for (int i = 3; i < current.size(); i += 2)
		{
			r.to.push_back(current[i]);
		}
		rules1.push_back(r);
		++count;
	}

	//moving to the second one
	count += 2;
	vector<char> terminals2;
	for (auto terminal : data[count])
	{
		if (terminal != delim && terminal != '~')
		{
			terminals2.push_back(terminal);
		}
	}
	++count;
	vector<rule> rules2;
	while (data[count].size() != 0 && count < data.size())
	{
		string current = data[count];
		rule r;
		r.from = current[0];
		r.is_ending = current[1] == '.';
		for (int i = 3; i < current.size(); i += 2)
		{
			r.to.push_back(current[i]);
		}
		rules2.push_back(r);
		++count;
	}

	//algorithm itself
	int length = min(rules1.size(), rules2.size());
	bool result = true;
	if ((rules1[0].is_ending && !rules2[0].is_ending) || (rules2[0].is_ending && !rules1[0].is_ending))
	{
		result = false;
	}
	else
	{
		pair<rule, rule> start;
		start.first = rules1[0]; start.second = rules2[0];
		vector<pair<rule, rule>> pairs;
		set<pair<rule, rule>> pairs_set;
		pairs.push_back(start); pairs_set.emplace(start);
		while (!pairs.empty() && result)
		{
			pair<rule, rule> prev = pairs.back();
			pairs.pop_back();
			for (int j = 0; j < terminals1.size(); ++j)
			{
				char terminal = terminals1[j];
				int ind2 = distance(terminals2.begin(), find(terminals2.begin(), terminals2.end(), terminal));
				pair<rule, rule> running;
				char first_start = prev.first.to[j];
				rule run_fst;
				for (auto rule : rules1)
				{
					if (rule.from == first_start)
					{
						run_fst = rule;
						break;
					}
				}
				running.first = run_fst;
				char second_start = prev.second.to[ind2];
				rule run_scnd;
				for (auto rule : rules2)
				{
					if (rule.from == second_start)
					{
						run_scnd = rule;
						break;
					}
				}
				running.second = run_scnd;
				if ((running.first.is_ending && !running.second.is_ending) || (running.second.is_ending && !running.first.is_ending))
				{
					result = false;
					break;
				}
				if (pairs_set.find(running) == pairs_set.end())
				{
					pairs.push_back(running);
					pairs_set.emplace(running);
				}
			}
		}
	}
	cout << "Result: " << result << endl;
	system("pause");
	return 1;
}