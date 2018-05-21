### Compile
```bin/bash
make
```
### Run
Sample xml file is included with the solution. Just run the following command:

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
### Uses of this software
- Check if the xml is valid.
- Get values of elements.

### Send me a PR for
- Querying and printing attributes. This software already parses attributes(see XmlAttribute and use --print-all option) but is not concerned with printing them.
- Security, typesafety enhancements

### Program Specifications
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
