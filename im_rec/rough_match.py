import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from all_imports_and_inits import *

### general overview:

# call rough_match() to initiate the automatic coupling process
# here the images and the dictionary with the relative coordinates are loaded

# then find_rotation_scale() is called to find the rotation and scale between the image and the template

# rotate_scale_template() is called to rotate and scale the template image

# find_translation() is called to find the translation of the template image within the larger image using normal template matching

# using aff_trans_point() the relative coordinates are transformed to the new coordinates in the picture from the camera

# then the positions of the fiber tips are found using template matching find_fibers() -> make sure to use the correct templates

# ask the user if the chip is marked correctly -> if not, call auto_couple() again, but with rs_method='bf'
#                                              -> if yes, continue and call match_positions()

# finally the positions of the fibers are matched with the input and output points on the chip using match_positions().
# right now we only print where the fiber should move

def read_img():
    """
    Reads an image from the webcam.

    Returns:
    - frame: numpy.ndarray Size: (1080, 1920, 3)
        The image read from the webcam.
    """
    # kill camera app
    print("Checking for open camera app...")
    PROCNAME = "WindowsCamera.exe"
    for proc in psutil.process_iter():
        if proc.name() == PROCNAME:
            proc.kill()
            print("Camera app closed.")
    
    print("Opening camera...")
    cap = cv2.VideoCapture(0)  # 0 is the default camera
    # Check if the webcam is opened correctly
    if not cap.isOpened():
        print("Error: Could not open video device!")
        exit()

    # Set the video frame width and height
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)


    # Read a frame from the webcam
    print("Reading frame...")
    ret, frame = cap.read()
    if not ret or frame is None:
        print("Error: Could not read frame from webcam - make sure the camera app is closed!")
        exit()
    print("Frame reading complete.")

    # Release the video device
    cap.release()

    return frame


def process_image(input_image, canny_low=100, canny_high=1, kernel_size=2):
    """
    Process the input image by converting it to grayscale, applying Canny edge detection,
    and dilating the edges using a specified kernel size.

    Parameters:
    - input_image: numpy.ndarray
        The input image to be processed.
    - canny_low: int, optional
        The lower threshold value for the Canny edge detection algorithm.
    - canny_high: int, optional
        The higher threshold value for the Canny edge detection algorithm.
    - kernel_size: int, optional
        The size of the kernel used for dilation. Bigger kernel size makes the lines thicker.

    Returns:
    - processed_image: numpy.ndarray
        The processed image after applying grayscale conversion, Canny edge detection,
        and dilation.
    """
    
    kernel = np.ones((kernel_size, kernel_size), np.uint8)
    # Check if the image is already grayscale
    if len(input_image.shape) > 2:
        image = cv2.cvtColor(input_image, cv2.COLOR_BGR2GRAY)
    else:
        image = input_image

    image = cv2.Canny(image, canny_low, canny_high)
    processed_image = cv2.dilate(image, kernel)             # this makes the lines thicker. 

    return processed_image

