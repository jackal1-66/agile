#ifndef AGILE_AgileSTL_HH
#define AGILE_AgileSTL_HH

#include <typeinfo>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>

namespace AGILe {

  using std::set;
  using std::map;
  using std::multimap;
  using std::type_info;
  using std::string;
  using std::less;
  using std::vector;
  using std::list;
  using std::pair;
  using std::make_pair;
  using std::runtime_error;
  using std::exception;
  using std::min;
  using std::stringstream;
  using std::istringstream;
  using std::ostringstream;
  using std::max;

  // Prefer to encourage Log::getLog()
  // using std::cout;
  // using std::cerr;

  using std::ostream;
  using std::istream;
  using std::cin;
  using std::setw;
  using std::endl;

}

#endif
