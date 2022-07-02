#include "grammar.h"

grammar::grammar()
{
}
grammar::grammar(const char* fname)
{
	std::ifstream f;
	f.open(fname);
	if(f.is_open())
	{
		
		char k[256];
		f.getline(k,256);
		sign temp(k,false);
		this->S=temp;

		f.getline(k,256);
		std::string s=k;
		split(s,this->N);	


		f.getline(k,256);
		s=k;
		split(s,this->T);
		std::string nt;
		
		while(!f.eof())
		{
			
			f>>nt;
		
			sign tmp(nt,false);
			
			f.getline(k,256);
			s=k;
			sign_list sign_lists;
			split(s,sign_lists,'|');
			std::list<sign_list> p;
			
			for (int i=0;i<sign_lists.size();++i)
			{
				sign_list ntv;
			    split(sign_lists[i],ntv);  
				p.push_back(ntv);
			}
			
			if(P.count(tmp)==0)
			{
				P[tmp]=p;
			}
		}
	/*	if(std::find(N.begin(),N.end(),S)==N.end())
		{
			N.push_back(S);
		}*/	
	    f.close();
	}
	else
	{
	std::cerr<<"rossz filenev"<<std::endl;
	}
	
}


grammar::grammar(const sign_list &n ,const sign_list &t,const std::map<sign,std::list<sign_list> >& p,const sign& s)
{
	this->N=n;
	this->T=t;
	this->P=p;
	this->S=s;
}


grammar::~grammar()
{
}

void grammar::split(const std::string str,sign_list &v,const char delim)
{
	char sub[256];
	std::istringstream iss(str);
	do
	{
		iss.getline(sub,256,delim);
		sign s(sub,false);
		if(!s.Is_empty())
		{
			v.push_back(s);
		}
	}
	while(iss);
}

 void grammar::split(const sign str,sign_list &v,const char delim)
 {
	char sub[256];
	std::istringstream iss((str.to_string()));
	do
	{
		iss.getline(sub,256,delim);
		sign* s= new sign(sub,false);
		sign_list::iterator it=std::find(this->N.begin(),this->N.end(),*s);
		if(it==this->N.end())
		{
			delete s;
			s=new sign(sub,true);
		}
		if(!(s->Is_empty()))
		{
			v.push_back(*s);
		}
		delete s;
	}
	while(iss);
 }
 
void grammar::replace(const sign& a,const sign & b)
{
    for(std::map<sign,std::list<sign_list> >::iterator it=P.begin();it!=P.end();++it)
    {
        for(std::list<sign_list>::iterator it2=it->second.begin();it2!=it->second.end();++it2)
        {
            for(sign_list::iterator it3=it2->begin();it3!=it2->end();++it3)
            {
                if((*it3)==a)
                {
                    *it3=b;
                }
            }
        }
    }
}


std::ostream& operator<<(std::ostream &s,grammar a)
{
	s<<"kezdojel:"<<" "<<a.S<<std::endl;
	
	s<<"terminalisok:"<<a.T<<" "<<std::endl;;
	
	s<<"nemterminalisok:"<<a.N<<" "<<std::endl;

	s<<"szabalyok:"<<std::endl;
	
	for(std::map<sign,std::list<sign_list> >::iterator it=a.P.begin();it!=a.P.end();++it)
	{
		std::pair<sign,std::list<sign_list > >v=*it;
		s<<v.first<<"->";
		std::list<sign_list>::iterator it2=v.second.begin();
		for(int i=0;i<int(v.second.size());++i)
		{
			s<<*it2;
			if(i>0 && (i%10)==0)
			{
				s<<std::endl;
				s<<v.first<<"->";
			}				
			else if(i!=(int)v.second.size()-1)
			{
				s<<"|";
			}
			it2++;
		}
		s<<std::endl;
	}
	return s;
}

