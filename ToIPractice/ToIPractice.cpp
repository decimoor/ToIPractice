#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

struct LetterProbCode {
	std::string letter;
	float prob;
	std::string code;

};

bool compareByProb(LetterProbCode& left, const LetterProbCode& right) {
	return left.prob > right.prob;
}

void putCode(std::vector<LetterProbCode>::iterator it, unsigned int numOfElements, float totalProb) {

	if(numOfElements > 1) {

		float probSum = 0;
		int nElements = 0;

		std::vector<LetterProbCode>::iterator firstPart = it;

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
		putCode(firstPart, nElements, totalProb / 2);
		putCode(secondPart, lengthOfSecondPart, totalProb / 2);

	}
}


int main() {

	std::setlocale(LC_ALL, "Russian");
	
	std::vector<LetterProbCode> alphabet;
	
	std::fstream file;
	file.open("input.txt", std::ios::in);
	if (file.is_open()) {
		
		std::string line;

		while (std::getline(file, line)) {
			try {
				if (line.substr(1, 1) != ":")
					throw std::exception();
				alphabet.push_back({ line.substr(0, 1), std::stof(line.substr(3)), ""});
			}
			catch (...) {
				std::cout << "В этой строке присутствует ошибка: " << line << std::endl;
				return 0;
			}
		}
	}
	else {
		std::cout << "Couldn't open file" << std::endl;
	}

	//checking input
	float totalProb = 0;
	for (unsigned int i = 0; i < alphabet.size(); i++) {
		totalProb += alphabet.at(i).prob;
	}

	if (totalProb != 1.00) {
		std::cout << "Вводные данные неверны: сумма всех вероятностей должна быть равна 1" << std::endl;
		std::cout << "Сумма всех вероятностей:  " << totalProb << std::endl;
		return 0;
	}

	std::sort(alphabet.begin(), alphabet.end(), compareByProb);
	putCode(alphabet.begin(), alphabet.size(), 1);

	for (unsigned int i = 0; i < alphabet.size(); i++) {
		std::cout << "Символ: " << alphabet.at(i).letter << " Вероятность: " << alphabet.at(i).prob << " Двоичный код: " << alphabet.at(i).code <<  std::endl;
	}
}