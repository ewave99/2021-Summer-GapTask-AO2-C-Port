#ifndef GENERIC_FUNCTIONS_H_
#define GENERIC_FUNCTIONS_H_

int stringIsInteger ( const char * string_to_test );
int inputAndValidateNumericChoice ( const int number_of_options, int * input_int_value );
int getNumericChoice ( const int number_of_options, const char * main_prompt, const char * invalid_input_message );

#endif
