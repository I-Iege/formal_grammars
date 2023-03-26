#include "gr_to_pd.h"

gr_to_pd::gr_to_pd(const grammar &h) {
  grammar g = h.chomsky();
  sign e("e");
  sign z0("z0", false);
  sign q0("0", false);
  sign qh("h", false);
  sign_list sl;
  sl.push_back(e);

  pd.T = g.T;
  pd.Z = g.N;
  pd.K = g.N;
  pd.K.push_back(q0);
  pd.K.push_back(qh);
  pd.Z.push_back(z0);
  pd.H.insert(qh);
  pd.Z0 = z0;
  pd.Q0 = q0;
  // type 1

  bool find = false;
  std::string t_info = "";
  for (std::list<sign_list>::iterator it = g.P[g.S].begin();
       !find && it != g.P[g.S].end(); ++it) {
    if (it->size() == 1 && *(it->begin()) == e) {
      find = true;
      move mv(z0, q0);
      sign_list sl_t;
      sl_t.push_back(z0);
      result r(sl_t, g.S);
      std::list<result> rl;
      rl.push_back(r);
      pd.M[mv] = rl;
      t_info += mv.to_string() + "->" + r.to_string();
      t_info += "<br/>";
    }
  }
  moves.push_back(t_info);
  // moves=this->to_string();

  // type 2.

  t_info = "";
  for (sign_list::iterator it = g.N.begin(); it != g.N.end(); ++it) {
    for (std::list<sign_list>::iterator it2 = g.P[*it].begin();
         it2 != g.P[*it].end(); ++it2) {
      if (it2->size() == 1 && it2->begin()->Is_terminal() &&
          (*(it2->begin())) != e) {
        std::string tmp_s = it->to_string();
        sign q(tmp_s, false);
        sign_list sl_t;
        sl_t.push_back(z0);
        move mv(z0, q0, *(it2->begin()));
        result r(sl_t, q);
        t_info += mv.to_string() + "->" + r.to_string();
        t_info += "<br/>";
        if (pd.M.count(mv) == 0) {
          std::list<result> rl;
          rl.push_back(r);
          pd.M[mv] = rl;
        } else {
          pd.M[mv].push_back(r);
        }
      }
    }
  }
  moves.push_back(t_info);
  // type3
  t_info = "";
  for (sign_list::iterator it = g.N.begin(); it != g.N.end(); ++it) {
    for (std::list<sign_list>::iterator it2 = g.P[*it].begin();
         it2 != g.P[*it].end(); ++it2) {
      if (it2->size() == 1 && it2->begin()->Is_terminal()) {
        for (sign_list::iterator it3 = g.N.begin(); it3 != g.N.end(); ++it3) {
          for (sign_list::iterator it4 = pd.Z.begin(); it4 != pd.Z.end();
               ++it4) {
            move mv(*it4, *it3, *(it2->begin()));
            sign_list sl_t;
            sl_t.push_back(*it4);
            sl_t.push_back(*it3);
            result r(sl_t, *it);
            t_info += mv.to_string() + "->" + r.to_string() + "<br/>";
            if (pd.M.count(mv) == 0) {
              std::list<result> rl;
              rl.push_back(r);
              pd.M[mv] = rl;
            } else {
              pd.M[mv].push_back(r);
            }
          }
        }
      }
    }
  }
  moves.push_back(t_info);
  // type4
  t_info = "";
  for (sign_list::iterator it = g.N.begin(); it != g.N.end(); ++it) {
    for (std::list<sign_list>::iterator it2 = g.P[*it].begin();
         it2 != g.P[*it].end(); ++it2) {
      if (it2->size() == 2) {
        move mv(*(it2->begin()), *(it2->begin() + 1));
        sign_list sl_t;
        result r(sl_t, *it);
        t_info += mv.to_string() + "->" + r.to_string() + "<br/>";
        if (pd.M.count(mv) == 0) {
          std::list<result> rl;
          rl.push_back(r);
          pd.M[mv] = rl;
        } else {
          pd.M[mv].push_back(r);
        }
      }
    }
  }
  moves.push_back(t_info);

  // type5
  t_info = "";
  move mv(z0, h.S);
  sign_list sl_t;
  result r(sl_t, qh);
  t_info += mv.to_string() + "->" + r.to_string() + "<br/>";
  if (pd.M.count(mv) == 0) {
    std::list<result> rl;
    rl.push_back(r);
    pd.M[mv] = rl;
  } else {
    pd.M[mv].push_back(r);
  }
  pd.H.insert(qh);
  moves.push_back(t_info);

  this->to_empty_stack_pd();
  t_info = this->to_string();
  moves.push_back(t_info);
  info.push_back("z<sub>0</sub>q<sub>0</sub>->z<sub>0</sub>q<sub>S</sub>");
  info.push_back("z<sub>0</sub>q<sub>0</sub>a->z<sub>0</sub>q<sub>X</sub>");
  info.push_back("Zq<sub>Y</sub>a->ZYq<sub>X</sub>");
  info.push_back("Z>q<sub>Y</sub>->q<sub>X</sub>");
  info.push_back("z<sub>0</sub>q<sub>S</sub>->q<sub>h</sub>");
  info.push_back("ok");
}

std::string gr_to_pd::to_string() const {
  std::string str = "";
  for (std::map<move, std::list<result>>::const_iterator it = pd.M.begin();
       it != pd.M.end(); ++it) {
    std::pair<move, std::list<result>> pr = *it;
    for (std::list<result>::iterator it2 = pr.second.begin();
         it2 != pr.second.end(); ++it2) {
      str += pr.first.to_string() + "->" + it2->to_string() + "<br/>";
    }
  }
  return str;
}

void gr_to_pd::to_empty_stack_pd() {
  sign z0("z0", false);
  sign e("e");
  sign q0("0", false);
  sign z00("z0\'", false);
  sign q00("0\'", false);
  sign qh("h\'", false);
  pd.H.insert(qh);
  pd.K.push_back(q00);
  pd.Z.push_back(z00);
  pd.K.push_back(qh);
  sign_list sl;
  sl.push_back(z00);
  sl.push_back(z0);

  result r(sl, q0);
  std::list<result> rl = {r};
  move mv(z00, q00);
  pd.M[mv] = rl;

  for (std::set<sign>::iterator it = pd.H.begin(); it != pd.H.end(); ++it) {
    for (sign_list::iterator it2 = pd.Z.begin(); it2 != pd.Z.end(); ++it2) {
      move mv(*it2, *it);
      sign_list sl;
      result r(sl, qh);
      if (pd.M.count(mv) == 0) {
        std::list<result> l = {r};
        pd.M[mv] = l;
      } else {
        pd.M[mv].push_back(r);
      }
    }
  }
}
gr_to_pd::~gr_to_pd() {}

std::string gr_to_pd::get_moves() const { return moves[alg_it]; }

push_down gr_to_pd::get_push_down() const { return pd; }
