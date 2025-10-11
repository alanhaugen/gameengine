#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H

#include "../x-platform/scene.h"

class Mesh;

class BSplineCurve
{
public:
    // Determines how many control points influence each segment and
    // how smooth the curve is
    // f. ex. d = 3 would mean a cubic B-spline.
    int degree = 3;
    std::vector<int> t; // knot vector, the length of t should be n + d + 2
    std::vector<glm::vec3> controlPoints;

private:
    float n; // The number of control points minus one
    float findKnotInterval(float x)
    {
        int my = n - 1; // indekstilsistekontrollpunkt

        while (x < t[my])
        {
            my--;
        }

        return my;
    }

public:
    glm::vec3 EvaluateBSplineSimple(float x)
    {
        n = controlPoints.size() - 1;
        int my = findKnotInterval(x);
        std::vector<glm::vec3> a;

        a.resize(degree+1);

        for (int i = 0; i <= degree; i++)
        {
            a[degree-i] = controlPoints[my-i];
        }

        for (int k = degree; k > 0; k--)
        {
            int j = my - k;

            for (int i = 0; i < k; i++)
            {
                j++;

                float w = (x - t[j])/(t[j+k] - t[j]);

                a[i] = a[i] * (1-w) + a[i+1] * w;
            }

            return a[0];
        }

        Log("Eval of BSpline failed");

        return glm::vec3();
    }
};

class RollingBall : public Scene
{
public:
    RollingBall();
    void Init();
    void Update();

    BSplineCurve curve;

    Mesh* ballMesh;
};

#endif // ROLLINGBALL_H
