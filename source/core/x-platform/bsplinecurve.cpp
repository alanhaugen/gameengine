#include "bsplinecurve.h"

float BSplineCurve::findKnotInterval(float x)
{
    int my = controlPoints.size() - 1; // indekstilsistekontrollpunkt

    while (x < t[my])
    {
        my--;
    }

    return my;
}

glm::vec3 BSplineCurve::EvaluateBSplineSimple(float x)
{
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
    }

    return a[0];
}
