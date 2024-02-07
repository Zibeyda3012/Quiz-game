#pragma once


class Person
{
	string _fullname;
public:
	Person(string fullname)
	{
		SetFullName(fullname);
	}

	void SetFullName(string fullname)
	{
		if (fullname.size() < 5) throw length_error("fullname must contain at least 5 symbols");
		this->_fullname = fullname;
	}

	string GetFullName() { return _fullname; }

};



class Admin :public Person
{
	string _username;
	string _password;

public:
	Admin(string fullname, string username, string password) :Person(fullname)
	{
		SetUsername(username);
		SetPassword(password);
	}

	void SetUsername(string username)
	{
		if (username.size() < 5) throw length_error("username must contain at least 5 symbols!!!");
		if (!(username[0] >= 65 && username[0] <= 90)) throw invalid_argument("first symbol of username must be uppercase letter!!!");
		this->_username = username;
	}

	void SetPassword(string password)
	{
		if (password.size() < 5) throw length_error("password must contain at least 5 symbols!!!");
		this->_password = password;

	}

	string GetUsername() { return _username; }
	string GetPassword() { return _password; }
};



class Player :public Person
{
	string _qName;
	int _correct;
	int _incorrect;
	int _pass;

public:

	Player(string fullname, string quizName, int correct, int incorrect, int pass) :Person(fullname)
	{
		this->_qName = quizName;
		this->_correct = correct;
		this->_incorrect = incorrect;
		this->_pass = pass;
	}

	int GetCorrect() { return _correct; }
	int GetIncorrect() { return _incorrect; }
	int GetPass() { return _pass; }
	string GetQuizName() { return _qName; }

	void print()
	{
		cout << "*****Result*****" << endl << endl;
		cout << "Player Name: " << Person::GetFullName() << endl;
		cout << "Correct answers: " << GetCorrect() << endl;
		cout << "Incorrect aswers: " << GetIncorrect() << endl;
		cout << "Pass: " << GetPass() << endl;
	}

};



class Question
{
	string _question;
	string _correct_answer;
	string _variant_1;
	string _variant_2;
	string _variant_3;

public:

	list<string> Variants;
	Question(string question, string correct_answer, string variant_1, string variant_2, string variant_3)
	{
		SetQuestion(question);
		SetCorrectAnswer(correct_answer);
		SetVariant_1(variant_1);
		SetVariant_2(variant_2);
		SetVariant_3(variant_3);
		SetVariants(correct_answer, variant_1, variant_2, variant_3);
	}

	void SetQuestion(string question)
	{
		if (question.size() < 1) throw invalid_argument("question is not given!!!");
		this->_question = question;
	}

	void SetCorrectAnswer(string answer)
	{
		if (answer.size() < 1) throw invalid_argument("correct answer is not given!!!");
		this->_correct_answer = answer;
	}

	void SetVariant_1(string variant_1)
	{
		if (variant_1.size() < 1) throw invalid_argument("variant is not given!!!");
		this->_variant_1 = variant_1;
	}

	void SetVariant_2(string variant_2)
	{
		if (variant_2.size() < 1) throw invalid_argument("variant is not given!!!");
		this->_variant_2 = variant_2;
	}

	void SetVariant_3(string variant_3)
	{
		if (variant_3.size() < 1) throw invalid_argument("variant is not given!!!");
		this->_variant_3 = variant_3;
	}

	void SetVariants(string var_1, string var_2, string var_3, string var_4)
	{
		Variants.push_back(var_1);
		Variants.push_back(var_2);
		Variants.push_back(var_3);
		Variants.push_back(var_4);
	}

	string GetCorrectVariant() { return _correct_answer; }
	string GetVariant_1() { return _variant_1; }
	string GetVariant_2() { return _variant_2; }
	string GetVariant_3() { return _variant_3; }
	string GetQuestion() { return _question; }

	list<string> ShuffleVariants()
	{
		srand(time(0));
		list<string>newlist;
		list<int>indexes;
		int counter = 0;
		while (counter < 4)
		{
			bool found = 0;
			int index = rand() % 4;
			for (auto i : indexes)
				if (i == index)
					found = 1;
			if (!found)

			{
				auto it = next(Variants.begin(), index);
				newlist.push_back(*it);
				indexes.push_back(index);
				counter++;
			}
		}
		newlist.push_back("pass");
		Variants = newlist;
		return Variants;
	}

};



class QuizNames
{
	string _quizName;
public:
	QuizNames(string quizName)
	{
		SetQuizName(quizName);
	}

