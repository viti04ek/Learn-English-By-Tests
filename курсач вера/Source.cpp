#include<iostream>
#include<Windows.h>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
#include<vector>
#include<string>


using namespace std;


enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


class Functions
{
public:

	void set_color(Color text, Color background)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}

	void set_cursor(int x, int y)
	{
		COORD myCoords = { x,y };
		SetConsoleCursorPosition(hStdOut, myCoords);
	}


	void choice_buttons(int ch, vector<string> buttons, int x, int y, int delta_x, int delta_y)
	{
		//system("cls");

		for (int i = 0; i < buttons.size(); i++)
		{
			set_cursor(x + delta_x * i, y + delta_y * i);

			if (i == ch)
				set_color(Black, White);
			else
				set_color(White, Black);

			cout << buttons[i];
		}
	}

	int choice(vector<string> buttons, bool up_down, int x, int y, int delta_x, int delta_y)
	{
		//system("cls");

		int key = 1, change = 0, A = 0;

		if (up_down == true)
		{
			choice_buttons(change, buttons, x, y, delta_x, delta_y);
			do
			{
				key = _getch();

				switch (key)
				{
				case Up:
					if (change > 0)
					{
						change--;
						choice_buttons(change, buttons, x, y, delta_x, delta_y);
					}
					break;

				case Down:
					if (change < buttons.size() - 1)
					{
						change++;
						choice_buttons(change, buttons, x, y, delta_x, delta_y);
					}
					break;

				case Enter: A++; break;

				}

			} while (A < 1);

			return change;
		}
		else
		{
			choice_buttons(change, buttons, x, y, delta_x, delta_y);
			do
			{
				key = _getch();

				switch (key)
				{
				case Left:
					if (change > 0)
					{
						change--;
						choice_buttons(change, buttons, x, y, delta_x, delta_y);
					}
					break;

				case Right:
					if (change < buttons.size() - 1)
					{
						change++;
						choice_buttons(change, buttons, x, y, delta_x, delta_y);
					}
					break;

				case Enter: A++; break;

				}

			} while (A < 1);

			return change;
		}
	}


	void only_button(vector<string> text, int x, int y)
	{
		int ex;

		ex = choice(text, true, x, y, 0, 0);

		return;
	}


	bool contains(char s, vector<string> str)
	{
		for (int i = 0; i < str.size(); i++)
			if (s == str[i][0])
				return true;

		return false;
	}

};


class Menu : public Functions
{
public:

	int start_menu()
	{
		system("cls");
		system("color 07");

		vector<string> buttons;

		buttons.push_back("PRESENT SIMPLE");
		buttons.push_back("PAST SIMPLE");
		buttons.push_back("FUTURE SIMPLE");
		buttons.push_back("ABOUT");
		buttons.push_back("EXIT");

		int ch;
		ch = choice(buttons, true, 45, 10, 0, 2);

		return ch;
	}


	int test_menu()
	{
		system("cls");
		system("color 07");

		vector<string> buttons;

		buttons.push_back("THEORY");
		buttons.push_back("TRAINING TEST");
		buttons.push_back("FINAL TEST");
		buttons.push_back("EXIT");

		int ch;
		ch = choice(buttons, true, 45, 10, 0, 2);

		return ch;
	}


	void about()
	{
		system("cls");

		set_cursor(30, 14);
		cout << "----------------------------------------------";
		set_cursor(30, 15);
		cout << "|   Created by Yevtushenko Vera, KA-11 IASA   |";
		set_cursor(30, 16);
		cout << "----------------------------------------------";

		vector<string> text = { "BACK TO MENU" };
		only_button(text, 45, 25);
	}

};


class Theory : public Functions
{
private:

	vector<string> text;

public:

	Theory()
	{

	}

	~Theory()
	{
		this->text.clear();
	}


