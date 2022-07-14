#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
                if(plaintext[i] + shift_key > 90){
                    plaintext[i] = ((plaintext[i] + shift_key) % 90) + 64;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % 90;
                }
            }
            else{
                if(plaintext[i] + shift_key > 122){
                    plaintext[i] = ((plaintext[i] + shift_key) % 122) + 96;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % 122;
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