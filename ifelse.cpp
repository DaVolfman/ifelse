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
	
	myPDA.addTransitionFunction("q_0",'i','z',"if_1","z");
	myPDA.addTransitionFunction("q_0",'i','S',"if_1","S");
	myPDA.addTransitionFunction("q_0",'i','I',"if_1","I");
	myPDA.addTransitionFunction("q_0",'i','L',"if_1","L");
	myPDA.addTransitionFunction("q_0",'e','I',"else_1","I");
	myPDA.addTransitionFunction("q_0",'{','S',"q_0","LS");
	myPDA.addTransitionFunction("q_0",'{','I',"q_0","LI");
	myPDA.addTransitionFunction("q_0",'}','L',"q_0",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",'}','I',"discard",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'z',"q_f","z");
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'S',"q_f",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'I',"q_f",NDPDA::stackLambda());

	myPDA.addTransitionFunction("if_1",'f','z',"q_0","ISz");
	myPDA.addTransitionFunction("if_1",'f','S',"q_0","IS");
	myPDA.addTransitionFunction("if_1",'f','I',"q_0","II");
	myPDA.addTransitionFunction("if_1",'f','L',"q_0","IL");
	
	myPDA.addTransitionFunction("else_1",'l','I',"else_2","I");
	myPDA.addTransitionFunction("else_2",'s','I',"else_3","I");
	myPDA.addTransitionFunction("else_3",'e','I',"q_0",NDPDA::stackLambda());
	
	myPDA.addTransitionFunction("discard",NDPDA::lambda(),'I',"discard",NDPDA::stackLambda());
	myPDA.addTransitionFunction("discard",NDPDA::lambda(),'L',"q_0",NDPDA::stackLambda());
	
	
	while( ! file.eof() ){
		getline(file, expression);
		if(expression[expression.length()-1] == '\r')
			expression = expression.substr(0,expression.length()-1);
		if(myPDA.is_in_language(expression)){
			cout << "Correct sequence" << endl;
		}else{
			cout << "Sequence is syntactically incorrect." << endl;
		}
	}
	
	return 0;
}
