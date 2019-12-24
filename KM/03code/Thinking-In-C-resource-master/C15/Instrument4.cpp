#include <iostream>

using namespace std;

enum  note{middleC, Csharp, Eflat};

class Instrument{
	public:
		virtual void play(note) const {
			cout<<"Instrument::play()\n";
		}
		virtual const char* what() const {
			return "Instrument";
		}
		virtual void adjust(int) {}
};

class Wind: public Instrument{
	public:
		void  play(note)  const  {
			cout<<"Wind::play()\n";
		}
		const char* what() const{
			return "Wind";
		}
		void adjust(int) {}
};


class Percussion: public Instrument{
	public:
		void play(note) const{
			cout<<"Percussion::play()\n";
		}
		const char* what() const{
			return "Percussion";
		}
		void adjust(int) {}
};

class Stringed: public Instrument{
	public:
		void play(note) const{
			cout<<"Stringed::play()\n";
		}
		const char* what() const{
			return "Stringed";
		}
		void adjust(int) {}
};
class Brass: public Wind{
	public:
		void play(note) const{
			cout<<"Brass::play()\n";
		}
		const char* what() const{
			return "Brass";
		}
		void adjust(int) {}
};

class WoodWind: public Wind{
	public:
		void play(note) const{
			cout<<"WoodWind::play()\n";
		}
		const char* what() const{
			return "WoodWind";
		}
		void adjust(int) {}
};

void tune(Instrument& i) {
	i.play(middleC);
}

void f(Instrument& i)
{
	i.adjust(1);
}

Instrument* A[] = {
	new Wind, 
	new Percussion,
	new Stringed,
	new Brass
};

int main()
{
	Wind flute;
	Percussion drum;
	Stringed violin;
	Brass flugelhorn;
	WoodWind recorder;

	tune(flute);
	tune(drum);
	tune(violin);
	tune(flugelhorn);
	tune(recorder);
	f(flugelhorn);
}
