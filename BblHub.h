#ifndef BBLHUB_H
#define BBLHUB_H


class MainWindow;
class ResourceManager;

class BBLHub
{
public:
    BBLHub();
    static MainWindow* mainWindow;
    static ResourceManager* resourceManager;

    static void SetMainWindow(MainWindow* mw){mainWindow = mw;}
    static void SetResourceManager(ResourceManager* rm){resourceManager = rm;}
};

#endif // BBLHUB_H
