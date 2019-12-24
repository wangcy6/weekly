//更改成员属性，使其成为mutable和const成员函数

#include <iostream>
#include <cstdlib>	//产生随机数
#include <ctime>	//产生随机种子

using namespace std;

class Quoter {
	mutable int	lastquote;
	public:
	Quoter();
	int lastQuote() const;
	const char* quote() const;
};

Quoter::Quoter()
	:lastquote(-1)
{
	srand(time(0));
}

int
Quoter::lastQuote() const
{
	return lastquote;
}

const char*
Quoter::quote() const
{
	static const char* quotes[] = {
		"bye bye bye", 
		"come on everybody", 
		"let`s us have fun", 
		"it`s a nice day", 
		"do you think so?"
	};
	//产生一个随机数等于lastquote
	const int qsize = sizeof quotes / sizeof *quotes;
	int qnum = rand() % qsize;
	//第一次直接返回, 因为初始化为-1, 以后只能保证和上次的不同
	//不能保证和上上次的不同
	while (lastquote >= 0 && qnum == lastquote)
	{
		qnum = rand() % qsize;
	}
	return quotes[lastquote = qnum];
}

int
main(void)
{
	const Quoter cq;
	cq.lastQuote();
	for(int i = 0; i < 20; i++) {
		cout<<cq.quote()<<endl;
	}

	return 0;
}
