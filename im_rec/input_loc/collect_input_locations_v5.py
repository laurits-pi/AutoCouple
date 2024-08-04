import os
import json
import matplotlib.pyplot as plt

# Ask user for path to image, display default: im_rec/templates
print("Enter the path to the image or press Enter to use the default path: im_rec/templates")
path = input("") or os.path.join('im_rec', 'templates')

# Ask user for name of chip, display default: chip_0.png
print("Enter the name of the chip or press Enter to use the default name: chip_0.png")
name = input("") or 'chip_0.png'

# Load the image
image_path = os.path.join(path, name)
image = plt.imread(image_path)

# Create a dictionary to store the coordinates
coordinates = {}

# Collect keys from the user
keys = input("Enter the connection names (separated by comma for multiple): ").split(',')
keys = [key.strip() for key in keys]

# Iterate over the keys and store them in the dictionary
for key in keys:
    coordinates[key] = []

# Create a figure and axes in Matplotlib
fig, ax = plt.subplots()

# Display the image
ax.imshow(image, cmap='gray')

# Define global variables for the callback ids
cid_click = None
cid_key = None

# Define dictionaries to store 'Input' and 'Output' coordinates
input_coordinates = {key: [] for key in coordinates.keys()}
output_coordinates = {key: [] for key in coordinates.keys()}

# Define a global variable for the warning text
warning_text = None
marker = None
def onclick(event):
    global cid_click, warning_text, marker
    if event.inaxes is None:  # Check if the click was outside the axes
        # Remove the previous warning text if it exists
        if warning_text is not None:
            warning_text.remove()
        warning_text = ax.text(0.5, 0.5, 'Please click inside the axis. Try again.', 
                horizontalalignment='center', verticalalignment='center', 
                transform=ax.transAxes, bbox=dict(facecolor='red', alpha=0.5))
        fig.canvas.draw()  # Redraw the figure to show the text
        return
    else:  # Click was inside the axes
        # Check if the selected location contains a negative value or is outside the image dimensions
        if event.xdata < 0 or event.ydata < 0 or event.xdata >= image.shape[1] or event.ydata >= image.shape[0]:
            if warning_text is not None:
                warning_text.remove()
            warning_text = ax.text(0.5, 0.5, 'The selected location contains a value outside the chip. Try again.', 
                    horizontalalignment='center', verticalalignment='center', 
                    transform=ax.transAxes, bbox=dict(facecolor='red', alpha=0.5))
            fig.canvas.draw()  # Redraw the figure to show the text
            return

        # Check if the selected location is at a black pixel
        if image[int(event.ydata), int(event.xdata)] == 0:
            if warning_text is not None:
                warning_text.remove()
            warning_text = ax.text(0.5, 0.5, 'The selected location is a black pixel. Try again.', 
                    horizontalalignment='center', verticalalignment='center', 
                    transform=ax.transAxes, bbox=dict(facecolor='red', alpha=0.5))
            fig.canvas.draw()  # Redraw the figure to show the text
            return

    # Remove the warning text if it got resolved
    if warning_text is not None:
        warning_text.remove()
        warning_text = None  # Reset the reference to the warning text
        fig.canvas.draw()  # Redraw the figure to remove the text

    if event.button == 1:  # Left mouse button
        # Append the coordinates to the list for the current key
        if counter < original_key_count:
            input_coordinates[param[0]].append((int(event.xdata), int(event.ydata)))
        else:
            output_coordinates[param[0]].append((int(event.xdata), int(event.ydata)))
        # Update the location of the marker
        if marker is not None:
            marker.remove()
        marker = ax.scatter(event.xdata, event.ydata, color='green', s=0.005*fig.dpi**2, marker='x')
        fig.canvas.draw()  # Redraw the figure to show the marker

