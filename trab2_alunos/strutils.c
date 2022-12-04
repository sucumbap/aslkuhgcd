#include "strutils.h"
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

// verifica se o carater "c" é uma letra maíuscula
int is_upper(int c){
    if (c >= 'A' && c <= 'Z') return 1;
    else return-1;                       // return c >= 'A' && c <= 'Z';
}

// verifica se o carater "c" é uma letra minúscula
int is_lower(int c) {
    if ( c >= 'a' && c <= 'z' ) return 1;
    else return -1;                      // return c >= 'a' && c <= 'z';
}

// verifica se o carater "c" é uma letra 
int is_letter(int c) {
    if (is_lower(c) || is_upper(c)) return 1;
    return -1;
}
//                                  ******INICIO*****
/**
 * Converte todas as letras da string "str" para minúsculas
 */
void str_tolower (char str[]) { 
    int i=0;
    while(str[i] != '\0'){
        if(is_upper(str[i]) == 1){ str[i] = str[i] - 'A' + 'a';	}
        i++;
    }
}
/**
 * Converte todas as letras da string "str" para maíusculas
 */  
void str_toupper (char str[]) {
    int i=0;
    while(str[i]!='\0'){
        if(is_lower(str[i]) == 1){ str[i] = str[i] - 'a' + 'A';}
        i++;
    }
}
 

/**

    
    
void str_trim (char str[]) 
{
	int i=0, aux=0;
	for (; str[i] != '\0' && is_space(str[i])=1     ;(i++);
	for (; str[i] != '\0' && ((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')); i++, aux++) str[aux] = str[i];
	str[aux] = '\0';
}
 Retira os separadores iniciais e finais da string "str".
 * Os separadores a considerar são: espaço, tab ('\t') e mudança de linha ('\n')
 */
 
 int is_space(char c){ // retorna true se for um ESPAÇO, TAB ou \n
    if(c == ' ' || c == '\t' || c == '\n'){return 1;}
    else return -1;
}

void str_trim (char str[]) {
	int i=0, k=0;
	while(str[i] != '\0' && is_space(str[i]) == 1 ){ i++;  }
    while( str[i] != '\0' &&  (is_lower(str[i])==1 || is_upper(str[i])==1 ) ){
                str[k] = str[i];
                i++;
                k++;
            }
    str[k] = '\0';
    }


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
int str_next (const char line[], int *pos, char word[], int max_size) {
	int i = *pos; 
    int k = 0;
    
    while( line[i] != '\0' &&  (is_space(line[i])==1) ){ i++; }
    
    if (line[i] == '\0') { return EOL; }
    
 	while(line[i] != '\0' &&  is_space(line[i])== -1){
		if(k >= max_size - 1) return OVERFLOW;
		word[k] = line[i];
        i++;
        k++;
	}
    word[k] = '\0';
	*pos = i;
	
	return 0;
} 

/**
 * Afeta o inteiro referido por "num", com o valor obtido da sequência  
    de dígitos em "line", a partir da posição indicada por "pos",
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
int str_next_int (const char line[], int *pos, int *num){
	int i = *pos; 
    int nmr = 0;  
    int nega = 0; //negative
    int bfore = 0;// antes
    
	while (line[i] != '\0' &&  is_space(line[i])==1 ){ i++; }
	if (line[i] == '\0') { return -1;} //return EOL
	if (line[i] == '+' || line[i] == '-'){
		if (line[i] == '-'){ nega = 1;}
		i++;
	}
	if (line[i]<'0' || line[i]>'9') return -3; // RETURN NO_NUMBER
    
	while (line[i] != '\0' && (line[i] >= '0' && line[i] <= '9') ){ 
		bfore = nmr;
		nmr = nmr * 10 + line[i] - '0';
        i++;
	}
	if (nega == 1){
		nmr = -nmr;
		bfore = -bfore;
		if(bfore<nmr) return -2; // RETURN OV
	}
	else if (bfore>nmr) return -2; // RETURN OV
	*num = nmr;
	*pos = i;
	return 0; // RETORNA SUCESS
}
