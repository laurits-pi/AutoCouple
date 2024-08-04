from all_imports_and_inits import *

def init_coords(arm):
    """
    Generates an array of coordinates for the specified arm.

    Args:
        arm (int): The arm number (1 or 2).

    Returns:
        numpy.ndarray: An array of coordinates for the specified arm.

    Raises:
        ValueError: If the arm number is not 1 or 2.

    Arm 1: spiral
    Arm 2: grid pattern, but every second row is reversed
    """
    def spiral_sort_key(coord):
        x, y = coord[:2] - center
        radius = np.sqrt(x**2 + y**2)
        angle = np.arctan2(y, x)
        return (radius, angle)

    max_vals = np.array([12, 12])                                       # change the maximal deviation in x, y
    delta = 3                                                           # change the step size
    x_vals = np.arange(-max_vals[0], max_vals[0]+delta, delta)
    y_vals = np.arange(-max_vals[1], max_vals[1]+delta, delta)
    z_vals = 0                                                          # to keep number of positons down, keep constant. doesn't change much anyways.
    xx, yy = np.meshgrid(x_vals, y_vals)
    all_coords = np.column_stack((xx.ravel(), yy.ravel(), np.zeros_like(xx.ravel()))) # this contains all possible coordinates in normal grid pattern

    if arm == 1:
        # Sort coordinates in spiral order
        center = np.mean(all_coords, axis=0)[:2]    
        spiral_coords = np.array(sorted(all_coords, key=spiral_sort_key))
        return spiral_coords
    elif arm == 2:
        # reverse order of every second row in array sequence
        all_coords2 = all_coords.copy()
        reshaped = all_coords2.reshape(len(y_vals), len(x_vals), 3)
        reshaped[1::2, :] = reshaped[1::2, ::-1]
        all_coords2 = reshaped.reshape(-1, 3)
        return all_coords2
    else:
        raise ValueError("arm must be 1 or 2")

def fine_match_scan(port):
    """
    Scans through all possible combinations of coordinates for two arms and calculates the average power level
    for each combination. Returns the coordinates with the highest average power level.

    Args:
        port (serial.Serial): The serial object for the power meter.

    Returns:
        tuple: A tuple containing the best location of the first arm, the best location of the second arm, and the best power level.
    """

    best_power_level = -75
    best_location_1 = np.zeros(3)
    best_location_2 = np.zeros(3)
    all_coords_1 = init_coords(1)
    all_coords_2 = init_coords(2)
    for coords1 in tqdm(all_coords_1, leave=True, desc='Arm 1', colour='#7cedff',  ascii="░▒▓█", unit='pos'):    # iteration over coordinates of first arm （spiral)
        move_to_abs_pos(1, coords1)
        for coords2 in tqdm(all_coords_2, leave=False, desc='Arm 2', colour='#7cedff', ascii="->", unit='pos'):  # iteration over coordinates of second arm   (grid)
            move_to_abs_pos(2, coords2)
            power_level = np.round(avg_power_level(port, duration=0.00), 1) # because so many measurements are done, only measure once without averaging
            if power_level > best_power_level:
                best_power_level = power_level
                best_location_1 = coords1
                best_location_2 = coords2
        if best_power_level > -65:
            return best_location_1, best_location_2, best_power_level
    return best_location_1, best_location_2, best_power_level

def to_minimize(position, arm, port, duration_mul=1):
    """This function is called by scipy.optimize.minimize(), because the movement has to be completed before the measurement is taken"""
    move_to_abs_pos(arm, position)
    return -np.round(avg_power_level(port, duration=0.05*duration_mul), 1) # minus sign such that the result is "smaller is better"
    
def fine_match_powell(port, x0_1=np.zeros(3), x0_2=np.zeros(3)):
    """
    Perform optimization of the power level of two arms connected to a waveguide using Powell's method.
    
    Args:
        port (serial.Serial): The serial object for the power meter.
        x0_1 (numpy.ndarray, optional): The initial position of the first arm. Defaults to np.zeros(3).
        x0_2 (numpy.ndarray, optional): The initial position of the second arm. Defaults to np.zeros(3).
    
    Returns:
        float: The final power level after fine-tuning.
    
    Description:
        This function performs fine-tuning of the power level of two arms connected to a port. It uses the Powell optimization method to minimize the power level. The function iteratively moves the arms to different positions and measures the power level. The best position for each arm is determined based on the power level. The process is repeated until the power level is below -48 dBm or until a maximum of 5 iterations is reached. The function also resets the axis position and limits the bounds further if the power level is not below -48 dBm after the second iteration. The final power level is calculated and returned.
    """

    t1 = perf_counter()

    best_positions  = np.array([x0_1, x0_2])
    best_powerlevel = 75.00
    iteration = 1
    max_iter  = 5
    bounds = ((-20, 20), (-15, 15), (-10, 10))
    while (avg_power_level(port, 1) < -48 and iteration <= max_iter) or (iteration <= 2):
        for arm in [1, 2]:
            result = minimize(                              # actual minimization routine
                to_minimize,
                best_positions[arm-1],
                bounds=bounds, 
                options={'xtol': 0.5,'maxiter': 100},  
                args=(arm, port, iteration),
                method='Powell')
            if result.fun < best_powerlevel:
                best_powerlevel = result.fun
                best_positions[arm-1] = result.x
            move_to_abs_pos(arm, best_positions[arm-1])
            print(f"Iteration {iteration}.{arm}: Power level: {-best_powerlevel:.1f} dBm, Best positions arm 1: {best_positions[0].round(1)}, arm 2: {best_positions[1].round(1)}, Measurements: {result.nfev}")
        if iteration == 3:
            reset_axis_position()
            best_positions = np.zeros((2, 3))
            print('Reset axis position, limit bounds further...')
            bounds = ((-5, 5), (-5, 5), (-10, 10))
        iteration += 1

    t2 = perf_counter()
    print(f'\nElapsed time: {t2-t1:.2f} s')
    sleep(1)
    final_power_level = avg_power_level(port, duration=0.5)
    print(f'\nFinal power level: {final_power_level:.2f} dBm')

    return final_power_level


def fine_match_main():
    """
    This function performs the fine matching process to establish and optimize the power level.

    Parameters:
        None

    Returns:
        None

    This function initializes a serial connection to a device connected to a COM port. It then measures the starting power level of the device and prints it.
    The function then resets the position of the device's axes. If the starting power level is below -65 dBm, it performs a brute force scan to find the signal strength of the device.
    If the starting power level is not below -65 dBm, it initializes the initial positions of the device's axes as zeros.
    Finally, it prints the initial positions of the device's axes and calls the `fine_match_powell` function to perform a Powell optimization on the device's axes.
    After the optimization is complete, the serial connection is closed.

    -75.00 dBm is the power level returned by the meter as long as there is no connection established.
    """

    port = serial.Serial(
            port='COM13', 
            baudrate=57600,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.016
           )
    
    starting_level = avg_power_level(port, duration=0.5)
    print(f'\nStarting power level: {starting_level:.2f} dBm')

    reset_axis_position()
    if starting_level < -65:
        print('Brute force scan...')
        x0_1, x0_2, best_power_level = fine_match_scan(port)
        print(f'\nFound signal of strength: {best_power_level} dBm, exited brute force loop.')
    else:
        x0_1, x0_2 = np.zeros((2, 3))

    print(f'Starting Powell optimization with inital --> arm 1: {x0_1.round(1)}, arm 2: {x0_2.round(1)}')
    fine_match_powell(port, x0_1, x0_2)
    port.close()


if __name__ == '__main__':
    fine_match_main()