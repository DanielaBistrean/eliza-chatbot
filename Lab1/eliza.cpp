#include <iostream>
#include <string.h>
#include <cstddef>
#include <cctype>
#include <utility>
#include <vector>
#include <stdlib.h>

#include "initial_message.h"

std::vector <std::pair <std::string, std::vector <std::string>>> vRules = 
{
	{
		"hello",
		{
			"How do you do. Please state your problem."
		}
	},
	{
		"computer",
		{
			"Do computers worry you?",
			"What do you think about machines?",
			"Why do you mention computers?",
			"What do you think machines have to do with your problem?"
		}
	},
	{
		"name",
		{
			"I am not interested in names"
		}
	},
	{
		"sorry",
		{
			"Please don't apologize",
			"Apologies are not necessary",
			"What feelings do you have when you apologize"
		}
	},
	{
		"remember",
		{
			"Do you often think of #~#",
			"Does thinking of #~# bring anything else to mind?",
			"What else do you remember",
			"Why do you recall #~# right now?",
			"What in the present situation reminds you of #~#",
			"What is the connection between me and #~#"
		}
	}

};

std::string
remove_punctuation(const std::string &sentence)
{
	std::string out{sentence};
	int len = sentence.size();
	
	for (int i = 0; i < len; i++)
	{
		if (ispunct(out[i]))
			out[i] = ' ';
	}

	return out;
}

ssize_t
findPattern (const std::string &sentence, const std::string &pattern)
{
	std::string tmp = " " + sentence + " ";

	auto found = tmp.find(" " + pattern + " ");

	if (found != std::string::npos)
		 return found;

	return -1;
}


int
main(int argc, char const *argv[])
{
	initial_message();
	
	while (1)
	{

		std::string input;
		std::string output = "I don't understand";

		std::cout << "ELIZA> ";
		getline(std::cin, input);

		std::string rmv = remove_punctuation(input);

		for (auto rule : vRules)
		{
			auto found = findPattern (rmv, rule.first);

			if (found >= 0)
			{
				auto dim = rule.first.length() + 1;
				auto startSec = found + dim;
				int r = rand() % rule.second.size();
				output = rule.second[r];

				auto it = output.find("#~#");
				if (it != std::string::npos)
				{
					std::string r = std::string(input.begin() + startSec, input.end());
					output.replace(it, 3, r);
				}

				break;
			}
		}

		std::cout << output << "\n";
	}

	return 0;
}