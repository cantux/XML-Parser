#include "XmlAttribute.hpp"

XmlAttribute::XmlAttribute(std::string attribute_name, std::string attribute_value)
: m_attribute_name(attribute_name)
, m_attribute_value(attribute_value)
{
}

XmlAttribute::~XmlAttribute()
{
}

std::string XmlAttribute::getName()
{
    return m_attribute_name;
}
void XmlAttribute::setName(std::string attr_name)
{
    m_attribute_name = attr_name;
}
    
std::string XmlAttribute::getValue()
{
    return m_attribute_value;
}
void XmlAttribute::getValue(std::string attr_value)
{
    m_attribute_value = attr_value;
}
