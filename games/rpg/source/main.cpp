#include "platforms/application.h"
#include "demos/rollingball.h"
#include "demos/empty.h"
#include "demos/pong.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);

    //application.AddScene(new VikingScene);
    //application.AddScene(new Empty);
    //application.AddScene(new RollingBall);
    application.AddScene(new Pong);
    return application.Run();
}
