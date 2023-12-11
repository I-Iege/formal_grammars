#pragma once

#include "grammar_alg.h"

import formal_languages;

class early_alg : public grammar_alg
{
public:

enum early_state{STEP1,STEP2,STEP4,STEP5,END};

early_alg(const grammar &gr,const std::vector<sign> &a);
~early_alg();

std::string get(const int &i,const int &j) const;

bool contains;
early_state show_state() const;
//inherited from grammar_alg
std::string to_string() const;


private:

void step1();
void step2(const int &j);
void step4(const int& i,const int &j,const std::vector<sign> &a);
void step5(const int &i,const int &j);

grammar g;
std::set<sign> e_set;
std::vector<std::vector<std::set<s_rule> > > table;
std::vector<std::vector<std::vector<std::set<s_rule> > > >table_vec;
std::vector<early_state> state;

};