# Define a callback function for key press events
def onkey(event):
    global cid_click, cid_key, counter, warning_text
    # Check if the warning is displayed
    if warning_text is not None:
        return
    if event.key == 'n':
        counter += 1
        # Disconnect the callback functions from the figure
        if cid_click is not None:
            fig.canvas.mpl_disconnect(cid_click)
        if cid_key is not None:
            fig.canvas.mpl_disconnect(cid_key)
        # Move on to the next key
        if keys:
            param[0] = keys.pop(0)
            if counter < original_key_count:
                ax.set_title(f"Select Input {param[0]}, then press 'n' to continue")
            else:
                ax.set_title(f"Select Output {param[0]}, then press 'n' to continue")
            fig.canvas.draw()
            # Connect the callback functions to the figure
            cid_click = fig.canvas.mpl_connect('button_press_event', onclick)
            cid_key = fig.canvas.mpl_connect('key_press_event', onkey)
        else:
            # Combine 'Input' and 'Output' coordinates into one dictionary
            for key in coordinates.keys():
                input_coord = input_coordinates[key][0] if input_coordinates[key] else None
                output_coord = output_coordinates[key][0] if output_coordinates[key] else None
                coordinates[key] = [input_coord, output_coord]
            plt.close()

# Initialize the counter
counter = 0

# Get a list of keys
keys = list(coordinates.keys())
original_key_count = len(keys)
# Duplicate the keys list to collect 'Input' and 'Output' points
keys = keys + keys
# Initialize the first key
param = [keys.pop(0)]
ax.set_title(f"Select Input {param[0]}, then press 'n' to continue")

# Connect the callback functions to the figure
cid_click = fig.canvas.mpl_connect('button_press_event', onclick)
cid_key = fig.canvas.mpl_connect('key_press_event', onkey)

# Wait for the user to click on the input and output
plt.show()

# Set the x coordinate for the input to 0 and the output to the width of the image
for key in coordinates.keys():
    if coordinates[key][0] is not None:
        coordinates[key][0] = (0, coordinates[key][0][1])
    if coordinates[key][1] is not None:
        coordinates[key][1] = (image.shape[1] - 1, coordinates[key][1][1])

# Define the radius within which to search for white pixels
radius = image.shape[0] // 1000
# For each key in the coordinates dictionary
for key in coordinates.keys():
    input_coord = coordinates[key][0]
    output_coord = coordinates[key][1]
    
    # For each coordinate (input and output)
    for coord in [input_coord, output_coord]:
        if coord is not None:
            x, y = coord
            
            # Initialize the y-coordinate of the white pixel furthest in the middle
            middle_y = y
            
            # Scan the pixels in the y-direction within the radius
            for i in range(y - radius, y + radius + 1):
                # Ensure the pixel is within the image boundaries
                if i > 0 and i < image.shape[0] - 1:
                    # If the pixel is white and the pixels above and below are black
                    if image[i, x] == 255 and image[i - 1, x] == 0 and image[i + 1, x] == 0:
                        # If the current pixel's y-coordinate is closer to the middle of the black pixels
                        if abs((i - 1) / 2 - i) < abs((i - 1) / 2 - middle_y):
                            # Update the y-coordinate
                            middle_y = i
            
            # Update the coordinate in the coordinates dictionary
            if coord == input_coord:
                coordinates[key][0] = (x, middle_y)
            else:
                coordinates[key][1] = (x, middle_y)

# Calculate relative coordinates using the dimensions of the image and add a second dictionary to store them
relative_coordinates = {}
for key in coordinates.keys():
    input_coord = coordinates[key][0]
    output_coord = coordinates[key][1]
    if input_coord is not None and output_coord is not None:
        relative_input = (input_coord[0] / image.shape[1], input_coord[1] / image.shape[0])
        relative_output = (output_coord[0] / image.shape[1], output_coord[1] / image.shape[0])
        relative_coordinates[key] = [relative_input, relative_output]
    else:
        relative_coordinates[key] = [None, None]

# ask user for the path to save the coordinates, default: coordinates_chip_0.json
name = name.replace('.png', '').replace('.PNG', '').replace('.jpg', '').replace('.JPG', '').replace('.jpeg', '').replace('.JPEG', '')
print("Enter the path to save the coordinates or press Enter to use the default path: ./coordinates_" + name + ".json")
path = input("") or os.path.join(os.getcwd(), 'coordinates_' + name + '.json')

# Save both dictionaries to a JSON file
with open(path, 'w') as f:
    json.dump({'absolute_coordinates': coordinates, 'relative_coordinates': relative_coordinates}, f)