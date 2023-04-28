#include "pch.h"
#include "CppUnitTest.h"
#include "../lab-10/lab-10.cpp"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string fname = "graph_test.txt";
			ofstream file(fname);
			file << "5 8\n";
			file << "0 1 4\n";
			file << "0 3 2\n";
			file << "0 4 1\n";
			file << "1 2 3\n";
			file << "1 3 3\n";
			file << "2 3 2\n";
			file << "2 4 3\n";
			file << "3 4 6\n";
			file.close();

			initGraph(fname);
			stringstream expected;

			

			expected << "| v\\v | v0| v1| v2| v3| v |" << endl;
			expected << "| v0  | 0 | 4 | ∞ | 2 | 1 |" << endl;
			expected << "| v1  | ∞ | 0 | 3 | 3 | ∞ |" << endl;
			expected << "| v2  | ∞ | ∞ | 0 | 2 | 3 |" << endl;
			expected << "| v3  | ∞ | ∞ | ∞ | 0 | 6 |" << endl;
			expected << "| v   | ∞ | ∞ | ∞ | ∞ | 0 |" << endl;

			stringstream actual;
			streambuf* coutBuffer = cout.rdbuf();
			cout.rdbuf(actual.rdbuf());

			printMatrix(makeWeightMatrixToString());

			cout.rdbuf(coutBuffer);

			Assert::AreEqual(expected.str(), actual.str());
		}
	};
}
