#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool contains_repeated_alpha_chars(string text);
string is_only_alphabetical(string text);
string get_substitution_cipher(string plaintext, string substitution_key);

int main(int argc, string argv[])
{
    if (argc == 2){
        if(strlen(argv[1]) != 26){
            printf("Key must be 26 characters long!\n");
        }
        else{
            if(!is_only_alphabetical(argv[1])){
                printf("Key must be alphabetical letters only!\n");
            }
            else{
                if(contains_repeated_alpha_chars(argv[1])){
                    printf("Key must not contain any repeated alphabetical characters!\n"); 
                }
                string plaintext = get_string("plaintext: ");
                printf("ciphertext: %s\n", get_substitution_cipher(plaintext, argv[1]));
                return 0;
            }
        }
        return 1;
    }
    else{
        printf("./substitution key");
        return 1;
    }

}

// IMPLEMENTATION:
// for every char in plaintext, downsize to fit between 0 <= x <= 25
// then let cipher[i] = substitution_key[plaintext[i]];
// finally, return cipher!
string get_substitution_cipher(string plaintext, string substitution_key){

}

bool contains_repeated_alpha_chars(string text){

}

string is_only_alphabetical(string text){
    int string_len = strlen(text);
    for(int i = 0; i < string_len; i++){
        if(!isalpha(text[i])){
            return false;
        }
    }
    return true;

}
