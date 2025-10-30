#include "platforms/application.h"
#include "demos/empty.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);
    application.AddScene(new Empty);
    return application.Run();
}
