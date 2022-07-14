#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int ASCII_UPPER_CASE_ONSET = 65;
const int ASCII_LOWER_CASE_ONSET = 97;
const int ALPHA_WRAPAROUND = 26;

string get_caesar_cipher(string plaintext, int shift_key);
bool is_only_digits(string text);

int main(int argc, string argv[]) 
{
    if (argc == 2 && is_only_digits(argv[1])){
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: %s\n", get_caesar_cipher(plaintext, atoi(argv[1])));
        return 0;
    }
    else{
        printf("Usage: ./caesar key\n");
    }
    return 1;
}


string get_caesar_cipher(string plaintext, int shift_key){
    int str_len = strlen(plaintext);
    for(int i = 0; i < str_len; i++){
        // in-place approach
        if(isalpha(plaintext[i])){
            if(isupper(plaintext[i])){
                plaintext[i] = (((plaintext[i] - ASCII_UPPER_CASE_ONSET) + shift_key) % ALPHA_WRAPAROUND) + ASCII_UPPER_CASE_ONSET;
                printf("Plain: %i\n", plaintext[i]);
            }
            else{
                plaintext[i] = (((plaintext[i] - ASCII_LOWER_CASE_ONSET) + shift_key) % ALPHA_WRAPAROUND) + ASCII_LOWER_CASE_ONSET;
 
            }
        }
    }
    //in-place approach done to save memory so although this is named plaintext, in actuality the result is ciphertext!
    return plaintext;
}

bool is_only_digits(string text){
    bool is_integer_str = true;
    int len_str = strlen(text);
    for (int i = 0; i < len_str; i++){
        if(!isdigit(text[i])){
            is_integer_str = false;
            break;
        }
    }
    return is_integer_str;
}