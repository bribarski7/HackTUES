#include "Help.h"
unsigned random(unsigned n) {
		unsigned index;
		if (n == 0) n++;
		index = rand() % n;
		return index;
}
int main()
{
   srand(time(NULL));

	fstream inFile;
	inFile.open("Hack_TUES.txt");
	if (inFile.fail()) {
		cerr << "Error opening file!";
		exit(1);
	}
	vector<Category> categories;


	string line;

	getline(inFile, line);
	while (!inFile.eof()) {
		Category category;
		category.name = line;
		getline(inFile, line);

		while (!inFile.eof())
		{
			if (line.substr(0, 2) != "  ") break;

			QuestionPack difficulty;
			difficulty.difficulty = line;

			while (!inFile.eof()) {
				getline(inFile, line);
				if (line.substr(0, 4) != "    ") break;

				Question question;
				question.question = line;
				getline(inFile, question.answers[0]);
				getline(inFile, question.answers[1]);
				getline(inFile, question.answers[2]);

				difficulty.questions.push_back(question);
			}

			category.packs.push_back(difficulty);
		}

		categories.push_back(category);
	}

	Category rcategory = categories[random(categories.size())];
	QuestionPack rpack = rcategory.packs[random(rcategory.packs.size())];
	Question rquestion = rpack.questions[random(rpack.questions.size())];
	cout << rquestion.question << endl;
	cout << rquestion.answers[0] << endl;
	cout << rquestion.answers[1] << endl;
	cout << rquestion.answers[2] << endl;
	return 0;
}