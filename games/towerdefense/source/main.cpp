#include <core/platforms/application.h>
#include "splash.h"
#include "mainmenu.h"
#include "game.h"
#include "victory.h"
#include "gameover.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);
    //application.AddScene(new Splash);
    application.AddScene(new MainMenu);
    application.AddScene(new Game);
    application.AddScene(new Victory);
    application.AddScene(new GameOver);
    return application.Run();
}
