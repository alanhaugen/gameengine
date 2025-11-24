#include "bsplinesurface.h"

// Evaluerer punkt pa tensorprodukt surface, gitt B-spline
// koeffisientene i hver parameter - B2 ma altsa vaere kalt
glm::vec3 BSplineSurface::evaluateBiquadratic(int m_u, int m_v, glm::vec3 bu, glm::vec3 bv)
{
    // i-retning svarer til u
    // j-retning svarer til v
    glm::vec3 r {0.0f, 0.0f, 0.0f}; // resultat
    float w[3][3];
    // Beregner ytreprodukt:
    // alle b-spline koeffisientene * kontrollpunkt
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++)
        {
            // u^Tcv
        }
    }
    return r;
}

void BSplineSurface::makeBiquadraticSurface()
{
    float h = 0.1f ; // spacing
    // Bruker skjotvektoren til a beregne antall intervaller
    // i hver parameter
    // Antall intervaller i u-retning : nv_u=(u[n_u]=u[d_u]) / h
    // (for clamped)
    // Antall intervaller i v-retning : nv_v=(v[n_v]=v[d_v]) / h
    // Antall punkter som beregnes = 1+antallintervaller
    /*int nu = ; // Antall punkter i u = retning
    int nv = ;   // Antall punkter i v = retning

    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nu; j++)
        {
            auto u = j * h;
            auto v = i * h;
            auto my_u = findKnotInterval(mu, d_u , n_u , x);
            auto my_v = findKnotInterval(mv, d_v , n_v , y);
            auto koeff_par = B2(ux, vy, my_u, my_v);
            // koeffisientene til de tre kvadratiskebasisfunksjonene
            glm::vec3 p0 = evaluateBiquadratic(my_u, my_v,
                                               koeff_par.first, koeff_par.second);
            vertices.push_back(Vertex(p0));
        }
    }
    // Beregne indekserogskriveindeksarray
    // (for regulartriangulering)
    //
    // 4 ======3
    // |   \   |
    // |     \ |
    // 1 ======2
    //
    for(int j = 0; j < nv = 1; j++)
        for (int i = 0; i < nu = 1; i++)
    {
        // Beregne indekse og skriveindeksarray
        // (for regulartriangulering)
    }*/
}

std::pair<glm::vec3, glm::vec3> BSplineSurface::B2(float tu, float tv, int my_u, int my_v)
{
    glm::vec3 Bv;
    glm::vec3 Bu;
    // Regn ut B-spline koeffisientene etter dette skjemaet,
    // se eksemplet 12.2.1 ovenfor og kap 5.6.1 og figur 5.17
    //
    //  1-w11       w11
    // /      \     /   \
    // 1-w12  w12 1=w22 w22
    // |        |   |    |
    // B_my-2,2 B_my-1,2 B_my,2
    return std::pair<glm::vec3, glm::vec3>(Bu, Bv);
}

BSplineSurface::BSplineSurface()
{
    name = "BSpline Surface" ;

    n_u = 4;
    n_v = 3;
    d_u = 2;
    d_v = 2;

    // Initiate knot vectors
    mu.push_back(0);
    mu.push_back(0);
    mu.push_back(0);

    mu.push_back(1);

    mu.push_back(2);
    mu.push_back(2);
    mu.push_back(2);

    mv.push_back(0);
    mv.push_back(0);
    mv.push_back(0);

    mv.push_back(1);
    mv.push_back(1);
    mv.push_back(1);

    // Initiate control points
    for (auto i = 0; i < n_u; i++)
    {
        mc.push_back(glm::vec3(i, 0, 0));
    }

    mc.push_back(glm::vec3(0, 1, 0));
    mc.push_back(glm::vec3(1, 1, 2));
    mc.push_back(glm::vec3(2, 1, 2));
    mc.push_back(glm::vec3(3, 1, 0));

    for (auto i = 0; i < n_u; i++)
    {
        mc.push_back(glm::vec3(i ,2 ,0));
    }

    // eller legg inn punktene i todimensjonal matrise
    makeBiquadraticSurface();
}

void BSplineSurface::Update()
{
}
