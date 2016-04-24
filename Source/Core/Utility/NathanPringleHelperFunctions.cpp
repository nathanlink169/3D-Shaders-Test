#include "CommonHeader.h"

namespace npw
{
    void SetupHelperFunctions()
    {
        srand(time(NULL));
    }

    int Random(int aMaximumNumber)
    {
        return (rand() % aMaximumNumber);
    }

    int Random(int aMinimumNumber, int aMaximumNumber)
    {
        return (rand() % (aMaximumNumber - aMinimumNumber) + aMinimumNumber);
    }

    double Random()
    {
        return (static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
    }

    double Random(double aMaximumNumber)
    {
        return (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / aMaximumNumber)));
    }

    double Random(double aMinimumNumber, double aMaximumNumber)
    {
        return (aMinimumNumber + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (aMaximumNumber - aMinimumNumber))));
    }

    double DistanceBetweenPoints(double aX1, double aY1, double aX2, double aY2)
    {
        return sqrt((aX2 - aX1) * (aX2 - aX1) + (aY2 - aY1) * (aY2 - aY1));
    }

    double DistanceBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2)
    {
        return sqrt((aX2 - aX1) * (aX2 - aX1) + (aY2 - aY1) * (aY2 - aY1) + (aZ2 - aZ1) * (aZ2 - aZ1));
    }

    bool CircleToCircleCollision(double aX1, double aY1, double aRadius1, double aX2, double aY2, double aRadius2)
    {
        return (DistanceBetweenPoints(aX1, aY1, aX2, aY2) < aRadius1 + aRadius2) ? true : false;
    }

    bool RectangleToRectangleCollision(double aX1, double aY1, double aWidth1, double aHeight1, double aX2, double aY2, double aWidth2, double aHeight2)
    {
        return (aX2 > aX1 + aWidth1 || aX2 + aWidth2 < aX1 || aY2 + aHeight2 > aY1 || aY2 < aY1 + aHeight1) ? false : true;
    }

    std::wstring wstringToString(std::string aString)
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &aString[0], (int)aString.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &aString[0], (int)aString.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }

    bool IsEven(int aNumber)
    {
        return (aNumber % 2 == 0) ? true : false;
    }

    bool IsOdd(int aNumber)
    {
        return (aNumber % 2 == 0) ? false : true;
    }

    bool IsPositive(int aNumber)
    {
        return (aNumber > 0) ? true : false;
    }

    bool IsPositive(double aNumber)
    {
        return (aNumber > 0) ? true : false;
    }

    bool IsNegative(int aNumber)
    {
        return (aNumber < 0) ? true : false;
    }

    bool IsNegative(double aNumber)
    {
        return (aNumber < 0) ? true : false;
    }

    void BreakIfTrue(bool Condition)
    {
        if (Condition == true)
            __debugbreak();
    }

    void BreakIfFalse(bool Condition)
    {
        if (Condition == false)
            __debugbreak();
    }

    double ToRadians(double d)
    {
        return d * M_PI / 180;
    }

    double ToDegrees(double r)
    {
        return r * 180 / M_PI;
    }
}