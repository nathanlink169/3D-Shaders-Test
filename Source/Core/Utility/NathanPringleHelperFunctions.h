/*
* Generic Helper Functions
* Author: Nathan Pringle
*
* These are generic helper functions that can be used in any project.
*/

#ifndef __NATHANPRINGLE_HELPER_FUNCTIONS_H_
#define __NATHANPRINGLE_HELPER_FUNCTIONS_H_

// Place this define above including math.h
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <time.h>
#include <string>
#include <Windows.h>
#include <vector>

namespace npw
{
    //
    // This function should be called at the beginning of the program
    // and serves to setup the helper functions. Currently, this function:
    //
    // - Seeds the random function
    //
    void SetupHelperFunctions();

    //
    // Gets a random integer between 0 and the maximum number passed 
    // through, inclusive.
    //
    int Random(int aMaximumNumber);

    //
    // Gets a random integer between the minimum and the maximum number 
    // passed through, inclusive.
    //
    int Random(int aMinimumNumber, int aMaximumNumber);

    //
    // Gets a random double between 0 and 1, inclusive.
    //
    double Random();

    //
    // Gets a random double between 0 and the maximum number 
    // passed through, inclusive.
    //
    double Random(double aMaximumNumber);

    //
    // Gets a random double between 0 and the maximum number 
    // passed through, inclusive.
    //
    double Random(double aMinimumNumber, double aMaximumNumber);

    //
    // Gets the distance between two 2D points.
    //
    double DistanceBetweenPoints(double aX1, double aY1, double aX2, double aY2);

    //
    // Gets the distance between two 3D points.
    //
    double DistanceBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2);

    //
    // Checks for two circles colliding. Returns true if there is collision.
    //
    bool CircleToCircleCollision(double aX1, double aY1, double aRadius1, double aX2, double aY2, double aRadius2);

    //
    // Checks for two rectangles colliding. Returns true if there is collision.
    //
    bool RectangleToRectangleCollision(double aX1, double aY1, double aWidth1, double aHeight1, double aX2, double aY2, double aWidth2, double aHeight2);

    //
    // Converts a string to a wstring.
    //
    std::wstring wstringToString(std::string aString);

    //
    // Checks to see if a number is even.
    //
    bool IsEven(int aNumber);

    //
    // Checks to see if a number is odd.
    //
    bool IsOdd(int aNumber);

    //
    // Checks to see if a number is above zero.
    //
    bool IsPositive(int aNumber);

    //
    // Checks to see if a number is above zero.
    //
    bool IsPositive(double aNumber);

    //
    // Checks to see if a number is above zero.
    //
    bool IsNegative(int aNumber);

    //
    // Checks to see if a number is above zero.
    //
    bool IsNegative(double aNumber);

    // 
    // Breaks the program if the condition is true (only works in debug mode)
    // 
    void BreakIfTrue(bool Condition);

    // 
    // Breaks the program if the condition is false (only works in debug mode)
    // 
    void BreakIfFalse(bool Condition);

    //
    // Deletes a pointer if the pointer can be deleted
    //
    template <typename T>
    void SafeDelete(T* Pointer)
    {
        if (Pointer != nullptr)
            delete Pointer;
    }

    //
    // Deletes a pointer to an array if the pointer can be deleted
    //
    template <typename T>
    void SafeDeleteArray(T* Pointer)
    {
        if (Pointer != nullptr)
            delete[] Pointer;
    }

    //
    // Deletes all the objects in a vector
    //
    template <typename T>
    void SafeDeleteVector(std::vector<T*>& Vector)
    {
        for (uint i = 0; i < Vector.size(); i++)
        {
            SafeDelete<T>(Vector[i]);
        }
        Vector.clear();
    }

    //
    // Check to see if an object pointer is in a vector
    //
    template <typename T>
    bool IsObjectInVector(T* Object, std::vector<T*>& Vector)
    {
        for (uint i = 0; i < Vector.size(); i++)
        {
            if (Object == Vector[i])
                return true;
        }
        return false;
    }

    //
    // Check to see if an object is in a vector
    //
    template <typename T>
    bool IsObjectInVector(T Object, std::vector<T>& Vector)
    {
        for (uint i = 0; i < Vector.size(); i++)
        {
            if (Object == Vector[i])
                return true;
        }
        return false;
    }

    //
    // Takes a value from Degrees and returns a Radian value
    //
    double ToRadians(double d);

    //
    // Takes a value from Radians and returns a Degress value
    //
    double ToDegrees(double r);

    //
    // Returns true is pointer is not null
    //
    template <typename T>
    bool IsNotNull(T* aPointer)
    {
        return ((aPointer == nullptr) ? false : true);
    }
}

#endif