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

class Scene;

namespace npw
{
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
    double DistanceBetweenPoints(vec2 aPoint1, vec2 aPoint2);
    double DistanceBetweenPoints(b2Vec2 aPoint1, b2Vec2 aPoint2);
    double DistanceBetweenPoints(b2Vec2 aPoint1, vec2 aPoint2);
    double DistanceBetweenPoints(vec2 aPoint1, b2Vec2 aPoint2);

    //
    // Gets the distance between two 3D points.
    //
    double DistanceBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2);
    double DistanceBetweenPoints(vec3 aPoint1, vec3 aPoint2);

    //
    // Gets the midpoint between two 2D points.
    // 
    Vector2 MidpointBetweenPoints(double aX1, double aY1, double aX2, double aY2);

    // 
    // Gets the midpoint between two 3D points.
    //
    Vector3 MidpointBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2);

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
    std::wstring stringToWstring(std::string aString);

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
	// Deletes all the objects in a map
	//
	template <typename T, typename U>
	void SafeDeleteMap(std::map<T, U*>& Map)
	{
		for each(auto iterator in Map)
			SafeDelete<U>(Map[iterator.first]);
		Map.clear();
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

    //
    // Returns the absolute value of a value
    //
    template <typename T>
    T AbsoluteValue(T aValue)
    {
        if (aValue < 0)
            return -aValue;
        return aValue;
    }

    //
    // Takes a vec2 and returns a b2Vec2
    //
    b2Vec2 vec2_To_b2Vec2(vec2 v);

    //
    // Takes a b2Vec2 and returns a vec2
    //
    vec2 b2Vec2_To_vec2(b2Vec2 v);

    //
    // Returns the minimum value of two numbers
    //
    template <typename T>
    T Minimum(T a, T b)
    {
        return (a < b) ? a : b;
    }

    //
    // Returns the maximum value of two numbers
    //
    template <typename T>
    T Maximum(T a, T b)
    {
        return (a > b) ? a : b;
    }

    //
    // Takes the position of a number between a range, and puts it in that space in a new range
    //
    template <typename T>
    void LockBetweenRange(T &number, T currentMin, T currentMax, T newMin, T newMax)
    {
        number = (number - currentMin) / (currentMax - currentMin);
        number *= (newMax - newMin);
        number += newMin;
    }

    //
    // Outputs a message to the debug log
    //
    void DebugMessage(const char* aMessage);

	//
	// Gets the Nth Root of a number
	//
	double NthRoot(uint aRoot, double aNumber);
}

#endif