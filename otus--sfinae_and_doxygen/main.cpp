#include <iostream>
#include <vector>
#include <list>
#include "ip_gen.h"
#include <cstdlib>
using std::cout;
int main() {
	ip_print(cout, char(-1));
	ip_print(cout, short(0));
	ip_print(cout, int(2130706433));
	ip_print(cout, 8875824491850138409LL);
	ip_print(cout, std::string("192.168.0.1"));
	ip_print(cout, std::vector<int>{147, 0, 0, 1});
	ip_print(cout, std::list<int>{127, 99, 0, 1});
	ip_print(cout, std::tuple<int, int, int, int>{192, 26, 11, 100});
	return 0;
}
