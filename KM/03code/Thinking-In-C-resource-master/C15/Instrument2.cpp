#include <iostream>

using namespace std;

enum note {middleC, Csharp, Eflat};

class Instrument{
	public:
		void play(note) const{
			cout<<"Instrument::play()\n";
		}
};


class Wind: public Instrument {
	public:
		void play(note) const {
			cout<<"Wind::play()\n";
		}
};


void tune(Instrument& i) {
	i.play(middleC);
}
void tune1(Instrument* i) {
	i->play(middleC);
}
void tune2(Wind& i) {
	i.play(middleC);
}
void tune3(Wind* i) {
	i->play(middleC);
}

int main()
{
	Wind flute;
	tune(flute);
	tune1(&flute);
	tune2(flute);
	tune3(&flute);
	return 0;
}
