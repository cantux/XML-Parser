#ifndef _XML_ELEMENT
#define _XML_ELEMENT

#include <vector>
#include <string>
#include <iostream>

class XmlAttribute;

class XmlElement
{
public:

    static int id;
    
    XmlElement();
    ~XmlElement();
    
    /**
     * @brief adds a child to this element.
     * 
     * @param child_element child element to be added.
     * 
     * @return this
     */
    XmlElement* addChild(XmlElement* child_element);
    
    /**
     * @brief adds atributes.
     * 
     * @param attribute_name.
     * 
     * @param attribute_value.
     */
    void addAttribute(std::string attribute_name, std::string attribute_value);
    
    void setName(std::string);
    void setValue(std::string);
    
    /**
     * @brief prints entire dom tree
     */
    void printTree();
    
    /**
     * @brief traverses dom and prints values of elements in the vector of names
     * 
     * @param element names vector to be printed
     */
    void printByName(std::vector<std::string> names);
    
private:
    std::vector<XmlAttribute*> m_attributes;
    std::vector<XmlElement*> m_childs;
    
    std::string m_element_name;
    std::string m_element_value;
};

#endif
