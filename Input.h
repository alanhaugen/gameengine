#ifndef INPUT_H
#define INPUT_H

struct Input
{
    bool W{false};
    bool A{false};
    bool S{false};
    bool D{false};

    bool UP{false};
    bool DOWN{false};
    bool LEFT{false};
    bool RIGHT{false};

    bool Q{false};
    bool E{false};
    bool R{false};
    bool C{false};

    bool LSHIFT{false};
    bool LCTRL{false};
    bool SPACE{false};

    bool RMB{false};    //Glory Mouse
    bool MMB{false};
    bool LMB{false};
    bool MB4{false};
    bool MB5{false};


    float MWHEEL{0.f};  //MouseWheel
    int MOUSEX{0};
    int MOUSEY{0};
};

#endif // INPUT_H
