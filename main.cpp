#include <cctype>  // for use of toupper or tolower functions
#include <iostream>

#include "XmlDocument.hpp"

static const char* version_argument_name = "--version";
static const char* element_argument_name = "--element";
static const char* printall_argument_name = "--print-all";

// compare 2 strings, ignoring case.
// return 0 when str1 and str2 are the same
// return < 0 when str1 is less than str2.
// return > 0 when str1 is greater than str2.
int compare(char const* str1, char const* str2)
{
    for (;(*str1 != '\0') && (*str2 != '\0'); ++str1, ++str2)
    {
        int ch1 = toupper(*str1);
        int ch2 = toupper(*str2);
        if (ch1 != ch2)
            return ch1 - ch2;
    }

    return static_cast<int>(*str1) - static_cast<int>(*str2);
}

int main(int argc, char* argv[])
{
    XmlDocument* xml_document = new XmlDocument(argv[1]);

    if(!compare(argv[2], version_argument_name))
    {
        std::cout << "version: " << xml_document->getVersion() << std::endl;
    }
    
    std::vector<std::string> element_names_to_query;
    for(int i = 2; i<argc; i++)
    {
        if(!compare(argv[i], printall_argument_name))
        {
            xml_document->printDocument();
        }
        std::vector<std::string> argument_tokens;
        std::string whole_argument = argv[i];
        xml_document->tokenize(whole_argument, argument_tokens,  ":");  
        if(!compare(argument_tokens[0].c_str(), element_argument_name))
        {
            element_names_to_query.push_back(argument_tokens[1]);
        }
    }
    xml_document->queryByElementNames(element_names_to_query);
}
