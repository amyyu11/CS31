//
//  array.cpp
//  Project 4
//
//  Created by Amy Yu on 5/5/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int split(string a[], int n, string splitter);
void swap (string a[], int first, int second);

int main()
{
    string h[7] = { "romanoff", "thor", "rogers", "banner", "", "danvers", "rogers" };
  //  assert(countMatches(h, 7, "rogers") == 2);
    assert(countMatches(h, 0, "") == 0);    // checks what happens when n = 0
    assert(countMatches(h, 5, "") == 1);    // checks if empty string is counted
    assert(countMatches(h, -1, "thor") == -1);  // checks if negative input for n returns -1
  //  assert(countMatches(h, 7, "rhodes") == 0);
 //   assert(countMatches(h, 0, "rogers") == 0);  // checks that no strings are looked at
  //  assert(detectMatch(h, 7, "rogers") == 2);
  //  assert(detectMatch(h, 2, "rogers") == -1);  // checks if only the first two strings in the array are looked at
    int bg;
    int en;
 //   assert(detectSequence(h, 7, "banner", bg, en) && bg == 3 && en == 3);
    assert(!detectSequence(h, -7, "banner", bg, en));   // checks if negative input for n returns false
    assert(!detectSequence(h, 0, "banner", bg, en));   // checks if negative input for n returns false
    assert(!detectSequence(h, 7, "stark", bg, en)); // checks if it returns false if the string is not in the array
    
    string b[7] = { "romanoff", "rogers", "rogers", "rogers", "", "danvers", "rogers" };
    assert(detectSequence(b, 7, "rogers", bg, en) && bg == 1 && en == 3);
    
    string g[4] = { "romanoff", "thor", "banner", "danvers" };
  //  assert(detectMin(g, 4) == 2);
    assert(detectMin(b, 7) == 4);   // checks empty string as min
    assert(detectMin(b, 0) == -1);   // checks if returns -1 if no strings are examined
    assert(detectDifference(h, 4, g, 4) == 2);  // g and h are different at position 2
    assert(detectDifference(h, 0, g, 4) == -1);  // returns -1 if the size is 0
//   assert(contains(h, 7, g, 4));   // h contains all elements in g in the same order
    assert(!contains(h, 7, b, 7));  // h does not contain all elements in b in the same order
    assert(!contains(h, -1, b, 7));  // cannot have negative size
     assert(!contains(h, 0, b, 7));  // a1 cannot have zero elements
    assert(contains(h, 7, h, 7));   // true if comparing the same array
    assert(moveToBack(g, -4 , 1) == -1 && g[1] == "thor" && g[3] == "danvers"); // array is unchanged if size is negative
    assert(moveToBack(g, 0 , 1) == -1 && g[1] == "thor" && g[3] == "danvers"); // returns -1 if n = 0
    assert(moveToBack(g, 4 , -1) == -1 && g[1] == "thor" && g[3] == "danvers"); // array is unchanged if position is negative
  //  assert(moveToBack(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");
    assert(moveToBack(b, 7, 0) == 0 && b[0] == "rogers" && b[6] == "romanoff");
   
    
    
    string f[4] = { "danvers", "banner", "thor", "rogers" };
    assert(moveToFront(f, -4, 2) == -1 && f[0] == "danvers" && f[2] == "thor"); // array is unchanged if size is negative
    assert(moveToFront(f, 4, -2) == -1 && f[0] == "danvers" && f[3] == "rogers");   // array is unchanged if position is negative
    assert(moveToFront(f, 0, 2) == -1 && f[0] == "danvers" && f[3] == "rogers");   // returns -1 if n = 0
 //   assert(moveToFront(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");
    
    string e[5] = { "danvers", "danvers", "danvers", "thor", "thor" };
    assert(deleteDups(e, 0) == 0 && e[1] == "danvers"); // returns 0 if n = 0 and leaves array unchanged
    assert(deleteDups(e, 5) == 2 && e[1] == "thor");
    assert(deleteDups(e, 2) == 2 && e[0] == "danvers");
    string c[7] = { "romanoff", "rogers", "rogers", "", "", "danvers", "rogers" };
    assert(deleteDups(c, 7) == 5  && c[1] == "rogers");
    
    string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
    string y[4] = { "banner", "danvers", "rhodes", "rogers" };
    string z[10];
    string z1[10];
    string z2[4];
    assert(meld(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");
    assert(meld(x, 2, y, 2, z1, 10) == 4 && z[0] == "banner");
    assert(meld(x, 4, y, 4, z2, 4) == -1);
    assert(meld(x, 0, y, 0, z2, 0) == 0);   // if two empty arrays are added
    
    assert(split(h, 0, "rogers") == 0); // returns 0 if empty array
 //   assert(split(h, 7, "rogers") == 3);
    string a[7] = { "romanoff", "rogers", "thor", "banner", "rogers", "rogers", "stark"  };
    assert(split(a, 4, "rogers") == 1);
    string a1[6] = { "rhodes", "rhodes", "tchalla", "thor", "peter", "stark" };
    assert(split(a1, 6, "banner") == 6);
    assert(split(a1, 6, "tchalla") == 4);
    
    cout << "All tests succeeded" << endl;
    
}

int countMatches(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            count++;    // increases count if the string is equal to the target
    }
    return count;
}

int detectMatch(const string a[], int n, string target)
{
    if (n < 0)
        return -1;  // if the length of the array is negative
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;   // position of string that is equal to target
    }
    return -1;  // if no strings equal target
}

