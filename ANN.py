import numpy as np

# Sigmoid activation function and its derivative
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

# Neural Network class
class SimpleANN:
    def __init__(self, input_size, hidden_size, output_size):
        # Initialize weights with random values
        self.weights_input_hidden = np.random.randn(input_size, hidden_size)
        self.weights_hidden_output = np.random.randn(hidden_size, output_size)
        self.bias_hidden = np.random.randn(1, hidden_size)
        self.bias_output = np.random.randn(1, output_size)

    def feedforward(self, X):
        # Feedforward propagation
        self.hidden_layer_input = np.dot(X, self.weights_input_hidden) + self.bias_hidden
        self.hidden_layer_output = sigmoid(self.hidden_layer_input)
        
        self.output_layer_input = np.dot(self.hidden_layer_output, self.weights_hidden_output) + self.bias_output
        self.output_layer_output = sigmoid(self.output_layer_input)
        
        return self.output_layer_output

    def backpropagate(self, X, y, output, learning_rate=0.1):
        # Calculate the error
        output_error = y - output
        output_delta = output_error * sigmoid_derivative(output)
        
        # Backpropagate the error to the hidden layer
        hidden_error = output_delta.dot(self.weights_hidden_output.T)
        hidden_delta = hidden_error * sigmoid_derivative(self.hidden_layer_output)
        
        # Update weights and biases using gradient descent
        self.weights_hidden_output += self.hidden_layer_output.T.dot(output_delta) * learning_rate
        self.bias_output += np.sum(output_delta, axis=0, keepdims=True) * learning_rate
        
        self.weights_input_hidden += X.T.dot(hidden_delta) * learning_rate
        self.bias_hidden += np.sum(hidden_delta, axis=0, keepdims=True) * learning_rate

    def train(self, X, y, epochs=10000, learning_rate=0.1):
        for epoch in range(epochs):
            # Feedforward
            output = self.feedforward(X)
            # Backpropagation
            self.backpropagate(X, y, output, learning_rate)
            if epoch % 1000 == 0:
                loss = np.mean(np.square(y - output))  # Mean Squared Error
                print(f'Epoch {epoch}/{epochs} Loss: {loss}')

# Example usage
if __name__ == "__main__":
    # Sample data for a binary classification task (e.g., AND gate)
    X = np.array([[0, 0],
                  [0, 1],
                  [1, 0],
                  [1, 1]])

    y = np.array([[0], [0], [0], [1]])  # Expected output for AND gate

    # Initialize the neural network with 2 input nodes, 2 hidden nodes, and 1 output node
    ann = SimpleANN(input_size=2, hidden_size=2, output_size=1)

    # Train the neural network
    ann.train(X, y, epochs=10000, learning_rate=0.1)

    # Test the neural network after training
    print("\nPredictions after training:")
    predictions = ann.feedforward(X)
    print(predictions)
