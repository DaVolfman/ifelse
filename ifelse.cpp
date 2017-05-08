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
	myPDA.addTransitionFunction("q_0",'i','R',"if_1","R");
	myPDA.addTransitionFunction("q_0",'e','S',"else_1",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",'e','E',"else_1","E");

	myPDA.addTransitionFunction("q_0",'{','S',"q_0","R");
	myPDA.addTransitionFunction("q_0",'}','R',"q_0",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",'}','S',"discard",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",'}','E',"discard",NDPDA::stackLambda());
	
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'E',"end",NDPDA::stackLambda());
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'S',"end",NDPDA::stackLambda());	
	myPDA.addTransitionFunction("q_0",NDPDA::lambda(),'z',"q_f","z");
	
	myPDA.addTransitionFunction("if_1",'f','z',"q_0","SEz");
	myPDA.addTransitionFunction("if_1",'f','R',"q_0","SER");
	myPDA.addTransitionFunction("if_1",'f','S',"q_0","SE");
	
	myPDA.addTransitionFunction("else_1",'l','E',"else_2","E");
	myPDA.addTransitionFunction("else_2",'s','E',"else_3","E");
	myPDA.addTransitionFunction("else_3",'e','E',"q_0","S");
	
	myPDA.addTransitionFunction("discard",NDPDA::lambda(),'E',"discard",NDPDA::stackLambda());
	myPDA.addTransitionFunction("discard",NDPDA::lambda(),'S',"discard",NDPDA::stackLambda());
	myPDA.addTransitionFunction("discard",NDPDA::lambda(),'R',"q_0",NDPDA::stackLambda());
	
	myPDA.addTransitionFunction("end",NDPDA::lambda(),'E',"end",NDPDA::stackLambda());
	myPDA.addTransitionFunction("end",NDPDA::lambda(),'S',"end",NDPDA::stackLambda());
	myPDA.addTransitionFunction("end",NDPDA::lambda(),'z',"q_f","z");	
	
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
