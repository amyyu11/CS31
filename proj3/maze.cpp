//
//  maze.cpp
//  Project 3
//
//  Created by Amy Yu on 4/26/19.
//  Copyright © 2019 Amy Yu. All rights reserved.
//

#include "grid.h"
#include<iostream>
#include<string>
#include<cassert>
using namespace std;

bool isCourseWellFormed(string course);
int driveSegment(int r, int c, char dir, int maxSteps);
int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps);

int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    draw(3, 1, 3, 4);
    assert(isCourseWellFormed("n2e1"));
    assert(isCourseWellFormed("neswese"));
    assert(!isCourseWellFormed("e1x"));
    assert(!isCourseWellFormed("e154"));
    assert(driveSegment(3, 1, 'N', 2) == 2);
    int len;
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(3,1, 3,4, "N2eE01n0s2e1", len) == 0  &&  len == 7);
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(3,1, 3,4, "e1x", len) == 2  &&  len == -999);
    len = -999;  // so we can detect whether driveCourse sets len
    assert(driveCourse(2,4, 1,1, "w3n1", len) == 3  &&  len == 1);
    assert(driveSegment(3, 1, 'E', 3) == 0);
     len = -999;
    assert(driveCourse(3, 2, 3, 2, "n4", len) == 2 && len == -999);
    cout << "All tests succeeded" << endl;
  
}

bool isCourseWellFormed(string course)
{
    for (int j = 0; j != course.size(); j++)    // sets all letters to uppercase
        course[j] = toupper(course[j]);
    
    int i = 0;
    if (course == "")
        return true;        // true if course of zero segments
    else if (course.size() == 1 && (course[0] == 'N' || course[0] == 'E' || course[0] == 'S' || course[0] == 'W'))
        return true;    // true if course only contains one letter
    else
    {
        if (course[0] == 'N' || course[0] == 'E' || course[0] == 'S' || course[0] == 'W')
        {
            while (i != course.size())
            {
                if (isdigit(course[i]))
                {
                   
                        
                    if (i < (course.size()-2) && isdigit(course[i+1]) && isdigit(course[i+2]))
                    {
                        return false;   // false if there are three digits in a row
                    }
                    
                    if (i < (course.size()-1) && isdigit(course[i+1]))  // two digits
                    {
                        i = i + 2;
                        continue;
                    }
                    
                    else
                        i++;
               
                }
                else if (course[i] == 'N' || course[i] == 'E' || course[i] == 'S' || course[i] == 'W')
                {
                     i++;
                }
                else
                {
                    return false;   // false if the 2nd character is not a valid letter or digit
                }
            }
        }
        else
        {
            return false;   // false if 1st character is not valid letter
        }
    
       return true; // true if all tests are passed
    }
}

int driveSegment(int r, int c, char dir, int maxSteps)
{
    int i = 1;
    dir = toupper(dir); // changes directions to uppercase

    if ((dir != 'N' && dir != 'E' && dir != 'S' && dir != 'W') || maxSteps < 0)     // checks if dir is not a valid direction or if maxSteps is negative
    {
       // cout << "No";
        return -1;
    }
    
    else if (dir == 'N')
    {
        // cout << "north";
        if (r == 1) // at edge of grid so cannot take any steps
            return 0;
        else
        {
            while (i <= maxSteps && (r-i) > 0)
            {
                if (isWall(r-i, c))
                    return (i - 1); // hits a wall so returns one less step
                else
                    i++;
            }
            if (maxSteps <= getRows())
                return (maxSteps);
            else
                return (r - 1); // if maxSteps is larger than the grid
        }
    }
    
    else if (dir == 'E')
    {
        if (c == getCols())
            return 0;   // already at edge
        else
        {
            while (i <= maxSteps)
            {
                if (isWall(r, c+i))
                    return (i - 1); // hits a wall
                else
                    i++;
            }
            if (maxSteps <= getCols())
                return (maxSteps);
            else
                return (getCols() - c); // if maxSteps is larger than the grid
        }
    }
    
    else if (dir == 'S')
    {
        if (r == getRows()) // already at edge
            return 0;
        
        else
        {
            while (i <= maxSteps)
            {
                if (isWall(r+i, c))
                    return (i - 1); // hits a wall
                else
                    i++;
            }
             if (maxSteps <= getRows())
                 return (maxSteps);
            else
            {
                return (getRows() - r); // if maxSteps is larger than grid
            }
        }
    }
    
    else if (dir == 'W')
    {
        if (c == 1)
            return 0;
        else
        {
            while (i <= maxSteps && (c-i) > 0)
            {
                if (isWall(r, c-i))
                    return (i - 1);
                else
                    i++;
            }
            if (maxSteps <= getCols())
                return (maxSteps);
            else
                return (c - 1);
        }
    }
    return -1;
}



int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps)
{
    int totalDistance = 0;  // max steps through whole course
    int row = sr;
    int column = sc;
    int steps = 0;  // number of steps taken in each course segment
    int maxSteps = 0; // max steps that can be taken in each segment
    char dir;
    for (int j = 0; j != course.size(); j++)
    {
        course[j] = toupper(course[j]); // changes all to uppercase
    }
    
    if (!isCourseWellFormed(course))    // if course is not valid
    {
        return 2;
    }
    
    if (sr <= 0 || sr > getRows() || sc <= 0 || sc > getCols() || er <= 0 || er > getRows() || ec <= 0 || ec > getCols() || isWall(sr, sc) || isWall(er, ec))   // checks if starting and ending positions are outside the grid or at walls
    {
        return 2;
    }
    
    int i = 0;
    if (isalpha(course[i])) // first character must be letter
    {
        while (i != course.size())
        {
             dir = course[i];
            if (i < (course.size()-2) && isdigit(course[i+1]) && isdigit(course[i+2]))  // two digits
            {
                int x = course[i+1] - '0';
                int y = course[i+2] - '0';
                steps = (10 * x) + y;
                i = i + 3;
            }
            else if (i < (course.size()-1) && isdigit(course[i+1])) // one digit
            {
                steps = course[i+1] - '0';
                i = i + 2;
               
            }
            else if (isalpha(course[i]))  // no digits
            {
                steps = 1;
                i++;
            }
            
            maxSteps = driveSegment(row, column, dir, steps);   // max steps that can be taken in that segment
      
            if (maxSteps == steps)
            {
                totalDistance = totalDistance + maxSteps;
                if (dir == 'N')
                    row = row - steps;
                else if (dir == 'E')
                    column = column + steps;
                else if (dir == 'S')
                    row = row + steps;
                else
                    column = column - steps;
                
                nsteps = totalDistance;
                continue;
            }
            else if (maxSteps < steps)  // if runs off grid or hits wall
            {
                nsteps = totalDistance + maxSteps;
                return 3;
            }
        }
    }
    if (row == er && column == ec)  // returns 0 if end position is correct
    {
        nsteps = totalDistance;
        return 0;
    }
    nsteps = totalDistance;
    return 1;   // returns 1 is not at end position
    
}


