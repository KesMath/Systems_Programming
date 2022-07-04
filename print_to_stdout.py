# python3 print_to_stdout.py

import sys
assert sys.version_info >= (3, 5), \
    "Python Version " + str(sys.version_info[0]) + "." + str(sys.version_info[1]) + " is not compatible with this application!\nInterpreter Version must be >= 3.5"
import math

def lcm(a: int, b: int):
    '''
        Returns: the least common multiple (LCM) of A & B.
        Raises a TypeError is either a or b is of type float or string
        
        Definition: least common multiple or smallest common multiple of two integers a and b, usually denoted by lcm(a, b),
        is the smallest positive integer that is divisible by both a and b

        Note: LCM is available as 'math.lcm(a, b, c ...d)' in Python versions >= 3.9.0
    '''
    if(isinstance(a, str) or isinstance(b, str)):
        raise TypeError("LCM() cannot be conducted on strings!")

    elif(isinstance(a, float) or isinstance(b, float)):
        raise TypeError("LCM() cannot be conducted on floats!")
    else:
        return abs(a*b) / math.gcd(a,b)

def print_to_stdout(iterations: int, int1: int, str1: str, int2: int, str2: str):
    '''
        Conditionally prints numbers 1 -> N to Standard Output.
        The condition is as follows:
            - when n divisible by int1 & int2, print concat(str1, str2)
            - when n divisible by int1, print str1
            - when n divisible by int2, print str2
        Raises Typerror when either int1 or int2 are floating points!
        (This function is scoped solely to use integers and as such, 
        do not want to deal with the subject of modulo operator and irrational numbers)

                Parameters:
                        iterations (int):  upper bound of cycles to print to std. out
                        str1       (str):  string to be printed when N divisible by int1
                        str2       (str):  string to be printed when N divisible by int2
                Returns:
                        N/A - void method
        '''
    if(isinstance(int1, float) or isinstance(int2, float)):
        raise TypeError("Function will not perform modulo using floating points")

    else:
        if (str1 is not None) and (str2 is not None) and (iterations > 0) and (int1 > 0) and (int2 > 0):
            #for a number to be divisible by A & B is equivalent to least common multiple or LCM(A,B)
            least_multiple = lcm(int1, int2)
            for i in range(1, iterations + 1):

                if i % least_multiple == 0:
                    print(str1 + str2)

                elif i % int1 == 0:
                    print(str1)

                elif i % int2 == 0:
                    print(str2)

                else:
                    print(i) 

def main():
    print_to_stdout(100, 3, "Crackle", 5, "Pop")

if __name__ == '__main__':
    main()