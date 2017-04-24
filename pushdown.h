#ifndef pushdown_h
#define pushdown_h

#include <string>
#include <map>


//only used if needed for primitve debug
#include <iostream>
using std::cerr;
using std::endl;


using std::string;
using std::multimap;


class NDPDA {
	protected:
	class params {
		public:
		string state;
		int inSymbol;
		char stackSymbol;
		bool operator<(const NDPDA::params that)const{
			if(state < that.state){
				return true;
			}else if(that.state < state){
				return false;
			}else{
				if(inSymbol < that.inSymbol){
					return true;
				}else if(that.inSymbol < inSymbol){
					return false;
				}else{
					return stackSymbol < that.stackSymbol;
				}
			}
		}
		params(){}
		params(const string& fromstate, const int input, const char stackTop){
			state = fromstate;
			inSymbol = input;
			stackSymbol = stackTop;
		}
	};
	class results{
		public:
			string state;
			string stackTop;
			results(){
			}
			results(string tostate, string stackOperation){
				state=tostate;
				stackTop=stackOperation;
			}
	};
	typedef std::pair<NDPDA::params,NDPDA::results> PDA_func_pair;
	
	multimap <params, results> transitions;
	
	public:
	string startState;
	string finalState;
	
	static string newStack(){ return "z"; }
	static int lambda(){ return -1; }
	static string stackLambda(){ return string(); }
		
	void addTransitionFunction(const string& fromstate, const int input, const char stackTop, string tostate, string stackOperation){
		transitions.insert(PDA_func_pair(params(fromstate,input,stackTop),results(tostate,stackOperation)));
	}
	
	bool is_in_language(string state, string input, string stack/*, string derivation*/){
		params args;
		results changes;
		multimap<params, results>::iterator iter, limit;
		
		if(state.empty() or stack.empty())
			return false;
			
		if(state == finalState){
			if(input.empty()){/*
				derivation = derivation+"("+state+",L,"+stack+") SUCCESS\n";
				cerr << derivation;*/
				return true;
			}else
				return false;
		}
		
		args = params(state, input[0], stack[0]);
		for(iter = transitions.lower_bound(args); iter!= transitions.upper_bound(args); ++iter){
			changes = iter->second;
			if(is_in_language(changes.state, string(input.substr(1)), changes.stackTop + stack.substr(1)/*,derivation+"("+state+","+input+","+stack+")|-"*/)){
				return true;
			}
		}
		
		args = params(state, lambda(), stack[0]);
		for(iter = transitions.lower_bound(args); iter!= transitions.upper_bound(args); ++iter){
			changes = iter->second;
			if(is_in_language(changes.state, input, changes.stackTop + stack.substr(1)/*,derivation+"("+state+","+input+","+stack+")|-"*/)){
				return true;
			}
		}
		
		/*derivation = derivation+"("+state+","+input+","+stack+") FAILED\n";
		cerr << derivation;*/
		return false;
	}
	
	bool is_in_language(string input){
		return is_in_language(startState, input, newStack()/*, string()*/);
	}
	
};




#endif
