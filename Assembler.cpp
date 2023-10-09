#include "Assembler.h"

int main() {
	// User input
	string codeFileName;
	cout << "Enter assembly file name: ";
	cin >> codeFileName;
	
	// Commands File

	ifstream binaryFile;
	binaryFile.open("commands.dat", ios_base::in | ios::binary);
	
	map<string, Command> commands;
	Command command;

	while (binaryFile.read((char*) &command, sizeof(Command))) {
		commands[command.name] = command;  // Map command name to binary equivalent
	}

	binaryFile.close();

	// Creating output.hex
	ofstream hexFile;

	string outputFileName = codeFileName + "_output.txt";
	hexFile.open(outputFileName);

	hexFile << "v2.0 raw\n";

	// Get labels and respective line numbers
	map<string, int> labels = getLabels(codeFileName);

	// Assembly file
	ifstream assemblyFile(codeFileName);

	if (!assemblyFile.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}

	int lineNum = 0;
	int count4Lines = 0;
	string line;
	
	while (getline(assemblyFile, line)) {
		// Regex match
		smatch match_title;
		smatch match_inCommandLabel;
		smatch match_regist;
		smatch match_immediate;

		// If it's label, remove label from line
		smatch match_label;
		regex_search(line, match_label, label);

		if (match_label.size() > 0) {
			line = match_label.suffix();
		}

		// Regex search
		regex_search(line, match_title, title);
		regex_search(line, match_inCommandLabel, inCommandLabel);
		regex_search(line, match_immediate, immediate);
		
		// Registers search
		vector<string> registers = getRegisters(line);
		
		// Check if line is a command
		if (match_title.size() > 0) {
			if (count4Lines == 4) {
				hexFile << "\n";
				count4Lines = 0;
			}

			// Get binary equivalent from map
			Command currentCommand = commands[match_title[1]];

			// Check if command is R-type
			if (currentCommand.type == "R") {
				 string result = RType(registers, currentCommand, match_immediate);

				 cout << result;
				 hexFile << binaryToHexadecimal(result);

				 count4Lines++;
			}
			
			// Check if command is I-type
			else if (currentCommand.type == "I") {
				string result = IType(registers, currentCommand, match_immediate, match_inCommandLabel, labels, lineNum);
				
				cout << result;
				hexFile << binaryToHexadecimal(result);
				count4Lines++;
			}

			// Check if command is J-type
			else if (currentCommand.type == "J") {
				string result = JType(match_inCommandLabel, labels, currentCommand);

				cout << result;
				hexFile << binaryToHexadecimal(result);
				count4Lines++;
			}
		}
		lineNum++;
	}
	hexFile.close();

	return 0;
}


string RType(vector<string>&registers, Command&currentCommand, smatch&match_immediate) {
	// Initialize registers
	string rd = "0";
	string rs = "0"; 
	string rt = "0";
	
	// Get registers according to the righ order
	if (currentCommand.rd && currentCommand.rs && currentCommand.rt) {
		rd = registers[0]; rs = registers[1]; rt = registers[2];
	}
	else if (currentCommand.rd && currentCommand.rs) {
		rd = registers[0]; rs = registers[1];
	}
	else if (currentCommand.rs && currentCommand.rt) {
		rs = registers[0]; rt = registers[1];
	}
	else if (currentCommand.rd && currentCommand.rt) {
		rd = registers[0]; rt = registers[1];
	}
	else if (currentCommand.rd) {
		rd = registers[0];
	}
	else if (currentCommand.rs) {
		rs = registers[0];
	}

	// Get sa
	string sa = match_immediate[0];

	// Convert to binary
	string rs_bin = bitset<5>(stoi(rs, nullptr, 10)).to_string();
	string rt_bin = bitset<5>(stoi(rt, nullptr, 10)).to_string();
	string rd_bin = bitset<5>(stoi(rd, nullptr, 10)).to_string();
	if (sa == "") sa = "0";
	string sa_bin = bitset<5>(stoi(sa, nullptr, 10)).to_string();

	// Return binary
	return currentCommand.opcode + rs_bin + rt_bin + rd_bin + sa_bin + currentCommand.funct + "\n";
}


string IType(vector<string>& registers, Command& currentCommand, smatch& match_immediate, smatch& match_inCommandLabel, map<string, int>&labels, int&lineNum) {
	// Initialize registers
	string rs = "0";
	string rt = "0";

	// Get registers according to the righ order

	if (currentCommand.rs && currentCommand.rt) {
		// Exception for beq and bne
		if (currentCommand.name == "beq" || currentCommand.name == "bne") {
			rs = registers[0]; rt = registers[1];
		}
		else {
			rt = registers[0]; rs = registers[1];
		}
	}
	else if (currentCommand.rt) {
		rt = registers[0];
	}

	// Get immediate
	string immediate = match_immediate[0];

	// Get label if any
	if (match_inCommandLabel.size() > 0 && match_immediate[0] == "") {
		string label = match_inCommandLabel[0];

		// Using PC as reference
		int address = labels[label] - lineNum - 1;
		immediate = to_string(address);
	}

	// Convert to binary
	string rs_bin = bitset<5>(stoi(rs, nullptr, 10)).to_string();
	string rt_bin = bitset<5>(stoi(rt, nullptr, 10)).to_string();
	if (immediate == "") immediate = "0";
	string immediate_bin = bitset<16>(stoi(immediate, nullptr, 10)).to_string();

	// Print binary
	return currentCommand.opcode + rs_bin + rt_bin + immediate_bin + "\n";
}


string JType(smatch&match_inCommandLabel, map<string, int>& labels, Command&currentCommand) {
	// Get label
	string label = match_inCommandLabel[0];

	// Get and calculate line number
	int address = labels[label] + (initialMemoryPosition / 4);

	// Convert to binary
	string address_bin = bitset<26>(address).to_string();

	// Print binary
	return currentCommand.opcode + address_bin + "\n";
}


string binaryToHexadecimal(string binary) {
	map<string, char> hex_dict = {
		{"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
		{"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
		{"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
		{"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
	};
	string hexadecimal;
	for (size_t i = 0; i < binary.length(); i += 4) {
		string group = binary.substr(i, 4);
		hexadecimal += hex_dict[group];
	}
	return hexadecimal;
}