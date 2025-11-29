#ifndef TRACKINGSPLINE_H
#define TRACKINGSPLINE_H

#include "core/components/visualobject.h"
#include "core/x-platform/bsplinecurve.h"
#include "core/components/component.h"
#include "core/components/timer.h"

class TrackingSpline : public Component
{
public:
    int splineDrawable = -1;
    int linesDrawable  = -1;
    std::vector<Vertex> points;
    VisualObject* followObject;

    float recreateSplineTime = 50.0f;

    BSplineCurve curve;

    Timer sampleTimer;

    TrackingSpline();
    void Update();
};

#endif // TRACKINGSPLINE_H
