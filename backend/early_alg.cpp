#include "early_alg.h"

void early_alg::step1()
{
    std::string t_info = "";
    for (std::list<sign_list>::iterator it = g.P[g.S].begin(); it != g.P[g.S].end(); ++it)
    {

        int z = 1;
        sign_list::iterator it2 = it->begin();
        sign_list e_signs;
        while (it2 != it->end() && e_set.count(*(it2)) > 0)
        {
            e_signs.push_back(*it2);
            s_rule sr(g.S, *(it), z);
            t_info += g.S.to_string() + "->" + it->to_string();
            t_info += "#" + sr.to_string() + "#" + e_signs.to_string() + "\n";
            table[0][0].insert(sr);
            ++z;
            ++it2;
        }
        s_rule sr(g.S, *(it), 0);
        t_info += g.S.to_string() + "->" + it->to_string();
        t_info += "#" + sr.to_string() + "\n";
        table[0][0].insert(sr);
    }
    info.push_back(t_info);
    state.push_back(STEP1);
    table_vec.push_back(table);
}

void early_alg::step2(const int& j)
{
    bool change;
    do
    {
        change = false;
        for (int i = 0; i <= j; ++i)
        {

            std::string t_info = "";
            sign_list e_signs_k;
            sign_list e_signs_z;

            for (std::set<s_rule>::iterator it = table[i][j].begin(); it != table[i][j].end(); ++it)
            {
                int z = 0;
                e_signs_z.clear();
                do
                {
                    if ((it->get_dot() + z) >= it->size())
                        continue;
                    sign b((*it)[it->get_dot() + z].to_string(), false);
                    if (g.P.count(b) > 0)
                    {
                        for (std::list<sign_list>::iterator it2 = g.P[b].begin(); it2 != g.P[b].end(); ++it2)
                        {
                            int k = 0;
                            e_signs_k.clear();
                            do
                            {

                                s_rule sr(b, *it2, k);
                                if (table[j][j].count(sr) == 0)
                                {
                                    t_info += b.to_string() + "->" + it2->to_string();
                                    t_info += "#" + sr.to_string() + "#" + it->to_string();
                                    t_info += "#" + std::to_string(i) + "#" + std::to_string(j);
                                    if (k > 0 || z > 0) // there is a non-terminal which is in e_set
                                    {
                                        t_info += "#" + e_signs_k.to_string() + e_signs_z.to_string() + "\n";
                                    }
                                    else
                                    {
                                        t_info += "\n";
                                    }
                                    table[j][j].insert(sr);
                                    change = true;
                                }
                                ++k;
                                if (k < it2->size())
                                    e_signs_k.push_back((*it2)[k]);
                            } while (k < it2->size() && e_set.count((*it2)[k]) > 0);
                            if (k == it2->size() && e_set.count((*it2)[k - 1]) > 0)
                            {
                                s_rule sr(b, *it2, k);
                                if (table[j][j].count(sr) == 0)
                                {
                                    t_info += b.to_string() + "->" + it2->to_string();
                                    t_info += "#" + sr.to_string() + "#" + it->to_string();
                                    t_info += "#" + std::to_string(i) + "#" + std::to_string(j);
                                    t_info += "#" + e_signs_k.to_string() + e_signs_z.to_string() + "\n";
                                    table[j][j].insert(sr);
                                    change = true;
                                }
                            }
                        }
                        ++z;
                        if ((it->get_dot() + z) < it->size())
                            e_signs_k.push_back((*it)[it->get_dot() + z]);
                    }
                } while (((it->get_dot() + z + 1) < it->size()) && e_set.count((*it)[it->get_dot() + z]) > 0
                         && !((*it)[it->get_dot() + z + 1]).Is_terminal());
            }

            if (t_info != "")
            {
                info.push_back(t_info);
                state.push_back(STEP2);
                table_vec.push_back(table);
            }
        }
    } while (change);
}

