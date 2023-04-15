#include "greibach.h"



greibach::greibach(const grammar& gr)
{	
    current=gr;
    current.eliminate_epsilon();
    g.push_back(current);

    eliminate_t();      //elininate terminals in long rules
    e_left_recursion(); //eliminate A->AX rules
    num=current.make_sort();
    sort_n();             //eliminate Ai->Aj i>j rules
    substitute_all();   //substitute non-terminals
    reduction();    //leave the unused rules
    info.push_back("end");
    state.push_back(END);

} 

greibach::~greibach()
{
}




greibach::greibach_state greibach::show_state() const
{
    if(alg_it<((int)state.size()-1))
	{
        return state[alg_it];
	}
	else
	{
		return END;
	}

}
std::string greibach::to_string() const
{
    return g[alg_it].to_string();
}

std::string greibach::sequence() const
{
    std::string str="";
    for(int i=0;i<g[alg_it].N.size();++i)
    {
        for(std::map<sign,int>::const_iterator it=num.begin();it!=num.end();++it)
        {
            if(it->second==i)
            {
                str+=it->first.to_string() + " ";
            }
        }
    }
    return str;
}
const grammar& greibach::get_grammar() const
{
    return g[alg_it];
}
		
const grammar& greibach::get_result() const
{ 
    return g.back(); 
}

void greibach::eliminate_t()
{
    grammar h=current;
    for(int i=0;i<h.N.size();++i)
	{
        for(std::list<sign_list>::iterator it2=h.P[h.N[i]].begin();it2!=h.P[h.N[i]].end();++it2)
        {
            for(sign_list::iterator it3=(it2->begin()+1);(it2->size()>1) && (it3!=it2->end());++it3)
            {
				if(it3->Is_terminal())
				{
					sign_list s_list;
					s_list.push_back(*it3);
					sign x;					
					if(!h.find_rule(s_list,x))	//if x->a does not exist
					{					
                        x=current.gen_sign();
						sign_list sl;
						std::list<sign_list> l; // make x->a rule
						sl.push_back(*it3);
						l.push_back(sl);			
                        h.P[x]=l;
                        h.N.push_back(x);
					}
					std::string tmp_s=it3->to_string();
                    *it3=x; 	//replace a with x
                    //commit changes
                    current=h;
                    g.push_back(current);
                    std::string t_info=x.to_string()+"->"+ tmp_s;
                    info.push_back(t_info);
                    state.push_back(NON_TERMINAL);
				}
			}

        }
	}
}

void greibach::reduction()
{	
    grammar h=current;
	
	std::set<sign> s_set;
	//szerepel e a nemterminalis szabalyok bal oldalan
	s_set.insert(h.S);	//S nek nem kell
	for(int k=0;k<h.N.size();++k)
	{
		sign b=h.N[k];
		bool is_exist=false;
		if(b==h.S)
		{
			continue;
		}
		for(int i=0;i<h.N.size() && !is_exist;++i)
		{
			sign a=h.N[i];
			std::list<sign_list>::iterator it=h.P[a].begin();
			while(it!=h.P[a].end() && !is_exist)
			{
				sign_list::iterator it2=std::find(it->begin(),it->end(),b);
				if(it2!=it->end())
				{
					s_set.insert(b);
					is_exist=true;
				}
				++it;
			}
		}
	}
	
	for(sign_list::iterator it=h.N.begin();it!=h.N.end();)
	{
			if(s_set.count(*it)==0)
			{
				std::string tmp_s=it->to_string();
				it=h.erase(*it);
                current=h;
                g.push_back(current);
                std::string t_info=tmp_s;
                        	info.push_back(t_info);
                        	state.push_back(REDUCTION);			
			}
			else
			{
				++it;
			}

			
	}

    //delete equal non-terminals
 /*   s_set.clear();
    bool find;
    std::vector<std::vector<sign>>  equal_list;
    for(sign_list::iterator it=h.N.begin();it!=h.N.end();++it)
    {
        find=false;
        if(s_set.count(*it)>0)
        {
            continue;
        }
        std::vector<sign> equals;
        for(sign_list::iterator it2=h.N.begin();it2!=h.N.end();++it2)
        {
            if(s_set.count(*it)>0 || (*it)==(*it2))
            {
                continue;
            }

            equals.push_back(*it);
            if(h.P[*it]==h.P[*it2]) //+ it* not in P[*it2]
            {
                s_set.insert(*it2);
                equals.push_back(*it2);
                find=true;
            }
        }
        if(find)
        {
            equal_list.push_back(equals);
        }
    }
    for(std::set<sign>::iterator it=s_set.begin();it!=s_set.end();++it)
    {
        h.N.erase(*it);
        h.P.erase(*it);
    }
    //replace all equal non-terminal with A
    for(std::vector<std::vector<sign> >::iterator it=equal_list.begin();it!=equal_list.end();++it)
    {
        sign A=*(it->begin());
        for(std::vector<sign>::iterator it2=(it->begin()+1);it2!=it->end();++it2)
        {
            h.replace(*it2,A);
        }
    }
    current=h;
    g.push_back(current);
    std::string t_info="azonos nemterminálisok törlése\n";
                info.push_back(t_info);
                state.push_back(REDUCTION);*/

}


