The lex definition file scans through a given input file written in the FP language and prints out all the tokens with labels.

Keywords are defined as specific strings and are checked first to distinguish them from identifiers.

Data types like Boolean, integer, float, etc. are defined by regular expressions. Regarding spaces between the negative sign and the digits, a function 
is called to remove those spaces to read the values correctly.

Character strings are always surrounded by parentheses.

Symbols and whitespace are defined appropriately.

Identifiers include all remaining combinations of character strings. Only these are inserted into the symbol table. Duplicates are not inserted; 
instead a message is printed out to indicate that the scanner has found a duplicate.

Finally, the contents of the symbol table is printed out to look like a diagram. The symbol table is implemented with linked-list chaining to an array 
of pointers.
