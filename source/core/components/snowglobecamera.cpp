#include "snowglobecamera.h"
#include "core/components/camera.h"
#include "core/components/fpvcamera.h"
#include "core/components/gameobject.h"

SnowGlobeCamera::SnowGlobeCamera(Camera* camera)
{
    name = "Snow Globe Camera";
    mainCamera = camera;
}

void SnowGlobeCamera::Update()
{
    if (gameObject)
    {
        if (init == false)
        {
            gameObject->AddComponent(new FPVCamera(mainCamera));
            init = true;
        }
        else
        {
            mainCamera->position = gameObject->GetPosition() - mainCamera->forward * distance;
        }
    }
}
