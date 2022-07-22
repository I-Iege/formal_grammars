#include "pd_to_gr.h"



pd_to_gr::pd_to_gr(const push_down& pd)
{
     grammar g;
     sign e("e");
     sign s("S",false);
     g.S=s;
     g.N.push_back(s);
     std::set<sign> n_terminals;
     std::list<sign_list> sl;
     for(sign_list::const_iterator it=pd.K.begin();it!=pd.K.end();++it)
     {
         std::string str=pd.Q0.to_string()+pd.Z0.to_string()+it->to_string();
         sign t(str,false);
         sign_list l;
         l.push_back(t);
         sl.push_back(l);
     }
     g.P[s]=sl;
     sign_list tue=pd.T;
     tue.push_back(e);
     for(auto it=pd.M.begin();it!=pd.M.end();++it)
     {
         move mv(it->first);
         sign c("c",false);
         std::list<result> l=it->second;
         for(std::list<result>::iterator it2=l.begin();it2!=l.end();++it2)
         {

             if(it2->stack.size()==0)
             {
                 std::string str_t=mv.c_state.to_string()+ mv.stack.to_string()+it2->n_state.to_string();
                 sign t(str_t,false);
                 n_terminals.insert(t);
                 std::list<sign_list> l;
                 sign_list sl;
                 sl.push_back(mv.c_terminal);
                 l.push_back(sl);
                 if(g.P.count(t)>0)
                 {
                     if((std::find(g.P[t].begin(),g.P[t].end(),sl)==g.P[t].end()))
                     g.P[t].push_back(sl);
                 }
                 else
                 {
                     g.P[t]=l;
                 }
             }
             else if(it2->stack.size()==1)
             {
                 for(sign_list::const_iterator it3=pd.K.begin();it3!=pd.K.end();++it3)
                 {
                     std::string str_t=mv.c_state.to_string()+ mv.stack.to_string()+it3->to_string();
                     sign t(str_t,false);
                     str_t=it2->n_state.to_string() + (it2->stack.begin()->to_string())+ it3->to_string();
                     sign t2(str_t,false);
                     std::list<sign_list> l;
                     n_terminals.insert(t);
                     n_terminals.insert(t2);
                     sign_list sl;
                     sl.push_back(mv.c_terminal);
                     sl.push_back(t2);
                     l.push_back(sl);
                     if(g.P.count(t)>0)
                     {
                         if((std::find(g.P[t].begin(),g.P[t].end(),sl)==g.P[t].end()))
                         g.P[t].push_back(sl);
                     }
                     else
                     {
                         g.P[t]=l;
                     }
                 }
             }
             else
             {
                 for(sign_list::const_iterator it3=pd.K.begin();it3!=pd.K.end();++it3)
                 {
                     for(sign_list::const_iterator it4=pd.K.begin();it4!=pd.K.end();++it4)
                     {
                         if(mv.c_terminal==e)
                            continue;
                         std::string  tmp_str=mv.c_state.to_string()+ mv.stack.to_string()+it4->to_string();
                         sign nt1(tmp_str,false);
                         tmp_str=it2->n_state.to_string() + it2->stack[1].to_string() + it3->to_string();
                         sign nt2(tmp_str,false);
                         tmp_str=it3->to_string()+ it2->stack[0].to_string() + it4->to_string();
                         sign nt3(tmp_str,false);
                         sign_list sl;
                         n_terminals.insert(nt1);
                         n_terminals.insert(nt2);
                         n_terminals.insert(nt3);
                         sl.push_back(mv.c_terminal);
                         sl.push_back(nt2);
                         sl.push_back(nt3);
                         std::list<sign_list> l={sl};
                         if(g.P.count(nt1)>0)
                         {
                             if((std::find(g.P[nt1].begin(),g.P[nt1].end(),sl)==g.P[nt1].end()))
                             g.P[nt1].push_back(sl);

                         }
                         else
                         {
                              g.P[nt1]=l;
                         }
                     }
                 }
             }
         }
     }
     for(std::set<sign>::iterator it=n_terminals.begin();it!=n_terminals.end();++it)
     {
         g.N.push_back(*it);
     }

     gr.push_back(g);
     info.push_back("redukálás");
    g.find_derivables();
   // gr.push_back(g);
  //  info.push_back("redukálás");
    g.reduction();
     gr.push_back(g);

     info.push_back("epszilon szabályok elhagyása");
     g.substitute_pd_e_rules();
     gr.push_back(g);
     info.push_back("átnevezés");
     g.rename();
     gr.push_back(g);
     info.push_back("ok");
}

pd_to_gr::~pd_to_gr()
{
}
grammar pd_to_gr::get_grammar() const
{
     return gr[alg_it];
}


std::string pd_to_gr::to_string() const
{
    return gr[alg_it].to_string();
}

