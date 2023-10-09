#include <iostream>
#include <string>
#include <fstream>
#include <map>
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


void WriteCommands(string filename) {
	// Write commands to binary file
	ofstream file(filename, ios_base:: out | ios_base::binary);
	Command command;

	// R-type
    command.name = "add";
	command.opcode = "000000";
	command.funct = "100000";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "sub";
	command.opcode = "000000";
	command.funct = "100010";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "and";
	command.opcode = "000000";
	command.funct = "100100";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "or";
	command.opcode = "000000";
	command.funct = "100101";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "slt";
	command.opcode = "000000";
	command.funct = "101010";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "sll";
	command.opcode = "000000";
	command.funct = "000000";
	command.type = "R";
	command.rs = false;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "srl";
	command.opcode = "000000";
	command.funct = "000010";
	command.type = "R";
	command.rs = false;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "jr";
	command.opcode = "000000";
	command.funct = "001000";
	command.type = "R";
	command.rs = true;
	command.rt = false;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "addu";
	command.opcode = "000000";
	command.funct = "100001";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

    command.name = "subu";
	command.opcode = "000000";
	command.funct = "100011";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "sltu";
	command.opcode = "000000";
	command.funct = "101011";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "mfhi";
	command.opcode = "000000";
	command.funct = "010000";
	command.type = "R";
	command.rs = false;
	command.rt = false;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "mflo";
	command.opcode = "000000";
	command.funct = "010010";
	command.type = "R";
	command.rs = false;
	command.rt = false;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	command.name = "mult";
	command.opcode = "000000";
	command.funct = "011000";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "multu";
	command.opcode = "000000";
	command.funct = "011001";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "div";
	command.opcode = "000000";
	command.funct = "011010";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "divu";
	command.opcode = "000000";
	command.funct = "011011";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "mul";
	command.opcode = "011100";
	command.funct = "000010";
	command.type = "R";
	command.rs = true;
	command.rt = true;
	command.rd = true;
	file.write((char*)&command, sizeof(Command));

	// I-type
	command.name = "addi";
	command.opcode = "001000";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "lw";
	command.opcode = "100011";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "sw";
	command.opcode = "101011";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "beq";
	command.opcode = "000100";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "bne";
	command.opcode = "000101";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));
	
	command.name = "slti";
	command.opcode = "001010";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "lui";
	command.opcode = "001111";
	command.funct = "000000";
	command.type = "I";
	command.rs = false;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "ori";
	command.opcode = "001101";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "andi";
	command.opcode = "001100";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "addiu";
	command.opcode = "001001";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "sltiu";
	command.opcode = "001011";
	command.funct = "000000";
	command.type = "I";
	command.rs = true;
	command.rt = true;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));
	
	// J-type
	command.name = "jal";
	command.opcode = "000011";
	command.funct = "000000";
	command.type = "J";
	command.rs = false;
	command.rt = false;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	command.name = "j";
	command.opcode = "000010";
	command.funct = "000000";
	command.type = "J";
	command.rs = false;
	command.rt = false;
	command.rd = false;
	file.write((char*)&command, sizeof(Command));

	// Close
	file.close();
}


// Binary file to map of Commands
map<string, Command> readCommands() {
	// Open file
	ifstream file("commands.dat", ios::in | ios::binary);

	map<string, Command> commands;

	// Read
	Command command;
	while (file.read((char*)&command, sizeof(Command))) {
		commands[command.name] = command;
	}

	// Close
	file.close();

	return commands;
}


int main() {
	WriteCommands("commands.dat");

	return 0;
}