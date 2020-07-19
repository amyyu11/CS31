//
//  decrypt.cpp
//  Project 5
//
//  Created by Amy Yu on 5/14/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

void makeLowerCase(char ciphertext[]);
void editText(char text[], char words[][81]);
int length(char crib[]);
bool check(char ciphertext[], char crib[], char cipherfragment[], char cribfragment[]);
bool decrypt(const char ciphertext[], const char crib[]);

/*void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"
    
    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
} */
int main()
 {
   char ciphertext[] = "Zysqjs zbguncyqzo jdsbyo eybmnu bg Wqzsvbbf.\nUnysqx eybmgxrsuu ymtbyu kcq Jicjjsy.\nNbuj sajysts rcvsyqr qgx sajysts zbgusykqjcks nbucjcbgu bg xcuzmuucbg wbymtu.\nZU 31 cu zdqrrsgecge!";
// char ciphertext[] = "My network connection at home was down, and I didn't have a way to copy my files and bring them to a SEASnet machine.";
    char crib[] = {"conspiracy theory"};
     char ciphertext2[] = {"DiebjiggK, zyxZYXzyx--Abca abCa    bdefg## $$hidbijk6437 wvuWVUwvu\n\n8 9\n"};
     char crib2[] = {    "   hush???hUSh---     --- until    JanuARY !!  "};
// char crib[] = {"pwddvpaowd ca"};
 //cout << length(crib);
     
     assert(decrypt("My network connection at home was down, and I didn't have a way to copy my files and bring them to a SEASnet machine.", "pwddvpaowd ca"));
     assert(decrypt(ciphertext, crib));
     assert(decrypt("Rzy pkr", "dog"));
     assert(decrypt(ciphertext2, crib2));

 }

void makeLowerCase(char ciphertext[])   // makes all characters lowercase
{
    for (int i = 0; ciphertext[i] != '\0'; i++)
        ciphertext[i] = tolower(ciphertext[i]);
}

void editText(char text[], char words[][81])    // places all words into a 2D array of characters
{
    int first = 0;
    int i = 0;
    int j = 0;
    while (text[i] != '\0')
    {
        if (isalpha(text[i]))
        {
            for (j = 0; text[j] != '\0'; j++)
            {
                if (!isalpha(text[i+j]))
                    break;
                
                else
                {
                    words[first][j] = text[i+j];
                }
            }
            first++;
            i = i + j;
        }
        else if (text[i] == '\n')   // places new line characters into 2D array
        {
            words[first][0] = '\n';
            first++;
            i++;
        }
        
        else
            i++;
        
    }
}

int length(char crib[])    // finds number of words
{
    int count = 0;
    for (int i = 0; crib[i] != '\0'; i++)
    {
        
        if (isalpha(crib[i]) && !isalpha(crib[i+1]))
            count++;
    }
    return count;
}

