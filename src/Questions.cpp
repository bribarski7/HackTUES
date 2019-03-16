struct Question {
	string question;
	string answers[3];
};

struct QuestionPack {
	vector<Question> questions;
	string difficulty;

};

struct Category {
	vector<QuestionPack> packs;
	string name;
};

unsigned random(unsigned n) {
		unsigned index;
		if (n == 0) return 0;
		index = rand() % n;
		return index;
}

void getNonEmptyLine(istream& is, string& line){
	while (!is.eof()) {
		getline(is, line);
		for(size_t i = 0; i < line.size(); i++){
			if(line[i] != ' ' && line[i] != '\t')
			return;
		}
	}
}

vector<Category> load_questions()
{
    srand(time(NULL));
    fstream inFile;
    inFile.open("res/Questions.txt");
    if (inFile.fail()) {
		cerr << "Error opening file!";
		exit(1);
	}

	vector<Category> categories;
	string line;

	getNonEmptyLine(inFile, line);
	while (!inFile.eof()) {
		Category category;
		category.name = line;
		getNonEmptyLine(inFile, line);
		if(inFile.eof()) break;

		while (!inFile.eof())
		{
			if (line.substr(0, 2) != "  ") break;

			QuestionPack difficulty;
			difficulty.difficulty = line;

			while (!inFile.eof()) {
				getNonEmptyLine(inFile, line);
				if(inFile.eof()) break;
				if (line.substr(0, 4) != "    ") break;

				Question question;
				question.question = line;
				getNonEmptyLine(inFile, question.answers[0]);
				getNonEmptyLine(inFile, question.answers[1]);
				getNonEmptyLine(inFile, question.answers[2]);

				difficulty.questions.push_back(question);
			}

			category.packs.push_back(difficulty);
		}

		categories.push_back(category);
	}

	 return categories;
}

Question getRandomQuestion(vector<Category> categories)
{
	Category rcategory = categories[random(categories.size())];
	QuestionPack rpack = rcategory.packs[random(rcategory.packs.size())];
	Question rquestion = rpack.questions[random(rpack.questions.size())];

	return rquestion;
}