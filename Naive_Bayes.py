# Import necessary libraries
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Step 1: Create a simple dataset (messages and labels)
# Messages: text data, Labels: 0 for 'ham' and 1 for 'spam'
messages = [
    "Free entry to win a prize",  # spam
    "Hi, how are you?",          # ham
    "Claim your free money now",  # spam
    "Let's meet for coffee",      # ham
    "You have won a free lottery", # spam
    "Are you coming to the party?", # ham
    "Congratulations! You've won a gift", # spam
    "What's the homework?",       # ham
    "Call now to get a free vacation", # spam
    "How's the weather today?"    # ham
]

labels = [1, 0, 1, 0, 1, 0, 1, 0, 1, 0]  # 1 for spam, 0 for ham

# Step 2: Convert the text messages into a format that the machine can understand
# We will use CountVectorizer to convert the text into a vector of word counts.
vectorizer = CountVectorizer()

# Convert the messages into a matrix of token counts (features)
X = vectorizer.fit_transform(messages)

# Step 3: Split the data into training and testing sets (80% training, 20% testing)
X_train, X_test, y_train, y_test = train_test_split(X, labels, test_size=0.2, random_state=42)

# Step 4: Create a Naive Bayes classifier and train it on the training data
classifier = MultinomialNB()
classifier.fit(X_train, y_train)

# Step 5: Predict the labels for the test data
y_pred = classifier.predict(X_test)

# Step 6: Evaluate the classifier performance
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy * 100}%")

# Step 7: Test the classifier with a new message
new_message = ["Free tickets to a concert"]
new_message_vector = vectorizer.transform(new_message)
prediction = classifier.predict(new_message_vector)

if prediction == 1:
    print("The message is Spam!")
else:
    print("The message is Ham!")