bool check(char ciphertext[], char crib[], char cipherfragment[], char cribfragment[])    // checks if crib is and cipher are valid matches
{
    char cipherWords[5000][81] = {"", ""};
    char cribWords[5000][81] = {"", ""};
    editText(ciphertext, cipherWords);  // puts ciphertext into array of words
    editText(crib, cribWords);  // puts crib into array of words
    
    int j = 0;
    for (int i = 0; i < strlen(crib); i++)  // creates cribfragment
    {
        if(isalpha(crib[i]))
        {
            cribfragment[j] = crib[i];
            j++;
        }
    }
    int i;
    bool pattern = true;
    bool len = false;
    
    for (i = 0; i < length(ciphertext); i++)
    {
        if (strlen(cribWords[0]) == strlen(cipherWords[i])) // checks that first word of crib and cipher are equal in length
        {
            
            if (length(crib) > 1)   // if crib is more than one word
            {
                for (int n = 0; n < length(crib); n++)
                {
                    if (strlen(cribWords[n]) == strlen(cipherWords[i+n]))   // checks for more words if crib is longer than one word
                    {
                        
                        if (n == length(crib)-1 )   // when on the last word of crib
                        {
                            len = true;
                            int x = 0;
                            for (int k = i; k < length(crib)+i; k++)
                            {
                                
                                for (int j = 0; cipherWords[k][j] != '\0'; j++) // creates cipherfragment
                                {
                                    if(isalpha(cipherWords[k][j]))
                                    {
                                        cipherfragment[x] = cipherWords[k][j];
                                        x++;
                                    }
                                }
                            }
                            
                            for (int m = 0; m < strlen(cribfragment); m++)
                            {
                                
                                for (int j = m+1; j < strlen(cribfragment); j++)
                                {
                                    if (cribfragment[m] == cribfragment[j]) // checks if pattern matches
                                    {
                                        
                                        if (cipherfragment[m] != cipherfragment[j])
                                        {
                                            pattern = false;
                                            m = strlen(cribfragment);
                                            break;
                                        }
                                        else if (m != strlen(cribfragment)-2)
                                            continue;
                                        else
                                        {
                                            return true;
                                        }
                                    }
                                    
                                    else if (cipherfragment[m] == cipherfragment[j])
                                    {
                                        
                                        if  (cribfragment[m] != cribfragment[j])
                                        {
                                            pattern = false;
                                            m = strlen(cribfragment);
                                            break;
                                        }
                                        else if (m != strlen(cribfragment)-2)
                                            continue;
                                        else
                                        {
                                            return true;
                                        }
                                        return true;
                                    }
                                    else if (m == strlen(cribfragment)-2 && j == m + 1) // true if all tests passed and checking last character
                                        return true;
                                }
                                
                            }
                        }
                        else
                            continue;
                    }
                    else
                        break;
                    if (pattern == false)
                    {
                        
                        break;
                    }
                }
                
            }
            
            else    // if crib is one word long
            {
                len = true;
                
                int x = 0;
                for (int k = i; k < length(crib)+i; k++)
                {
                    
                    for (int j = 0; cipherWords[k][j] != '\0'; j++) // creates cipherfragment
                    {
                        if(isalpha(cipherWords[k][j]))
                        {
                            cipherfragment[x] = cipherWords[k][j];
                            x++;
                        }
                    }
                }
                
                for (int m = 0; m < strlen(cribfragment); m++)
                {
                    
                    for (int j = m+1; j < strlen(cribfragment); j++)
                    {
                        if (cribfragment[m] == cribfragment[j]) // checks if pattern matches
                        {
                            
                            if (cipherfragment[m] != cipherfragment[j])
                            {
                                pattern = false;
                                m = strlen(cribfragment);
                                break;
                            }
                            else if (m != strlen(cribfragment)-2)
                                continue;
                            else
                            {
                                return true;
                            }
                        }
                        
                        else if (cipherfragment[m] == cipherfragment[j])
                        {
                            
                            if  (cribfragment[m] != cribfragment[j])
                            {
                                pattern = false;
                                m = strlen(cribfragment);
                                break;
                            }
                            else if (m != strlen(cribfragment)-2)
                                continue;
                            else
                            {
                                return true;
                            }
                            return true;
                        }
                        else if (m == strlen(cribfragment)-2 && j == m + 1) // true if all tests passed and checking last character
                            return true;
                    }
                    
                }
        
            }
            
        }
        
    }
    if (pattern == false || len == false)
        return false;
    
    return true;
}

bool decrypt(const char ciphertext[], const char crib[])
{
    char cipherfragment[5000] = "";
    char cribfragment[5000] = "";
    char copyCipher[5000] = "";
    char copyCipher2[5000] = "";
    char copyCrib[5000] = "";
    strcpy(copyCipher, ciphertext);
    makeLowerCase(copyCipher);
    strcpy(copyCipher2, ciphertext);
    makeLowerCase(copyCipher2);
    strcpy(copyCrib, crib);
    makeLowerCase(copyCrib);

    if (copyCrib[0] == '\0' || strlen(copyCrib) > 80)
        return false;
    
    if (strlen(copyCrib) > strlen(copyCipher))  // crib cannot be longer than ciphertext
        return false;
    
    bool x = check(copyCipher, copyCrib, cipherfragment, cribfragment);
    
    if (x == false)
        return false;

    
    char alphabet[27] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'
    };
    
    char key[27] = {};  // key is made up of null bytes

    for (int n = 0; n < 27; n++)
    {
        for (int m = 0; m < 27; m++)
        {
            if (alphabet[m] == cipherfragment[n])
            {
                key[m] = cribfragment[n];   // sets letter to corresponding position in alphabet
            }
            
        }
    }

    for (int r = 0; r < 27; r++)
    {
        key[r] = toupper(key[r]);   // changes all key to uppercase
        
    }
    
    for (int i = 0; i < strlen(copyCipher); i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (key[j] == '\0')
                continue;
            
            if (copyCipher[i] == alphabet[j])
            {
                copyCipher2[i] = key[j];    // translates ciphertext
                break;
            }
        }
        
    }
    cout << copyCipher2;    // prints translated message
    return true;
}

