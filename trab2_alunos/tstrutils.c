/**
 * tstrutils.c
 * Este programa contém um conjunto de testes para validar as implementações
 * presentes no ficheiro "strutils.c".
 * 
 * ISEL, outubro de 2022
 * 
 * Build   : gcc -Wall  -o tstrutils tstrutils.c strutils.c  
 * Execute : tstrutils
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <string.h>

#include "test_utils.h"
#include <limits.h>
#include "strutils.h"


// Toupper, tolower tests

void case_empty_string() {
    char line[] = "";
      
    str_tolower(line);
    ASSERT_TRUE(line[0] == 0);
    
    str_toupper(line);
    ASSERT_TRUE(line[0] == 0);
}

void touuper_and_reverse_lower_string() {
    char line[] = " small string ";
    char upper_expected[] = " SMALL STRING ";
    char lower_expected[] = " small string ";
      
    str_toupper(line);
    ASSERT_EQUAL_STR(upper_expected, line);
    
    str_tolower(line);
    ASSERT_EQUAL_STR(lower_expected, line);
}


// Trim tests

void trim_empty_string() {
    char line[] = "     ";
      
    str_trim(line);
    
    ASSERT_TRUE(line[0] == 0);
}

void trim_start_string() {
    char line[] = "     hello";
    char expected[] = "hello";
    str_trim(line);
    
    ASSERT_EQUAL_STR(expected, line);
}


void trim_end_string() {
    char line[] = "hello    ";
    char expected[] = "hello";
    str_trim(line);
    
    ASSERT_EQUAL_STR(expected, line);
}


void trim_all_string() {
    char line[] = "     hello    ";
    char expected[] = "hello";
    str_trim(line);
    
    ASSERT_EQUAL_STR(expected, line);
}

// Words tests

void retrieve_a_simple_word_from_line() {
	char line[] = "hello";
	char expected[] = "hello", word[10] = "?";
	

	int pos = 0;
    ASSERT_EQUAL_INT(0, str_next(line, &pos, word, sizeof(word)));
	ASSERT_EQUAL_INT(5, pos);
	ASSERT_EQUAL_STR(expected, word);
}

void retrieve_a_simple_big_word_from_line() {
	char line[] = "hello";
	char expected[] = "hell", word[5] = "?";
	

	int pos = 0;
    ASSERT_EQUAL_INT(-2, str_next(line, &pos, word, sizeof(word)));
 
    ASSERT_EQUAL_STR(expected, word);
}



void retrieve_a_simple_word_and_terminator_from_line() {
	char line[] = "hello";
	char expected[] = "hello", word[10] = "?";
	

	int pos = 0;
    
    ASSERT_EQUAL_INT(0, str_next(line, &pos, word, sizeof(word)));
	ASSERT_EQUAL_INT(5, pos);
	ASSERT_EQUAL_STR(expected, word);
 
 
	ASSERT_EQUAL_INT(-1, str_next(line, &pos, word, sizeof(word)));
	 
}


void retrieve_a_simple_word_from_line_with_separators() {
	char line[] = "  hello  ";
	char expected[] = "hello", word[10] = "?";
	

	int pos = 0;
    
    ASSERT_EQUAL_INT(0, str_next(line, &pos, word, sizeof(word)));
	ASSERT_EQUAL_INT(7, pos);
	ASSERT_EQUAL_STR(expected, word);
	 
	ASSERT_EQUAL_INT(-1, str_next(line, &pos, word, sizeof(word)));
	 
}

void retrieve_two_words_from_line() {
	char line[] = "  ABC 123";
	char expected1[] = "ABC", expected2[] = "123";
	
	char word[4] = "?";
	

	int pos = 0;
    ASSERT_EQUAL_INT(0, str_next(line, &pos, word, sizeof(word)));
	ASSERT_EQUAL_INT(5, pos);
	ASSERT_EQUAL_STR(expected1, word);
	
	ASSERT_EQUAL_INT(0, str_next(line, &pos, word, sizeof(word)));
	ASSERT_EQUAL_INT(9, pos);
	ASSERT_EQUAL_STR(expected2, word);
  
	ASSERT_EQUAL_INT(-1, str_next(line, &pos, word, sizeof(word))); 
}

 


// Numbers


void retrieve_a_number_from_line() {
	char line[] = "123";
	int expected = 123, num = 1000;
	
	int pos = 0;
    ASSERT_EQUAL_INT(0, str_next_int(line, &pos, &num));
	ASSERT_EQUAL_INT(3, pos);
	ASSERT_EQUAL_INT(expected, num);
}

void retrieve_a_number_with_separators_from_line() {
	char line[] = "   123   ";
	int expected = 123, num=1000;
	char word[10] = "?";
	
	int pos = 0;
    ASSERT_EQUAL_INT(0, str_next_int(line, &pos, &num));
	ASSERT_EQUAL_INT(6, pos);
	ASSERT_EQUAL_INT(expected, num);
	 
	ASSERT_EQUAL_INT(-1, str_next(line, &pos, word, sizeof(word))); 
}


void retrieve_two_numbers_from_line() {
	char line[] = " 12345 6789";
	int expected1 =12345, expected2 = 6789, num;
	
	char word[10] = "?";
	

	int pos = 0;
    ASSERT_EQUAL_INT(0, str_next_int(line, &pos, &num));
	ASSERT_EQUAL_INT(6, pos);
	ASSERT_EQUAL_INT(expected1, num);
	
	
	
	ASSERT_EQUAL_INT(0, str_next_int(line, &pos, &num));
	ASSERT_EQUAL_INT(11, pos);
	ASSERT_EQUAL_INT(expected2, num);
 
  
	ASSERT_EQUAL_INT(-1, str_next(line, &pos, word, sizeof(word))); 
}


void number_from_line_underflow() {
    char okmin[] = "-2147483648";
	char underflow[] = "-2147483649";
    
    int expected_min= INT_MIN;
   
    
    int num, pos=0;
    
    ASSERT_EQUAL_INT(0, str_next_int(okmin, &pos, &num));
	ASSERT_EQUAL_INT(strlen(okmin), pos);
	ASSERT_EQUAL_INT(expected_min, num);
	
    pos = 0;
    num=0;
    ASSERT_EQUAL_INT(-2, str_next_int(underflow, &pos, &num));
    ASSERT_TRUE(0 == num);
}

void number_from_line_overflow() {
    
    char okmax[] = "+2147483647";
	char overflow[] = "+2147483648";
    
 
    int expected_max= INT_MAX;
    
    int num, pos=0;
    
    ASSERT_EQUAL_INT(0, str_next_int(okmax, &pos, &num));
	ASSERT_EQUAL_INT(strlen(okmax), pos);
	ASSERT_EQUAL_INT(expected_max, num);
	
    pos = 0;
    num=0;
    ASSERT_EQUAL_INT(-2, str_next_int(overflow, &pos, &num));
    ASSERT_TRUE(0 == num);
}


int main() {
       
    // Toupper, tolower tests
    TEST(case_empty_string);
    TEST(touuper_and_reverse_lower_string);
    
    // Trim tests
    TEST(trim_empty_string);
    TEST(trim_start_string);
    TEST(trim_end_string);
    TEST(trim_all_string);

	// Strings
	TEST(retrieve_a_simple_word_from_line);
	TEST(retrieve_a_simple_word_and_terminator_from_line);
	TEST(retrieve_a_simple_big_word_from_line);
	TEST(retrieve_a_simple_word_from_line_with_separators);
	TEST(retrieve_two_words_from_line);
	 	
	
	// Numbers
	TEST(retrieve_a_number_from_line);
	TEST(retrieve_a_number_with_separators_from_line);
	TEST(retrieve_two_numbers_from_line);
    TEST(number_from_line_underflow);
    TEST(number_from_line_overflow);
	
	return 0;
}
	


