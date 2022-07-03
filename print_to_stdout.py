
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
        return abs(a) * abs(b)

def print_to_stdout(iterations: int, string1: str, string2: str):
    '''
        Conditionally prints numbers 1 -> N to Standard Output.
        The condition is as follows:
            whe

                Parameters:
                        iterations (int):  upper bound of cycles to print to std. out
                        string1    (str):  string to be printed when N divisible by 3
                        string2    (str):  string to be printed when N divisible by 5
                Returns:
                        N/A - void method
        '''
    if (string1 is not None) and (string2 is not None) and (iterations > 0):
        #for a number to be divisible by A & B is equivalent to least common multiple or LCM of(A*B)
        lcm = lcm(3, 5)
        for i in range(1, iterations + 1):

            if i % lcm == 0:
               print(string1 + string2)

            elif i % 3 == 0:
                print(string1)

            elif i % 5 == 0:
                print(string2)

            else:
                print(i) 

def main():
    #print(lcm(3, 5))
    #print_to_stdout(100, "Crackle", "Pop")

if __name__ == '__main__':
    main()