sign grammar::gen_sign()
{
	sign a;
	sign_list::iterator	it;
	int count=0;
	do
	{
		a.gen_sign();
		it=std::find(N.begin(),N.end(),a);
		++count;
	}
    while(N.end()!=it && count<100);
    if(count==100)
    {
        count=0;
        do
        {
            sign a1(a.to_string() +std::to_string(count) ,false);
            it=std::find(N.begin(),N.end(),a1);
            ++count;
        }
        while(N.end()!=it);
    }
	return a;
}

std::list<sign_list>::iterator grammar::findprefix(const sign a)
{
	std::list<sign_list>::iterator it=this->P[a].begin();
	while(it!=P[a].end() && *(it->begin())!=a)
	{
		++it;
	}
	return it;
}

grammar grammar::chomsky() const
{
	grammar g=*this;
    //eliminate epsilon/lamda rules
    g.eliminate_epsilon();

    // create new roules for the long rules
    std::map<sign,std::list<sign_list> > tmp_p=g.P;
    for(int j=0;j<g.N.size();++j)
    {
        for(std::list<sign_list>::iterator it2=tmp_p[g.N[j]].begin();it2!=tmp_p[g.N[j]].end();++it2)
        {
            std::list<sign_list>::iterator rule=std::find(g.P[N[j]].begin(),g.P[N[j]].end(),*it2);
            for(int i=it2->size();rule!=g.P[N[j]].end() && i>2;--i)
            {

                sign a;
                sign_list sl;
                    if(rule!=g.P[N[j]].end())
                    {
                        sl.push_back(*(rule->end()-1));
                        rule->pop_back();
                        sl.push_front(*(rule->end()-1));
                        rule->pop_back();

                    }
                    if(!g.find_rule(sl,a) )
                    {
                        a=g.gen_sign();
                        g.N.push_back(a);
                        std::list<sign_list> l;
                        l.push_back(sl);
                        g.P[a]=l;

                    }
                    rule->push_back(a);
            }
        }
    }




     // substitute the chain rules
    bool changed;
	do
	{
        changed=false;
        for(sign_list::iterator it=g.N.begin();it!=g.N.end();++it)
        {
            std::set<sign> s_set;
            for(std::list<sign_list>::iterator it2=g.P[*it].begin();it2!=g.P[*it].end();)
            {
                if(it2->size()==1 && !it2->begin()->Is_terminal()) // A->B rule
                {
                    changed=true;
                    sign b=*(it2->begin()); // B
                    it2=g.P[*it].erase(it2); // delete A->B rule
                    if(s_set.count(b)==0)
                    {
                        sign_list A;
                        A.push_back(*it);
                        for(std::list<sign_list>::iterator it3=g.P[b].begin();it3!=g.P[b].end();++it3)  //insert B's rules to A's rules
                        {
                            if(*it3!=A) //do not insert A->A rule
                            g.P[*it].insert(g.P[*it].end(),*it3);
                        }
                //		it2=g.P[*it].begin();
                        s_set.insert(b); // if B will appear again
                    }
                }
                else
                {
                    ++it2;
                }
            }
        }
	}
    while(changed);


    g.eliminate_t();
    g.T=T;
    return g;
}


bool grammar::find_rule(const sign_list &a,sign &b)
{
	for(sign_list::iterator it=N.begin();it!=N.end();++it)
	{
		if(P[*it].size()==1 && (*(P[*it].begin())) == a)
		{
			b=*it;
			return true;
		}
	}
	return false;
}

