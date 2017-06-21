C++ program called "xmlreport" that runs from the command line. Parses any valid XML file and prints a report following the rules below.
The program will return 0 when successful, or 1 for any error detected.

The syntax is as follows:
```
./xmlreport filename [--version] [--element:] [--element:] [...]
```

1. When using xmlreport with the file products.xml only, the output will produce all unique elements. All elements starting with <? can be ignored for this output.

example: 

```
./xmlreport products.xml --print-all
```

output:

```

            products
                product
                    name
                    description
                    country
                    company
                    cost
                    type
```

2. When using xmlreport with the file products.xml and --version, a report will output all unique elements and version number. Note that --version should always be provided as the second param...

example: 

```
./xmlreport products.xml --version --print-all
```

output:

```
    products
        product
            name
            description
            country
            company
            cost
            type

    version = 1.0
```

3. When using xmlreport with the file products.xml and --element:, a report will output the all unique data for the listed elements at the same level, in the order of the listed elements.

E.g. if the level is <products><product><name> then all elements matching that level will be output.

example: 

```
./xmlreport products.xml --element:name
```

output:

```
    Apple
    Pear
    Grapes
    shirt
    ...
```
example: 

```
./xmlreport products.xml --element:name --element:cost
```

output:

```
    Apple, £0.17
    Pear, £0.12
    Grapes, £0.78
    shirt, £7.45
    ...
```
example: 

```
./xmlreport products.xml --element:cost --element:name
```

output:

```
    £0.17, Apple
    £0.12, Pear
    £0.78, Grapes
    £7.45, shirt
    ...
```

Other requirements:

a) checks that the first line starts with a valid xml version element. e.g. <?xml version="1.0" encoding="UTF-8"?>. The version number can be any value in the format n.n

b) Ignore any elements including the child elements where a start and end tag don't match. I will edit products.xml and create errors to test.

c) Function implementation may be no more than 40 lines (including comments).

d) Global variables and constants are not allow. I.e. only allows variables and constants as members of a class, or within member functions and main.

e) #define cannot be used for constants.

f) No use of C++ 11 features.

g) No function can be copy/pasted, so if you need to use the provided compare function for example in multiple classes then re-factor.

h) this must be C++, so no use of 'C' style casts and no use of int as boolean.

i) --element and --version are case insensitive. e.g. --ELEMENT and --element are treated the same.

j) There will be no warnings produced by the compiler on level 4, no memory leaks and the program will not crash.


The start code is provided, and any class or function can be used from the provided included header files.

```
#include <cctype>  // for use of toupper or tolower functions
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>

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
    return 0;
}
```
