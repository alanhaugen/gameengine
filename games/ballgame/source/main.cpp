#include <core/platforms/application.h>

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray, "RPG", 1100, 700);
    return application.Run();
}