	void print(string file_name)
	{
		system("cls");

		ifstream F;
		F.open(file_name, ifstream::app);

		string row;

		while (getline(F, row))
			text.push_back(row);

		//set_cursor(0, 3);
		for (int i = 0; i < text.size(); i++)
			cout << text[i] << endl;;

		text.clear();
		text.push_back("BACK TO MENU");
		only_button(text, 310, 35);

		F.close();
	}

};


class Training_test : public Functions
{
private:

	vector<string> variants;
	vector<string> explanation;
	int number_of_questions;

public:

	Training_test()
	{
		this->number_of_questions = 0;
	}

	~Training_test()
	{
		variants.clear();
		explanation.clear();
	}


	int print_test(string file_name)
	{
		system("cls");

		ifstream F;
		F.open(file_name, ifstream::app);


		string variant;
		int correct = 0;

		getline(F, variant);

		while (variant[0] != '-')
		{
			system("cls");
			system("color 07");

			int correct_answer, answer;
			string question;
			vector<string> numbers = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

			question = variant;

			int i = 0;
			while (getline(F, variant))
			{
				if (variant[0] == '+')
				{
					correct_answer = i;
				}
				else
				{
					if (!contains(variant[0], numbers))
						variants.push_back(variant);
					else
						break;

					i++;
				}
			}


			set_cursor(10, 3);
			cout << question;

			answer = choice(variants, false, 10, 5, 20, 0);


			system("cls");
			system("color 07");

			set_cursor(10, 3);
			cout << question;

			for (int i = 0; i < variants.size(); i++)
			{
				set_cursor(10 + 20 * i, 5);
				set_color(White, Black);

				if (i == answer && i != correct_answer)
					set_color(Red, Black);

				if (i == correct_answer)
					set_color(Green, Black);

				cout << variants[i];
			}


			explanation.push_back(variant);

			while (getline(F, variant))
			{
				if (!contains(variant[0], numbers) && variant[0] != '-')
					explanation.push_back(variant);
				else
					break;
			}


			set_color(White, Black);
			for (int i = 0; i < explanation.size(); i++)
			{
				set_cursor(10, 7 + i);
				cout << explanation[i];
			}

			variants.clear();
			variants.push_back("NEXT QUESTION");
			only_button(variants, 30, 9 + explanation.size());


			if (answer == correct_answer)
				correct++;
			number_of_questions++;


			variants.clear();
			explanation.clear();
		}

		F.close();

		return correct;
	}


	void print_result(string file_name)
	{
		system("cls");

		int correct_answers, result;

		correct_answers = print_test(file_name);

		result = (correct_answers * 100) / number_of_questions;


		ifstream F;
		F.open(file_name, ifstream::app);

		string variant;
		vector<string> numbers = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

		while (variant[0] != '-')
			getline(F, variant);


		getline(F, variant);

		while (!F.eof())
		{
			int number1, number2;


			number1 = stoi(variant);

			getline(F, variant);

			number2 = stoi(variant);


			if (result >= number1 && result < number2)
			{
				getline(F, variant);

				explanation.push_back(variant);

				while (!contains(variant[0], numbers))
				{
					getline(F, variant);

					explanation.push_back(variant);
				}

				explanation.pop_back();

				break;
			}
		}

		system("cls");
		system("color 07");

		set_cursor(1, 2);
		cout << "YOUR RESULT: " << result << "%";

		for (int i = 0; i < explanation.size(); i++)
		{
			set_cursor(1, 3 + i);
			cout << explanation[i];
		}


		vector<string> button = { "BACK TO MENU" };
		only_button(button, 10, 5 + explanation.size());


		F.close();

	}

};


class Final_test : public Functions
{
private:

	vector<string> variants;
	vector<string> explanation;
	int number_of_questions;

public:

	Final_test()
	{
		this->number_of_questions = 0;
	}

	~Final_test()
	{
		variants.clear();
		explanation.clear();
	}


