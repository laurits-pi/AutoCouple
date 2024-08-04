#include "stdafx.h"
#include "Mpc08D.h"
#include "initialization.h"
#include "movement.h"
#include <iostream>
#include <chrono>
#include <thread>

bool performConMovement(int arm, char axis, double distance /* in micrometers */) {
    const int pulses_per_um = 20;
    int pulses = static_cast<int>(distance * pulses_per_um);
    int axis_num;

    if (arm == 1) {
        switch (axis) {
        case 'z': axis_num = 1; break;
        case 'x': axis_num = 2; break;
        case 'y': axis_num = 3; break;
        default:
            std::cerr << "Invalid axis for arm 1" << std::endl;
            return false;
        }
    }
    else if (arm == 2) {
        switch (axis) {
        case 'z': axis_num = 4; break;
        case 'x': axis_num = 5; break;
        case 'y': axis_num = 6; break;
        default:
            std::cerr << "Invalid axis for arm 2" << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Invalid arm number" << std::endl;
        return false;
    }

    int result{};

    //double old_position;
    //int result = get_abs_pos(axis_num, &old_position);
    //if (result == -1) {
    //    std::cerr << "Error reading old position for axis " << axis << std::endl;
    //    return false;
    //}

    //result = check_alarm(axis_num);
    //if (result != 0) {
    //    std::cerr << "Alarm triggered on axis " << axis_num << " before movement." << std::endl;
    //    checkForErrors();
    //    checkAllAlarms(axis_num);
    //    return false;
    //}

    result = con_pmove(axis_num, static_cast<double>(pulses));
    if (result != 0) {
        std::cerr << "Movement failed for axis " << axis << "!" << std::endl;
        return false;
    }

    //auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        if (check_status(axis_num) & 1) break;

        //if (checkAlarmAfterStep(axis_num, "check_done")) return false;

        //auto current_time = std::chrono::high_resolution_clock::now();
        //auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

        //if (elapsed_time > 100) {
        //    std::cerr << "Movement timed out." << std::endl;
        //    return false;
        //}

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //double new_position;
    //new_position = get_abs_pos(axis_num, &new_position);
    //if (new_position == -1) {
    //    std::cerr << "Error reading new position for axis " << axis << std::endl;
    //    return false;
    //}


    //std::cout << "Constant movement successful for axis " << axis << std::endl;
    //std::cout << "  Old position: " << old_position / pulses_per_um << " um" << std::endl;
    //std::cout << "  New position: " << new_position / pulses_per_um << " um" << std::endl;

    return true;
}

bool performTrpMovement(int arm, char axis, double distance /* in micrometers */) {
    const int pulses_per_um = 20;
    int pulses = static_cast<int>(distance * pulses_per_um);
    int axis_num;

    if (arm == 1) {
        switch (axis) {
        case 'z': axis_num = 1; break;
        case 'x': axis_num = 2; break;
        case 'y': axis_num = 3; break;
        default:
            std::cerr << "Invalid axis for arm 1" << std::endl;
            return false;
        }
    }
    else if (arm == 2) {
        switch (axis) {
        case 'z': axis_num = 4; break;
        case 'x': axis_num = 5; break;
        case 'y': axis_num = 6; break;
        default:
            std::cerr << "Invalid axis for arm 2" << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Invalid arm number" << std::endl;
        return false;
    }

    double old_position;
    int result = get_abs_pos(axis_num, &old_position);
    if (result == -1) {
        std::cerr << "Error reading old position for axis " << axis << std::endl;
        return false;
    }

    result = check_alarm(axis_num);
    if (result != 0) {
        std::cerr << "Alarm triggered on axis " << axis_num << " before movement." << std::endl;
        checkForErrors();
        checkAllAlarms(axis_num);
        return false;
    }

    result = set_profile(axis_num, trapezoidal_vl, trapezoidal_vh, trapezoidal_accel, trapezoidal_decel);
    if (result != 0) {
        std::cerr << "Failed to set trapezoidal profile for axis " << axis << std::endl;
        return false;
    }

    result = con_pmove(axis_num, static_cast<double>(pulses));
    if (result != 0) {
        std::cerr << "Movement failed for axis " << axis << "!" << std::endl;
        return false;
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        if (check_status(axis_num) & 1) break;

        if (checkAlarmAfterStep(axis_num, "check_done")) return false;

        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

        if (elapsed_time > 100) {
            std::cerr << "Movement timed out." << std::endl;
            return false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    double new_position;
    result = get_abs_pos(axis_num, &new_position);
    if (result == -1) {
        std::cerr << "Error reading new position for axis " << axis << std::endl;
        return false;
    }

    std::cout << "Trapezoidal movement successful for axis " << axis << std::endl;
    std::cout << "  Old position: " << old_position / pulses_per_um << " um" << std::endl;
    std::cout << "  New position: " << new_position / pulses_per_um << " um" << std::endl;

    return true;
}

bool resetAxisPosition(int axis) {
    int result = reset_pos(axis);
    if (result != 0) {
        std::cerr << "Failed to reset position for axis " << axis << std::endl;
        return false;
    }
    return true;
}

double getAxisPosition(int axis) {
    double position;
    int result = get_abs_pos(axis, &position);
    if (result != 0) {
        std::cerr << "Failed to get position for axis " << axis << std::endl;
        return -1.0; // Indicate failure
    }
    return position;
}