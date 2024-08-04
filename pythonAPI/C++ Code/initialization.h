#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "stdafx.h"
#include "Mpc08D.h"
#include <iostream>

class CTestApp : public CWinApp {
public:
    virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};

extern CTestApp theApp;

int getNumAxes();
bool checkForErrors();
bool checkHardwareLimits(int axis);
void checkAllAlarms(int axis);
bool checkAlarmAfterStep(int axis, const std::string& step);
void print_axis_info(int axis, const std::string& axis_label);

// Speed and Acceleration Constants
extern const double max_speed;
extern const double con_speed;
extern const double trapezoidal_vl;
extern const double trapezoidal_vh;
extern const double trapezoidal_accel;
extern const double trapezoidal_decel;

#endif // INITIALIZATION_H
