#ifndef TRACKINGSPLINE_H
#define TRACKINGSPLINE_H

#include "core/x-platform/bsplinecurve.h"
#include "core/components/component.h"
#include "core/components/timer.h"

class TrackingSpline : public Component
{
public:
    Renderer::Drawable* splineDrawable = nullptr;
    Renderer::Drawable* linesDrawable = nullptr;
    std::vector<Vertex> points;

    BSplineCurve curve;

    Timer sampleTimer;

    TrackingSpline();
    void Update();
};

#endif // TRACKINGSPLINE_H
