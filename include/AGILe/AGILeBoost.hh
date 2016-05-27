#ifndef AGILE_AGILEBOOST_HH
#define AGILE_AGILEBOOST_HH

#include "boost/smart_ptr.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/assign.hpp"

#include <boost/algorithm/string.hpp>

#include "boost/foreach.hpp"
#define foreach BOOST_FOREACH

namespace AGILe {
  using boost::shared_ptr;
  using boost::lexical_cast;
  using namespace boost::assign;
}

#endif
