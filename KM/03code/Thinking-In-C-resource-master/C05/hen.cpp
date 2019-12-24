#include <iostream>
using namespace std;

class Hen {
	public:

		class Nest {
			int x;
			friend class Hen;

			public:

			class Egg {
				int y;
				friend class Nest;

				public:    
				void display() {
					cout << "Hen::Nest::Egg::display: " << y << endl;
				}
			};

			void initEgg(Egg* e) {
				e->y = 2;
			}
			void display() {
				cout << "Hen::Nest::display: " << x << endl;
			}
		};

		void initNest(Nest* n) {
			n->x = 1;
		}
		void display() {
			cout << "Hen::display\n";
		}
};

int main() {
	Hen h;
	Hen::Nest n;
	Hen::Nest::Egg e;

	h.initNest(&n);
	n.initEgg(&e);
	h.display();
	n.display();
	e.display();
}
