#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include <glm/glm.hpp>

class BSplineCurve
{
public:
    // Determines how many control points influence each segment and
    // how smooth the curve is
    // f. ex. d = 3 would mean a cubic B-spline.
    int degree = 3;
    std::vector<float> t; // knot vector, the length of t should be n + d + 2
    std::vector<glm::vec3> controlPoints;

private:
    float findKnotInterval(float x);

public:
    glm::vec3 EvaluateBSplineSimple(float x);
};

#endif // BSPLINECURVE_H