	void SetQuizName(string name)
	{
		if (name.size() < 0)
			throw invalid_argument("quiz name is not given!!!");
		this->_quizName = name;
	}

	string GetQuizName() { return _quizName; }

	friend ostream& operator<<(ostream& print, const QuizNames& other);

};

ostream& operator<<(ostream& print, const QuizNames& other)
{
	print << other._quizName << endl;
	return print;
}



class Quiz
{
	string _quizName;
	list<Question> questions;
	Player** players = nullptr;
	Admin** admins = nullptr;
	QuizNames** Names = nullptr;
	int player_count = 0; //oyuncu sayi
	int size; //question sayi
	int quiz_count = 0;//quiz sayi

public:

	Quiz()
	{
		questions;
		size = 0;
	}
	//Quiz Name

	int GetQuizCount() { return quiz_count; }

	QuizNames** GetQuizNames() { return Names; }

	void AddQuizNames(QuizNames* quizName)
	{
		if (quiz_count == 0)
		{
			Names = new QuizNames * [1];
			Names[0] = quizName;
			quiz_count++;
		}

		else
		{
			QuizNames** newQuizNames = new QuizNames * [quiz_count + 1];
			for (size_t i = 0; i < quiz_count; i++)
			{
				newQuizNames[i] = Names[i];
			}
			newQuizNames[quiz_count] = quizName;
			quiz_count++;

			delete[] Names;
			Names = newQuizNames;
		}
	}

	void WriteQuizNamesToFile(string file, string quiz_name)
	{
		ofstream quizName_file(file, ios::app);

		if (quizName_file.is_open())
		{
			quizName_file << quiz_name << endl;
			quizName_file.close();
		}

		else
			cout << "file couldn't be opened" << endl;
	}


	QuizNames** ReadQuizNamesFromFile(string file)
	{
		ifstream quizName_file(file, ios::in);

		if (quizName_file.is_open())
		{
			string quiz_name = "";
			int index = 0;
			QuizNames** newQuizNames = new QuizNames * [index] {};

			while (!quizName_file.eof())
			{
				if (!quizName_file.eof())
				{
					getline(quizName_file, quiz_name);
					QuizNames* qName = new QuizNames(quiz_name);
					AddQuizNames(qName);
				}
			}

			quizName_file.close();
			return newQuizNames;

		}

		else
		{
			cout << "file couldn't be opened" << endl;
			return nullptr;
		}
	}

	void printQuizNames()
	{
		for (size_t i = 0; i < quiz_count; i++)
			cout << *(Names[i]) << endl;
	}


	//Admin

	void AddAdmin(Admin* admin)
	{
		if (admin_count == 0)
		{
			admins = new Admin * [1];
			admins[0] = admin;
			admin_count++;
		}

		else
		{
			Admin** newAdmins = new Admin * [admin_count + 1];
			for (size_t i = 0; i < admin_count; i++)
			{
				newAdmins[i] = admins[i];
			}
			newAdmins[admin_count] = admin;
			admin_count++;

			delete[] admins;
			admins = newAdmins;
		}
	}

	bool checkAdmin(string username)
	{
		for (size_t i = 0; i < admin_count; i++)
			if (admins[i]->GetUsername() == username)
				return true;
		return false;
	}

	bool adminLogin(string username, string password)
	{
		for (size_t i = 0; i < admin_count; i++)
			if (admins[i]->GetUsername() == username && admins[i]->GetPassword() == password)
				return true;

		return false;
	}


	//questions

	list<Question> Read_Questions_From_File(string file, int& count)
	{
		srand(time(0));
		ifstream f(file, ios::in);
		list<Question> newQuestion;
		if (f.is_open())
		{
			string question = "";
			string correct_variant = "";
			string variant_1 = "";
			string variant_2 = "";
			string variant_3 = "";
			while (!f.eof())
			{
				getline(f, question, '~');
				getline(f, correct_variant, '~');
				getline(f, variant_1, '~');
				getline(f, variant_2, '~');
				getline(f, variant_3, '~');
				if (f.eof())break;
				Question* q = new Question(question, correct_variant, variant_1, variant_2, variant_3);
				int a = 1 + rand() % 4;
				if (a == 1)
					newQuestion.push_back(*q);
				else if (a == 2)
				{
					if (!newQuestion.empty())
					{
						auto it = newQuestion.begin();
						advance(it, newQuestion.size() / 2);
						newQuestion.insert(it, *q);
					}
					else
						newQuestion.push_front(*q);
				}

				else
					newQuestion.push_front(*q);
				count++;
			}

			f.close();
		}

		else
		{
			cout << "file is not opened";
		}
		return newQuestion;
	}

