#include <stdbool.h>


#define EOL         -1
#define OVERFLOW    -2
#define NO_NUMBER   -3


/**
 * Converte todas as letras da string "str" para minúsculas
 */
void str_tolower (char str[]);  


/**
 * Converte todas as letras da string "str" para maíusculas
 */  
void str_toupper (char str[]);    


/**
 * Retira os separadores iniciais e finais da string "str".
 * Os separadores a considerar são: espaço, tab ('\t') e mudança de linha ('\n')
 */
void str_trim (char str[]);       


/**
 * Coloca em "word" a próxima sequência de caracteres em "line",
 * de dimensão máxima "max_size"-1,  a partir da posição indicada por "pos",
 * saltando eventuais separadores (espaços e/ou tabs) iniciais.
 * O valor referido por "pos" é modificado para a posição do caracter imediatamente 
 * a seguir à sequeência retornada.
 * 
 * Retorna:
 *   0 em caso de sucesso
 *   EOL (-1) se não foi encontrado nenhum caracter "não espaço" até ao fim da string.
 *   OVERFLOW (-2)  se a sequência foi truncada por ser maior ou igual a max_size.
 * 
 */
int str_next (const char line[], int *pos, char word[], int max_size);	  


/**
 * Afeta o inteiro referido por "num", com o valor obtido da sequência  
 * de dígitos em "line", a partir da posição indicada por "pos",
 * saltando eventuais separadores iniciais. 
 * A sequência de digitos pode ser precedida pelo sinal '-' ou '+'.
 * 
 * O valor referido por "pos" é modificado para a posição do caracter
 * imediatamente a seguir à sequència de dígitos correspondente ao inteiro obtido.
 * 
 * Retorna:
 *   0 em caso de sucesso
 *   EOL (-1) se não foi encontrado nenhum caracter "não espaço" até ao fim da string.
 *   OVERFLOW  (-2) se o número é demasiado grande ou pequeno para caber num inteiro.
 *   NO_NUMBER (-3) se a próxima sequência de carateres não é de dígitos
 */
int str_next_int (const char line[], int *pos, int *num);
