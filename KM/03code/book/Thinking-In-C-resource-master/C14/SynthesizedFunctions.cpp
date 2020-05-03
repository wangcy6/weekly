#include <iostream>

using namespace std;

class GameBoard{
	public:
		GameBoard()
		{
			cout<<"GameBoard()\n";
		}

		GameBoard(const GameBoard&)
		{
			cout<<"GameBoard(const GameBoard&) \n";
		}

		GameBoard& operator=(const GameBoard&) {
			cout<<"GameBoard& operator&=(const GameBoard&) \n";
			return *this;
		}

		~GameBoard()
		{
			cout<<"~GameBoard() \n";
		}
};


class Game {
	GameBoard gb;
	public:
	Game(){
		cout<<"Game() \n";
	}

	Game(const Game& g)
		:
			gb(g.gb)
	{
		cout<<"Game(const Game& g) \n";
	}

	Game(int)
	{
		cout<<"Game(int) \n";
	}

	Game& operator=(const Game& g)
	{
		gb = g.gb;
		cout<<"Game& operator=() \n";
		return *this;
	}

	class other{};

	operator other() const
	{
		cout<<"Game::operator other()\n";
		return other();
	}

	~Game()
	{
		cout<<"~Game()\n";
	}
};


class Chess: public Game{};

void f(Game::other)
{}


class Checkers:public Game{
	public:
		Checkers()
		{
			cout<<"Checkers()\n";
		}

		Checkers(const Checkers& c):
			Game(c)
	{
		cout<<"Checkers(const Checkers& c) \n";
	}

		Checkers& operator=(const Checkers& c)
		{
			Game::operator=(c);
			cout<<"Checkers& operator=()\n";
			return *this;
		}
};


int main()
{
	Chess d1;

	cout<<"\nd2(d1)"<<endl;
	Chess d2(d1);

	cout<<"\nd1 = d2"<<endl;
	d1 = d2;

	cout<<"\nf(d1)"<<endl;
	f(d1);

	cout<<"\ngo\n";
	Game::other go;

	cout<<"\nCheckers"<<endl;
	Checkers c1, c2(c1);

	cout<<"\nc1 = c2"<<endl;
	c1 = c2;
	cout<<endl;
	return 0;

}