	void WriteQuestionsToFile(string file)
	{
		ofstream f(file, ios::out);

		if (!f.is_open())
		{
			cout << "file is not opened" << endl;
			return;
		}

		if (questions.size() != 0)
		{
			for (auto i : questions)
			{
				f << i.GetQuestion() << "~" << i.GetCorrectVariant() << "~" << i.GetVariant_1() << "~" << i.GetVariant_2() << "~" << i.GetVariant_3() << "~" << endl;
			}

			f.close();
		}
		else
			cout << "questions are null";
	}

	void AddQuestion(Question* question)
	{
		questions.push_back(*question);
		size++;
	}

	bool CheckQuestion(Question* question)
	{
		for (size_t i = 0; i < size; i++)
			if (question[i].GetQuestion() == question->GetQuestion())
				return true;

		return false;
	}

	bool CheckQuizName(string quiz_name)
	{
		if (quiz_name.size() < 3) return false;
		return true;
	}

	void printCreateQuizOptions(int select)
	{
		string arr[3] = { "New","Back","Save" };

		cout << endl;
		for (size_t i = 0; i < 3; i++)
		{
			if (i == select - 1)
				cout << yellow << arr[i] << white << endl;
			else
				cout << arr[i] << endl;
		}
	}

	void CreateQuizOptions()
	{
		int num;

		int choice = 1;
		printCreateQuizOptions(choice);


		while (true)
		{

			num = _getch();

			//arrow
			if (num == 224)
			{
				num = _getch();

				if (num == 80)  //down arrow
				{
					if (choice < 3)
						choice++;

					else if (choice == 3)
						choice = 1;
				}

				else if (num == 72)  //up arrow
				{
					if (choice > 1)
						choice--;

					else if (choice == 1)
						choice = 3;
				}
			}

			//w
			else if (num == 119)
			{
				if (choice > 1)
					choice--;

				else if (choice == 1)
					choice = 3;

			}

			//s
			else if (num == 115)
			{
				if (choice < 3)
					choice++;

				else if (choice == 3)
					choice = 1;

			}


			//enter
			else if (num == 13)
			{
				if (choice == 1) //new
				{
					create_quiz_choice = 1;
					return;
				}


				else if (choice == 2) //back
				{
					create_quiz_choice = 2;
					return;
				}


				else if (choice == 3) //save
				{
					create_quiz_choice = 3;
					return;
				}


			}

			system("cls");
			printCreateQuizOptions(choice);
		}

	}

	void CreateQuiz()
	{
		string quizName;
		string question, var_1, var_2, var_3, var_4;

		cout << "enter quiz name: ";
		getline(cin, quizName);

		if (!CheckQuizName(quizName))
			throw invalid_argument("quiz name is not given");
		else
			_quizName = quizName;


		do
		{
			cout << "enter question: ";
			getline(cin, question);
			cout << "enter correct variant: ";
			getline(cin, var_1);
			cout << "enter incorrect variant: ";
			getline(cin, var_2);
			cout << "enter incorrect variant: ";
			getline(cin, var_3);
			cout << "enter incorrect variant: ";
			getline(cin, var_4);

			AddQuestion(new Question(question, var_1, var_2, var_3, var_4));

			CreateQuizOptions();

			if (create_quiz_choice == 1) //new
				continue;
			else if (create_quiz_choice == 2) //back
				return;
			else if (create_quiz_choice == 3) //save
			{
				WriteQuestionsToFile(_quizName);
				QuizNames* qName = new QuizNames(_quizName);
				AddQuizNames(qName);
				WriteQuizNamesToFile(QuizName_file, _quizName);

				return;
			}

		} while (true);


	}


	//Player
	void AddPlayer(Player* player)
	{
		if (this->player_count == 0)
		{
			this->players = new Player * [1];
			players[0] = player;
			player_count++;
		}

		else
		{
			Player** nPlayers = new Player * [player_count + 1];
			for (size_t i = 0; i < player_count; i++)
			{
				nPlayers[i] = players[i];
			}
			nPlayers[player_count] = player;
			player_count++;

			delete[] players;
			players = nPlayers;
		}
	}

	void printResult(Player* player)
	{
		cout << endl << endl;
		player->print();
	}

	void WritePlayerResultoFile(string file, string username, string quiz_name, int correct, int incorrect, int pass)
	{
		fstream f(file, ios::app);
		if (!f.is_open())
		{
			cout << "file is not opened" << endl;
			return;
		}
		f << username << "~" << quiz_name << "~" << correct << "~" << incorrect << "~" << pass << "~" << endl;
		f.close();

	}


