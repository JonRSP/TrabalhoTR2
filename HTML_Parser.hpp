#ifndef HTML_PRS_H
#define HTML_PRS_H
#include <regex>
#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <set>

class HTML_Parser
{
public:
	static std::set<std::string> getUrl   (const char*);
	static std::set<std::string> getSource(const char*);
	static std::set<std::string> getImport(const char*);
	static std::string 					 getHtml  (const char*);
};
#endif