void early_alg::step4(const int& i, const int& j, const std::vector<sign>& a)
{
    std::string t_info = "";
    sign_list e_signs;
    for (std::set<s_rule>::iterator it = table[i][j - 1].begin(); it != table[i][j - 1].end(); ++it)
    {
        int k = 0;
        e_signs.clear();
        while (it->get_dot() + k < it->size() && e_set.count((*it)[it->get_dot() + k]) > 0)
        {
            e_signs.push_back((*it)[it->get_dot() + k]);
            ++k;
        }
        if (it->get_dot() + k < it->size())
        {
            sign b((*it)[it->get_dot() + k]);
            if (b == a[j - 1])
            {
                s_rule sr = *it;
                t_info += it->to_string();
                sr.set_dot(it->get_dot() + k + 1);
                t_info += "#" + sr.to_string() + "#" + std::to_string(i) + "#" + std::to_string(j);
                if (k > 0)
                {
                    t_info += "#" + e_signs.to_string() + "\n";
                }
                else
                {
                    t_info += "\n";
                }
                sr.set_dot(it->get_dot() + k + 1);
                table[i][j].insert(sr);
            }
        }
    }
    for (std::set<s_rule>::iterator it = table[i][j].begin(); it != table[i][j].end(); ++it)
    {
        int k = 0;
        e_signs.clear();
        while (it->get_dot() + k < it->size() && e_set.count((*it)[it->get_dot() + k]) > 0)
        {
            e_signs.push_back((*it)[it->get_dot() + k]);
            ++k;
        }
        if (it->get_dot() + k < it->size())
        {
            s_rule sr = *it;
            t_info += it->to_string();
            int k = 0;
            e_signs.clear();
            while (it->get_dot() + k < it->size() && e_set.count((*it)[it->get_dot() + k]) > 0)
            {
                e_signs.push_back((*it)[it->get_dot() + k]);
                ++k;
            }
            if (it->get_dot() + k <= it->size() && k > 0)
            {
                t_info += it->to_string();
                sr.set_dot(it->get_dot() + k);
                t_info += "#" + sr.to_string() + "#" + std::to_string(i) + "#" + std::to_string(j);
                if (k > 0)
                {
                    t_info += "#" + e_signs.to_string() + "\n";
                }
                else
                {
                    t_info += "\n";
                }
                sr.set_dot(it->get_dot() + k + 1);
                table[i][j].insert(sr);
            }
            t_info += "#" + sr.to_string() + "#" + std::to_string(i) + "#" + std::to_string(j);
            if (k > 0)
            {
                t_info += "#" + e_signs.to_string() + "\n";
            }
            else
            {
                t_info += "\n";
            }
            sr.set_dot(it->get_dot() + k + 1);
            table[i][j].insert(sr);
        }
    }
    if (t_info != "")
    {
        info.push_back(t_info);
        state.push_back(STEP4);
        table_vec.push_back(table);
    }
}

