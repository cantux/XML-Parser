CC=g++
CFLAGS=-c -Wall -ggdb
MODULES= 
SOURCES=

all: xmlreport

xmlreport: main.o xml
	$(CC) -o xmlreport main.o XmlDocument.o XmlElement.o XmlAttribute.o
	
main.o: main.cpp		
	$(CC) $(CFLAGS) main.cpp

xml: XmlElement.hpp XmlElement.cpp XmlAttribute.hpp XmlAttribute.cpp XmlDocument.hpp XmlDocument.cpp
	$(CC) $(CFLAGS) XmlDocument.cpp XmlElement.cpp XmlAttribute.cpp
	
clean:
	rm -rf *o xmlreport
