#include "stdafx.h"
#include "Mpc08D.h"
#include "initialization.h"
#include "movement.h"
#include <iostream>

// Exported function to initialize the application
extern "C" __declspec(dllexport) bool InitApp() {
    return theApp.InitInstance();
}

// Exported function to perform continuous speed movement
extern "C" __declspec(dllexport) bool PerformConMovement(int arm, char axis, double distance) {
    return performConMovement(arm, axis, distance);
}

// Exported function to perform trapezoidal speed movement
extern "C" __declspec(dllexport) bool PerformTrpMovement(int arm, char axis, double distance) {
    return performTrpMovement(arm, axis, distance);
}

// Exported function to wait for movement to end
extern "C" __declspec(dllexport) void waitForMovementEnd(int axis_num) {
    while (true) {
        if (check_status(axis_num) & 1) break;
    }
}

// Exported function to reset axis position
extern "C" __declspec(dllexport) bool ResetAxisPosition(int axis) {
    return resetAxisPosition(axis);
}

// Exported function to get axis position
extern "C" __declspec(dllexport) double GetAxisPosition(int axis) {
    return getAxisPosition(axis);
}
