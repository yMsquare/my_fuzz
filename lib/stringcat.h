
#ifndef STRINGCAT_H
#define STRINGCAT_H
#include <string>
using namespace std;

string CatString(const std::optional<string>& str1, const std::optional<string>& str2) {
   return  str1.value()+ str2.value();
}

string ReverseString(const std::optional<string>& str1) {
   string bs =str1.value_or("");
   int len = bs.length();
   for (int i = 0;i<len/2;i++) {
      char tmp;
      tmp = bs[len-i-1];
      bs[len-i-1] = bs[i];
      bs[i]  = tmp;
   }
   return bs;
}



#endif //STRINGCAT_H
