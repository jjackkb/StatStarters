#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
  Member();
  Member(std::string &);
  Member(std::string &, std::string &);
  void set_memberId(std::string &);
  void set_memberAbbrev(std::string &);
  std::string get_memberId();
  std::string get_memberAbbrev();

private:
  std::string memberId_;
  std::string memberAbbrev_;
};

#endif // MEMBER_H