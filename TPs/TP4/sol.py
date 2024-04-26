# import time

# start_time = time.time()

string_a = input()
string_b = input()

def are_equivalent(string_a, string_b):

    len_a = len(string_a)
    len_b = len(string_b)

    if len_a != len_b: # error handling
        return False
    
    if len_a == 0:
        return False

    if string_a == string_b: # base case (they are equal)
        return True
    
    if len_a == 1 or len_b == 1: 
        return string_a == string_b
    
    if len_a % 2 == 0:  # If even length

        mid = len_a // 2

        string_a_1 = string_a[:mid]
        string_a_2 = string_a[mid:]

        string_b_1 = string_b[:mid]
        string_b_2 = string_b[mid:]

        first_case = are_equivalent(string_a_1, string_b_1) and are_equivalent(string_a_2, string_b_2)
        if first_case:
            return True
        else:
            second_case = are_equivalent(string_a_1, string_b_2) and are_equivalent(string_a_2, string_b_1)
            return second_case

    else:  # If odd length
        return False
    
if are_equivalent(string_a, string_b):
    print("YES")
else:
    print("NO")


# end_time = time.time()

# print("time: ", (end_time - start_time) * 1000)
