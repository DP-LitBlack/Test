params = gyroparams

% Generate N samples at a sampling rate of Fs with a sinusoidal frequency
% of Fc.
N = 300;
Fs = 100;
Fc = 1;

t = (0:(1/Fs):((N-1)/Fs)).';
acc = zeros(N, 3);
angvel = zeros(N, 3);
angvel(:,1) = sin(2*pi*Fc*t);

imu = imuSensor('SampleRate', Fs, 'Gyroscope', params);
[~, gyroData] = imu(acc, angvel);

figure
plot(t, angvel(:,1), '--', t, gyroData(:,1))
xlabel('Time (s)')
ylabel('Angular Velocity (rad/s)')
title('Ideal Gyroscope Data')
legend('x (ground truth)', 'x (gyroscope)')

imu = imuSensor('SampleRate', Fs, 'Gyroscope', params);
imu.Gyroscope.RandomWalk = 0.091; % (rad/s)*sqrt(Hz)
imu.Gyroscope.NoiseDensity = 0.0125; % (rad/s)/sqrt(Hz)

[~, gyroData] = imu(acc, angvel);

figure
plot(t, angvel(:,1), '--', t, gyroData(:,1))
xlabel('Time (s)')
ylabel('Angular Velocity (rad/s)')
title('Random Walk Gyroscope Data')
legend('x (ground truth)', 'x (gyroscope)')

fid = fopen('data_with_noise.txt', 'w');
for i = 1:length(gyroData(:,1))
    fprintf(fid, '%.4f\n', gyroData(i,1));
end
fclose(fid);

fid = fopen('data_original.txt', 'w');
for i = 1:length(angvel(:,1))
    fprintf(fid, '%.4f\n', angvel(i,1));
end
fclose(fid);