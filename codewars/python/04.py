"""
Simple, given a string of words, return the length of the shortest word(s).

String will never be empty and you do not need to account for different data types.

"""

def find_short(s):
    l = 99
    for word in s.split(" "):
        if(len(word)<l):
            l = len(word)
            
    return l # l: shortest word length


"""
def find_short(s):
    return min(len(x) for x in s.split())
"""


