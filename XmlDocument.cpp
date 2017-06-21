#include "XmlDocument.hpp"
#include "XmlElement.hpp"

XmlDocument::XmlDocument(char* file_name)
    : m_the_element(new XmlElement)
    , m_file_name(file_name)
    , m_document_name("\0")
    , m_document_version("\0")
{
    createDocument();
} 

XmlDocument::~XmlDocument()
{
    delete m_the_element;
}

void XmlDocument::createDocument()
{
    //open file
    std::string line;
    std::ifstream myfile(m_file_name.c_str());
    if (myfile.is_open())
    {
        //get document version
        std::getline(myfile,line);
        parseDocumentVersion(line);

        addElement(myfile, m_the_element);
        
        /*
        m_the_element->printTree();
        std::vector<std::string> names;
        names.push_back("cost");
        names.push_back("company");
        m_the_element->printByName(names);
        print whole file.
        while ( std::getline(myfile,line) )
        {
            std::cout << line << std::endl;
        }*/
        
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl; 
        exit(3);
    }
}

std::string XmlDocument::getVersion()
{
    return m_document_version;
}

void XmlDocument::parseDocumentVersion(std::string info_line)
{
    std::vector<std::string> tokens;
    tokenize(info_line, tokens);
    
    //hack
    std::vector<std::string> version_tokens;
    tokenize(tokens[1], version_tokens, "=");
    m_document_version = version_tokens[1];
}

bool XmlDocument::moveUntilChar(std::ifstream& file, char move_until_this_char, std::string& string_until_char)
{
    char s = '\0';
    while (s != move_until_this_char)
    {       
        file.get(s);
        if(file.eof()) 
        {
            string_until_char = "\0";
            return false;
        }
        else if(s == '<' || s == '>' || s == '\n'){}
        else
        {
            string_until_char.append(1, s); //fill - append: concatanates (int)arg1 times of (char)arg2 to end of this
        }
    }
    return true;
    
}

bool XmlDocument::compareWithNextChar(std::ifstream& file, char next_char)
{
    char s;
    file.get(s);
    if(s == next_char)
    {
        return true;
    } 
    else
    {
        file.unget(); 
        return false;
    }
}

std::string XmlDocument::addElement(std::ifstream& file, XmlElement* element)
{
    std::string string_until_start_tag = "\0";
    std::string string_until_end_tag = "\0";
    std::string element_name = "\0";
    
    if(!moveUntilChar(file, '<', string_until_start_tag))
    {
        return "\0";
    }
    else
    {
        if(compareWithNextChar(file, '/'))
        {//next char is "/" --> return string until end tag
            
            element->setValue(string_until_start_tag);
             
            if(moveUntilChar(file, '>', string_until_end_tag))
            {//return element name
                //std::cout<<"end " << string_until_end_tag<<std::endl;
                return string_until_end_tag;
            }
        }
        else
        {//next char is not slash  --> this is start tag
            if(!moveUntilChar(file, '>', string_until_end_tag))
            {
                std::cout<<"closing braces don't match"<<std::endl;
                exit(1);
            }     
            
            XmlElement* new_element = new XmlElement();
            
            setAttributesToElement(new_element, string_until_end_tag);
            element_name = extractElementName(string_until_end_tag);
            new_element->setName(element_name);
            
            //std::cout<<"start " << element_name<<std::endl;
            element->addChild(new_element);
            if(element_name == addElement(file, new_element))//recurse to child
            {//recurse to sibling
                return addElement(file, element);
            }
            else
            {
                std::cout<<"start and end tags don't match"<<std::endl;
                exit(2);
            }
        }
    }
    return "errors, unknownks of them";
}

void XmlDocument::tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters) const
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

std::string XmlDocument::extractElementName(std::string start_tag_string)
{
    std::vector<std::string> tokens;
    tokenize(start_tag_string, tokens); 
    
    return tokens[0]; //first token is the element name//rest are the attributes
}

bool XmlDocument::setAttributesToElement(XmlElement* element, std::string start_tag_string)
{
    if(element)
    {
        std::vector<std::string> tokens;
        tokenize(start_tag_string, tokens);
        
        //i=1 is a hack//0 is the element name//1 is the first attribute-value pair.    
        for(unsigned int i = 1; i<tokens.size(); ++i)
        {
            std::vector<std::string> attribute_value_name_pair;
            tokenize(tokens[i], attribute_value_name_pair, "=");
            element->addAttribute(attribute_value_name_pair[0], attribute_value_name_pair[1]);
        }
        return true;
    }
    return false;
}

bool XmlDocument::queryByElementNames(std::vector<std::string> element_names)
{
    if(m_the_element)
    {
        m_the_element->printByName(element_names);
        return true;
    }
    return false;
}

bool XmlDocument::printDocument()
{
    if(m_the_element)
    {
        m_the_element->printTree();
        return true;
    }
    return false;
}
