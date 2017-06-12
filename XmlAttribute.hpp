#ifndef _XML_ATTRIBUTE
#define _XML_ATTRIBUTE

#include <string>

class XmlAttribute
{
public:
    XmlAttribute(std::string attribute_name, std::string attribute_value);
    ~XmlAttribute();
    
    std::string getName();
    void setName(std::string attr_name);
    
    std::string getValue();
    void getValue(std::string attr_value);
    
private:
    std::string m_attribute_name;
    std::string m_attribute_value;
};

#endif
