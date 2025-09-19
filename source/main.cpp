#include "platforms/application.h"

int main(int argumentQuantity, char *argumentArray[])
{
    Application application(argumentQuantity, argumentArray);
    return application.Run();
}
