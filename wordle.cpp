// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

bool isEnglish(const std::string& word, const std::set<std::string>& dict);

char* first_blank(std::string& str);

void wordle_helper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& out
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict
) {
		std::set<std::string> out;
		if (in.length() == 0) return out;
		int num_blanks = 0;
		for (const char& ch : in) {
			if (ch == '-') num_blanks ++;
		}
		if (num_blanks < floating.length()) return out;
		wordle_helper(in, floating, dict, out);
    return out;
}

// Define any helper functions here

bool isEnglish(const std::string& word, const std::set<std::string>& dict) {
    return (dict.find(word) != dict.end());
}

char* first_blank(std::string& str) {
	const size_t index = str.find('-');
	if (index == std::string::npos) return nullptr;
	return &(str.at(index));
}

void wordle_helper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
		std::set<std::string>& out
) {
	std::string new_in = in;

	if (floating.length() > 0) {
		// cout << "new_in: " << new_in << ", floating: " << floating << '\n';
		for (size_t i = 0; i < new_in.length(); i ++) {
			char& ch = new_in[i];
			if (ch == '-') {
				ch = floating.back();
				wordle_helper(new_in, floating.substr(0, floating.length() - 1), dict, out);
				ch = '-';
			}
		}
	} else {
		char* blank = first_blank(new_in);
		if (blank != nullptr) {
			for (char i = 'a'; i <= 'z'; i ++) {
				*blank = i;
				wordle_helper(new_in, floating, dict, out);
			}
			*blank = '-';
		} else {
			if (isEnglish(new_in, dict)) {
				out.insert(new_in);
			}
		}
	}
}