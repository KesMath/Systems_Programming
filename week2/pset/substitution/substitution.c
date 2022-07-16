#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int ASCII_UPPER_CASE_ONSET = 65;
const int ASCII_LOWER_CASE_ONSET = 97;

bool contains_repeated_alpha_chars(string text);
bool is_only_alphabetical(string text);
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
                else{
                    string plaintext = get_string("plaintext: ");
                    printf("ciphertext: %s\n", get_substitution_cipher(plaintext, argv[1]));
                    return 0;
                }
            }
        }
        return 1;
    }
    else{
        printf("./substitution key\n");
        return 1;
    }
}

// IMPLEMENTATION:
// for every char in plaintext, downsize to fit between 0 <= x <= 25
// then let cipher[i] = substitution_key[plaintext[i]];
// finally, return cipher!
string get_substitution_cipher(string plaintext, string substitution_key){
    int string_len = strlen(plaintext);
    for(int i = 0; i < string_len; i++){
        if(isupper(plaintext[i])){
            // in-place approach
            plaintext[i] = substitution_key[plaintext[i] - ASCII_UPPER_CASE_ONSET];
        }
        else{
            // in-place approach
            plaintext[i] = tolower(substitution_key[plaintext[i] - ASCII_LOWER_CASE_ONSET]);
        }
    }
    //in-place approach done to save memory so although this is named plaintext, in actuality the result is ciphertext!
    return plaintext;
}


// creates an occurrence array (reference it as A) where A is
// an array of length 26 where index or position corresponds
// to alphabetical letter and A[index] = occurrence

// if character is indeed repeated, that means we will point back to
// or reference the same A[index] and increment! 
// If (A[index] > 1), that implies a repeated character exists! 
bool contains_repeated_alpha_chars(string text){
    bool contains_repeated_alpha = false;
    int occurrence_arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int string_len = strlen(text);

    //populating occurrence_array
    for(int i = 0; i < string_len; i++){
        if(isalpha(text[i])){
            if(isupper(text[i])){
                int index = text[i] - ASCII_UPPER_CASE_ONSET;
                occurrence_arr[index] = occurrence_arr[index] + 1;
                //optimization check
                if(occurrence_arr[index] > 1){
                    contains_repeated_alpha = true;
                    break;
                }
            }
            else{
                int index = text[i] - ASCII_LOWER_CASE_ONSET;
                occurrence_arr[index] = occurrence_arr[index] + 1;
                //optimization check
                if(occurrence_arr[index] > 1){
                    contains_repeated_alpha = true;
                    break;
                }
            }
        }
    }

    return contains_repeated_alpha;
}

bool is_only_alphabetical(string text){
    int string_len = strlen(text);
    for(int i = 0; i < string_len; i++){
        if(!isalpha(text[i])){
            return false;
        }
    }
    return true;

}
