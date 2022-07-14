#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int ASCII_UPPER_CASE_STARTING_BOUNDARY = 64;
const int ASCII_UPPER_CASE_ENDING_BOUNDARY = 90;

const int ASCII_LOWER_CASE_STARTING_BOUNDARY = 96;
const int ASCII_LOWER_CASE_ENDING_BOUNDARY = 122;

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

// Similar approach to their rotate() function
// but instead of downsizing upper case and lower case to fit into
// the bounds of [0,25], this approach retains the original ASCII bounds
// 65 <= uppercase <= 90, 97 <= lowercase <= 122, performs the shift,
// and uses respective modulo (uppercase bound = 64, lowercase = 96)
// to generate new uppercase or lowercase cipher
string get_caesar_cipher(string plaintext, int shift_key){
    int str_len = strlen(plaintext);
    for(int i = 0; i < str_len; i++){
        // in-place approach
        if(isalpha(plaintext[i])){
            if(isupper(plaintext[i])){
                if(plaintext[i] + shift_key > ASCII_UPPER_CASE_ENDING_BOUNDARY){
                    // adding the ASCII_UPPER_CASE_STARTING_BOUNDARY assures char wraps around into uppercase ascii territory
                    plaintext[i] = ((plaintext[i] + shift_key) % ASCII_UPPER_CASE_ENDING_BOUNDARY) + ASCII_UPPER_CASE_STARTING_BOUNDARY;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % ASCII_UPPER_CASE_ENDING_BOUNDARY;
                }
            }
            else{
                if(plaintext[i] + shift_key > ASCII_LOWER_CASE_ENDING_BOUNDARY){
                    plaintext[i] = ((plaintext[i] + shift_key) % ASCII_LOWER_CASE_ENDING_BOUNDARY) + ASCII_LOWER_CASE_STARTING_BOUNDARY;
                }
                else{
                    plaintext[i] = (plaintext[i] + shift_key) % ASCII_LOWER_CASE_ENDING_BOUNDARY;
                }
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