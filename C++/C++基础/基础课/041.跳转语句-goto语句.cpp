#include <iostream>
using namespace std;

int main() // goto
{
	cout << "1、xxx" << endl;
	cout << "2、xxx" << endl;

	goto FLAG;

	cout << "3、xxx" << endl;
	cout << "4、xxx" << endl;

FLAG:
	cout << "5、xxx" << endl;
	return 0;
}