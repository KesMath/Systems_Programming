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
        //in-place approach
        //TODO: perform modulo when addition > 26
        if(isalpha(plaintext[i])){
            plaintext[i] = plaintext[i] + shift_key;
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