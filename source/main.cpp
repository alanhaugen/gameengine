#include "platforms/application.h"
#include "demos/rollingball.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Breakout", 1100, 700);
    application.AddScene(new RollingBall);
    return application.Run();
}
