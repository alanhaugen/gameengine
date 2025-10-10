#include "platforms/application.h"
#include "demos/vikingscene.h"
#include "demos/empty.h"
#include "demos/rollingball.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);
    //application.AddScene(new VikingScene);
    //application.AddScene(new Empty);
    application.AddScene(new RollingBall);
    return application.Run();
}