	Player** ReadPlayerResultFromFile(string file, int& size)
	{
		{
			ifstream f(file, ios::in);

			if (f.is_open())
			{
				string qName = "";
				string name = "";
				string correct = "";
				string incorrect = "";
				string pass = "";

				int player_count = 0;

				Player** newPlayers = new Player * [player_count] {};

				while (!f.eof())
				{
					getline(f, name, '~');
					if (f.eof())break;
					getline(f, qName, '~');
					getline(f, correct, '~');
					getline(f, incorrect, '~');
					getline(f, pass, '~');

					Player* player = new Player(name, qName, stoi(correct), stoi(incorrect), stoi(pass));
					AddPlayer(player);
					size++;
				}

				f.close();
				this->player_count = player_count;

				return newPlayers;

			}

			else
			{
				cout << "file is not opened";
				return nullptr;
			}
		}
	}

	void ShowAllPlayers()
	{
		for (size_t i = 0; i < player_count; i++)
		{
			cout << endl;
			players[i]->print();
		}

	}

	//LeaderBoard

	void DeleteElement(Player**& arr, int& count, int it)
	{
		Player** newArr = new Player * [count - 1];
		int index = 0;

		for (size_t i = 0; i < count; i++)
		{
			if (i == it)
				continue;
			else
				newArr[index++] = arr[i];
		}

		delete[] arr;
		arr = newArr;
		count--;
	}