def process_template(template, image, canny_low=100, canny_high=1, kernel_size=16, rel_size=1):
    """
    Process the template image and return the processed template and padded template.

    Parameters:
    - template: numpy.ndarray
        The template image to be processed.
    - image: numpy.ndarray
        The input image to compare the template against.
    - canny_low: int, optional
        The lower threshold value for the Canny edge detection algorithm. Default is 100.
    - canny_high: int, optional
        The higher threshold value for the Canny edge detection algorithm. Default is 1.
    - kernel_size: int, optional
        The size of the kernel used for dilation. Bigger kernel size makes the lines thicker. Default is 16.
    - rel_size: float, optional
        The relative size of the processed template compared to the input image. Default is 1.

    Returns:
    - template_loc: numpy.ndarray
        The processed template image.
    - template_pad: numpy.ndarray
        The padded template image.
    """

    # previously I set the rel_size such that the sizes actually match. but that means that for diffent zooms of the camera
    # this value has to be changed by hand. because of that I now set it to 1 and compute the scale only in the find_rotation_scale() function
    # this needs to be accounted for in the aff_trans_point() function which right now doesn't work. but it already works for drawing the rotated
    # rectangle on the image in auto_couple()
    
    kernel = np.ones((kernel_size, kernel_size), np.uint8)

    if len(template.shape) > 2:
        template_loc = cv2.cvtColor(template, cv2.COLOR_BGR2GRAY)
    else:
        template_loc = template

    template_loc = cv2.Canny(template_loc, canny_high, canny_low)
    # rotation, scale, M = find_rotation_scale_feat(img1, tmp1)y_low)
    template_loc = cv2.dilate(template_loc, kernel)
    template_loc = cv2.resize(template_loc, (int(image.shape[0]*rel_size), int(image.shape[0]*rel_size)))
    # add padding to the template equally on each side
    template_pad = np.pad(template_loc, ((image.shape[0]//2-template_loc.shape[0]//2, image.shape[0]//2-template_loc.shape[0]//2), (image.shape[1]//2-template_loc.shape[1]//2, image.shape[1]//2-template_loc.shape[1]//2)), 'constant', constant_values=(0, 0))
    template_pad = template_pad[:1080, :1920]
    return template_loc, template_pad

def find_rotation_scale(image, template_pad, bp_low=5, bp_high=20, cutoff_high_freq=8, upsample_factor=100, normalization=None):
    """
    Finds the rotation and scale between an image and a template using cross-correlation.

    Parameters:
    - image: numpy.ndarray
        The input image.
    - template_pad: numpy.ndarray
        The template image.
    - bp_low: int, optional
        The lower cutoff frequency for the bandpass filter. Default is 5.
    - bp_high: int, optional
        The higher cutoff frequency for the bandpass filter. Default is 20.
    - cutoff_high_freq: int, optional
        The cutoff frequency for the log-polar transformation. Default is 8.
    - upsample_factor: int, optional
        The upsampling factor for the cross-correlation. Default is 10.
    - normalization: str or None, optional
        The type of normalization to apply during cross-correlation. Default is None.

    Returns:
    - recovered_angle: float
        The rotation angle between the image and the template.
    - error: float
        The error value of the cross-correlation.
    - shift_scale: float
        The scale factor between the image and the template.
    """
    # bandpass filter
    image_fil = difference_of_gaussians(image, bp_low, bp_high)
    template_fil = difference_of_gaussians(template_pad, bp_low, bp_high)

    # circular window
    w_image = window('hamming', image.shape) * image_fil                # Method 1
    w_template = window('hamming', template_pad.shape) * template_fil

    # fft
    image_fft = np.abs(fft.fftshift(fft.fft2(w_image)))
    template_fft = np.abs(fft.fftshift(fft.fft2(w_template)))

    # create log-polar transformed ffts
    shape = image_fft.shape
    radius = shape[0]//cutoff_high_freq   # only use low freq

    image_fft_lp = warp_polar(image_fft, radius=radius, output_shape=shape, scaling='log')
    template_fft_lp = warp_polar(template_fft, radius=radius, output_shape=shape, scaling='log')

    image_fft_lp_half = image_fft_lp[: shape[0]//2, :]           # just use half of the fft
    template_fft_lp_half = template_fft_lp[: shape[0]//2, :]

    # cross-correlation
    shift, _, _ = phase_cross_correlation(template_fft_lp_half, image_fft_lp_half, upsample_factor=upsample_factor, normalization=normalization)
    # use translation parameters to calculate rotation and scale
    shiftr, shiftc = shift[:2]
    recovered_angle = (360 / shape[0]) * shiftr
    klog = shape[1] / np.log(radius)
    shift_scale = np.exp(shiftc / klog)

    return recovered_angle, shift_scale


def find_rotation_scale_bf(image, template, scale_range=(0.82, 0.86), scale_step=0.01, rotation_range=(-4, 4), rotation_step=0.05):
    """
    Brute force method to find the rotation and scale of a template in an image. Generate many different templates
    and check which one is fitting the best.

    Parameters:
    - image: numpy.ndarray
        The input image.
    - template: numpy.ndarray
        The template image to be rotated and scaled.
    - scale_range: tuple, optional
        The range of scale factors to check. Default is (0.7, 0.95).
    - scale_step: float, optional
        The step size for the scale factor. Default is 0.01.
    - rotation_range: tuple, optional
        The range of rotation angles to check. Default is (-5, 5).
    - rotation_step: float, optional
        The step size for the rotation angle. Default is 0.1.

    Returns:
    - best_rotation: float
        The best rotation angle.
    - best_scale: float
        The best scale factor.
    """
    def rotate_image(image, angle):
        (h, w) = image.shape[:2]
        center = (w / 2, h / 2)
        M = cv2.getRotationMatrix2D(center, angle, 1.0)
        rotated = cv2.warpAffine(image, M, (w, h))
        return rotated

    def scale_image(image, scale):
        h, w = image.shape[:2]
        scaled = cv2.resize(image, (int(w * scale), int(h * scale)))
        return scaled

    def match_template(image, template):
        res = cv2.matchTemplate(image, template, cv2.TM_CCOEFF)
        _, max_val, _, _ = cv2.minMaxLoc(res)
        return max_val

    def process_scale_rotation(image, template, scale, angle):
        scaled_template = scale_image(template, scale)
        rotated_template = rotate_image(scaled_template, angle)
        if rotated_template.shape[0] > image.shape[0] or rotated_template.shape[1] > image.shape[1]:
            return -np.inf, scale, angle
        max_val = match_template(image, rotated_template)
        return max_val, scale, angle

    best_scale = 1.0
    best_rotation = 0
    best_val = -np.inf

    scales = np.arange(scale_range[0], scale_range[1], scale_step)
    rotations = np.arange(rotation_range[0], rotation_range[1] + rotation_step, rotation_step)
    total_iterations = len(scales) * len(rotations)

    with ThreadPoolExecutor() as executor:
        futures = []
        with tqdm(total=total_iterations, desc="Trying different orientations", unit=" matched templates") as pbar:
            for scale in scales:
                for angle in rotations:
                    futures.append(executor.submit(process_scale_rotation, image, template, scale, angle))
            
            for future in as_completed(futures):
                max_val, scale, angle = future.result()
                pbar.update(1)
                if max_val > best_val:
                    best_val = max_val
                    best_scale = scale
                    best_rotation = angle

    return best_rotation, best_scale

def rotate_scale_template(template, angle, scale):
    """
    Rotate and scale a template image.

    Parameters:
    - template: numpy.ndarray
        The template image to be rotated and scaled.
    - angle: float
        The rotation angle in degrees.
    - scale: float
        The scale factor.

    Returns:
    - template_rotated: numpy.ndarray
        The rotated and scaled template image.
    """
    padding = int(template.shape[1]*0.023), int(template.shape[1]*0.023) # this padding is needed to not cut off the template after rotating it
    template_rotated = np.pad(template, padding, 'constant', constant_values=(0, 0))
    template_rotated = rotate(template_rotated, angle)
    template_rotated = rescale(template_rotated, scale)
    template_rotated = ((template_rotated - template_rotated.min()) * (255 / (template_rotated.max() - template_rotated.min()))).astype(np.uint8)
    return template_rotated, padding

def find_translation(image, template_rotated):
    """
    Finds the translation of the rotated and scaled template image within the camera image.

    Parameters:
    - image: numpy.ndarray
        The larger image to search for the template.
    - template_rotated: numpy.ndarray
        The rotated and scaled template image.

    Returns:
    - top_left: tuple
        The top-left corner of the template in the image.
    - bottom_right: tuple
        The bottom-right corner of the template in the image.
    """
    # rotation, scale, M = find_rotation_scale_feat(img1, tmp1)
    if template_rotated.shape[0] > image.shape[0] or template_rotated.shape[1] > image.shape[1]:
        raise ValueError(f"The template image is larger than the source image: {template_rotated.shape} > {image.shape}")
    result = cv2.matchTemplate(image, template_rotated, cv2.TM_CCOEFF_NORMED)
    top_left = cv2.minMaxLoc(result)[3]
    bottom_right = (top_left[0] + template_rotated.shape[1], top_left[1] + template_rotated.shape[0])
    return top_left, bottom_right

# this function just exists for a version of aff_trans_point
def interpolate_point(point1, point2, ratio):
    """
    Calculate a new point that is a certain ratio along the line formed by point1 and point2.

    Parameters:
    - point1: tuple of two floats
        The first point that forms the line.
    - point2: tuple of two floats
        The second point that forms the line.
    - ratio: float
        The ratio along the line for the new point. Should be between 0 and 1.

    Returns:
    - new_point: tuple of two floats
        The calculated x and y positions.
    """
    new_x = (1 - ratio) * point1[0] + ratio * point2[0]
    new_y = (1 - ratio) * point1[1] + ratio * point2[1]
    return (new_x, new_y)

# this function is in the middle of being redone. you can find the old version at the very bottom of this file
def aff_trans_point(template_rot, point, angle, translation, padding, type):
    """
    Takes a point in relative coordinates on template and transforms it to the new absolute coordinates in the image.
    
    Parameters:
    - template_rot: numpy.ndarray
        The rotated and scaled template image.
    - point: tuple
        The point to be transformed in relative coordinates of template. So for example (0.5, 0.5) would be the center of the template.
    - angle: float
        The rotation angle in degrees.
    - translation: tuple
        The upper left corner of the template in the image.
    - padding: tuple
        The padding added to template_rot.
    """
    template_size = (template_rot.shape[1] - 2*padding[0], template_rot.shape[0] - 2*padding[1])
    template_center = (template_size[0]//2, template_size[1]//2)

    # Create the rotated rectangle
    center_img = tuple((np.array(template_center) + np.array(translation) + np.array(padding)).astype(int).tolist())
    rotated_rect = cv2.RotatedRect(center_img, template_size, -angle)

    # Get the corner points of the rectangle and draw it on the image
    box = cv2.boxPoints(rotated_rect)
    box = np.intp(box)  # ensure the coordinates are integer

    if type == 'Input':
        new_point = interpolate_point(box[0], box[1], 1-point[1])
    
    elif type == 'Output':
        new_point = interpolate_point(box[2], box[3], point[1])

    transformed_point = np.array(new_point)

    # Calculate the error in the transformation
    x_err = 0.005 * template_size[0]
    y_err = 0.005 * template_size[1]    
    return transformed_point, (x_err, y_err)

def find_fibers(image, tmpl_in, tmpl_out):
    """
    Finds the positions of fibers in an image using template matching.

    Parameters:
    - image: numpy.ndarray
        The input image.
    - tmpl_in: numpy.ndarray
        The template image for the fiber input.
    - tmpl_out: numpy.ndarray
        The template image for the fiber output.

    Returns:
    - tip_in: tuple
        The tip position of the fiber input.
    - tip_out: tuple
        The tip position of the fiber output.
    """
    result_in = cv2.matchTemplate(image, tmpl_in, cv2.TM_CCOEFF_NORMED)
    result_out = cv2.matchTemplate(image, tmpl_out, cv2.TM_CCOEFF_NORMED)

    top_left_in = cv2.minMaxLoc(result_in)[3]
    top_left_out = cv2.minMaxLoc(result_out)[3]
    tip_in = np.array(top_left_in) + np.array([41, 15])     # The offset is needed because the top left of the template is not exactly
    tip_out = np.array(top_left_out) + np.array([11, 17])   # the fiber tip in the template image (new template -> this need to be adjusted)
    return tip_in, tip_out

def select_points_on_image(image, key):
    """
    Displays an image using matplotlib and allows the user to select six points on the image.
    The six points are:
    1. The input fiber tip
    2. The chip input
    3. The output fiber tip
    4. The chip output
    5. A corner
    6. A neighboring corner

    Parameters:
        image (numpy.ndarray): The image to display.
        key (str): The key to use in the labels.

    Returns:
        tuple: A tuple containing the following points:
            1. The input fiber tip
            2. The chip input
            3. The output fiber tip
            4. The chip output
            5. The distance between the two neighboring corners in pixels
    """    
    # Initialize an empty list to store the selected points
    points = []
    labels = [
        "Please select the input fiber tip",
        f"Please select the chip input {key}",
        "Please select the output fiber tip",
        f"Please select the chip output {key}",
        "Select a corner",
        "Select a neighboring corner"
    ]
    
    # Create a Matplotlib figure and axis
    fig, ax = plt.subplots()
    ax.imshow(image, cmap='gray')  # Assuming the image is grayscale; change 'cmap' if needed
    ax.axis('off')  # Turn off the axis labels

    # Maximize the window
    manager = plt.get_current_fig_manager()
    try:
        manager.window.showMaximized()
    except AttributeError:
        manager.window.state('zoomed')

    # Temporary storage for the current click position
    current_click = []

    # Function to handle mouse clicks
    def on_click(event):
        if event.button == 1 and event.inaxes:  # Left mouse button and inside the axis
            x, y = int(event.xdata), int(event.ydata)
            current_click.clear()
            current_click.append((x, y))
            ax.clear()
            ax.imshow(image, cmap='gray')
            ax.axis('off')  # Keep axis labels off
            for point in points:
                ax.plot(point[0], point[1], 'rx')
            ax.plot(x, y, 'rx')  # Plot a red 'X' on the selected point
            plt.draw()

    # Function to handle key presses
    def on_key(event):
        if event.key == 'n' and current_click:
            points.append(current_click[0])
            current_click.clear()
            if len(points) < 6:
                fig.suptitle(labels[len(points)] + " | Press 'n' to confirm, 'r' to try again")
            if len(points) == 6:
                plt.close(fig)
            plt.draw()
        elif event.key == 'r':
            points.clear()
            current_click.clear()
            ax.clear()
            ax.imshow(image, cmap='gray')
            ax.axis('off')  # Keep axis labels off
            fig.suptitle(labels[0] + " | Press 'n' to confirm, 'r' to try again")
            plt.draw()

    # Set the initial title
    fig.suptitle(labels[0] + " | Press 'n' to confirm, 'r' to try again")
    plt.draw()

    # Connect the event handlers
    cid_click = fig.canvas.mpl_connect('button_press_event', on_click)
    cid_key = fig.canvas.mpl_connect('key_press_event', on_key)

    # Display the image and wait for user interaction
    plt.show()

    # Disconnect the event handlers
    fig.canvas.mpl_disconnect(cid_click)
    fig.canvas.mpl_disconnect(cid_key)

    # Ensure we have exactly six points selected
    if len(points) != 6:
        raise ValueError("Six points were not selected.")

    fiber_input = points[0]
    chip_input = points[1]
    fiber_output = points[2]
    chip_output = points[3]
    corner1 = points[4]
    corner2 = points[5]

    # Calculate the distance between the two neighboring corners
    distance = np.sqrt((corner2[0] - corner1[0])**2 + (corner2[1] - corner1[1])**2)

    return [distance, fiber_input, fiber_output, chip_input, chip_output]

def match_positions(pixels_per_µm, tip_in, tip_out, new_inp, new_otp, safety_margin=69):
    """
    Matches the positions of the fibers and the input/output points on the chip.

    Parameters:
    - pixels_per_µm: float
        The number of pixels per micrometer.
    - tip_in: tuple
        The tip position of the input fiber.
    - tip_out: tuple
        The tip position of the output fiber.
    - new_inp: tuple
        The input point on the chip.
    - new_otp: tuple
        The output point on the chip.
    - safety_margin: int, optional
        The safety margin in micrometers. Default is 10.
    """
    print("\nMoving the fibers the following distances:")
    # match y positions
    y_diff_in  = (new_inp[1] - tip_in[1])  / pixels_per_µm
    y_diff_out = (new_otp[1] - tip_out[1]) / pixels_per_µm

    # match x positions
    x_diff_in  = (new_inp[0] - tip_in[0])  / pixels_per_µm
    x_diff_out = (new_otp[0] - tip_out[0]) / pixels_per_µm

    print(f'Using safety margin: {safety_margin} µm')
    # print(f'x_diff_in/out without safety margin ({safety_margin}): {x_diff_in:.1f}, {x_diff_out:.1f}')
    if x_diff_in < 0:
        x_diff_in += safety_margin
    else:
        x_diff_in -= safety_margin
    if x_diff_out < 0:
        x_diff_out += safety_margin
    else:
        x_diff_out -= safety_margin
    # print(f'x_diff_in/out with safety margin: {x_diff_in:.1f}, {x_diff_out:.1f}')
    
    print(f'Input fiber: {y_diff_in:.2f} µm in y, {x_diff_in:.2f} µm in x')
    print(f'Output fiber: {y_diff_out:.2f} µm in y, {x_diff_out:.2f} µm in x')
    return int(x_diff_in), int(y_diff_in), int(x_diff_out), int(y_diff_out)

def find_distances(chip_type, key, safety_margin):
    """
    Automatically finds the distances between the fibers and the input/output points on the chip.

    ### WARNING: x, y here is in the image coordinate system, not the chip coordinate system

    Parameters:
    - chip_type: int
        The type of chip template to use.
    - key: str
        The key for the relative coordinates of the chip template.
    - safety_margin: float
        Distance in micrometer that the x axis will keep to the chip.

    Returns:
    - x_diff_in: float
        The x distance between the fibers and the input point.
    - y_diff_in: float
        The y distance between the fibers and the input point.
    - x_diff_out: float
        The x distance between the fibers and the output point.
    - y_diff_out: float
        The y distance between the fibers and the output point.
    """

    def get_method():
        method = None

        def set_method(selected_method):
            nonlocal method
            method = selected_method
            root.destroy()

        root = tk.Tk()
        root.title("Select Method")

        label = tk.Label(root, text="Select method to use for rough matching:")
        label.pack(pady=10)

        button_fmt = tk.Button(root, text="Fourier-Mellin Transform", command=lambda: set_method('fmt'))
        button_fmt.pack(side=tk.LEFT, padx=20)

        button_bf = tk.Button(root, text="Brute Force", command=lambda: set_method('bf'))
        button_bf.pack(side=tk.LEFT, padx=20)

        button_manual = tk.Button(root, text="Manual", command=lambda: set_method('manual'))
        button_manual.pack(side=tk.LEFT, padx=20)

        root.mainloop()
        return method
    
    rs_method = get_method()

    if rs_method is None:
        raise ValueError("No method selected")

    image = read_img()          # read image from webcam
    if rs_method == 'manual':
        print('Using manual method...')
        result = select_points_on_image(image, key)
        print(result)
        result[0] /= 4960    # convert found distance (in pixels) to pixels/µm by dividing by the chip's actual edge length in µm
        return match_positions(*result, safety_margin=safety_margin)

    # print("Current working directory:", os.getcwd())
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    # print("New working directory:", os.getcwd())

    file_path_rloc = os.path.join('input_loc', f'coordinates_chip_{chip_type}.json')
    print("Looking for location json file:", os.path.abspath(file_path_rloc))

    with open(file_path_rloc, 'r') as f:
        rel_loc = json.load(f)['relative_coordinates']

    template = cv2.imread(os.path.join('templates', f'chip_{chip_type}.png'), cv2.IMREAD_GRAYSCALE)
    fib_inp_tmp = cv2.imread(os.path.join('templates', 'fibers', 'fiberhead_input.jpg'), cv2.IMREAD_GRAYSCALE)
    fib_otp_tmp = cv2.imread(os.path.join('templates', 'fibers', 'fiberhead_output.jpg'), cv2.IMREAD_GRAYSCALE)

    # image = cv2.imread('captured_image.jpg', cv2.IMREAD_COLOR)    # only for testing purposes
    img1 = process_image(image)
    tmp1, tmp1_pad = process_template(template, img1, rel_size=1)

    if rs_method == 'fmt':
        print('Using Fourier-Mellin Transform method...')
        rotation, scale = find_rotation_scale(img1, tmp1_pad)
        print(f'Found Rotation: {rotation:.2f}°, Scale: {scale:.2f}')
    elif rs_method == 'bf':
        print('Using Brute-Force method...')
        rotation, scale = find_rotation_scale_bf(img1, tmp1_pad)
        print(f'Found Rotation: {rotation:.2f}°, Scale: {scale:.2f}')

    tmp1_rot, padding = rotate_scale_template(tmp1, rotation, scale)

    top_left, _ = find_translation(img1, tmp1_rot)

    inp, otp = rel_loc[key]
    new_inp, new_inp_err = aff_trans_point(tmp1_rot, inp, rotation, top_left, padding, 'Input')
    new_otp, new_otp_err = aff_trans_point(tmp1_rot, otp, rotation, top_left, padding, 'Output')

    # locate fibers in the image
    fib_inp, fib_otp = find_fibers(img1, fib_inp_tmp, fib_otp_tmp)

    # Calculate the size of the template without padding
    template_size = (tmp1_rot.shape[1] - 2*padding[0], tmp1_rot.shape[0] - 2*padding[1])
    template_center = (template_size[0]//2, template_size[1]//2)

    # Create the rotated rectangle
    center_img = tuple((np.array(template_center) + np.array(top_left) + np.array(padding)).astype(int).tolist())
    rotated_rect = cv2.RotatedRect(center_img, template_size, -rotation)

    # Get the corner points of the rectangle and draw it on the image
    box = cv2.boxPoints(rotated_rect)
    box = np.intp(box)  # ensure the coordinates are integer
    image_copy = image.copy()
    # Now draw the rectangle on the copy
    image_rgb = cv2.drawContours(image_copy, [box], 0, (0, 255, 255), 2)

    fig, ax = plt.subplots(1, 1, figsize=(10, 10))
    ax.imshow(image_rgb)
    ax.scatter(new_inp[0], new_inp[1], c='r', s=100, marker='x', label='Input')
    ax.scatter(new_otp[0], new_otp[1], c='b', s=100, marker='x', label='Output')
    ax.errorbar(new_inp[0], new_inp[1], xerr=new_inp_err[0], yerr=new_inp_err[1], ls='None', linewidth=2, c='r')
    ax.errorbar(new_otp[0], new_otp[1], xerr=new_otp_err[0], yerr=new_otp_err[1], ls='None', linewidth=2, c='b')
    ax.scatter(fib_inp[0], fib_inp[1], c='r', s=60, marker='D', label='Fiber Input')
    ax.scatter(fib_otp[0], fib_otp[1], c='b', s=60, marker='D', label='Fiber Output')

    root = tk.Tk()
    root.withdraw()  # hide the main window

    # Show the plot and pause for a while to let the user see it
    plt.show(block=False)
    plt.pause(0.1)

    user_response = messagebox.askyesno("Confirmation", "Is the chip marked correctly?\n\nYes: Proceed with fiber movement\nNo: Rerun with another method")
    root.destroy()  # destroy the main window
    plt.close(fig)  # close the figure after getting user response

    if not user_response:
        # show original and processed image and template
        print('Check for right image pre-processing and template selection!')
        fig, ax = plt.subplots(1, 3, figsize=(20, 10))
        ax[0].imshow(image)
        ax[0].set_title('Original Image')
        ax[1].imshow(img1, cmap='gray')
        ax[1].set_title('Processed Image')
        ax[2].imshow(tmp1_pad, cmap='gray')
        ax[2].set_title('Processed Template')
        plt.show()

        # Allow user to decide what to do next by running the function again
        return find_distances(chip_type, key, safety_margin)

    # find the distances between the input and output fibers
    pixels_per_µm = template_size[1] / 4960
    return match_positions(pixels_per_µm, fib_inp, fib_otp, new_inp, new_otp, safety_margin=safety_margin)