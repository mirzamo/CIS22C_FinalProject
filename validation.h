/**
 A simple message table for errors.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

/**
 Enum class for set of errors that could be encountered from user input.
*/
enum class Error
{
    BAD_IFILE, BAD_OFILE, BAD_INPUT, BAD_SEARCH, EMPTY_STACK, ERROR_COUNT
};

/**
 Prints out the Error selected.
*/
const char* const ErrorTable[ static_cast<int>(Error::ERROR_COUNT) ]  =
{
    "\n  Error: Please enter a valid input file.\n",
    "\n  Error: Please enter a valid output file.\n",
    "\n  Error: Bad input, please try again.\n",
    "\n  Error: No athlete name searched for is found.\n",
    "\n  Error: Nothing has been deleted.\n"
} ;

void printErrorMsg(Error);

#endif // VALIDATION_H

