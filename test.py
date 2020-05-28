import sys
import os
import numpy as np

if os.name == 'nt':
    sys.path.insert(0, '.\\bin\\Release')
else:
    sys.path.insert(0, '.\\bin')
    
import py_array

print('========== Python array storage ==========')

# Testing 2d array
array_2d = np.array([
    [1, 2, 3, 4, 5],
    [6, 7, 8, 9, 10]
])

print(f'2d array sum: { py_array.array_sum(array_2d) }')

# Testing 2d array
array_3d = np.array([
    [
        [1, 1, 1],
        [1, 1, 1],
        [1, 1, 1]
    ],
    [
        [1, 1, 1],
        [1, 1, 1],
        [1, 1, 1]
    ],
    [
        [1, 1, 1],
        [1, 1, 1],
        [1, 1, 1]
    ]
])

print(f'3d array sum: { py_array.array_sum(array_3d) }')

