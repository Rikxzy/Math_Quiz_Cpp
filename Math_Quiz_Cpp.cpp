// Math_Quiz_Cpp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
#include <iostream>
#include<string>
#include<cmath>
using namespace std;

enum enQuestionLevel { Easy = 1 , Mid = 2, Hard = 3, Mix = 4 };
enum enOpType { add = 1 ,sub = 2, mul = 3 , Div = 4, Mix_op = 5 };

struct stQuizzQuestion
{
	short int Number1 = 0, Number2 = 0;
	enOpType OperationType;
	enQuestionLevel QuestionLevel;
	short int CorrectAnswer = 0, PlayerAnswer = 0;
	bool AnswerResults = 0;
};
struct stQuizz
{
	stQuizzQuestion QuizzQuestion[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionsLevel;
	enOpType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};
int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
	//srand((unsigned)time(NULL)); must write it once in main.
}
short ReadHowManyQst()
{
	short NumberOfQst;
	do
	{
		cout << "********** Welcome to the Math Quizz **********\t\n";
		cout << "Enter How Many Question Do You Want to Solve ? : ";
		cin  >> NumberOfQst;
	} while (NumberOfQst < 1);
	cout << "\n********** We Wish You Good Luck :) ***********\n";
	return NumberOfQst;
}

enQuestionLevel QstLvl()
{
	short QstLvl;
	do 
	{
		cout << "-----------------------------------------------\t\n";
		cout << "Enter Your Question Level ? : "<<endl;
		cout << "[1]-Easy  [2]-Mid  [3]-Hard  [4]-Mix :  ";
		cin >> QstLvl;
	} while (QstLvl < 1 || QstLvl > 4);

	return (enQuestionLevel )QstLvl;
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}
enOpType  OperationType()
{
	short OpType;
	do 
	{
		cout << "-----------------------------------------------\t\n";
		cout << "Enter Your Operation Type ? : "<<endl;
		cout << "[1]-Add  [2]-Sub  [3]-Mul  [4]-Div  [5]-Mix  :  ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);
	return (enOpType) OpType;
}
string GetOpTypeSymbol(enOpType OpType)
{
	switch (OpType)
	{
	case enOpType::add:
		return "+";
	case enOpType::sub:
		return "-";
	case enOpType::mul:
		return "x";
	case enOpType::Div :
		return "/";
	default:
		return "Mix";
	}
}
int SimpleCalculator(int Number1,int Number2,enOpType OpType)
{
	switch(OpType)
	{
	case enOpType::add :
		return Number1 + Number2;	
	case enOpType::sub:
		return Number1 - Number2;
	case enOpType::mul :
		return Number1 * Number2;
	case enOpType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}
enOpType GetRandomOpType()
{
	int op = RandomNumber(1, 4);
	return (enOpType)op;
}

stQuizzQuestion GenerateQuestion(enQuestionLevel QstLvl , enOpType Optype)   
{
	stQuizzQuestion Question;

	if (QstLvl == enQuestionLevel::Mix)
	{
		QstLvl = (enQuestionLevel)RandomNumber(1, 3);
	}
	if(Optype == enOpType::Mix_op)
	{
		Optype = (enOpType)RandomNumber(1, 4);
	}

	Question.OperationType = Optype;

	switch (QstLvl)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionLevel::Mid:
		Question.Number1 = RandomNumber(20, 60);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}
	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QstLvl;
	return Question;
}
void GenerateQuizzQuestions(stQuizz &Quizz)
{

	for(int Question = 0 ; Question < Quizz.NumberOfQuestions ; Question++ )
	{
		Quizz.QuizzQuestion[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
	
}

int readQstAnswer()
{
	int Answer;
	cout << "Your Answer ? = ";
	cin >> Answer;
	return Answer;
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]  : ";
		cout << Quizz.QuizzQuestion[QuestionNumber].Number1 << " "
			<< GetOpTypeSymbol(Quizz.QuizzQuestion[QuestionNumber].OperationType) << " "
			<< Quizz.QuizzQuestion[QuestionNumber].Number2 << " = ";

		cin >> Quizz.QuizzQuestion[QuestionNumber].PlayerAnswer;

		if (Quizz.QuizzQuestion[QuestionNumber].PlayerAnswer == Quizz.QuizzQuestion[QuestionNumber].CorrectAnswer)
		{
			cout << "Correct!\n";
			Quizz.NumberOfRightAnswers++;
		}
		else
		{
			cout << "Wrong! Correct Answer: " << Quizz.QuizzQuestion[QuestionNumber].CorrectAnswer << endl;
			Quizz.NumberOfWrongAnswers++;
		}
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}


void PlayMathGame()
{
	stQuizz GameQuizz;

	GameQuizz.NumberOfQuestions = ReadHowManyQst();
	GameQuizz.QuestionsLevel = QstLvl();
	GameQuizz.OpType = OperationType();

	GenerateQuizzQuestions(GameQuizz);
	AskAndCorrectQuestionListAnswers(GameQuizz);
	cout << "\nQuiz Completed! Right Answers: " << GameQuizz.NumberOfRightAnswers << ", Wrong Answers: " << GameQuizz.NumberOfWrongAnswers << "\n";

cout << (GameQuizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
	
	
}

void StartGame()
{
	char PlayAgain= 'Y';
	do 
	{
		system("color 0E");
		PlayMathGame();
		cout << "Do You Want To Play Again ^_^  : ";
		cin >> PlayAgain;
	}
	while (PlayAgain == 'y' || PlayAgain == 'Y');
	cout << "\n***********The End***********\n\n";
	system("color 4E");
}


int main()
{
	//srand((unsigned)time(NULL)); must write it once in main.
	srand((unsigned)time(NULL));

	StartGame();	
}
