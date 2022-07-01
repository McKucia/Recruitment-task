#include <iostream>
#include <string>
#include <algorithm>
 
const std::string WHITESPACE = " \n\r\t";
 
std::string trim(const std::string &s)
{
    int start = s.find_first_not_of(WHITESPACE);
	int end = s.find_last_not_of(WHITESPACE);
	std::string tmp = (start == std::string::npos) ? "" : s.substr(start);
	tmp = end == (std::string::npos) ? "" : tmp.substr(0, end + 1);
    return tmp;
}

int main()
{
    std::string s = "      	przykładowy string ";
    std::cout << trim(s) << std::endl;
 
    return 0;
}