bool detectSequence(const string a[], int n, string target, int& begin, int& end)
{
    if (n < 0)
        return false;
    for (int i = 0; i < n; i++)
    {
      if (a[i] == target)
      {
          begin = i;    // first occurence of target is set to begin
          for (int j = i; j < n; j++)
          {
              if (a[j] == target)
              {
                  end = j;  // last occurence of target is set to end
                  
              }
             else
                 break; // makes sure that it is consecutive sequence
          }
      }
      else
          continue;
        
        return true;
    }
    return false;   // if no strings equal target
}

int detectMin(const string a[], int n)
{
    string temp = a[0];
    int min = 0;    // initially sets a[min] to first string in array
    if (n <= 0)
        return -1;
    else
        for (int i = 0; i < n-1; i++)
        {
            if (a[i] <= a[min]) // checks if each string is array is less than the minimum
            {
                min = i;    // sets a new minimum
            }
            
            else
                continue;
        }
    
    return min;
}

int moveToBack(string a[], int n, int pos)
{
    string temp;
    temp = a[pos];
    if (n <= 0 || pos < 0)
        return -1;
    for (int i = pos; i < (n-1); i++)
    {
        a[i] = a[i+1];  // moves every string after a[pos] up
    }
    a[n-1] = temp;  // sets a[pos] to the last position
    return pos;
}

int moveToFront(string a[], int n, int pos)
{
    string temp;
    temp = a[pos];
    if (n <= 0 || pos < 0)
        return -1;
    for (int i = pos; i > 0; i--)
    {
        a[i] = a[i-1];   // moves every string after a[pos] back
    }
    a[0] = temp;    // sets a[pos] to the first position
    return pos;
}

int detectDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 <= 0)
        return -1;  // if the length of either array is negative or zero
    if (n1 <= n2)
    {
        for (int i = 0; i < n1; i++)
        {
            if (a1[i] != a2[i])
            {
                return i;   // position that string a1 is not equal to string a2
            }
        }
    
        return n1;
    }
    else    // if n2 > n1
    {
        for (int j = 0; j < n1; j++)
        {
            if (a1[j] != a2[j])
            {
                return j;
            }
        }
        return n2;
    }
}


 int deleteDups(string a[], int n)
{
    string temp;
    if (n < 0)
        return -1;
    for (int i = 0; i < (n-1); i++)
    {
        
        if (a[i] == a[i+1])
        {
            moveToBack(a, n, i);    // moves any duplicates to the back of the array
            i--;    // i is not incremented if there is a duplicate
            n--;    // decreases the number of significant elements in array
        }
    }
    return n;
}

bool contains(const string a1[], int n1, const string a2[], int n2)
{
    int j = 0;
    int count = 0;
    if (n1 < 0 || n2 < 0)
        return false;
    if (n2 == 0)    // if string a2 is empty
        return true;
    if (n2 > n1)    // second array cannot be longer than first array
        return false;
    for (int i = 0; i < n1; i++)
    {
        if (a1[i] == a2[j])
        {
            while (j < n2)
            {
                if (a1[i] == a2[j])
                {
                    count++;    // increments count if strings in both arrays are equal
                    j++;
                    break;
                }
                else
                break;
            }
        }
    }
    if (count == n2)    // if all strings in a2 are in a1
        return true;
    else
        return false;
}

int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    int k = 0;
    int pos = 0;
    if (n1 < 0 || n2 < 0)
        return -1;
    
    if (max < (n1 + n2))    // result must be long enough for both arrays a1 and a2
        return -1;
    
    for (int i = 0; i < n1-1; i++)
    {
        if (a1[i] > a1[i+1])    // checks if a1 has n1 elements in nondecreasing order
            return -1;
    }
     for (int i = 0; i < n2-1; i++) // checks if a2 has n2 elements in nondecreasing order
     {
        if (a2[i] > a2[i+1])
            return -1;
     }
    for (int j = 0; j < max; j++)
    {
        while (k < n2)
        {
            if (a1[j] <= a2[k])
            {
                result[pos] = a1[j];
                pos++;
                break;  // breaks out of loop to increment position of a1
            }
            else
            {
                result[pos] = a2[k];
                pos++;
                k++;    // continues checking position of s2
            }
        }
    }
    return (n1 + n2);
}



int split(string a[], int n, string splitter)
{
    int last = n - 1;   // last position in array
    int i;
    for (i = 0; i < last; i++)
    {
        if (a[i] >= splitter)   // checks if elements are greater than splitter
        {
            swap(a, i, last);   // moves string to end of the array
            last--;
        }
    }
    for (int j = 0; j < i-1; j++)
    {
        if (a[j] == splitter)   // if element is the same as splitter
        {
            swap(a, j, i-1);    // moves element to the middle position
            if (a[i-1] > splitter)
                i--;
            break;
        }
            
    }
    
    int count = 0;
    for (int k = 0; k < n; k++)
    {
       
        if (a[k] < splitter)
            count++;    // number of elements that is less that splitter
    }

    if (count == 0)
        return n;
    else
        return count;
}


void swap (string a[], int first, int second)   // swaps two strings in an array
{
    string temp = a[first];
    a[first] = a[second];
    a[second] = temp;
}
