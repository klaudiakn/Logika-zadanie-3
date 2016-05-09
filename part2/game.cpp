#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
const int n=11;

bool cmp(char *a, string b) //returns true if two strings are equal 
{
	if(strcmp(a, b.c_str())==0) return true;
	return false;
}

void get_arg(int i, char *a) //get's random argument to create task 
{
	srand(time(NULL));
	int c=rand()%3;
	switch (c)
	{
		
		case 0: 
			a[i]='0';
			return;
		case 1:
			a[i]='1';
			return;
		case 2:
			a[i]='X';
			return;
	}
}
int  get_op(int i, char *a) //gets random operator, returns 1, if it's 'or' (v), 2 if it's 'and'(&), 3 if it's implicataion (>)
{
	srand(time(NULL));
	int c=rand()%3;
	switch (c)
	{
		case 0:
		{
			a[i]='v';
			return 1; 
		}
		case 1:
		{
			a[i]='&';
			return 2; 
		}
		case 2:
		{
			a[i]='>';	
			return 3; 
		}
	}
}

char solve_not(char a, string file_source) //solves not, based on the data included in the file file_sources 
{
	char r;
	fstream file;
	file.open(file_source.c_str(), ios::in); //open the file 

	if(file.good())
	{
		while(1)
		{
			char c;
			file>>c>>r; //reading the lines 
			if(c==a) //if the first character in the file is our argument, then the next in the line is the solution 
				return r;
		}	
	}
}

char solve_and(char a, char b, string file_source) //solves 'and' sentence, based in the data included in the file file_solution
{
	char r; //this will be the solution 
	fstream file;
	file.open(file_source.c_str(), ios::in); //opening the file 
	if(file.good())
	{
		while(1)
		{
			char c, d;
			file>>c>>d>>r; //reading lines consisting of three characters separated by space 
			if(c==a and d==b) //if the first character is our fist argument and the second character is our second argument, then the third one is the solution 
				return r; //return solution
		}
	}

}

char solve_impl(char a, char b, string file_source) //solves implication, based on the data included in the file file_source 
{
	char r;
	fstream file;
	file.open(file_source.c_str(), ios::in); //opening the file 
	if(file.good())
	{
		while(1) //like in solve_and 
		{
			char c, d;
			file>>c>>d>>r;
			if(c==a and d==b)
				return r;
		}
	}
}

char solve_or(char a, char b, string file_source) //solves or sentence, based on the data included in the file file_source, just like solve_impl and solve_and
{
	char r;
	fstream file;
	file.open(file_source.c_str(), ios::in);
	if(file.good())
	{
		while(1)
		{
			char c, d;
			file>>c>>d>>r;
			if(c==a and d==b)
				return r;
		}
	}
}

char solve_task(int i, char a, char b, string sources[4]) //solves task, where a is the first argument, b is the second argument, i is the number of operand, 
													//and sources is the array with the names of files with definitions of logical operators
{
	if(i==1) return solve_or(a, b, sources[0]); //i=1 that means it's or sentence, and the name of file with definition for it  is in sources[0]
	if(i==2) return solve_and(a, b, sources[1]); //i=2 is for and sentence, the name of the file in sources[1]
	if(i==3) return solve_impl(a, b, sources[2]); //i=3 if for implication, the name of the file in sources[2]
}
char get_task(string sources[4]) //creates random task to solve (solution in the variable 'solution')
{
	srand(time(NULL));
	char a[n];
	char solution; 
	char prev_sol=' '; //previous solution, we need it to solve the task 
	int i; //counter 
	for(i=0; i<11; i++) //creating random task containging at most 10 characters 
	{
		int b=rand()%4; //getting random number from 0-3
		if(b==0) //0 is for argument 0 
		{
			a[i]='(';
			a[++i]='0';
			int o=get_op(++i, a); //we get random operator 
			get_arg(++i, a); //and another argument 
			a[++i]=')';	
			solution=solve_task(o, '0', a[i-1], sources); //we solve the task composed of two arguments and one operator, that we draw 
		}
		else {
			if(b==1) //similarly to the previous, but the first argument is 1 
			{
				a[i]='(';
				a[++i]='1';
				int o=get_op(++i, a);
				get_arg(++i, a);
				a[++i]=')';	
				solution=solve_task(o, '1', a[i-1], sources);
			}
			else
			{
				if(b==2) //and the same thing but wih argument X 
				{
					a[i]='(';
					a[++i]='X';
					int o=get_op(++i, a);
					get_arg(++i, a);
					a[++i]=')';	
					solution=solve_task(o,'X', a[i-1], sources);
					
				}
				else //if we draw '3' then it's ~ (not)
				{
					a[i]='~';
					get_arg(++i, a); //getting argument for ~
					solution=solve_not(a[i], sources[3]); //solving not, the name of the file with definition of this operand is in the sources[3]
				}
			}
		}
		int o;
		if(i<9) //if it's not the end of the whole task, we get another operand to conncet tasks 
		{
			o=get_op(++i, a);
			
		}
		
		if(prev_sol!=' ') //if it's not the first task we created, then we solve combined tasks (previous one and the one we've just created) 
			solution=solve_task(o, prev_sol, solution, sources);
		prev_sol=solution; //chaning previous task to our current solution 
	}
	cout<<"Twoje zadanie to: "<<a<<endl; //write the task 

	return solution; //return correct solution 
}



