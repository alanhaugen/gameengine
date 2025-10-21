#include "platforms/application.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Breakout", 1100, 700);
    application.AddScene(new MainMenu);
    application.AddScene(new Game);
    application.AddScene(new GameOver);
    application.AddScene(new Victory);
    return application.Run();
}
