#include "Help.h"
int main()
{
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

	for (size_t category_i = 0; category_i < categories.size(); ++category_i)
	{
		Category c = categories[category_i];
		for (size_t pack_i = 0; pack_i < c.packs.size(); ++pack_i)
		{
			QuestionPack p = c.packs[pack_i];
			for (size_t question_i = 0; question_i < p.questions.size(); ++question_i) {
				Question q = p.questions[question_i];
				cout << q.question << endl;
				for (int i = 0; i < 3; i++) {
					cout << q.answers[i] << endl;
				}
			}
		}

	}

	return 0;
}