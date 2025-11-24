#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

#include <vector>
#include "glm/glm.hpp"
#include "visualobject.h"

class BSplineSurface : public VisualObject
{
private:
    int n_u = 4; // antall kontrollpunkter for u
    int n_v = 3; // antall kontrollpunkter for v
    int d_u = 2;
    int d_v = 2;

    float hu = 0.1f;
    float hv = 0.1f;

    std::vector<Vertex> vertices;

    std::vector<float> mu ; // skjotvektor u
    std::vector<float> mv ; // skjotvektor v
    std::vector<glm::vec3> mc;

    // kontrollpunktene linjevis u retning matrise
    // elleritodimensjonalstd::pair<Vec3, Vec3> B2(float tu , float tv, int my_u, int my_v ) ;
    // Hardkodet for grad d_u = d_v = 2
    glm::vec3 c[4][3];

    glm::vec3 evaluateBiquadratic(int m_u, int m_v, glm::vec3 bu, glm::vec3 bv);
    void makeBiquadraticSurface();
    std::pair<glm::vec3, glm::vec3> B2(float tu, float tv ,
                                       int my_u, int my_v);
public :
    BSplineSurface();
    void Update();
};

#endif // BSPLINESURFACE_H