void greibach::substitute(grammar& h,const sign a,std::list<sign_list>::iterator r)
{
	sign s=*(r->begin());
	sign_list a_rule;
	a_rule.push_back(a);
	if(!s.Is_terminal() && h.P[s].size()>0)
	{
        	std::list<sign_list> L=h.P[s];
        	for(std::list<sign_list>::iterator it=L.begin();it!=L.end();++it)
		{
            		sign_list r2=*r;
            		r2.pop_front();
            		r2.push_front(*it);
            		h.P[a].push_back(r2);
		}
        	r=h.P[a].erase(r);
        	current=h;
        	g.push_back(current);
	}

}


void greibach::substitute_all()
{
        grammar h=current;
        for(int n=h.N.size()-1;n>=0;--n)
		{
            for (int i=0;i<h.N.size();++i)
			{
                sign a=h.N[i];
                std::list<sign_list>::iterator it=h.P[a].begin();
                while(it!=h.P[a].end())
				{
					sign b=*(it->begin());
					if(!b.Is_terminal() && num[b]==n)
					{
                        std::string t_info=b.to_string();
                        info.push_back(t_info);
                        state.push_back(SUBSTITUTE);
                        substitute(h,a,it);
                        it=h.P[a].begin();
					}
					else
					{
						++it;
					}	
				}
			}
		}
}

void greibach::e_left_recursion()
{
    grammar h=current;
    for (int i=0;i<h.N.size();++i)
	{
        	sign a=h.N[i];
        	std::list<sign_list>::iterator it=h.findprefix(a);
		std::list<sign_list> d;
		sign z;
		bool is_found=false;
        	std::string t_info="";
        	while(it!=h.P[a].end())
		{
		//	std::cout<<a<<"->"<<a<<std::endl;
        	//	std::string t_info="";


			if(!is_found)
			{
                		t_info+=a.to_string() + "->" + it->to_string();
                		z=h.gen_sign();
                		h.N.push_back(z);
				is_found=true;
			}
            		else
            		{
                		t_info+="|" + it->to_string();
            		}	
			// Z->AZ szabalyok beszurasa
					
			it->pop_front();
			d.push_back(*it);
			it->push_back(z);
			d.push_back(*it);

            		h.P[a].erase(it);
            		it=h.findprefix(a);

		}
		// A szabalyok kibővitese
		if(d.size()>0)
		{
            h.P[z]=d;
            t_info+="#"+ z.to_string()+"->";
            for(std::list<sign_list>::iterator it2=d.begin();it2!=d.end();++it2)
            {
                if(it2!=d.begin())
                {
                    t_info+="|";
                }
                t_info+=it2->to_string();
            }
            t_info+="#";
            it=h.P[a].begin();
            int p_size=(int)h.P[a].size();
			if(p_size>0)
			{
				for (int j=0;j<p_size;++j)	
				{
                    if(j!=0)
                    {
                        t_info+="|";
                    }
                    else
                    {
                        t_info+=a.to_string() + "->";
                    }
                    sign_list r=*it;
                    r.push_back(z);
                    h.P[a].push_back(r);
                    t_info+=r.to_string();
                    ++it;
				}
			}
			else
			{
				sign_list r;
				r.push_front(z);
                h.P[a].push_back(r);
            }
            info.push_back(t_info);
            state.push_back(LEFT_REC);
            current=h;
            g.push_back(current);
		//	std::cout<<*this<<std::endl;
		}
	}
	


}


void greibach::sort_n()
{
    grammar h=current;
    for (int i=0;i<h.N.size();++i)
	{
        sign a=h.N[i];
        std::list<sign_list>::iterator it=h.P[a].begin();
        while(it!=h.P[a].end())
		{
			sign b=*(it->begin());
			if(!b.Is_terminal() && num.count(a)>0 && num[a]>num[b])
			{
				std::string t_info="";
                t_info+=a.to_string() + "->" + it->to_string()+"#" +a.to_string() +">"+b.to_string() +"#"+b.to_string();
				info.push_back(t_info);
				state.push_back(SORT);		
                substitute(h,a,it);
            //    e_left_recursion();
                h=current;
                it=h.P[a].begin();
			}
			else
			{
				++it;
			}
		}
	}
}

