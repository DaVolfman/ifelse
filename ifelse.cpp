#include "pushdown.h"
#include <string>
#include <fstream>
#include <iostream>

using std::cerr;
using std::cout;
using std::ifstream;
using std::endl;
using std::string;

int main(int argc, char** argv){
	NDPDA myPDA;
	ifstream file("sequence.txt");
	string currentState;
	string expression;
	
	if(file.fail()){
		cerr << "Error: could not open input file sequence.txt" << endl;
		return 66;
	}
	
	myPDA.startState = "q_0";
	myPDA.finalState = "q_f";
	
	myPDA.addTransitionFunction("q_0", NDPDA::lambda(), 'z', "q_1", "Sz");
	
	myPDA.addTransitionFunction("q_1", 'i', 'S', "q_1", "IE");
	myPDA.addTransitionFunction("q_1", 'i', 'S', "q_1", "I");

	myPDA.addTransitionFunction("q_1", 'f', 'I', "q_1", NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_1", 'f', 'I', "q_1", "S");
	myPDA.addTransitionFunction("q_1", 'f', 'I', "q_1", "LSR");

	myPDA.addTransitionFunction("q_1", 'e', 'E', "q_1", "ABC");
	myPDA.addTransitionFunction("q_1", 'e', 'E', "q_1", "ABCS");
	myPDA.addTransitionFunction("q_1", 'e', 'E', "q_1", "ABCLSR");

	myPDA.addTransitionFunction("q_1", '{', 'L', "q_1", NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_1", '}', 'R', "q_1", NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_1", 'l', 'A', "q_1", NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_1", 's', 'B', "q_1", NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_1", 'E', 'C', "q_1", NDPDA::stackLambda());

	myPDA.addTransitionFunction("q_1", NDPDA::lambda(), 'z', "q_f", "z");
	
	while( ! file.eof() ){
		getline(file, expression);
		if(myPDA.is_in_language(expression)){
			cout << "Correct sequence" << endl;
		}else{
			cout << "Sequence is syntactically incorrect." << endl;
		}
	}
	
	return 0;
}
