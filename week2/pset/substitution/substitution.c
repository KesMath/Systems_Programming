#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool contains_all_alphas_at_least_once(string text);
string is_only_alphabetical(string text);
string get_substitution_cipher(string plaintext, string substitution_key);

int main(int argc, string argv[])
{
    if (argc == 2){
        if(strlen(argv[1]) != 26){
            printf("Key must be 26 characters long!\n");
            return 1;
        }
        else{
            if(!is_only_alphabetical(argv[1])){
                printf("Key must be alphabetical letters only!\n");
                return 1;
            }
            else{
                if(!contains_all_alphas_at_least_once(argv[1])){
                    printf("Key must contain all alphabetical characters at least once!\n");
                    return 1;  
                }
                string plaintext = get_string("plaintext: ");
                printf("ciphertext: %s\n", get_substitution_cipher(plaintext, argv[1]));
                return 0;
            }
        }
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

bool contains_all_alphas_at_least_once(string text){

}

string is_only_alphabetical(string text){

}
