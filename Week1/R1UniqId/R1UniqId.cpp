#include <string>
#include <vector>
using namespace std;

#define UNIQ_ID_HELP_HELP(x) a_##x
#define UNIQ_ID_HELP(x) UNIQ_ID_HELP_HELP(x)
#define UNIQ_ID UNIQ_ID_HELP(__LINE__)

int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = { "hello", "world" };
	vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}
