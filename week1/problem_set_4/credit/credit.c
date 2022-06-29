#include <cs50.h>
#include <stdio.h>

string is_valid_credit_card(long digits);

int main(void) 
{
    long digits = get_long("Number: ");
    printf("%s", is_valid_credit_card(digits));
    
}

string is_valid_credit_card(long digits){
    // RETURNS 'AMEX', 'MASTERCARD', 'VISA' in accordance with passing Luhn's Critera and rulings below else 'INVALID'
    // RULINGS:
    // AMEX: 15 Digit numbers starting with 34 or 37
    // MASTERCARD: 16 digit numbers starting with 51, 52, 53, 54, 55
    // VISA: 13 and 16 digit numbers starting with 4
    return "INVALID\n";
}