void game(string sources[4]) { //the main function
	system("clear");
	cout<<"Zaczynamy gre. Dostaniesz 8 zadan. Mozesz pomylic sie tylko 2 razy. (Masz 2 'zycia')."<<endl;
	cout<<"Aby odpowiedziec poprawnie na pytanie musisz znac zasady logiki trojwartosciowej."<<endl;
	cout<<"Jedynki oznaczaja prawde, zera falsz, a X- nieznane."<<endl;
	cout<<"'~' oznacza negacje i neguje jedynie znak stojacy bezposrednio za nim, 'v' oznacza lub, a '>' implikacje."<<endl;
	cout<<"Kolejnosc wykonywania zadan zalezy od nawiasow, gdy ich nie ma, wykonuj od lewej do prawej. "<<endl;
	cout<<"Jako odpowiedz masz podac '0', '1' lub 'X' i potwierdzic enterem, inne odpowiedzi beda ignorowane."<<endl;
	cout<<"Wcisnij dowolny klawisz, aby rozpoczac."<<endl;
	getchar();
	getchar();
	int counter=0;
	int points=0;
	for(int j=0; j<8; j++) //there are 8 tasks
	{
		system("clear");
		cout<<"Punkty: "<<points<<"  Zycia: "<<2-counter<<endl;
		char b=get_task(sources); //getting task to solve, the correct answer is in the variable b 
		char answer; //answer given by the player 
		
		cin>>answer; 
		while(answer!='0' and answer!='X' and answer!='1') //ignoring random keys
		{
			cout<<"Niepoprawny format odpowiedzi. Wpisz '0' lub 'X' lub '1'."<<endl;
			cin>>answer;
		}
		if(answer==b)  //if answer is correct 
		{
			cout<<"Dobrze! Dostajesz 1 punkt!"<<endl;
			points++;
			sleep(3);
		}
		else //if it's incorrect 
		{
			cout<<"Zla odpowiedz! Tracisz zycie!"<<endl;
			counter++;
			if(counter==3) //if player lost all his lifes it's the end of the game 
			{
				cout<<"Przegrywasz!"<<endl; 
				cout<<"Aby zagrac jeszcze raz nacisnij p, aby wyjsc z gry nacisnij q. "<<endl;
				return;
			}
			sleep(3);
		}
	
	}
	system("clear");
	cout<<"Gratulacje wygrales! Twoj wynik to "<<points<<" punktow!"<<endl;
	cout<<"Aby zagrac jeszcze raz nacisnij p, aby wyjsc z gry nacisnij q."<<endl;
	
	return;
	
}

int main(int argc, char** argv) {
	char input = 0;
	string sources[4];
	if(argc==9) //if parameters are given, we put them into sources array, in which sources[0] is for or, sources[1] is for and, sources[2] is for implication, sources[3] is for not 
	{
		for(int j=1; j<argc; j++) //reading parameters given in the command line to the array sources 
		{
			if(cmp(argv[j], "--or")) sources[0]=argv[++j];
			if(cmp(argv[j], "--and")) sources[1]=argv[++j];
			if(cmp(argv[j], "--impl")) sources[2]=argv[++j];
			if(cmp(argv[j], "--not")) sources[3]=argv[++j];
		}
	}
	else {
		if(argc!=1) //if there are more than one and less than 3 file names given 
		{
			cout<<"Bledny format paramretow! Podaj wszystkie parametry plikow albo zaden i zostana one ustawione na domyslne!"<<endl;
			return 1;
		}
		else{ //if there are no parameters given, we take the default or.txt, and.txt, impl.txt and not.txt

		sources[0]="or.txt";
		sources[1]="and.txt";
		sources[2]="impl.txt";
		sources[3]="not.txt";
		}
	}
	system("clear");
	cout << "Witaj w grze logicznej!" << endl;
	cout << "Nacisnij q, aby wyjsc, lub p aby grac." << endl;	
	while(1) {
		cin >> input;
		if(input == 'p') {
			game(sources);
		} else if(input == 'q') {
			break;
		} else if(input != '\n') {
			cout << "Nieznane wejscie'" << input << "'! Ignoruje...\n";
		}
	}

	return 0;
}
