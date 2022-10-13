#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <set>
#include <map>
#include <ctype.h>

struct LetterProbCode {
	std::string letter;
	float prob;
	std::string code;

};

bool compareByProb(LetterProbCode& left, const LetterProbCode& right) {
	return left.prob > right.prob;
}

void putCode(std::vector<LetterProbCode>::iterator it, unsigned int numOfElements) {

	if(numOfElements > 1) {

		std::vector<LetterProbCode>::iterator firstPart = it;
		float totalProb = 0;
		for (int i = 0; i < numOfElements; i++) {
			totalProb += it->prob;
			it++;
		}

		float probSum = 0;
		int nElements = 0;

		it = firstPart;

		while (probSum < totalProb / 2) {
			probSum += it->prob;
			it->code += "1";
			it++;
			nElements++;
		}
		
		std::vector<LetterProbCode>::iterator secondPart = it;

		unsigned int lengthOfSecondPart = numOfElements - nElements;
		for (unsigned int i = 0; i < lengthOfSecondPart; i++) {
			it->code += "0";
			it++;
		}
		putCode(firstPart, nElements);
		putCode(secondPart, lengthOfSecondPart);

	}
}


int main() {

	// modes: 0 - letters with probs, 1 - text
	int mode = 0;

	std::setlocale(LC_ALL, "Russian");
	
	std::vector<LetterProbCode> alphabet;
	std::map<char, int> lettersCount;
	int totalChars = 0;
	
	std::fstream file;
	file.open("input.txt", std::ios::in);
	if (file.is_open()) {
		
		std::string line;
		std::getline(file, line);
		mode = std::stoi(line);

		if (mode == 0) {
			while (std::getline(file, line)) {
				try {
					if (line.substr(1, 1) != ":")
						throw std::exception();
					alphabet.push_back({ line.substr(0, 1), std::stof(line.substr(3)), "" });
				}
				catch (...) {
					std::cout << "В этой строке присутствует ошибка: " << line << std::endl;
					return 0;
				}
			}
		}
		else {
			std::set<char> chars;
			 
			while (std::getline(file, line)) {
				for (int i = 0; i < line.length(); i++) {
					std::set<char> arr = {' ', ',', '!', '?', '-', '_', '.', '—'};
					if (arr.find(line[i]) == arr.end())
					{
						totalChars++;
						if (chars.find(std::tolower(line[i])) == chars.end()) {
							chars.insert(std::tolower(line[i]));
							lettersCount[std::tolower(line[i])] = 1;
						}
						else {
							lettersCount[std::tolower(line[i])]++;
						}
					}
				}
			}
		}

	}
	else {
		std::cout << "Couldn't open file" << std::endl;
	}

	//checking input
	if (mode == 0) {


		float totalProb = 0;
		for (unsigned int i = 0; i < alphabet.size(); i++) {
			totalProb += alphabet.at(i).prob;
		}

		if (totalProb != 1.00) {
			std::cout << "Вводные данные неверны: сумма всех вероятностей должна быть равна 1" << std::endl;
			std::cout << "Сумма всех вероятностей:  " << totalProb << std::endl;
			return 0;
		}

		
	}
	else {
		for (std::map<char, int>::iterator i = lettersCount.begin(); i != lettersCount.end(); i++) {
			alphabet.push_back({ std::string(1, i->first), i->second / (float)totalChars, "" });
		}
	}

	std::sort(alphabet.begin(), alphabet.end(), compareByProb);
	putCode(alphabet.begin(), alphabet.size());

	for (unsigned int i = 0; i < alphabet.size(); i++) {
		std::cout << "Символ: " << alphabet.at(i).letter << " Вероятность: " << alphabet.at(i).prob << " Двоичный код: " << alphabet.at(i).code << std::endl;
	}

	while (std::getchar() != '\n');

}