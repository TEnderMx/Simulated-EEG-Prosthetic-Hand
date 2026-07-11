import cv2
import mediapipe as mp
import pylsl

# UPDATED: 5 channels instead of 2 (One for each finger)
info = pylsl.StreamInfo('NDS-Behavior', 'behavior', 5, 30, 'float32', 'camera123')
outlet = pylsl.StreamOutlet(info)

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)

N = int(input("Choose Camera: 0=Camera, 1=OBS \n"))
cap = cv2.VideoCapture(N)
print("Camera started.")

# Default starting positions [Thumb, Index, Middle, Ring, Pinky]
last_positions = [0.5, 0.5, 0.5, 0.5, 0.5]

while cap.isOpened():
    success, image = cap.read()
    if not success:
        continue

    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(image_rgb)

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            # Extract the Y-coordinate for all 5 fingertips
            last_positions[0] = hand_landmarks.landmark[4].y  # Thumb
            last_positions[1] = hand_landmarks.landmark[8].y  # Index
            last_positions[2] = hand_landmarks.landmark[12].y # Middle
            last_positions[3] = hand_landmarks.landmark[16].y # Ring
            last_positions[4] = hand_landmarks.landmark[20].y # Pinky
            
            mp.solutions.drawing_utils.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            
    # Push all 5 values to LSL simultaneously
    outlet.push_sample(last_positions)
            
    cv2.imshow('MediaPipe Hand Tracker', image)
    if cv2.waitKey(5) & 0xFF == 27: # Press 'ESC' to exit
        break

cap.release()
cv2.destroyAllWindows()