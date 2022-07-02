#ifndef PD_TO_GR_H
#define PD_TO_GR_H
#include "grammar_alg.h"
#include "push_down.h"
#include "grammar.h"
class pd_to_gr :public grammar_alg
{

public:
    pd_to_gr(const push_down& pd);
    ~pd_to_gr();
    grammar get_grammar() const;
    std::string to_string() const;
private:
    std::vector<grammar> gr;

};
#endif // PD_TO_GR_H
