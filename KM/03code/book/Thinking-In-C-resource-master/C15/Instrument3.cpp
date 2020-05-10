#include <iostream>

using namespace std;

enum  note{middleC, Csharp, Eflat};

class Instrument{
	public:
		virtual void play(note) const {
			cout<<"Instrument::play()\n";
		}
};

class Wind: public Instrument{
	public:
		void play(note) const{
			cout<<"Wind::play()\n";
		}
};

void tune(Instrument& i) {
	i.play(middleC);
}


int main()
{
	Wind flute;

	tune(flute);
}
