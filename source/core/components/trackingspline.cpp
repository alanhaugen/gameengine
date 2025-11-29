#include "trackingspline.h"
#include "core/components/gameobject.h"

TrackingSpline::TrackingSpline()
{
    name = "Tracking Spline";

    sampleTimer.Start();
}

void TrackingSpline::Update()
{
    if (sampleTimer.TimeSinceStarted() > recreateSplineTime)
    {
        glm::vec3 pos;

        if (gameObject)
        {
            pos = gameObject->GetPosition();
        }
        else if (followObject)
        {
            pos = followObject->GetPosition();
        }

        sampleTimer.Reset();
        curve.controlPoints.push_back(pos);
        points.push_back(pos);

        if (splineDrawable != -1)
        {
            renderer->RemoveDrawable(splineDrawable);
        }

        std::vector<Vertex> vertices;

        // Recompute knot vector
        int n = curve.controlPoints.size() - 1;
        int d = curve.degree;
        curve.t.resize(n + d + 2);
        for (int i = 0; i < n + d + 2; ++i)
            curve.t[i] = float(i);

        // Sample curve
        float uStart = curve.t[d];
        float uEnd   = curve.t[curve.t.size() - d - 1];

        for (float f = 0.0f; f <= 1.0f; f += 0.01f)
        {
            float u = glm::mix(uStart, uEnd, f);
            vertices.push_back(Vertex(curve.EvaluateBSplineSimple(u), glm::vec3(1,1,1)));
        }

        splineDrawable = renderer->CreateDrawable(vertices, std::vector<unsigned>(), "shaders/color.vert.spv", "shaders/color.frag.spv", Renderer::LINES_STRIP);
        //linesDrawable = &renderer->CreateDrawable(points, std::vector<unsigned>(), "shaders/color.vert.spv", "shaders/color.frag.spv", Renderer::LINES_STRIP);
    }
}