void grammar::eliminate_t()
{
    sign e("e");
    for(int i=0;i<N.size();++i)
	{
        for(std::list<sign_list>::iterator it2=P[N[i]].begin();it2!=P[N[i]].end();++it2)
		{
			for(sign_list::iterator it3=it2->begin();it2->size()>1 && it3!=it2->end();++it3)
			{
                if(it3->Is_terminal() && (*it3)!=e)
				{
					sign_list s_list;
					s_list.push_back(*it3);
					sign x;					
                    if(!find_rule(s_list,x))	//if x->a does not exist for all x in N
					{					
						x=this->gen_sign();
						sign_list sl;
						std::list<sign_list> l; // make x->a rule
						sl.push_back(*it3);
						l.push_back(sl);			
						P[x]=l;
                        N.push_back(x);
                        it2=P[N[i]].begin();
                        *it3=x;
                        it3=it2->begin();
					}
                    else
                    {
					*it3=x; 	//replace a with x
                    }
				}
			}
		}
    }
}
void grammar::eliminate_epsilon()
{
	sign e("e");
	std::set<sign> e_set=make_epsilon_set(e);
	
	if(e_set.count(this->S)>0) // S0->e | S
	{
		bool find=false;
		for(sign_list::iterator it=N.begin(); !find && it!=N.end();++it)
		{
			for(std::list<sign_list>::iterator it2=P[*it].begin(); !find && it2!=P[*it].end();++it2)
			{
				for(sign_list::iterator it3=it2->begin(); !find && it3!=it2->end();++it3)
				{
					if(*it3==this->S)
					{
						find=true;
						sign s("S0",false);
						sign_list sl;
						std::list<sign_list> l;
						sl.push_back(this->S);
						l.push_back(sl);
						sl.pop_back();
						sl.push_back(e);
						l.push_back(sl);
						this->P[s]=l;
                        N.push_back(s);
                        S=s;
					}
				}
			}
		}	
    }

    std::vector<int> leave;
    std::set<int> stay;
    sign_list e_rule;
    e_rule.push_back(e);
    std::list<sign_list> l;
    for(int i=0;i!=N.size();++i)
    {
        l.clear();
        for(std::list<sign_list>::iterator it2=P[N[i]].begin();it2!=P[N[i]].end();++it2)
        {
            leave.clear();
            stay.clear();
            int c=0;
            for(sign_list::iterator it3=it2->begin();it3!=it2->end();++it3)
            {

                if(e_set.count(*it3)>0)
                {
                    leave.push_back(c);
                }
                else
                {
                    stay.insert(c);
                }
                ++c;

            }
            //construct the new rules
            if(leave.size()>0)
            {
                std::list<sign_list> new_rules=make_comb_rules(leave,stay,*it2);
                for(std::list<sign_list>::iterator it3=new_rules.begin();it3!=new_rules.end();++it3)
                {
                    l.push_back(*it3);
                }
            }
        }
        //delete epsilon rules
        std::list<sign_list>::iterator e_it=std::find(P[N[i]].begin(),P[N[i]].end(),e_rule);
        if(e_it!=P[N[i]].end() && N[i]!=S)
        {
            P[N[i]].erase(e_it);
        }
        //insert the new rules
        for(std::list<sign_list>::iterator it2=l.begin();it2!=l.end();++it2)
        {
            sign_list tmp_sl;
            tmp_sl.push_back(N[i]); //do not insert B -> B rules
            if(std::find(P[N[i]].begin(),P[N[i]].end(),*it2)==P[N[i]].end() && tmp_sl!=*it2)
            {
                P[N[i]].push_back(*it2);
            }
        }
    }
}
std::map<sign,int> grammar::make_sort()
{
	std::map<sign,int> m;
    m.insert(std::pair<sign,int>(S,0));
    int  j=0;
    for(int i=1;i<N.size();++i)
	{
        if(N[i]==S)
        {
            --j;
            continue;
        }
        m.insert(std::pair<sign,int>(N[i],i+j));
	}
	return m;
}


sign_list::iterator grammar::erase(const sign a)
{
    sign_list::iterator it;

    P.erase(a);
    it=N.erase(a);
	return it;
}

std::set<sign> grammar::make_epsilon_set(sign e)
{
	// make H0
	std::set<sign> s;
	std::map<sign,std::list<sign_list> >::iterator it;
	for(it=this->P.begin();it!=this->P.end();++it)
	{
		std::list<sign_list>::iterator it2;
		bool l=true;
		for(it2=it->second.begin();l && it2!=it->second.end() ;++it2)
		{
		
			if(it2->size()==1 && *(it2->begin()) == e)
			{
				s.insert(it->first);
				l=false;
			}
		}
	}
	//make Hn
	bool l=true;
	while(l)
	{
		l=false;
		for(it=this->P.begin();it!=this->P.end();++it)
		{
			l=false;
			if(s.count(it->first)==0)
			{
				std::list<sign_list>::iterator it2;
				for(it2=it->second.begin();it2!=it->second.end();++it2)
				{
					sign_list::iterator it3=it2->begin();
					while(it3!=it2->end() && s.count(*it3)>0)
					{
						++it3;
					}
					if(it3==it2->end())
					{
						s.insert(it->first);
						l=true;
					}
				}
			}
		}

	}
/*	for(std::set<sign>::iterator it=s.begin();it!=s.end();++it)
	{
		std::cout<<(*it)<<" ";
	}
	std::cout<<std::endl;*/
	return s;
}

