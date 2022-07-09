#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int PERIOD = 46;
int QUESTION_MARK = 63;
int EXCLAMATION_POINT = 33;
float COLEMAN_LIAU_TERM_1 = 0.0588;
float COLEMAN_LIAU_TERM_2 = 0.296;
float COLEMAN_LIAU_TERM_3 = 15.8;

bool issentence_punctuation(char c);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade_level(int letter_count, int sentence_count, int word_count);


int main(void) 
{
    string text = get_string("Text: ");
    int letter_cout = count_letters(text);
    int word_cout = count_words(text);
    int sent_cout = count_sentences(text);

    // for debugging
    printf("letters: %i\n", letter_cout);
    printf("words: %i\n", word_cout);
    printf("sentences: %i\n", sent_cout);

    int grade = calculate_grade_level(letter_cout, sent_cout, word_cout);
    if(grade > 16){
        printf("Grade 16+\n");
    }
    else if(grade < 1){
        printf("Before Grade 1\n");
    }
    else{
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text){
    int cout = 0;
    int len_str = strlen(text);
    for (int i = 0; i < len_str; i++){
        if(isalpha(text[i])){
            cout++;
        }
    }
    return cout;
}

int count_words(string text){
    int cout = 1;
    int len_str = strlen(text);
    for(int i = 0; i < len_str; i++){
        if(isspace(text[i])){
            cout++;
        }
    }
    return cout;
}


int count_sentences(string text){
    int cout = 0;
    int len_str = strlen(text);
    for(int i = 0; i < len_str; i++){
        if(issentence_punctuation(text[i])){
            cout++;
        }
    }
    return cout;
}

int calculate_grade_level(int letter_count, int sentence_count, int word_count){
    int grade = 0;
    if(word_count > 0){ // protect against DIVISION-BY-Zero
        // Recall in C, dividing INT/INT causes loss of precision (truncation) if result is a decimal number
        // Thus, we can cast either the numerator or denominator to preserve precision
        double avg_letters = (letter_count / (double) word_count) * 100;
        printf("avg_letters: %f\n", avg_letters);
        double avg_sentences = (sentence_count / (double) word_count) * 100;
        printf("avg_sentences: %f\n", avg_sentences);
        grade = (int) round((COLEMAN_LIAU_TERM_1 * avg_letters) - (COLEMAN_LIAU_TERM_2 * avg_sentences) - COLEMAN_LIAU_TERM_3);
    }
    return grade;
}

bool issentence_punctuation(char c){
    if(c == QUESTION_MARK || c == EXCLAMATION_POINT || c == PERIOD){
        return true;
    }
    return false;
}