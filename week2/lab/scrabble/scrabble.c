#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
const int ASCII_UPPER_CASE_ONSET = 65;
const int ASCII_LOWER_CASE_ONSET = 97;

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if(score1 > score2){
        printf("Player 1 wins!\n");
    }
    else if(score1 < score2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
}
// DESIGN approach (Sub-Optimal):
// We can create an alphabet array or (char array) where 0th index = 'A', 1st index = B, etc
// Then we can iterate through this array and find index of the target char in
// and break out of loop when we get that index. Then we can use POINTS[i] to get
// necessary scrabble point mapping for that car and add results to accumulator and repeat!

// https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html 
// Design approach (BEST):
// We realize that the ASCII Chart preserves alphabetical ordering:
// a = 97, b = 98, c = 99, A = 65, B = 66, C = 67 , etc.
// Thus for lower case chars, we can subtract 97 and for upper case chars,
// we can minus 65 to get this ordering within the bounds of 0 <= index <= 26!
// Afterwards, the problem is straightforward as we can use POINTS[index]
// to get necessary scrabble point mapping for each char and add results to an accumulator!

int compute_score(string word)
{
    int score = 0;
    int word_length = strlen(word);
    for(int i = 0; i < word_length; i++){

        if(islower(word[i])){
            score += POINTS[(int) word[i] - ASCII_LOWER_CASE_ONSET];
        }
        else if(isupper(word[i])){
            score += POINTS[(int) word[i] - ASCII_UPPER_CASE_ONSET];
        }
        else{
            //no need to add zero for non letter chars ... just continue!
            continue;
        }
    }

    return score;
}
