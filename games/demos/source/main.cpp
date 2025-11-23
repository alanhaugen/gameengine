#include <core/platforms/application.h>
#include "vikingscene.h"
#include "rollingball.h"
#include "flappybird.h"
#include "empty.h"
#include "pong.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Demos", 800, 500);

    //application.AddScene(new RollingBall);
    //application.AddScene(new VikingScene);
    //application.AddScene(new Pong);
    //application.AddScene(new FlappyBird);
    application.AddScene(new Empty);

    return application.Run();
}
