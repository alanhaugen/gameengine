#include <core/platforms/application.h>
#include "vikingscene.h"
#include "rollingball.h"
#include "empty.h"
#include "pong.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Demos", 1100, 700);

    application.AddScene(new VikingScene);
    application.AddScene(new RollingBall);
    application.AddScene(new Pong);
    application.AddScene(new Empty);
    return application.Run();
}
