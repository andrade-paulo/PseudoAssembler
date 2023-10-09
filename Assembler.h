#include "GetFunctions.h"
using namespace std;

struct Command {
	string name;
	string opcode;
	string funct;
	string type;
	bool rs;
	bool rt;
	bool rd;
};

const int initialMemoryPosition = 0x00400000;

string RType(vector<string>&, Command&, smatch&);

string IType(vector<string>&, Command&, smatch&, smatch&, map<string, int>&, int&);

string JType(smatch&, map<string, int>&, Command&);

string binaryToHexadecimal(string binary);