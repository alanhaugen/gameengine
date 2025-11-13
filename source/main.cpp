#include "platforms/application.h"
//#include "demos/pong.h"
//#include "demos/rollingball.h"
//#include "demos/empty.h"
//#include "demos/vikingscene.h"
#include "demos/physicstestscene.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);

    //application.AddScene(new VikingScene);
    //application.AddScene(new Empty);
    //application.AddScene(new RollingBall);
    //application.AddScene(new Pong);
    //application.AddScene(new PhysicsTestScene);
    return application.Run();
}
