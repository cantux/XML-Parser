#ifndef _XML_DOCUMENT
#define _XML_DOCUMENT

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <istream>
#include <ostream>
#include <iterator>

class XmlElement;

/**
 * @brief A cpp xml document parser and representation
 */ 
class XmlDocument
{
public:
    /**
     * @brief news an element and creates dom tree
     * 
     * @param file_name relative path to xml file to be parsed.
     */ 
    XmlDocument(char* file_name);
    
    /**
     * @brief destructor that deletes the first element.
     */
    ~XmlDocument();
    
    std::string getVersion();
    
    /**
     * @brief traverses dom tree and prints the ocucrences of element_names
     * 
     * @param element_names string vector of element names 
     * 
     * @return 
     */ 
    bool queryByElementNames(std::vector<std::string> element_names);
    
    /**
     * @brief takes a std::string and tokenizes it by the delimeters parameter and puts it into the tokens vector
     *      made public since it is a nice utility
     *      TODO: move this function to a ParserUtility
     * 
     * @param str string to be tokenized
     * 
     * @param tokens string vector reference to fill in the tokens
     * 
     * @param delimeters sentinels for tokenizing the str
     */ 
    void tokenize(const std::string& str,
                      std::vector<std::string>& tokens,
                      const std::string& delimiters = " ") const;
                      
    bool printDocument();
    
private:
    /**
     * @brief parses the file pointed by the m_file_name property
     * called from constructor
     * calls addElement for creating dom tree
     * calls parseDocumentVersion for filling m_document_version
     */
    void createDocument();
    
    /**
     * @brief parses first line of xml document to extract document version
     */
    void parseDocumentVersion(std::string info_line);
    
    /**
     * @brief recursive function to create dom tree
     *          creates new elements and adds them to m_the_element pointer
     *          stdlib exits if start and close delimeters don't match
     *          stdlib exits if start element names and close element names don't match
     * 
     * @param file reference of file pointer
     * 
     * @param element parent element
     * 
     * @return either element name or element value
     */
    std::string addElement(std::ifstream& file, XmlElement* element);
    
    /**
     * @brief moves the file pointer until the delimeter and fills the string_until_char
     *          crucial for addElement
     *          excludes newline, '<' and '>' chars from string_until_char for convinience
     *          has a sentinel role for parsing the xml document, see return of this function
     *          TODO: move this function to a ParserUtility
     * 
     * @param file reference to the current location in the file
     * 
     * @param move_until_this_char file pointer is moved until this character is encountered
     * 
     * @param strin_until_char reference to string from the start point to move_until_this_char is encountered.
     * 
     * @return returns true unless eof is encountered. false return stops recursing of addElement
     */ 
    bool moveUntilChar(std::ifstream& file, char move_until_this_char, std::string& string_until_char);
    
    /**
     * @brief compares the next char in the stream to the given char.
     *          if next char is not the one we are looknig for we use fstream::unget to return to previous point in the stream
     *          TODO: move this function to a ParserUtility
     * 
     * @param file file stream reference
     * 
     * @param next_char char to be compared with stream
     * 
     * @return true if next_char is found, ow false
     */ 
    bool compareWithNextChar(std::ifstream& file, char next_char);

    /**
     * @brief utility for extracting first token from a space delimetered string
     *          TODO: move this function to a ParserUtility
     * @return element name
     */ 
    std::string extractElementName(std::string start_tag_string);
    
    /**
     * @brief sets attributes from a string to the given element
     * 
     * @param element attributes will be set to this element
     * 
     * @param start_tag_string string to be parsed
     * 
     * @return false if element points to an empty location, ow true
     */ 
    bool setAttributesToElement(XmlElement* element, std::string start_tag_string);
    
    //starting element of the tree
    XmlElement* m_the_element;
    
    std::string m_file_name;
    std::string m_document_name;
    std::string m_document_version;
};

#endif
