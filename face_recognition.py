import cv2
import face_recognition
import os

# Load known faces
known_face_encodings = []
known_face_names = []

# Load images from the 'images' folder
image_folder = 'images'
for image_name in os.listdir(images):
    if image_name.endswith('.jpg') or image_name.endswith('.png'):
        # Load the image
        image_path = os.path.join(images, image_name)
        image = face_recognition.load_image_file(image_path)
        
        # Get the face encoding
        face_encoding = face_recognition.face_encodings(image)[0]
        
        # Append the encoding and name
        known_face_encodings.append(face_encoding)
        known_face_names.append(os.path.splitext(image)[0])  # Get name without extension

# Initialize the webcam
video_capture = cv2.VideoCapture(0)

while True:
    # Capture a single frame from the webcam
    ret, frame = video_capture.read()
    
    # Convert the frame from BGR to RGB
    rgb_frame = frame[:, :, ::-1]
    
    # Find all the faces and face encodings in the current frame
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)
    
    # Loop through each face found in the frame
    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        # Check if the face matches any known faces
        matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
        name = "Unknown"
        
        # Use the known face with the smallest distance to the new face
        face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
        best_match_index = np.argmin(face_distances)
        if matches[best_match_index]:
            name = known_face_names[best_match_index]
        
        # Draw a box around the face
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 255, 0), 2)
        
        # Draw a label with the name
        cv2.putText(frame, name, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 255), 2)

    # Display the resulting image
    cv2.imshow('Video', frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close windows
video_capture.release()
cv2.destroyAllWindows()