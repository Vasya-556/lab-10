#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

int** weightInt;
string** weight;
int vertices;
int edges;

void initGraph(string fname); 
void makeWeightMatrix(string line);
string makeWeightMatrixToString();
void printMatrix(string matrix);
void saveMatrixToFile(string matrix, string fileName);

int main()
{
	char fname[] = "graph_02_4.txt";
	initGraph(fname);
	string fileToSave;
	int menu;
	do
	{
		cout << "Chose operation:" << endl;
		cout << "[1] - Print" << endl;
		cout << "[2] - Save" << endl;
		cout << "[0] - Exit" << endl;
		cin >> menu;
		switch (menu)
		{
		case 1:
			printMatrix(makeWeightMatrixToString());
			break;

		case 2:
			cout << "Input file to save(without .txt): ";
			cin.ignore();
			getline(cin, fileToSave);
			fileToSave += ".txt";
			saveMatrixToFile(makeWeightMatrixToString(), fileToSave);
			break;
		case 0:
			break;

		default:
			break;
		}
	} while (menu != 0);
}

void initGraph(string fname) {
	ifstream input(fname);
	if (!input.is_open()) {
		cout << "Error opening file " << fname << endl;
		return;
	}

	string line;
	if (getline(input, line)) {
		vertices = stoi(line.substr(0, line.find(" ")));
		edges = stoi(line.substr(line.find(" ") + 1));
		weight = new string * [vertices];
		weightInt = new int* [vertices];
		for (int i = 0; i < vertices; i++) {
			weight[i] = new string[vertices];
			weightInt[i] = new int[vertices];
			for (int j = 0; j < vertices; j++) {
				if (i == j) {
					weight[i][j] = "0";
				}
				else {
					weight[i][j] = "∞";
				}
			}
		}
	}
	else {
		cout << "Empty input file" << endl;
		return;
	}

	while (getline(input, line)) {
		makeWeightMatrix(line);
	}

	input.close();
}

void makeWeightMatrix(string line) {
	int from = stoi(line.substr(0, line.find(" ")));
	line = line.substr(line.find(" ") + 1);
	int to = stoi(line.substr(0, line.find(" ")));
	line = line.substr(line.find(" ") + 1);
	int lineWeight = stoi(line);

	weight[from][to] = std::to_string(lineWeight);
	weightInt[from][to] = lineWeight;
}

string makeWeightMatrixToString() {
	stringstream result;
	result << "| v\\v |";
	for (int i = 0; i < vertices - 1; i++) {
		result << " v" << i << "|";
	}
	result << " v |";
	for (int i = 0; i < vertices - 1; i++) {
		result << "\n| v" << i << "  |";
		for (int j = 0; j < vertices - 1; j++) {
			result << " " << weight[i][j] << " |";
		}
		result << " " << weight[i][vertices - 1] << " |";
	}
	result << "\n| v   |";
	for (int j = 0; j < vertices - 1; j++) {
		result << " " << weight[vertices - 1][j] << " |";
	}
	result << " " << weight[vertices - 1][vertices - 1] << " |";
	return result.str();
}

void printMatrix(string matrix) {
	cout << matrix << endl;
}

void saveMatrixToFile(string matrix, string fileName) {
	ofstream outputFile(fileName);
	if (outputFile.is_open()) {
		outputFile << matrix;
		outputFile.close();
	}
	else {
		cerr << "Cannot open file to write" << endl;
	}
}