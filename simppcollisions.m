% Script for simulating 3D animation of proton-proton collisions at the ALICE experiment with mildly curved particle tracks

% 
clear; close all; clc;

% Number of collision events to simulate
numEvents = 500;

% Initialize figure
fig = figure('Name', 'ALICE Experiment Simulation', 'NumberTitle', 'off');
hold on;
xlabel('x [m]');
ylabel('y [m]');
zlabel('z [m]');
title('3D Animation of Proton-Proton Collisions');
grid on;
axis equal;
view(3);

% Define detector dimensions (simplified)
ITS_radius = 0.5; % meters
TPC_outer_radius = 2.8; % meters
TOF_radius = 3.7; % meters
EMCal_radius = 1.5; % meters

% Draw simplified detectors
drawCylinder(0, 0, -6, 0, 0, 6, ITS_radius, 'r', 'none', 0.3);
drawCylinder(0, 0, -2.8, 0, 0, 2.8, TPC_outer_radius, 'g', 'none', 0.3);
drawCylinder(0, 0, -13, 0, 0, 13, TOF_radius, 'b', 'none', 0.3);
drawCylinder(0, 0, -13, 0, 0, 13, EMCal_radius, 'y', 'none', 0.3);


% Setup video writer
videoFileName = 'PP_Collision_Simulation06.avi';
v = VideoWriter(videoFileName);
v.FrameRate = 6; % Frames per second

% Open video file with error checking
try
    open(v);
catch ME
    error('Failed to open video file: %s', ME.message);
end

% Animation loop
for i = 1:numEvents
    % Starting point of the track
    x = 0;
    y = 0;
    z = 0;
    
    % Initial direction (random direction)
    theta = rand() * 2 * pi;
    phi = rand() * pi - pi / 2;
    dx = cos(phi) * cos(theta);
    dy = cos(phi) * sin(theta);
    dz = sin(phi);
    
    % Simulate track points
    track_length = 2; % meters (adjust as needed)
    numPoints = 100; % number of points along the track
    step = track_length / numPoints;
    
    for j = 1:numPoints
        % Update position
        x = x + step * dx;
        y = y + step * dy;
        z = z + step * dz;
        
        % Add mild curvature (adjust as needed)
        dx = dx + randn() * 0.01;
        dy = dy + randn() * 0.01;
        dz = dz + randn() * 0.01;
        
        % Normalize direction vector
        mag = sqrt(dx^2 + dy^2 + dz^2);
        dx = dx / mag;
        dy = dy / mag;
        dz = dz / mag;
        
        % Plot track point
        plot3(x, y, z, 'k.', 'MarkerSize', 10);
        
        % Pause for visualization
        pause(0.05);
        
        % Write frame to video
        try
            writeVideo(v, getframe(fig));
        catch ME
            error('Failed to write frame to video: %s', ME.message);
        end
    end
end

% Close the video file
try
    close(v);
catch ME
    error('Failed to close video file: %s', ME.message);
end

% Function definition for drawing cylinders
function drawCylinder(x1, y1, z1, x2, y2, z2, radius, faceColor, edgeColor, faceAlpha)
    [X, Y, Z] = cylinder(radius, 100);
    X = X + x1;
    Y = Y + y1;
    Z = Z * (z2 - z1) + z1;
    surf(X, Y, Z, 'FaceColor', faceColor, 'EdgeColor', edgeColor, 'FaceAlpha', faceAlpha);
end
