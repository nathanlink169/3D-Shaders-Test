#include "CommonHeader.h"

namespace npw
{
    std::random_device rd;
    std::mt19937_64 mt(rd());

    int Random(int aMaximumNumber)
    {
        return (int)(Random() * aMaximumNumber);
    }

    int Random(int aMinimumNumber, int aMaximumNumber)
    {
        if (aMaximumNumber - aMinimumNumber == 0)
            return aMinimumNumber;
        return (int)(Random(aMaximumNumber - aMinimumNumber) + aMinimumNumber);
    }

    double Random()
    {
        std::uniform_real_distribution<double> distribution(0, 1);
        return distribution(mt);
    }

    double Random(double aMaximumNumber)
    {
        return (Random() * aMaximumNumber);
    }

    double Random(double aMinimumNumber, double aMaximumNumber)
    {
        if (aMaximumNumber - aMinimumNumber == 0)
            return aMinimumNumber;
        return (Random(aMaximumNumber - aMinimumNumber) + aMinimumNumber);
    }

    double DistanceBetweenPoints(double aX1, double aY1, double aX2, double aY2)
    {
        return sqrt((aX2 - aX1) * (aX2 - aX1) + (aY2 - aY1) * (aY2 - aY1));
    }

    double DistanceBetweenPoints(vec2 aPoint1, vec2 aPoint2)
    {
        return DistanceBetweenPoints(aPoint1.x, aPoint1.y, aPoint2.x, aPoint2.y);
    }

    double DistanceBetweenPoints(b2Vec2 aPoint1, b2Vec2 aPoint2)
    {
        return DistanceBetweenPoints(aPoint1.x, aPoint1.y, aPoint2.x, aPoint2.y);
    }

    double DistanceBetweenPoints(b2Vec2 aPoint1, vec2 aPoint2)
    {
        return DistanceBetweenPoints(aPoint1.x, aPoint1.y, aPoint2.x, aPoint2.y);
    }

    double DistanceBetweenPoints(vec2 aPoint1, b2Vec2 aPoint2)
    {
        return DistanceBetweenPoints(aPoint1.x, aPoint1.y, aPoint2.x, aPoint2.y);
    }

    double DistanceBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2)
    {
        return sqrt((aX2 - aX1) * (aX2 - aX1) + (aY2 - aY1) * (aY2 - aY1) + (aZ2 - aZ1) * (aZ2 - aZ1));
    }

    double DistanceBetweenPoints(vec3 aPoint1, vec3 aPoint2)
    {
        return DistanceBetweenPoints(aPoint1.x, aPoint1.y, aPoint1.z, aPoint2.x, aPoint2.y, aPoint2.z);
    }

    vec2 MidpointBetweenPoints(double aX1, double aY1, double aX2, double aY2)
    {
        double deltaX = aX2 - aX1;
        double deltaY = aY2 - aY1;

        return vec2((float)(aX1 + (deltaX / 2)), (float)(aY1 + (deltaY / 2)));
    }

    vec3 MidpointBetweenPoints(double aX1, double aY1, double aZ1, double aX2, double aY2, double aZ2)
    {
        double deltaX = aX2 - aX1;
        double deltaY = aY2 - aY1;
        double deltaZ = aZ2 - aZ1;

        return vec3((float)(aX1 + (deltaX / 2)), (float)(aY1 + (deltaY / 2)), (float)(aZ1 + (deltaZ / 2)));
    }

    bool CircleToCircleCollision(double aX1, double aY1, double aRadius1, double aX2, double aY2, double aRadius2)
    {
        return (DistanceBetweenPoints(aX1, aY1, aX2, aY2) < aRadius1 + aRadius2) ? true : false;
    }

    bool RectangleToRectangleCollision(double aX1, double aY1, double aWidth1, double aHeight1, double aX2, double aY2, double aWidth2, double aHeight2)
    {
        return (aX2 > aX1 + aWidth1 || aX2 + aWidth2 < aX1 || aY2 + aHeight2 > aY1 || aY2 < aY1 + aHeight1) ? false : true;
    }

    std::wstring stringToWstring(std::string aString)
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

    b2Vec2 vec2_To_b2Vec2(vec2 v)
    {
        return b2Vec2(v.x, v.y);
    }
    vec2 b2Vec2_To_vec2(b2Vec2 v)
    {
        return vec2(v.x, v.y);
    }

    void DebugMessage(const char* aMessage)
    {
        OutputDebugStringA(aMessage);
    }

	double NthRoot(uint aRoot, double aNumber)
	{
		BreakIfTrue(aRoot == 0);

		return pow(aNumber, 1.0 / aRoot);
	}
}