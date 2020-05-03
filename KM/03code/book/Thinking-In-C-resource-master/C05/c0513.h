#ifndef _HANDLE_H
#define _HANDLE_H

class Handle{
	struct Cheshire;
	Cheshire* smile;
	public:

	void initialize();
	void cleanup();
	int read();
	void change(int);
};


#endif  //_HANDLE_H
