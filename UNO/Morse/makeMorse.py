#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

from pdb import set_trace as st

# https://fr.wikipedia.org/wiki/Code_Morse_international


char2morse = {          
          "!": "---.",      "\"": ".-..-.",     "$": "...-..-",    "'": ".----.",  
          "(": "-.--.",      ")": "-.--.-",     "+": ".-.-.",      ",": "--..--", 
          "-": "-....-",     ".": ".-.-.-",     "/": "-..-.", 
          "0": "-----",      "1": ".----",      "2": "..---",      "3": "...--", 
          "4": "....-",      "5": ".....",      "6": "-....",      "7": "--...", 
          "8": "---..",      "9": "----.", 
          ":": "---...",     ";": "-.-.-.",     "=": "-...-",      "?": "..--..", 
          "@": ".--.-.", 
          "A": ".-",         "B": "-...",       "C": "-.-.",       "D": "-..", 
          "E": ".",          "F": "..-.",       "G": "--.",        "H": "....", 
          "I": "..",         "J": ".---",       "K": "-.-",        "L": ".-..", 
          "M": "--",         "N": "-.",         "O": "---",        "P": ".--.", 
          "Q": "--.-",       "R": ".-.",        "S": "...",        "T": "-", 
          "U": "..-",        "V": "...-",       "W": ".--",        "X": "-..-", 
          "Y": "-.--",       "Z": "--..", 
          "[": "-.--.",      "]": "-.--.-",     "_": "..--.-", "&": ".-...",
 }

morse = list()

# char* MorseAlphabet[] =  

for i in range(96):
    morse.append("")

for c in char2morse.keys():
    # print("%i %s" % (ord(c), c))
    morse[ord(c)] = char2morse[c]

# print(morse)
# print(len(morse))

print('char* MorseAlphabet[] = {')
for i in range(33, 96):
    c = morse[i]
    if not c:
        c = ""
    
    print("\t\'%s\',\t// %s %i" % (c, chr(i), i))
print('};')