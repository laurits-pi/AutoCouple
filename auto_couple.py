from all_imports_and_inits import *
from im_rec.rough_match import find_distances
import fine_match_combined_seq

chip_number = 'Q1_7'      # needs to exist in im_rec\templates\chip_{chip_number}.png and im_rec\input_loc\coordinates_chip_{chip_number}.json
waveguide_name = '4.01'   # needs to exist within the json file

z_in, x_in, z_out, x_out = find_distances(chip_number, waveguide_name, 90)


perform_continuous_movement(1, 'z', -200)    # -200µm to not run into a rotated chip while moving sidewards
perform_continuous_movement(2, 'z', -200)
for i, dist in enumerate([x_in, z_in, x_out, z_out]):
    if i == 0:
        perform_continuous_movement(1, 'x', dist)
    elif i == 1:
        perform_continuous_movement(1, 'z', dist+200)
    elif i == 2:
        perform_continuous_movement(2, 'x', dist)
    elif i == 3:
        perform_continuous_movement(2, 'z', -dist+200)

fine_match_combined_seq.fine_match_main()