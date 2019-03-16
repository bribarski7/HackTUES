#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
char TestFile[] = "Test.txt";

char Mario[]= "Hack_Tues.txt";

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

