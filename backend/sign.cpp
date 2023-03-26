#include "sign.h"

sign::sign() {
  str = "";
  t = false;
}
sign::sign(const std::string &name, const bool &term) : str(name), t(term) {}

sign::sign(const char *name, const bool &term) : str(name), t(term) {}

sign::sign(const sign &a) {
  this->str = a.str;
  this->t = a.t;
}

std::string sign::to_string() const { return str; }
bool sign::Is_empty() const { return (str.length() == 0); }

bool sign::Is_terminal() const { return t; }

bool sign::Is_equal(const std::string &s) { return this->str == s; }

void sign::gen_sign() {
  char v1 = (rand() % 26) + 65;
  char v2[2];
  v2[0] = v1;
  v2[1] = '\0';
  this->str = std::string(v2);
  this->t = false;
}
sign &sign::operator=(const char *a) {
  this->str = a;
  this->t = false;
  return *this;
}
sign &sign::operator=(const sign &a) {
  this->str = a.str;
  this->t = a.t;
  return *this;
}

bool operator==(const sign &a, const sign &b) { return a.str == b.str; }

bool operator!=(const sign &a, const sign &b) { return !(a.str == b.str); }

bool operator<(const sign &a, const sign &b) { return a.str < b.str; }

bool operator>(const sign &a, const sign &b) { return a.str > b.str; }

std::ostream &operator<<(std::ostream &s, sign a) {
  s << a.to_string();
  return s;
}
