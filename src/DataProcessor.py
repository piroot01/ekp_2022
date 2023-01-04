#==================================================================
#  
#  File: DataProcessor.py
#  Description: Program for generating various plots.
#  Author: Tomas Machacek
#  Date: 2 Jan 2023
#  Notes: It uses Madgwicks fusion algorithm (part of imufusion).
#
#==================================================================

# system headers
import matplotlib.pyplot as plt
import numpy as np
import imufusion
from dataclasses import dataclass
from scipy.interpolate import interp1d

# File where ouput data will be stored.
outputFile = "data/"

# Various settings
sampleRate = 200

# Gain of the filter.
beta = 6
accelerationRejection = 30
magneticRejection = 0
n = 20

# Very important parameter specifying when the imu is moving.
accelerationTreshold = 0.6
margin = int(0.1 * sampleRate)

# Generate 2D array from csv.
data = np.genfromtxt(outputFile + "output.csv", delimiter = ",")

# Split the data into subarrays.
timeStamp = (data[:, 0] - data[0, 0]) / 1000000
accelerometer = data[:, 1:4] * 2.0 / 32767.0 
gyroscope = data[:, 4:7] * 250.0 / 32767.0

# Plot raw data from imu.
rawDataFig, rawDataAxes = plt.subplots(nrows = 2, sharex = True)

rawDataFig.suptitle("Raw data from IMU")

rawDataAxes[0].plot(timeStamp, gyroscope[:, 0], label = "gx", lw = 0.8)
rawDataAxes[0].plot(timeStamp, gyroscope[:, 1], label = "gy", lw = 0.8)
rawDataAxes[0].plot(timeStamp, gyroscope[:, 2], label = "gz", lw = 0.8)
rawDataAxes[0].set_ylabel("[deg/s]")
rawDataAxes[0].grid()
rawDataAxes[0].legend(loc = 'upper right')

rawDataAxes[1].plot(timeStamp, accelerometer[:, 0], label = "ax", lw = 0.8)
rawDataAxes[1].plot(timeStamp, accelerometer[:, 1], label = "ay", lw = 0.8)
rawDataAxes[1].plot(timeStamp, accelerometer[:, 2], label = "az", lw = 0.8)
rawDataAxes[1].set_ylabel("[m/s\u00b2]")
rawDataAxes[1].set_xlabel("[s]")
rawDataAxes[1].grid()
rawDataAxes[1].legend(loc = 'upper right')

rawDataFig.savefig(outputFile + "raw_data.png", dpi = 300)

# Instanciate imufusion.
offset = imufusion.Offset(sampleRate)
ahrs = imufusion.Ahrs()
ahrs.settings = imufusion.Settings(beta, accelerationRejection, magneticRejection, n * sampleRate)

# Create arrayy of time deltas between entries.
timeDelta = np.diff(timeStamp, prepend = timeStamp[0])

# Create two arrays for euler angles and acceleration. 
eulerAngles = np.empty((len(timeStamp), 3))
acceleration = np.empty((len(timeStamp), 3))

# Fill the arrays.
for index in range(len(timeStamp)):
    gyroscope[index] = offset.update(gyroscope[index])
    ahrs.update_no_magnetometer(gyroscope[index], accelerometer[index], timeDelta[index])
    eulerAngles[index] = ahrs.quaternion.to_euler()
    acceleration[index] = 9.81 * ahrs.earth_acceleration

# Plot euler angles.
eulerAnglesFig, eulerAnglesAxes = plt.subplots()
eulerAnglesFig.suptitle("Euler angles")

eulerAnglesAxes.plot(timeStamp, eulerAngles[:, 0], label = "roll", lw = 0.8)
eulerAnglesAxes.plot(timeStamp, eulerAngles[:, 1], label = "pitch", lw = 0.8)
eulerAnglesAxes.plot(timeStamp, eulerAngles[:, 2], label = "yaw", lw = 0.8)
eulerAnglesAxes.set_ylabel("[deg]")
eulerAnglesAxes.set_xlabel("[s]")
eulerAnglesAxes.grid()
eulerAnglesAxes.legend(loc = 'upper right')

eulerAnglesFig.savefig(outputFile + "euler_angles.png", dpi = 300)

# Plot acceleration.
accelerationFig, accelerationAxes = plt.subplots()
accelerationFig.suptitle("Acceleration")

accelerationAxes.plot(timeStamp, acceleration[:, 0], label = "ax", lw = 0.8)
accelerationAxes.plot(timeStamp, acceleration[:, 1], label = "ay", lw = 0.8)
accelerationAxes.plot(timeStamp, acceleration[:, 2], label = "az", lw = 0.8)
accelerationAxes.set_ylabel("[m/s\u00b2]")
accelerationAxes.set_xlabel("[s]")
accelerationAxes.grid()
accelerationAxes.legend(loc = 'upper right')

