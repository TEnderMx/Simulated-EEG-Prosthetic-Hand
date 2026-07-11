% Load model
modelNumber = 17; % Choose Model to Use

% Find file
folderName = 'training models';
fileName = fullfile(folderName, sprintf('%d_training_model.mat', modelNumber));

% Check if file exists
if ~isfile(fileName)
    error('File %s does not exist. Please check your modelNumber.', fileName);
end

fprintf('Loading Model: %s\n', fileName);
load(fileName);

% Setup hardware
hardware = serialport("COM3", 9600); 
pause(10);

% Connect to LSL
lib = lsl_loadlib();
disp('Looking for data stream...');
result = lsl_resolve_byprop(lib, 'name', 'NDS-SpikeRates', 1, 1);
inlet = lsl_inlet(result{1});

disp('Connected!');

% Run loop
while true
    pause(0.1); 
    [chunk, ~] = inlet.pull_chunk();
    
    if ~isempty(chunk)
        live_data = chunk(1:14, :); 
        live_features = mean(live_data, 2)';
        
        % Predict 5 fingers
        predicted_probs = net(live_features'); 
        
        % Convert predictions
        servo_angles = zeros(1, 5);
        
        % Boundary checks
        servo_angles(predicted_probs > 0.6) = 90;
        
        % Send to hardware arduino
        data_packet = servo_angles(2);
        write(hardware, data_packet, "uint8"); 
        
        % Print out the live angles
        fprintf('Index: %2d\n', servo_angles(2));
        
        % Read arduino serial monitor
        pause(0.05);
        if hardware.NumBytesAvailable > 0
            arduinoMsg = readline(hardware);
            fprintf('Arduino says: %s\n', arduinoMsg);
        end
    end
end