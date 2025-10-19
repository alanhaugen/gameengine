#include "platforms/application.h"
#include "demos/vikingscene.h"
#include "demos/empty.h"
#include "demos/pong.h"
#include "demos/flappybird.h"
#include "demos/rollingball.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Flappy Bird", 1100, 700);
    //application.AddScene(new Empty);
    //application.AddScene(new VikingScene);
    //application.AddScene(new RollingBall);
    //application.AddScene(new Pong);
    application.AddScene(new FlappyBird);
    return application.Run();
}
