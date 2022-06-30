#include <cs50.h>
#include <stdio.h>

string is_valid_credit_card(long digit);

int main(void) 
{
    long digit = get_long("Number: ");
    printf("%s", is_valid_credit_card(digit));
    
}

string is_valid_credit_card(long digit){
    // RETURNS 'AMEX', 'MASTERCARD', 'VISA' in accordance with passing Luhn's Critera and rulings below else 'INVALID'
    // RULINGS:
    // AMEX: 15 Digit numbers starting with 34 or 37
    // MASTERCARD: 16 digit numbers starting with 51, 52, 53, 54, 55
    // VISA: 13 and 16 digit numbers starting with 4

    int sum_of_product_digits; // sum of digits of every other digit multiplied by 2
    int sum2; // sum of other digits
    int cout = 1; // used to validate digit length in addition to counting every other digit

    //TODO: add logic to obtain initial digits to identify which CC issuer
    while(digit > 0){
        int rightmost_digit = digit % 10;

        if(cout % 2 == 0){
            if(rightmost_digit != 0){ //don't want to waste computation on zero multiplications
                int product = 2 * rightmost_digit;
                if(product > 9){
                    //max value of digit * 2 = 9 * 2 = 18 hence only 2 iterations needed
                    for(int i = 0; i < 2; i++){
                        int trailing_digit = product % 10;
                        sum_of_product_digits += trailing_digit;
                        product -= trailing_digit;
                        product /= 10; 
                    }
                }
                else{
                    sum_of_product_digits += product;
                }
            }
        }
        else{
            sum2 += rightmost_digit;
        }

        digit -= rightmost_digit; // subtracting digit to zero out rightmost digit
        digit /= 10; // 'pop off' that trailing zero
        cout++;
    }
    int final_sum = sum_of_product_digits + sum2;
    if(cout != 15 || cout != 16 || final_sum % 10 != 0){
        return "INVALID\n";
    }
    else{
        //TODO: 
    }
}