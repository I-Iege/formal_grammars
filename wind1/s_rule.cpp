#include "s_rule.h"

s_rule::s_rule(sign k,const sign_list& a,int n) : sign_list(a),n(k), dot(n)
{
}

bool operator<(const s_rule& a, const s_rule& b)
{
	if(a.n!=b.n)
	{
		return a.n<b.n;
	}
	else if(a.dot!=b.dot)
	{
		return a.dot<b.dot;
	}
	else
	{
		int i;
		for(i=0;(int)a.r.size()>i && (int)b.r.size()>i && a.r[i]==b.r[i];++i);
		if(a.size()==i)
		{
			if(b.size()==i)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if(b.size()==i)
		{
			return false;
		}
		else
		{
			return a[i]<b[i];
		}
	}	
}

bool operator==(const s_rule& a, const s_rule& b)
{
	if(  a.r==b.r && a.n==b.n && a.dot==b.dot)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const s_rule& a, const s_rule& b)
{
	return !(a==b);
}

int s_rule::get_dot() const
{
	return this->dot;
}

void s_rule::set_dot(const int a)
{
	this->dot=a;
}
sign s_rule::get_n() const
{
	return this->n;
}

std::string s_rule::to_string() const
{
	std::string s="";
	s+=this->n.to_string();
	s+="->";
	for(int i=0;i<this->size();++i)
	{
        	if(i==this->dot)
		{
			s+=".";
		}
        	s+=" ";
		s+=(*this)[i].to_string();
	}
	if(this->size()==this->dot)
	{
		s+=".";
	}
	return s;

}
std::ostream& operator<<(std::ostream &s,const s_rule &a)
{
	s<<a.to_string();
	return s;
}