void early_alg::step5(const int& i, const int& j)
{
    bool change;
    do
    {
        change = false;
        for (int k = i; k < j; ++k)
        {
            std::string t_info = "";
            sign_list e_signs;
            for (std::set<s_rule>::iterator it = table[i][k].begin(); it != table[i][k].end(); ++it)
            {
                int m = 0;
                e_signs.clear();
                do
                {
                    if (it->get_dot() + m < it->size())
                    {
                        sign b = (*it)[it->get_dot() + m];
                        for (std::set<s_rule>::iterator it2 = table[k][j].begin(); it2 != table[k][j].end(); ++it2)
                        {
                            if ((it2->get_n() == b) && (it2->get_dot() == it2->size()))
                            {

                                s_rule sr = *it;
                                sr.set_dot(it->get_dot() + m + 1);
                                if (table[i][j].count(sr) == 0)
                                {
                                    t_info += it->to_string();
                                    t_info += "#" + sr.to_string() + "#" + it2->to_string();
                                    t_info
                                        += "#" + std::to_string(i) + "#" + std::to_string(j) + "#" + std::to_string(k);
                                    if (m > 0)
                                    {
                                        t_info += "#" + e_signs.to_string();
                                    }
                                    else
                                    {
                                        t_info += "\n";
                                    }

                                    table[i][j].insert(sr);
                                    change = true;
                                }
                            }
                        }
                        ++m;
                        if ((it->get_dot() + m) < it->size())
                            e_signs.push_back((*it)[it->get_dot() + m]);
                    }
                } while (it->get_dot() + m + 1 < it->size() && e_set.count((*it)[it->get_dot() + m]) > 0);

                for (std::set<s_rule>::iterator it = table[i][j].begin(); it != table[i][j].end(); ++it)
                {
                    int k = 0;
                    e_signs.clear();
                    while (it->get_dot() + k < it->size() && e_set.count((*it)[it->get_dot() + k]) > 0)
                    {
                        e_signs.push_back((*it)[it->get_dot() + k]);
                        ++k;
                    }
                    if (it->get_dot() + k <= it->size())
                    {
                        s_rule sr = *it;
                        t_info += it->to_string();
                        int k = 0;
                        e_signs.clear();
                        while (it->get_dot() + k < it->size() && e_set.count((*it)[it->get_dot() + k]) > 0)
                        {
                            e_signs.push_back((*it)[it->get_dot() + k]);
                            ++k;
                        }
                        if (it->get_dot() + k <= it->size() && k > 0)
                        {
                            t_info += it->to_string();
                            sr.set_dot(it->get_dot() + k);
                            t_info += "#" + sr.to_string() + "#" + std::to_string(i) + "#" + std::to_string(j);
                            if (k > 0)
                            {
                                t_info += "#" + e_signs.to_string() + "\n";
                            }
                            else
                            {
                                t_info += "\n";
                            }
                            table[i][j].insert(sr);
                        }
                        t_info += "#" + sr.to_string() + "#" + std::to_string(i) + "#" + std::to_string(j);
                        if (k > 0)
                        {
                            t_info += "#" + e_signs.to_string() + "\n";
                        }
                        else
                        {
                            t_info += "\n";
                        }
                        sr.set_dot(it->get_dot() + k + 1);
                        table[i][j].insert(sr);
                    }
                }
            }
            if (t_info != "")
            {
                info.push_back(t_info);
                state.push_back(STEP5);
                table_vec.push_back(table);
            }
        }
    } while (change);
}
early_alg::early_alg(const grammar& gr, const std::vector<sign>& a)
{
    int n = (int)a.size();
    this->g = gr;
    sign e("e", true);
    e_set = g.make_epsilon_set(e); // A eN : A->* e
    table.resize(n + 1);
    for (int i = 0; i < n + 1; ++i)
    {
        table[i].resize(n + 1);
    }
    table_vec.push_back(table);
    step1();
    int j = 0;
    while (j <= n)
    {
        step2(j);
        int i = j;
        ++j;
        if (j == n + 1)
        {
            break;
        }
        while (i >= 0)
        {
            step4(i, j, a);
            step5(i, j);
            --i;
        }
    }
    contains = false;
    for (int i = 0; !contains && i < (int)table[0].size(); ++i)
    {
        for (std::set<s_rule>::iterator it = table[i][a.size()].begin(); !contains && it != table[i][a.size()].end();
             ++it)
        {
            if (it->get_n() == g.S && it->size() == it->get_dot())
            {
                contains = true;
            }
        }
    }
    info.push_back("end");
    state.push_back(END);
}

early_alg::~early_alg() {}

std::string early_alg::get(const int& i, const int& j) const
{
    std::string s = "";
    for (std::set<s_rule>::iterator it = table_vec[alg_it][i][j].begin(); it != table_vec[alg_it][i][j].end(); ++it)
    {
        s += it->to_string();
        s += "\n";
    }
    return s;
}

std::string early_alg::to_string() const { return ""; }

early_alg::early_state early_alg::show_state() const { return state[alg_it]; }
