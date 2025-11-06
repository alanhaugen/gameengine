#include <core/platforms/application.h>

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "Tower Defense", 1100, 700);
    return application.Run();
}
