#include <core/platforms/application.h>
#include "splash.h"
#include "mainmenu.h"
#include "game.h"
#include "victory.h"
#include "gameover.h"
#include "physicstest.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 640, 480);
    application.AddScene(new Splash);
    application.AddScene(new PhysicsTest);
    application.AddScene(new MainMenu);
    application.AddScene(new Game);
    application.AddScene(new Victory);
    application.AddScene(new GameOver);
    return application.Run();
}