accelerationFig.savefig(outputFile + "acceleration.png", dpi = 300)

# Determine when the imu is moving
isMoving = np.empty(len(timeStamp))

for index in range(len(timeStamp)):
    if np.sqrt(acceleration[index].dot(acceleration[index])) > accelerationTreshold:
        isMoving[index] = True
    else:
        isMoving[index] = False

for index in range(len(timeStamp) - margin):
    isMoving[index] = any(isMoving[index:(index + margin)])

for index in range(len(timeStamp) - 1, margin, -1):
    isMoving[index] = any(isMoving[(index - margin):index])

# Calculate velocity.
velocity = np.zeros((len(timeStamp), 3))

for index in range(len(timeStamp)):
    if isMoving[index]:
        velocity[index] = velocity[index - 1] + timeDelta[index] * acceleration[index]

# Find start ans stop indices of each moving period.
isMovingDiff = np.diff(isMoving, append = isMoving[-1])

@dataclass
class IsMovingPeriod:
    startIndex: int = -1
    stopIndex: int = -1

isMovingPeriods = []
isMovingPeriod = IsMovingPeriod()

for index in range(len(timeStamp)):
    if isMovingPeriod.startIndex == -1:
        if isMovingDiff[index] == 1:
            isMovingPeriod.startIndex = index
    elif isMovingPeriod.stopIndex == -1:
        if isMovingDiff[index] == -1:
            isMovingPeriod.stopIndex = index
            isMovingPeriods.append(isMovingPeriod)
            isMovingPeriod = IsMovingPeriod()

# Remove integral drift from velocity.
velocityDrift = np.zeros((len(timeStamp), 3))

for isMovingPeriod in isMovingPeriods:
    startIndex = isMovingPeriod.startIndex
    stopIndex = isMovingPeriod.stopIndex

    t = [timeStamp[startIndex], timeStamp[stopIndex]]
    x = [velocity[startIndex][0], velocity[stopIndex][0]]
    y = [velocity[startIndex][1], velocity[stopIndex][1]]
    z = [velocity[startIndex][2], velocity[stopIndex][2]]

    tNew = timeStamp[startIndex:(stopIndex + 1)]

    velocityDrift[startIndex:(stopIndex + 1), 0] = interp1d(t, x)(tNew)
    velocityDrift[startIndex:(stopIndex + 1), 1] = interp1d(t, y)(tNew)
    velocityDrift[startIndex:(stopIndex + 1), 2] = interp1d(t, z)(tNew)

velocity = velocity - velocityDrift

# Plot velocity.
velocityFig, velocityAxes = plt.subplots()
velocityFig.suptitle("Velocity")

velocityAxes.plot(timeStamp, velocity[:, 0], label = "vx", lw = 0.8)
velocityAxes.plot(timeStamp, velocity[:, 1], label = "vy", lw = 0.8)
velocityAxes.plot(timeStamp, velocity[:, 2], label = "vz", lw = 0.8)
velocityAxes.set_ylabel("[m/s]")
velocityAxes.set_xlabel("[s]")
velocityAxes.grid()
velocityAxes.legend(loc = 'upper right')

velocityFig.savefig(outputFile + "velocity.png", dpi = 300)

# Calculate position.
position = np.zeros((len(timeStamp), 3))

for index in range(len(timeStamp)):
    position[index] = position[index - 1] + timeDelta[index] * velocity[index]


# Plot position.
positionFig, positionAxes = plt.subplots()
positionFig.suptitle("Position")

positionAxes.plot(timeStamp, position[:, 0], label = "x", lw = 0.8)
positionAxes.plot(timeStamp, position[:, 1], label = "y", lw = 0.8)
positionAxes.plot(timeStamp, position[:, 2], label = "z", lw = 0.8)
positionAxes.set_xlabel("[s]")
positionAxes.set_ylabel("[m]")
positionAxes.grid()
positionAxes.legend(loc = 'upper right')

positionFig.savefig(outputFile + "position.png", dpi = 300)

# Plot posifion in 3D.
positionFig3D, positionAxes3D = plt.subplots(subplot_kw={"projection": "3d"})
positionFig3D.suptitle("Position in 3D")

positionAxes3D.scatter(position[:, 0], position[:, 1], position[:, 2], s = 1)
positionAxes3D.set_box_aspect((np.ptp(position[:, 0]), np.ptp(position[:, 1]), np.ptp(position[:, 2])))
positionAxes3D.set_proj_type('persp') 
positionAxes3D.set_xlabel("[m]")
positionAxes3D.set_ylabel("[m]")
positionAxes3D.set_zlabel("[m]")

positionFig3D.savefig(outputFile + "position_3D.png", dpi = 300)
