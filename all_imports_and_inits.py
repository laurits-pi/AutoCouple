### This file has the following purposes:
# 1. Import all the necessary modules
# 2. Make C++ fuctions form the dll available as python functions
# 3. Initialize the APICO controller
# 4. Define miscellaneous functions
#
# Within the folder AutoCoupling, you can just import this file with "from all_imports_and_inits import * ".
# The names of the functions will be the same as in this file, that also includes the modules (i.e. np.sin() )

import os
import cv2
import json
import psutil
import ctypes
import serial
import threading
import numpy as np
import tkinter as tk
from tqdm import tqdm
import scipy.fft as fft
# import fine_match_recursive
from tkinter import messagebox
import matplotlib.pyplot as plt
from scipy.optimize import minimize
from time import perf_counter, sleep
from skimage.registration import phase_cross_correlation
from skimage.transform import warp_polar, rotate, rescale
from skimage.filters import window, difference_of_gaussians
from concurrent.futures import ThreadPoolExecutor, as_completed


# Kill the APICO app because the API will give random errors otherwise
print("Checking for open apps using the API...")
PROCNAME  = "ApicoAutoAlignmentSystem.exe"
PROCNAME2 = "AutoCoupling.exe"
for proc in psutil.process_iter():
    if proc.name() == PROCNAME:
        proc.kill()
        print("APICO app closed.")
        sleep(0.5)
    if proc.name() == PROCNAME2:
        proc.kill()
        print("AutoCoupling app closed.")
        sleep(0.5)


os.chdir(os.path.dirname(os.path.abspath(__file__)))
dll_path = os.path.join(os.path.curdir, 'pythonAPI', 'V5', 'movement_API.dll')
robotic_arm_dll = ctypes.CDLL(dll_path)


# Initialize the application
if not robotic_arm_dll.InitApp():
    print("Initialization failed")
    exit()

# Define the function argument types and return type
robotic_arm_dll.InitApp.argtypes = []
robotic_arm_dll.InitApp.restype = ctypes.c_bool

robotic_arm_dll.PerformConMovement.argtypes = [ctypes.c_int, ctypes.c_char, ctypes.c_double]
robotic_arm_dll.PerformConMovement.restype = ctypes.c_bool

robotic_arm_dll.PerformTrpMovement.argtypes = [ctypes.c_int, ctypes.c_char, ctypes.c_double]
robotic_arm_dll.PerformTrpMovement.restype = ctypes.c_bool

robotic_arm_dll.waitForMovementEnd.argtypes = [ctypes.c_int]
robotic_arm_dll.waitForMovementEnd.restype = None

robotic_arm_dll.ResetAxisPosition.argtypes = [ctypes.c_int]
robotic_arm_dll.ResetAxisPosition.restype = ctypes.c_bool

robotic_arm_dll.GetAxisPosition.argtypes = [ctypes.c_int]
robotic_arm_dll.GetAxisPosition.restype = ctypes.c_double


def perform_continuous_movement(arm, axis, distance):
    """
    Move the arm along the specified axis for the specified distance in continuous mode

    Parameters
    ----------
    arm : int
        The arm to move (1 or 2)
    axis : str
        The axis to move ('x', 'y', or 'z')
    distance : float
        The distance to move in µm
    """
    return robotic_arm_dll.PerformConMovement(arm, axis.encode('utf-8'), ctypes.c_double(distance))


def perform_trapezoidal_movement(arm, axis, distance):
    """
    Move the arm along the specified axis for the specified distance in trapezoidal mode

    Parameters
    ----------
    arm : int
        The arm to move (1 or 2)
    axis : str
        The axis to move ('x', 'y', or 'z')
    distance : float
        The distance to move in µm
    """
    return robotic_arm_dll.PerformTrpMovement(arm, axis.encode('utf-8'), ctypes.c_double(distance))


def reset_axis_position():
    """
    Reset the position of all axis to zero

    Parameters
    ----------
    axis : int
        The axis to reset
    """
    for i in range(1, 7):
        robotic_arm_dll.ResetAxisPosition(i)


def get_axis_position(axis):
    """
    Get the current position of the specified axis

    Parameters
    ----------
    axis : int
        The axis to query

    Returns
    -------
    float
        The current position of the axis in µm
    """
    return robotic_arm_dll.GetAxisPosition(axis) / 20

def read_power_level(port):
    """
    Read the power level from the specified port. Port must be a serial.Serial object. Port must be closed after function call.

    Parameters
    ----------
    port : object
        The port object for communication.

    Returns
    -------
    float
        The power level in dBm.
    """
    command = bytes.fromhex('EEAA03010000')
    port.write(command)
    response = port.read(4)
    value = int.from_bytes(response, byteorder='big')  # Convert response to integer
    power_level_dbm = (value - 10000) / 100
    return power_level_dbm

def avg_power_level(port, duration=1):
    """
    Calculate the average power level over a specified duration by continuously reading the power level from the given port.
    Port must be a serial.Serial object. Port must be closed after function call.
    
    Parameters
    ----------
    duration : float
        The duration in seconds for which the power level is averaged.
    port : object
        The port object for communication.

    Returns
    -------
    float
        The average power level over the specified duration.
    """
    start_time = perf_counter()
    power_level_sum = read_power_level(port)
    calls_to_read   = 1
    while perf_counter() - start_time < duration:
        power_level_sum += read_power_level(port)
        calls_to_read += 1
    return power_level_sum / calls_to_read

def find_current_position(arm):
    """
    Finds the current position of the specified arm.

    Parameters:
        arm (int): The arm number (1 or 2).

    Returns:
        numpy.ndarray: An array containing the current positions of the three axes of the specified arm in microns.

    Raises:
        ValueError: If the arm number is not 1 or 2.
    """
    if arm == 1:
        return np.array([get_axis_position(2), get_axis_position(3), get_axis_position(1)])
    elif arm == 2:
        return np.array([get_axis_position(5), get_axis_position(6), get_axis_position(4)])
    else:
        raise ValueError("Arm must be 1 or 2")

def move_to_abs_pos(arm, position):
    """
    Moves the arm to the absolute position specified by the given coordinates.
    
    Parameters:
        arm (int): 
           The arm number (1 or 2).
        position (numpy.ndarray):
           An array containing the target position of the arm in microns for each axis.
    """
    curr_pos = find_current_position(arm)

    dx, dy, dz = position - curr_pos

    perform_continuous_movement(arm, 'x', dx)
    perform_continuous_movement(arm, 'y', dy)
    perform_continuous_movement(arm, 'z', dz)