	int print_test(string file_name)
	{
		system("cls");

		ifstream F;
		F.open(file_name, ifstream::app);


		string variant;
		int correct = 0;

		getline(F, variant);

		while (variant[0] != '-')
		{
			int correct_answer = 0;
			int answer;
			string question;
			vector<string> numbers = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

			question = variant;

			int i = 0;
			while (getline(F, variant))
			{
				system("cls");
				system("color 07");


				if (variant[0] == '+')
				{
					correct_answer = i;
				}
				else
				{
					if (!contains(variant[0], numbers) && variant[0] != '-')
						variants.push_back(variant);
					else
						break;

					i++;
				}
			}


			set_cursor(10, 3);
			cout << question;

			answer = choice(variants, false, 10, 5, 30, 0);


			if (answer == correct_answer)
				correct++;
			number_of_questions++;


			variants.clear();
		}

		F.close();

		return correct;
	}


	void print_result(string file_name)
	{
		system("cls");

		int correct_answers, result;

		correct_answers = print_test(file_name);

		result = (correct_answers * 100) / number_of_questions;


		ifstream F;
		F.open(file_name, ifstream::app);

		string variant;
		vector<string> numbers = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

		while (variant[0] != '-')
			getline(F, variant);


		getline(F, variant);

		while (!F.eof())
		{
			int number1, number2;


			number1 = stoi(variant);

			getline(F, variant);

			number2 = stoi(variant);


			if (result >= number1 && result < number2)
			{
				getline(F, variant);

				explanation.push_back(variant);

				while (!contains(variant[0], numbers))
				{
					getline(F, variant);

					explanation.push_back(variant);
				}

				explanation.pop_back();

				break;
			}
		}


		system("cls");
		system("color 07");


		set_cursor(1, 2);
		cout << "YOUR RESULT: " << result << "%";

		for (int i = 0; i < explanation.size(); i++)
		{
			set_cursor(1, 3 + i);
			cout << explanation[i];
		}


		vector<string> button = { "BACK TO MENU" };
		only_button(button, 10, 5 + explanation.size());


		F.close();
	}

};


int main()
{
	system("color 07");

	string present_simple_training_test = "Present Simple training test.txt";
	string present_simple_final_test = "Present Simple final test.txt";
	string present_simple_theory = "Present Simple theory.txt";

	string past_simple_training_test = "Past Simple training test.txt";
	string past_simple_final_test = "Past Simple final test.txt";
	string past_simple_theory = "Past Simple theory.txt";

	string future_simple_training_test = "Future Simple training test.txt";
	string future_simple_final_test = "Future Simple final test.txt";
	string future_simple_theory = "Future Simple theory.txt";


	while (true)
	{
		Theory theory;
		Training_test training_test;
		Final_test final_test;
		Menu m;

		int start_choice = m.start_menu();

		bool repeat = true;


		switch (start_choice)
		{
		case 0:
			while (repeat)
			{
				int menu_choice = m.test_menu();

				switch (menu_choice)
				{
				case 0: theory.print(present_simple_theory); break;

				case 1: training_test.print_result(present_simple_training_test); break;

				case 2: final_test.print_result(present_simple_final_test); break;

				case 3: repeat = false; break;
				}
			}
			break;

		case 1:
			while (repeat)
			{
				int menu_choice = m.test_menu();

				switch (menu_choice)
				{
				case 0: theory.print(past_simple_theory); break;

				case 1: training_test.print_result(past_simple_training_test); break;

				case 2: final_test.print_result(past_simple_final_test); break;

				case 3: repeat = false; break;
				}
			}
			break;

		case 2:
			while (repeat)
			{
				int menu_choice = m.test_menu();

				switch (menu_choice)
				{
				case 0: theory.print(future_simple_theory); break;

				case 1: training_test.print_result(future_simple_training_test); break;

				case 2: final_test.print_result(future_simple_final_test); break;

				case 3: repeat = false; break;
				}
			}
			break;

		case 3: m.about(); break;

		case 4: return 0;

		}
	}
}