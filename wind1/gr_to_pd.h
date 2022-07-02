#ifndef GR_T0_PD_H
#define GR_T0_PD_H
#include "grammar_alg.h"
#include "push_down.h"
#include "grammar.h"

class gr_to_pd : public grammar_alg
{
	public:

    gr_to_pd(const grammar& g);
    ~gr_to_pd();
    //inherited from grammar_alg
    std::string to_string() const;

    std::string get_moves() const;
    push_down get_push_down() const;
    private:
    push_down pd;
    void to_empty_stack_pd();
    std::vector<std::string> moves;

	
};
#endif // GR_T0_PD_H
