#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

#include "rule.hpp"
#include "ruleset.hpp"

void fun(vector<object> vec){
	auto size = vec.size();
	if(size < 9){
		vec.push_back(object());
		for(string val: { "e", "a", "b", "c" }){
			vec[size] = object(val);
			fun(vec);
		}
	}
	else{
		vector<rule> rules = {
			{object("e"), object("e"), object("e")},
			{object("e"), object("a"), object("a")},
			{object("e"), object("b"), object("b")},
			{object("e"), object("c"), object("c")},
			
			{object("a"), object("e"), object("a")},
			{object("a"), object("a"), vec[0]     },
			{object("a"), object("b"), vec[1]     },
			{object("a"), object("c"), vec[2]     },
			
			{object("b"), object("e"), object("b")},
			{object("b"), object("a"), vec[3]     },
			{object("b"), object("b"), vec[4]     },
			{object("b"), object("c"), vec[5]     },
			
			{object("c"), object("e"), object("c")},
			{object("c"), object("a"), vec[6]     },
			{object("c"), object("b"), vec[7]     },
			{object("c"), object("c"), vec[8]     },
			
		};
		ruleset tmp(rules);
		if(tmp.is_group()){
			tmp.print();
		}
	}
}


int main(){
	vector<object> v;
	fun(v);
	return 0;
}
