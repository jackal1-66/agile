#ifndef AGILE_UTILS_HH
#define AGILE_UTILS_HH

#include "AGILe/AGILe.hh"
#include <algorithm>

namespace AGILe {


  inline int nocase_cmp(const string& s1, const string& s2) {
    string::const_iterator it1 = s1.begin();
    string::const_iterator it2 = s2.begin();
    while ( (it1 != s1.end()) && (it2 != s2.end()) ) {
      if(::toupper(*it1) != ::toupper(*it2)) { // < Letters differ?
        // Return -1 to indicate smaller than, 1 otherwise
        return (::toupper(*it1) < ::toupper(*it2)) ? -1 : 1;
      }
      // Proceed to the next character in each string
      ++it1;
      ++it2;
    }
    size_t size1 = s1.size(), size2 = s2.size(); // Cache lengths
    // Return -1,0 or 1 according to strings' lengths
    if (size1 == size2) return 0;
    return (size1 < size2) ? -1 : 1;
  }


  inline string toLower(const string& s) {
    return boost::to_lower_copy(s);
  }


  inline string toUpper(const string& s) {
    return boost::to_upper_copy(s);
  }


  template <typename Real>
  inline bool fuzzyEquals(Real a, Real b, Real tolerance = 0.001) {
    const double absavg = fabs(a + b)/2.0;
    const double absdiff = fabs(a - b);
    return (absavg == 0.0 && absdiff == 0.0) || absdiff/absavg < tolerance;
  }


  /// Split a string with single-character delimiters, ignoring zero-length
  /// substrings. Designed for getting elements of filesystem paths, naturally.
  inline std::vector<std::string> split(string path, const string delim = ":") {
    if (delim.length() != 1) {
      throw runtime_error("Rivet::split(string): delimiter must be a single character.");
    }
    /// @todo Reduce copying of vectors somehow?
    std::vector<std::string> dirs;
    boost::split(dirs, path, boost::is_any_of(delim));
    return dirs;
  }



  template <typename T>
  inline std::string toString(const T& value) {
    std::string strval = lexical_cast<std::string>(value);
    //std::cout << "*" << value << "*" << strval << "*" << std::endl;
    return strval;
  }

  template <typename T>
  inline T as(const std::string& strvalue) {
    T tval = lexical_cast<T>(strvalue);
    return tval;
  }

  template <>
  inline bool as<bool>(const std::string& value) {
    if (nocase_cmp(value, "true") == 0  || nocase_cmp(value, "yes") == 0 || nocase_cmp(value, "on") == 0) return true;
    if (nocase_cmp(value, "false") == 0 || nocase_cmp(value, "no") == 0  || nocase_cmp(value, "off") == 0) return false;
    return as<int>(value);
  }

  inline int asInt(const std::string& value) { return as<int>(value); }
  inline double asDouble(const std::string& value) { return as<double>(value); }
  inline bool asBool(const std::string& value) {  return as<bool>(value); }


}
#endif


#ifndef CEDARSTD
#define CEDARSTD
namespace std {

  template <typename T>
  inline void operator+=(std::set<T>& s1, const std::set<T>& s2) {
    for (typename std::set<T>::const_iterator s = s2.begin(); s != s2.end(); ++s) {
      s1.insert(*s);
    }
  }

  template <typename T>
  inline void operator+=(std::vector<T>& s1, const std::vector<T>& s2) {
    for (typename std::vector<T>::const_iterator s = s2.begin(); s != s2.end(); ++s) {
      s1.push_back(*s);
    }
  }

  template <typename T>
  inline string join(const std::vector<T>& v, const std::string& sep = " ") {
    std::stringstream out;
    for (size_t i = 0; i < v.size(); ++i) {
      if (i != 0) out << sep;
      out << v[i];
    }
    return out.str();
  }

}

#endif
