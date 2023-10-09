#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

// Constants

const regex title("(\\w+) ");
const regex inCommandLabel("[^$\\d ](\\w*)(\\n|$)");
const regex label("(\\w*):");
const regex regist("[$]\\d+|[$].\\d+");
const regex immediate(" \\d*(\\n|$| )");

// Funtions

map<string, int> getLabels(string);

vector<string> getRegisters(string);