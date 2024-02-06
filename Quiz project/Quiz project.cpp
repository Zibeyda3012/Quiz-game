
#include<iostream>
#include<string>
#include<algorithm>
#include<random>
#include<conio.h>
#include<Windows.h>
#include<list>
#include<fstream>

using namespace std;

#define blue "\x1B[34m"
#define red "\x1B[31m"
#define green "\x1B[32m"
#define orange "\x1B[33m"
#define white "\x1B[0m"
#define yellow "\x1B[33m"


int admin_count = 0;
int counter = 0;     //quiz icerisinde olan suallarin sayi
int create_quiz_choice = 0;
int game_period_choice = 0;
string QuizName_file = "quiz_names.txt";
string my_answer;
string Player_file = "Player_results.txt";

#include"AllFunctions.h"
Quiz q;
#include"Menu.h"


int main()
{
	/*
		Admin ucun username:Admin, passsword:admin
		Admin-nin username-i boyuk herfle baslmalidir ve en az 5 simvol olmalidir.
		Admin-nin passwordu minimum 5 simvoldan ibaret olmalidir.
		Yeni admin yaradilmasi ve elave olunmasini start() funksiyasi daxilinde ede bilersiniz.
	*/

	MainMenu();


}