void grammar::reduction()
{	
    bool find;
	std::set<sign> s_set;
    //occur in the right-hand sides of the rules?
    s_set.insert(S);
    for(int k=0;k<N.size();++k)
    {
        sign b=N[k];
        bool is_exist=false;
        if(b==S)
        {
            continue;
        }
        for(int i=0;i<N.size() && !is_exist;++i)
        {
            sign a=N[i];
            std::list<sign_list>::iterator it=P[a].begin();
            while(it!=P[a].end() && !is_exist)
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
    for(sign_list::iterator it=N.begin();it!=N.end();)
    {
        if(s_set.count(*it)==0)
        {
           it=erase(*it);

        }
        else
        {
            ++it;
        }
    }

    //reachable from S
    s_set.clear();
    s_set.insert(S);
    std::set<sign> ready;
    for(auto it=P[S].begin();it!=P[S].end();++it)
    {
        for(auto it2=it->begin();it2!=it->end();++it2)
        {
            if(!it2->Is_terminal())
            {
                s_set.insert(*it2);
            }
        }
    }
    ready.insert(S);
    do
    {
        find=false;
        for(auto it=N.begin();it!=N.end();++it)
        {
            if(ready.count(*it)==0 && s_set.count(*it)>0)
            {
                for(auto it2=P[*it].begin();it2!=P[*it].end();++it2)
                {
                    for(auto it3=it2->begin();it3!=it2->end();++it3)
                    {
                        if(!it3->Is_terminal())
                        {
                            s_set.insert(*it3);
                            find=true;
                        }
                    }
                }
                ready.insert(*it);
            }
        }
    }
    while(find);
    for(sign_list::iterator it=N.begin();it!=N.end();)
    {
        if(s_set.count(*it)==0)
        {
            it=erase(*it);
        }
        else
        {
            ++it;
        }
    }

    //there are rules with not existing non-terminals
    s_set.clear();
    for(sign_list::iterator it=N.begin();it!=N.end();++it)
    {
        s_set.insert(*it);
    }

    for(auto it=P.begin();it!=P.end();++it)
    {
        for(auto it2=it->second.begin();it2!=it->second.end();)
        {
            find=false;
            for(auto it3=it2->begin(); !find && it3!=it2->end();++it3)
            {
                if(s_set.count(*it3)==0 && !it3->Is_terminal())
                {
                    find=true;
                }
            }
            if(find)
            {
                it2=it->second.erase(it2);
            }
            else
            {
                ++it2;
            }
        }
    }
}


std::string grammar::to_string() const
{
    std::string s="";
    /*
    s<<"kezdojel:"<<a.S.to_string()<<std::endl;

    s<<"terminalisok:";
    for(int i=0;i<a.N.size();++i)
    {
        s<<a.N[i].to_string()<<" ";
    }
    s<<std::endl;

    s<<"nemterminalisok:";
    for(int i=0;i<a.T.size();++i)
    {
        s<<a.T[i].to_string()<<" ";
    }
    s<<std::endl;

    s<<"szabalyok:"<<std::endl;
    */
    

    s+=this->S.to_string();
    s+="->";
    std::map<sign,std::list<sign_list> > tmp_P=this->P;
    std::list<sign_list>::const_iterator it2=tmp_P[S].begin();
    for(int i=0;i<int(tmp_P[S].size());++i)
    {

       
        for(sign_list::const_iterator it3=it2->begin(); it3!=it2->end(); ++it3)
        {
            s+=" ";
            s+=it3->to_string();
        }
        if(i>0 && (i%5)==0 && (i+1)!=int(tmp_P[S].size()))
        {
            s+="\n";
            s+=this->S.to_string();
            s+="->";
        }
        else if(i!=(int)tmp_P[S].size()-1)
        {
            s+="|";
        }
        it2++;
    }
    s+="\n";

	std::map<sign,std::list<sign_list> >::const_iterator it=tmp_P.begin();
    while(it!=tmp_P.end())
    {

        std::pair<sign,std::list<sign_list > >v=*it;
        if(v.first!=this->S)
        {
			s+=v.first.to_string();
			s+="->";
			std::list<sign_list>::const_iterator it2=v.second.begin();
			for(int i=0;i<(int)(v.second.size());++i)
			{
				for(sign_list::const_iterator it3=it2->begin(); it3!=it2->end(); ++it3)
				{
					s+=" ";
					s+=it3->to_string();
				}
                if(i>0 && (i%5)==0 && (i+1)!=int(v.second.size()))
				{
					s+="\n";
					s+=v.first.to_string();
					s+="->";
				}				
				else if(i!=(int)v.second.size()-1)
				{
					s+="|";
				}
				it2++;
			}
			s+="\n";
        }
        ++it;
    }
    return s;
}


void grammar::find_derivables()
{
    std::set<sign> derivable;
    bool find=false;
    bool change;
    do
    {
        change=false;
        for(int i=0;i<N.size();++i)
        {
            if(derivable.count(N[i])>0)
            {
                continue;
            }
            find=false;
            for(std::list<sign_list>::iterator it=P[N[i]].begin(); !find && it!=P[N[i]].end();++it)
            {
                int c=0;
                for(sign_list::iterator it2=it->begin();!find && it2!=it->end();++it2)
                {
                    if( !it2->Is_terminal() && (derivable.count(*it2)==0) )
                    {
                       break;
                    }
                    else
                    {
                        ++c;
                    }
                }
                if(c==it->size())
                {
                    find=true;
                    derivable.insert(N[i]);
                    change=true;
                }
            }
        }
    }
    while(change);
    N.clear();
    for(std::set<sign>::iterator it=derivable.begin();it!=derivable.end();++it)
    {
        N.push_back(*it);
    }
    for(auto it=P.begin();it!=P.end();)
    {
        if(derivable.count(it->first)==0)
        {
            it=P.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for(int i=0;i<N.size();++i)
    {
        for(std::list<sign_list>::iterator it=P[N[i]].begin();it!=P[N[i]].end();)
        {
            bool find=false;
            for(sign_list::iterator it2=it->begin();!find && it2!=it->end();++it2)
            {
                if( !it2->Is_terminal() && (derivable.count(*it2)==0) )
                {
                    find=true;
                }

            }
            if(find)
            {
                it=P[N[i]].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void grammar::rename()
{
    std::map<sign,sign> names;
    int n_size=N.size();
    for(int i=0;i<n_size;++i)
    {
        if(N[i]!=this->S)
        {
            sign s=this->gen_sign();
            N.push_back(s);
            std::pair<sign,sign> p(N[i],s);
            names.insert(p);
        }
    }
     std::map<sign,std::list<sign_list> > tmp_p;
     for(auto it=P.begin();it!=P.end();++it)
     {
            for(std::list<sign_list>::iterator it2=it->second.begin();it2!=it->second.end();++it2)
            {
                for(sign_list::iterator it3=it2->begin();it3!=it2->end();++it3)
                {
                    if(!it3->Is_terminal() && (*it3)!=S)
                    {
                        *it3=names[*it3];

                    }

                }
                if(it->first!=S)
                {
                    if(tmp_p.count(names[it->first])==0)
                    {
                        std::list<sign_list> l;
                        l.push_back(*it2);
                        tmp_p[names[it->first]]=l;
                    }
                    else
                    {
                        tmp_p[names[it->first]].push_back(*it2);
                    }
                }
                else
                {
                    if(tmp_p.count(it->first)==0)
                    {
                        std::list<sign_list> l;
                        l.push_back(*it2);
                        tmp_p[it->first]=l;
                    }
                    else
                    {
                        tmp_p[it->first].push_back(*it2);
                    }

                }

            }
     }
     P=tmp_p;
     N.clear();
     N.push_back(S);
     for(auto it=names.begin();it!=names.end();++it)
     {
        N.push_back(it->second);
     }

}

void grammar::to_file(const std::string& fname) const
{
	std::ofstream f;
	f.open(fname);
	if(f.is_open())
	{
		f<<S<<"\n";
		f<<N<<"\n";
		f<<T<<"\n";
		std::map<sign,std::list<sign_list> > tmp_P=this->P;
		for(sign_list::const_iterator it=N.begin();it!=N.end();++it)
		{          
			f<<*it<<" ";
            int c=0;
			for(std::list<sign_list>::iterator it2=tmp_P[*it].begin();it2!=tmp_P[*it].end();++it2)
			{
                ++c;
				f<<*it2;
            //    if(c!=it2->size())
                    f<<"|";

			}
            f<<"\n";
		}	
	}
}

void grammar::make_combination_list(std::vector<std::vector<int> >& store, std::vector<int> prefix, int current_number, int max_number, int need_more)
{
      if(need_more == 0)
      {
            store.push_back(prefix);
            return;
      }

      for(int next_number = current_number; need_more <= max_number - next_number + 1; next_number++)
      {
        std::vector<int> temp = std::vector<int>(prefix);
        temp.push_back(next_number);
        make_combination_list(store, temp, next_number+1, max_number, need_more - 1);
      }
}

std::list<sign_list> grammar::make_comb_rules(std::vector<int> leave,std::set<int> stay,const sign_list &rule)
{
    std::vector<int> empty_vec;
    std::vector<std::vector<int> >comb_list;
    std::list<sign_list> new_rules;

    std::set<int> index;
    for(int i=0;i<(int)leave.size();++i)
    {
        comb_list.clear();
        sign_list new_rule;
        index=stay;
        if(i>0)
        {
            make_combination_list(comb_list,empty_vec,0,leave.size()-1,i);
            for(std::vector<std::vector<int> >::iterator it=comb_list.begin();it!=comb_list.end();++it)
            {
                index=stay;
                new_rule.clear();
                for(std::vector<int>::iterator it2=it->begin();it2!=it->end();++it2)
                {
                    index.insert(leave[*it2]);
                }
                for(std::set<int>::iterator it2=index.begin();it2!=index.end();++it2)
                {
                    new_rule.push_back(rule[*it2]);
                }
                if(new_rule.size()>0)
                {
                    new_rules.push_back(new_rule);
                }
            }
        }
        else
        {
            new_rule.clear();
            for(std::set<int>::iterator it=index.begin();it!=index.end();++it)
            {
                new_rule.push_back(rule[*it]);
            }
            if(new_rule.size()>0)
            {
                new_rules.push_back(new_rule);
            }

        }

    }
    return new_rules;
}

void grammar::substitute_pd_e_rules()
{
    sign e("e");
    sign_list epsilon_rule;
    epsilon_rule.push_back(e);
    std::set<sign> e_rule_set;
    for(auto it=P.begin();it!=P.end();++it)
    {
        if(it->second.size()==1 && (*(it->second.begin()))==epsilon_rule)
        {
            e_rule_set.insert(it->first);
        }
    }
    for(int i=0;i<N.size();++i)
    {
        for(std::list<sign_list>::iterator it2=P[N[i]].begin();it2!=P[N[i]].end();++it2)
        {
            for(sign_list::iterator it3=it2->begin();it3!=it2->end();)
            {
                if(e_rule_set.count(*it3)>0)
                {
                    it3=it2->erase(it3);
                }
                else
                {
                    ++it3;
                }
            }
        }
    }
    for(std::set<sign>::iterator it=e_rule_set.begin();it!=e_rule_set.end();++it)
    {
        N.erase(*it);
        P.erase(*it);
    }
}
