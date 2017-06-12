#include "XmlElement.hpp"
#include "XmlAttribute.hpp"

int XmlElement::id = 0;

XmlElement::XmlElement()
: m_attributes()
, m_childs()
, m_element_name("\0")
, m_element_value("\0")
{
    //std::cout <<"id is : " << id << std::endl;
    id++;
}

XmlElement::~XmlElement()
{
    std::vector<XmlAttribute*>::iterator attribute_it = m_attributes.begin();
    while(attribute_it != m_attributes.end())
    {
        delete *attribute_it;
        m_attributes.erase(attribute_it);
    }
    std::vector<XmlElement*>::iterator child_it = m_childs.begin();
    while(child_it != m_childs.end())
    {
        delete *child_it;
        m_childs.erase(child_it);
    }
}

XmlElement* XmlElement::addChild(XmlElement* child_element)
{
    //std::cout << "this : " << this << std::endl;
    //std::cout << "child to add : " << child_element << std::endl;
    m_childs.push_back(child_element);
    return this;
}

void XmlElement::addAttribute(std::string attribute_name, std::string attribute_value)
{
    XmlAttribute* new_attribute = new XmlAttribute(attribute_name, attribute_value);
    m_attributes.push_back(new_attribute);
}

void XmlElement::setName(std::string name)
{
    m_element_name = name;
}

void XmlElement::setValue(std::string value)
{
    m_element_value = value;
}
    
void XmlElement::printTree()
{
    std::cout << "name : " << m_element_name << "\tvalue : " << m_element_value << std::endl;
    for(std::vector<XmlAttribute*>::iterator attribute_it = m_attributes.begin(); attribute_it != m_attributes.end(); ++attribute_it)
    {
        std::cout << "attribute name: " << (*attribute_it)->getName() << "\tattribute value: " << (*attribute_it)->getValue() << std::endl;
    }
    for(std::vector<XmlElement*>::iterator child_it = m_childs.begin(); child_it != m_childs.end(); ++child_it)
    {
        (*child_it)->printTree();
    }
}

void XmlElement::printByName(std::vector<std::string> names)
{
    for(std::vector<std::string>::iterator string_it = names.begin(); string_it != names.end(); ++string_it)
    {
        if(m_element_name == *string_it)
        {
            std::cout << m_element_name << " : " << m_element_value << std::endl;
        }
    }
    for(std::vector<XmlElement*>::iterator child_it = m_childs.begin(); child_it != m_childs.end(); ++child_it)
    {
        (*child_it)->printByName(names);
    }
}
