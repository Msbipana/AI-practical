# Import necessary libraries
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Step 1: Generate synthetic data (e.g., predicting house prices based on square footage)
np.random.seed(42)

# Generate data: Let's assume square footage (X) and price (Y)
X = 2 * np.random.rand(100, 1)  # 100 random square footage values between 0 and 2
y = 3 + 5 * X + np.random.randn(100, 1)  # y = 3 + 5 * X + noise

# Step 2: Split the data into training and test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Step 3: Create and train a linear regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Step 4: Make predictions using the test set
y_pred = model.predict(X_test)

# Step 5: Evaluate the model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

# Output evaluation metrics
print(f"Mean Squared Error (MSE): {mse}")
print(f"R-squared (R2): {r2}")

# Step 6: Visualize the results
plt.figure(figsize=(8,6))

# Plotting the training data and the regression line
plt.scatter(X_train, y_train, color='blue', label='Training data')
plt.plot(X_train, model.predict(X_train), color='red', label='Regression line')

# Plotting the test data
plt.scatter(X_test, y_test, color='green', label='Test data')

plt.title('Linear Regression: House Price Prediction')
plt.xlabel('Square Footage')
plt.ylabel('Price')
plt.legend()
plt.show()