	void printLeaderBoard(string quizName)
	{
		fstream f(Player_file, ios::in);
		if (!f.is_open())
		{
			cout << "File is not open" << endl;
			return;
		}
		int size = 0;
		ReadPlayerResultFromFile(Player_file, size);
		Player** newList = new Player * [size];
		string qName = "";
		string name = "";
		string correct = "";
		string incorrect = "";
		string pass = "";
		int l = 0;
		while (!f.eof())
		{
			getline(f, name, '~');
			if (f.eof())break;
			getline(f, qName, '~');
			getline(f, correct, '~');
			getline(f, incorrect, '~');
			getline(f, pass, '~');
			if (qName != quizName)continue;
			Player* player = new Player(name, qName, stoi(correct), stoi(incorrect), stoi(pass));
			newList[l++] = player;
		}
		int iterator = 0;
		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < l - i - 1; j++)
			{
				if (newList[j]->GetCorrect() < newList[j + 1]->GetCorrect())
				{
					auto temp = newList[j];
					newList[j] = newList[j + 1];
					newList[j + 1] = temp;
				}
			}
		}
		cout << endl;
		for (int i = 0; i < 10 && i < l; i++)
		{
			string name = newList[i]->GetFullName();
			cout << endl << name;
			for (int s = 0; s < 10 - (name.size()); s++)
				cout << " ";
			cout << (i != 0 ? " " : "");
			cout << "  " << newList[i]->GetCorrect() << "  "
				<< newList[i]->GetIncorrect() << "  " << newList[i]->GetPass() << endl;
		}
		if (newList)
		{
			for (int i = 0; i < l; i++)
				if (newList[i])
					delete newList[i];
			delete[] newList;
		}


	}


	//Game

	bool checkAnswer(Question question, string answer)
	{
		if (answer == question.GetCorrectVariant())
			return true;
		return false;
	}


	list<Question> ShuffleQuestions(list<Question>& newquestion, int count)
	{

		srand(time(0));
		list<Question>newlist;
		list<int>indexes;
		int counter = 0;
		while (counter < count)
		{
			bool found = 0;
			int index = rand() % count;
			for (auto i : indexes)
				if (i == index)
					found = 1;
			if (!found)

			{
				auto it = next(questions.begin(), index);
				newlist.push_back(*it);
				indexes.push_back(index);
				counter++;
			}
		}

		return newlist;

	}


	void printVariants(int select, Question* question)
	{
		int count = 0;
		for (auto i : question->Variants)
		{
			if (count == select - 1)
				cout << red << i << white << endl;
			else
				cout << i << endl;
			count++;
		}
	}


	void printGameChoiceOptions(int select)
	{
		string arr[3] = { "Next","Previous","Submit" };

		cout << endl;
		for (size_t i = 0; i < 3; i++)
		{
			if (i == select - 1)
				cout << yellow << arr[i] << white << endl;
			else
				cout << arr[i] << endl;
		}
	}


	int GameChoiceOptions()
	{
		int num;

		int choice = 1;
		printGameChoiceOptions(choice);

		while (true)
		{
			num = _getch();

			//arrow
			if (num == 224)
			{
				num = _getch();

				if (num == 80)  //down arrow
				{
					if (choice < 3)
						choice++;

					else if (choice == 3)
						choice = 1;
				}

				else if (num == 72)  //up arrow
				{
					if (choice > 1)
						choice--;

					else if (choice == 1)
						choice = 3;
				}
			}

			//w
			else if (num == 119)
			{
				if (choice > 1)
					choice--;

				else if (choice == 1)
					choice = 3;

			}

			//s
			else if (num == 115)
			{
				if (choice < 3)
					choice++;

				else if (choice == 3)
					choice = 1;

			}


			//enter
			else if (num == 13)
			{
				if (choice == 1) //Next
				{
					return 1;
				}

				else if (choice == 2) //Prev
				{
					return -1;
				}

				else if (choice == 3) //submit
				{
					return 0;
				}

			}

			system("cls");
			printGameChoiceOptions(choice);
		}

	}


	void print(Question question, int& pass_count, string name)
	{
		cout << question.GetQuestion() << endl << endl;
		question.ShuffleVariants();
		int num;
		int choice = 1;
		printVariants(choice, &question);

		while (true)
		{
			num = _getch();

			//arrow
			if (num == 224)
			{
				num = _getch();

				if (num == 80)  //down arrow
				{
					if (choice < 5)
						choice++;

					else if (choice == 5)
						choice = 1;
				}

				else if (num == 72)  //up arrow
				{
					if (choice > 1)
						choice--;

					else if (choice == 1)
						choice = 5;
				}
			}

			//w
			else if (num == 119)
			{
				if (choice > 1)
					choice--;

				else if (choice == 1)
					choice = 5;

			}

			//s
			else if (num == 115)
			{
				if (choice < 5)
					choice++;

				else if (choice == 5)
					choice = 1;

			}


			//enter
			else if (num == 13)
			{
				auto i = question.Variants.begin();
				if (choice == 5) //pass
				{
					pass_count++;
					break;
				}

				for (size_t k = 0; k < choice - 1; k++)
					i++;


				my_answer = (*i);
				break;

			}

			system("cls");
			cout << question.GetQuestion() << endl << endl;
			printVariants(choice, &question);
		}

	}


	void StartGame()
	{
		string name, quiz_name;
		int pass_count = 0;
		int correct = 0;
		int incorrect = 0;

		cout << "enter you name: ";
		getline(cin, name);

		if (name.size() < 0) throw invalid_argument("Person name is not given!!!");

		cout << "enter quiz name: ";
		getline(cin, quiz_name);
		int count = 0;
		list<Question>newquestion = Read_Questions_From_File(quiz_name, count);
		//ShuffleQuestions(newquestion, count);

		for (auto i = newquestion.begin(); i != newquestion.end();)
		{
			print(*i, pass_count, name);
			if (checkAnswer(*i, my_answer))
				correct++;
			else
				incorrect++;

			int step = GameChoiceOptions();

			if (step == 1) //next
			{
				if (i != (newquestion.end()))
				{
					i++;
					if (i == newquestion.end())
					{
						cout << "you have reached the final question,if you want to finish please enter ~next~ or ~submit~,if you want to continue answering questions enter ~previous~" << endl;
						int a = GameChoiceOptions();


						if (a == 0 || a == 1)
						{
							Player* player = new Player(name, quiz_name, correct, incorrect, pass_count);
							AddPlayer(player);
							printResult(player);
							WritePlayerResultoFile(Player_file, name, quiz_name, correct, incorrect, pass_count);
							system("pause");
							return;
						}
						else
							i--;
					}

				}
			}

			else if (step == -1) //previous
			{
				if (i != newquestion.begin())
					i--;
			}

			else if (step == 0) //submit
			{
				Player* player = new Player(name, quiz_name, correct, incorrect, pass_count);
				AddPlayer(player);
				printResult(player);
				WritePlayerResultoFile(Player_file, name, quiz_name, correct, incorrect, pass_count);
				system("pause");
				return;
			}
		}

	}


	~Quiz()
	{

		if (players != nullptr)
		{
			for (size_t i = 0; i < player_count; i++)
				delete players[i];

			delete[] players;
		}

		if (admins != nullptr)
		{
			for (size_t i = 0; i < admin_count; i++)
				delete admins[i];

			delete[] admins;
		}

		if (Names != nullptr)
		{
			for (size_t i = 0; i < quiz_count; i++)
				delete Names[i];

			delete[] Names;
		}
	}
};