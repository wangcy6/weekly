//将c0816.cpp指针用引用进行代替的版本
void t(int&) {}

void u(const int &cir)
{
	//cir = 2;
	int i = cir;
	//int& cr2  = cir;
}

const char*& v()
{
	return "result of function v()";
}

const int & w() {
	static int i;
	return i;
}

int main() {
	int x = 0;
	int& ir = x;
	const int& cir = x;
	t(ir);
	//t(cir);
	u(ir);
	u(cir);
	//char& cr = v();
	const char& ccr = v();
	const int& ccir = w();
	//w() = 1;


}
