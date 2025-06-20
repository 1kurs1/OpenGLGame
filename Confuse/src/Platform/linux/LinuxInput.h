#pragma once

#include "Confuse/Input.h"

namespace Confuse{
    class LinuxInput : public Input{
    protected:
        virtual bool isKeyPressedImpl(int keycode) override;

        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> getMousePositionImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };
}