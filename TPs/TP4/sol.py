# NOTES
# do a var for saving lens
# import time

# start_time = time.time()

string_a = [x for x in input()]
string_b = [x for x in input()]

def are_equivalent(string_a, string_b):

    len_a = len(string_a)
    len_b = len(string_b)

    if len_a != len_b: # error handling
        return False

    if string_a == string_b: # base case (they are equal)
        return True
    
    if len_a == 1 or len_b == 1: 
        return string_a == string_b
    
    string_a_1 = string_a[:len_a // 2]
    string_a_2 = string_a[len_a // 2:]

    string_b_1 = string_b[:len_b // 2]
    string_b_2 = string_b[len_b // 2:]

    first_case = are_equivalent(string_a_1, string_b_1) and are_equivalent(string_a_2, string_b_2)

    if first_case:
        return first_case
    
    else:
        second_case = are_equivalent(string_a_1, string_b_2) and are_equivalent(string_a_2, string_b_1)
        return second_case
    
if are_equivalent(string_a, string_b):
    print("YES")
else:
    print("NO")

# end_time = time.time()

# print("time: ", (end_time - start_time) * 1000)
