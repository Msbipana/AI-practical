import tensorflow as tf
from tensorflow.keras import datasets, layers, models
import matplotlib.pyplot as plt

# Step 1: Load and preprocess the CIFAR-10 dataset
(x_train, y_train), (x_test, y_test) = datasets.cifar10.load_data()

# Normalize pixel values to be between 0 and 1
x_train, x_test = x_train / 255.0, x_test / 255.0

# Step 2: Define a very simple CNN model
model = models.Sequential([
    layers.Conv2D(16, (3, 3), activation='relu', input_shape=(32, 32, 3)),  # One convolutional layer
    layers.MaxPooling2D((2, 2)),  # Max pooling layer to reduce spatial dimensions
    layers.Flatten(),  # Flatten the 3D output to 1D
    layers.Dense(10, activation='softmax')  # Output layer with 10 units for 10 classes
])

# Step 3: Compile the model
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# Step 4: Train the model
model.fit(x_train, y_train, epochs=5, validation_data=(x_test, y_test))

# Step 5: Evaluate the model on the test set
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=2)
print(f"Test accuracy: {test_acc}")

# Optional: Display a sample image from the test dataset
plt.imshow(x_test[0])
plt.title(f"Label: {y_test[0]}")
plt.show()
