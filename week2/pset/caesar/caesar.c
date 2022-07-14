#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int ASCII_UPPER_CASE_LOWER_BOUND = 64;
const int ASCII_UPPER_CASE_UPPER_BOUND = 90;

const int ASCII_LOWER_CASE_LOWER_BOUND = 96;
const int ASCII_LOWER_CASE_UPPER_BOUND = 122;

string get_caesar_cipher(string plaintext, int shift_key);
bool is_integer_str(string text);

int main(int argc, string argv[]) 
{
    if (argc == 2){
        string plaintext = get_string("plaintext: ");
        if(is_integer_str(argv[1])){
            printf("ciphertext: %s\n", get_caesar_cipher(plaintext, atoi(argv[1])));
        }
    }
    else{
        printf("Usage: ./caesar key\n");
    }
}

string get_caesar_cipher(string plaintext, int shift_key){
    int str_len = strlen(plaintext);
    for(int i = 0; i < str_len; i++){
        //in-place approach without auxillary arrays which saves 26 bytes * 8 bits = 206 bits of memory!
        if(isalpha(plaintext[i])){
            if(isupper(plaintext[i])){
                if(plaintext[i] + shift_key > ASCII_UPPER_CASE_UPPER_BOUND){
                    plaintext[i] = ((plaintext[i] + shift_key) % ASCII_UPPER_CASE_UPPER_BOUND) + ASCII_UPPER_CASE_LOWER_BOUND;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % ASCII_UPPER_CASE_UPPER_BOUND;
                }
            }
            else{
                if(plaintext[i] + shift_key > ASCII_LOWER_CASE_UPPER_BOUND){
                    plaintext[i] = ((plaintext[i] + shift_key) % ASCII_LOWER_CASE_UPPER_BOUND) + ASCII_LOWER_CASE_LOWER_BOUND;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % ASCII_LOWER_CASE_UPPER_BOUND;
                }
            }
        }
    }

    //in-place approach done to save memory so although this is named plaintext, in actuality the result is ciphertext!
    return plaintext;
}

bool is_integer_str(string text){
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