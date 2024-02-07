#pragma once

void start()
{
	Admin* NewAdmin = new Admin("Zibeyda Musayeva", "Admin", "admin");
	int size = 0;
	q.AddAdmin(NewAdmin);
	q.ReadQuizNamesFromFile(QuizName_file);
	q.ReadPlayerResultFromFile(Player_file, size);
}

void QuizVisuals()
{
	string text = R"(

                                                                                                                   
                                               ,----,                                             ____             
    ,----..                      ,---,       .'   .`|          ,----..      ,---,               ,'  , `.    ,---,. 
   /   /   \             ,--, ,`--.' |    .'   .'   ;         /   /   \    '  .' \           ,-+-,.' _ |  ,'  .' | 
  /   .     :          ,'_ /| |   :  :  ,---, '    .'        |   :     :  /  ;    '.      ,-+-. ;   , ||,---.'   | 
 .   /   ;.  \    .--. |  | : :   |  '  |   :     ./         .   |  ;. / :  :       \    ,--.'|'   |  ;||   |   .' 
.   ;   /  ` ;  ,'_ /| :  . | |   :  |  ;   | .'  /          .   ; /--`  :  |   /\   \  |   |  ,', |  '::   :  |-, 
;   |  ; \ ; |  |  ' | |  . . '   '  ;  `---' /  ;           ;   | ;  __ |  :  ' ;.   : |   | /  | |  ||:   |  ;/| 
|   :  | ; | '  |  | ' |  | | |   |  |    /  ;  /            |   : |.' .'|  |  ;/  \   \'   | :  | :  |,|   :   .' 
.   |  ' ' ' :  :  | | :  ' ; '   :  ;   ;  /  /--,          .   | '_.' :'  :  | \  \ ,';   . |  ; |--' |   |  |-, 
'   ;  \; /  |  |  ; ' |  | ' |   |  '  /  /  / .`|          '   ; : \  ||  |  '  '--'  |   : |  | ,    '   :  ;/| 
 \   \  ',  . \ :  | : ;  ; | '   :  |./__;       :          '   | '/  .'|  :  :        |   : '  |/     |   |    \ 
  ;   :      ; |'  :  `--'   \;   |.' |   :     .'           |   :    /  |  | ,'        ;   | |`-'      |   :   .' 
   \   \ .'`--" :  ,      .-./'---'   ;   |  .'               \   \ .'   `--''          |   ;/          |   | ,'   
    `---`        `--`----'            `---'                    `---`                    '---'           `----'     
                                                                                                                   


)";

	cout << orange << text << white << endl;
}

void About_Game()
{
	system("cls");
	string aboutTitle = { " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ About Quiz Game ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " };
	string aboutText = { R"(
Welcome to the Quiz game, a classic intelligence testing game,where you have to give correct answers to as many questions as possible.)"
	};
	string buttons = { " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ About Buttons ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " };
	string next = { R"(
   Next - if you want to pass question without answering press next button)" };
	string prev = { R"(
   Previous - if you want to go back to previous question without answering press previous button)" };

	string submit = { R"(
   Submit - if you want to submit your answers and finish quiz press submit button)" };

	string note = { R"(
   Main purpose of our game is learning new things while having fun,so good luck and have fun:))" };

	string sideNote = { R"(
   Quiz Game - Version 1.0 )" };


	string* arr = new string[8]{ aboutTitle, aboutText,buttons,next,prev,submit,note,sideNote };


	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; arr[i][j] != '\0'; j++)
		{
			if (_kbhit())
			{
				cin.ignore();
				system("cls");

				for (size_t k = 0; k <= i; k++)
					cout << arr[k] << endl;

				break;

			}
			cout << arr[i][j];
			Sleep(40);
		}

		cout << endl;
	}


}

void printMainMenu(int select)
{
	string arr[4] = { "Guest","Admin","About Game","Exit" };

	QuizVisuals();
	for (size_t i = 0; i < 4; i++)
	{
		if (i == select - 1)
			cout << "\t\t\t\t\t\t\t" << red << arr[i] << white << endl;
		else
			cout << "\t\t\t\t\t\t\t" << arr[i] << endl;
	}
}

void printGuestMenu(int select)
{
	string arr[4] = { "Quiz names","Start Quiz","Board of Leaders","Exit" };

	QuizVisuals();
	for (size_t i = 0; i < 4; i++)
	{
		if (i == select - 1)
			cout << "\t\t\t\t\t\t\t" << red << arr[i] << white << endl;
		else
			cout << "\t\t\t\t\t\t\t" << arr[i] << endl;
	}
}

void printAdminMenu(int select)
{
	string arr[5] = { "Create Quiz","Show All Players","Quiz names","Board of Leaders","Exit" };

	QuizVisuals();
	for (size_t i = 0; i < 5; i++)
	{
		if (i == select - 1)
			cout << "\t\t\t\t\t\t\t" << red << arr[i] << white << endl;
		else
			cout << "\t\t\t\t\t\t\t" << arr[i] << endl;
	}
}

void GuestMenu()
{
	int num;

	int choice = 1;
	printGuestMenu(choice);


	while (true)
	{
		num = _getch();

		//arrow
		if (num == 224)
		{
			num = _getch();

			if (num == 80)  //down arrow
			{
				if (choice < 4)
					choice++;

				else if (choice == 4)
					choice = 1;
			}

			else if (num == 72)  //up arrow
			{
				if (choice > 1)
					choice--;

				else if (choice == 1)
					choice = 4;
			}
		}

		//w
		else if (num == 119)
		{
			if (choice > 1)
				choice--;

			else if (choice == 1)
				choice = 4;

		}

		//s
		else if (num == 115)
		{
			if (choice < 4)
				choice++;

			else if (choice == 4)
				choice = 1;

		}


		//enter
		else if (num == 13)
		{
			if (choice == 1) //quiz names
			{
				system("cls");
				q.printQuizNames();
				system("pause");
			}

			else if (choice == 2) //start quiz
			{
				system("cls");

				try
				{
					q.StartGame();
				}
				catch (exception ex)
				{
					cout << ex.what();
				}

				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}
			}

			else if (choice == 3) //leaderboard
			{
				system("cls");
				string quizName;
				q.printQuizNames();
				cout << "\n\n" << "please enter quiz name: ";
				getline(cin, quizName);
				q.printLeaderBoard(quizName);
				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}

			}

			else if (choice == 4) //exit
			{
				return;
			}

		}

		system("cls");
		printGuestMenu(choice);

	}
}

void AdminMenu()
{
	int num;

	int choice = 1;
	printAdminMenu(choice);


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
			if (choice == 1) //create quiz
			{
				system("cls");
				try
				{
					q.CreateQuiz();
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}

				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}
			}

			else if (choice == 2) //show all players
			{
				system("cls");

				try
				{
					q.ShowAllPlayers();

				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}

				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}
			}

			else if (choice == 3) //quiz Names
			{
				system("cls");
				q.printQuizNames();
				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}
			}

			else if (choice == 4) //leaderboard
			{
				system("cls");
				string quizName;
				q.printQuizNames();
				cout << "\n\n" << "please enter quiz name: ";
				getline(cin, quizName);
				q.printLeaderBoard(quizName);
				cout << "\n\n" << yellow << "please press backspace button to go back to Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}

			}

			else if (choice == 5) //exit
			{
				return;
			}

		}

		system("cls");
		printAdminMenu(choice);

	}
}

void MainMenu()
{
	int num;

	start();
	int choice = 1;
	printMainMenu(choice);


	while (true)
	{

		num = _getch();

		//arrow
		if (num == 224)
		{
			num = _getch();

			if (num == 80)  //down arrow
			{
				if (choice < 4)
					choice++;

				else if (choice == 4)
					choice = 1;
			}

			else if (num == 72)  //up arrow
			{
				if (choice > 1)
					choice--;

				else if (choice == 1)
					choice = 4;
			}
		}

		//w
		else if (num == 119)
		{
			if (choice > 1)
				choice--;

			else if (choice == 1)
				choice = 4;

		}

		//s
		else if (num == 115)
		{
			if (choice < 4)
				choice++;

			else if (choice == 4)
				choice = 1;

		}


		//enter
		else if (num == 13)
		{
			if (choice == 1) //player
			{
				system("cls");
				GuestMenu();
			}

			else if (choice == 2) //admin
			{
				system("cls");
				string username, password;
				cout << "username: ";
				getline(cin, username);
				if (q.checkAdmin(username))
				{
					cout << "password: ";
					getline(cin, password);
					if (q.adminLogin(username, password))
						AdminMenu();

					else
						throw invalid_argument("incorrect password");
				}

			}

			else if (choice == 3) //about game
			{
				system("cls");
				About_Game();

				cout << yellow << "please press backspace button to go back to Main Menu... " << white << endl;
				while (num != 8)
				{
					num = _getch();
					if (num == 8)
					{
						system("cls");
						break;
					}
				}
			}

			else if (choice == 4) //exit
			{
				try
				{
					//q.WriteQuizNamesToFile(QuizName_file);
					//q.WritePLayerResultsToFile(Player_file);
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}

				system("cls");
				cout << "You are quitting game";
				for (size_t i = 0; i < 3; i++)
				{
					cout << ".";
					Sleep(400);
				}
				break;
			}

		}

		system("cls");
		printMainMenu(choice);

	}
}






