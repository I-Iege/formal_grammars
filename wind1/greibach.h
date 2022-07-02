#ifndef GREIBACH_H
#define GREIBACH_H

#include "grammar_alg.h"
#include "grammar.h"


class greibach : public grammar_alg
{
public:
    enum greibach_state{LEFT_REC,SORT,SUBSTITUTE,REDUCTION,END,NON_TERMINAL};
	greibach(const grammar& gr);
    ~greibach();
    std::string sequence() const;

//inherited from grammar_alg
	std::string to_string() const;

    greibach_state show_state() const;
	const grammar& get_grammar()const;
private:	
	std::vector<grammar> g;
    grammar current;
	std::map<sign,int> num;
    std::vector<greibach_state> state;
    void substitute(grammar& h,const sign a,std::list<sign_list>::iterator r);
	void substitute_all();
    void e_left_recursion();
    void sort_n();
	void eliminate_t();
	void reduction();
};



#endif
