#include "initialization.h"

CTestApp theApp;

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
END_MESSAGE_MAP()

int num_axes;
const double max_speed = 2000.0;
const double con_speed = 2000.0;
const double trapezoidal_vl = 100.0;  // low speed for trapezoidal motion
const double trapezoidal_vh = 20000.0;  // high speed for trapezoidal motion
const double trapezoidal_accel = 1000.0;
const double trapezoidal_decel = 1000.0;

int getNumAxes() {
    return num_axes;
}

bool checkForErrors() {
    int errCode = get_last_err();
    if (errCode != 0) {
        std::cout << "Error detected: " << errCode << std::endl;
        return true;
    }
    return false;
}

bool checkHardwareLimits(int axis) {
    enable_el(axis, 1);
    int limit_status = check_limit(axis);

    if (checkForErrors()) {
        return true;
    }

    switch (limit_status) {
    case 0:
        std::cout << "No limit signal is active." << std::endl;
        break;
    case 1:
        std::cerr << "Positive limit signal is active." << std::endl;
        return true;
    case -1:
        std::cerr << "Negative limit signal is active." << std::endl;
        return true;
    case 2:
        std::cerr << "Error: Both positive and negative limit signals are active simultaneously!" << std::endl;
        return true;
    case -3:
        std::cerr << "Error in checking limit signal." << std::endl;
        return true;
    default:
        std::cerr << "Unknown status." << std::endl;
        return true;
    }
    return false;
}

void checkAllAlarms(int axis) {
    int alarmStatus;

    alarmStatus = check_alarm(axis);
    std::cout << "General alarm status: " << alarmStatus << std::endl;

    alarmStatus = check_limit(axis);
    std::cout << "Limit alarm status: " << alarmStatus << std::endl;
}

bool checkAlarmAfterStep(int axis, const std::string& step) {
    if (check_alarm(axis) != 0) {
        std::cerr << "Alarm triggered on axis " << axis << " after " << step << std::endl;
        checkAllAlarms(axis);
        checkForErrors();
        return true;
    }
    return false;
}

void print_axis_info(int axis, const std::string& axis_label) {
    int status = check_status(axis);
    if (status == -1) {
        std::cerr << "Error reading status for " << axis_label << std::endl;
        return;
    }

    double position;
    int result = get_abs_pos(axis, &position);
    if (result == -1) {
        std::cerr << "Error reading position for " << axis_label << std::endl;
        return;
    }

    std::cout << "Status of " << axis_label << ":" << std::endl;
    std::cout << "  Home signal: " << ((status & (1 << 30)) ? "Active" : "Not active") << std::endl;
    std::cout << "  Positive limit: " << ((status & (1 << 29)) ? "Active" : "Not active") << std::endl;
    std::cout << "  Negative limit: " << ((status & (1 << 28)) ? "Active" : "Not active") << std::endl;
    std::cout << "  Alarm signal: " << ((status & (1 << 26)) ? "Active" : "Not active") << std::endl;
    std::cout << "  Z Pulse signal: " << ((status & (1 << 8)) ? "Active" : "Not active") << std::endl;
    std::cout << "  Motion state: " << ((status & 1) ? "Stop" : "Moving") << std::endl;
    std::cout << "  Current position: " << position << " pulses" << std::endl;
}

BOOL CTestApp::InitInstance() {
    CWinApp::InitInstance();

    num_axes = auto_set();
    if (num_axes <= 0) {
        std::cerr << "Detection failed!" << std::endl;
        return FALSE;
    }

    int errCode = get_last_err();
    if (errCode != 0) {
        std::cerr << "Error detected: " << errCode << std::endl;
    }

    int result = init_board();
    if (result <= 0) {
        std::cerr << "Initialization failed!" << std::endl;
        return FALSE;
    }

    int alarmStatus;
    alarmStatus = check_alarm(1);
    std::cout << "General alarm status: " << alarmStatus << std::endl;

    std::cout << "Board initialized successfully!" << std::endl;
    std::cout << "Number of detected axes: " << num_axes << std::endl;

    for (int i = 0; i < num_axes; ++i) {
        int ch = i + 1;
        set_outmode(ch, 1, 0);
        set_alm_logic(ch, 0);
        set_home_mode(ch, 0);
        set_el_logic(ch, 1);
        set_org_logic(ch, 1);
        int cardNum = ((ch - 1) / 4) + 1;
        int bitNum = ch - (cardNum - 1) * 4;
        outport_bit(cardNum, bitNum, 0);
    }

    for (int axis = 1; axis <= num_axes; ++axis) {
        result = set_maxspeed(axis, max_speed);
        if (result != 0) {
            std::cerr << "Failed to set max speed for axis " << axis << std::endl;
            return FALSE;
        }
        result = set_conspeed(axis, con_speed);
        if (result != 0) {
            std::cerr << "Failed to set constant speed for axis " << axis << std::endl;
            return FALSE;
        }
    }

    set_backlash(2, 1.6*20); // arm 1 x 
	set_backlash(3, 0.9*20); //       y
    set_backlash(1, 1.0*20); //       z 
    set_backlash(5, 0.3*20); // arm 2 x
	set_backlash(6, 0.7*20); //       y
    set_backlash(4, 1.0*20); //       z
    
    result = 0;
	//for (int axis = 1; axis <= 6; ++axis) {
	//	result += start_backlash(axis);
	//}
    if (result != 0) {
		std::cerr << "Failed to set backlash for all axes" << std::endl;
		return FALSE;
	}
    return TRUE;
}
