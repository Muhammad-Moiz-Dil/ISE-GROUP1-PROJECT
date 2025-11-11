// Chat application state
const state = {
    apiBaseUrl: 'http://localhost:18080', // Updated to Drogon backend port
    currentState: 'MAIN_MENU',
    isTyping: false
};

// DOM Elements
const chatMessages = document.getElementById('chat-messages');
const messageForm = document.getElementById('message-form');
const userInput = document.getElementById('user-input');

// Initialize the chat
function initChat() {
    // Focus the input field when the page loads
    userInput.focus();
    
    // Add event listeners
    messageForm.addEventListener('submit', handleSubmit);
    
    // Clear chat messages
    chatMessages.innerHTML = '';
    
    // Send welcome message and show main menu
    addBotMessage("Hello! I'm your AI assistant. How can I help you today?");
    showMainMenu();
    
    // Reset state to main menu
    state.currentState = 'MAIN_MENU';
}

// Handle form submission
async function handleSubmit(e) {
    e.preventDefault();
    
    const message = userInput.value.trim();
    if (!message) return;
    
    // Add user message to chat
    addUserMessage(message);
    userInput.value = '';
    
    // Show typing indicator
    showTypingIndicator();
    
    try {
        // Process the message based on current state
        await processUserInput(message);
    } catch (error) {
        console.error('Error processing message:', error);
        addBotMessage("Sorry, I encountered an error. Please try again.");
    } finally {
        // Always remove typing indicator when done
        removeTypingIndicator();
    }
}

// Process user input based on current state
async function processUserInput(input) {
    try {
        // Call the appropriate API endpoint based on current state
        const response = await fetch(`${state.apiBaseUrl}/chat`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            body: JSON.stringify({
                message: input,
                state: state.currentState || 'MAIN_MENU'  // Ensure state is never undefined
            }),
            mode: 'cors'  // Enable CORS
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        
        const data = await response.json();
        
        // Update state if provided in the response
        if (data.newState) {
            state.currentState = data.newState;
        }
        
        // Display the bot's response first
        if (data.response) {
            // Only show the message, we'll handle the options separately
            addBotMessage(data.response);
        }
        
        // Handle state-specific UI updates after showing the response
        if (state.currentState === 'MAIN_MENU' && input === 'A') {
            // Only show loan categories if user just chose to apply for a loan
            showLoanCategories();
        } else if (state.currentState === 'LOAN_CATEGORY' && input === 'H') {
            // Only show home loan areas if user just chose home loans
            showHomeLoanAreas();
        } else if (state.currentState === 'MAIN_MENU' && input === 'H') {
            // If user chose home loans from main menu, show areas
            showHomeLoanAreas();
        }
        
    } catch (error) {
        console.error('Error:', error);
        addBotMessage("I'm having trouble connecting to the server. Please make sure the backend is running on port 18080.");
    }
}

// Show main menu options
function showMainMenu() {
    const menu = `\nPlease select an option:\n` +
                 `A. Ask a question\n` +
                 `H. Home Loan Information\n` +
                 `C. Car Loan Information\n` +
                 `S. Student Loan Information\n` +
                 `P. Personal Loan Information`;
    
    // Add a small delay to make it feel natural
    setTimeout(() => {
        addBotMessage(menu);
    }, 500);
}

// Show loan categories
function showLoanCategories() {
    const categories = `\nPlease select a loan category:\n` +
                     `H. Home Loan\n` +
                     `C. Car Loan\n` +
                     `S. Student Loan\n` +
                     `P. Personal Loan`;
    
    addBotMessage(categories);
}

// Show home loan area options
function showHomeLoanAreas() {
    const areas = `\nPlease select an area for home loan information:\n` +
                 `1. Area 1\n` +
                 `2. Area 2\n` +
                 `3. Area 3\n` +
                 `4. Area 4`;
    
    addBotMessage(areas);
}

// Add a message from the user to the chat
function addUserMessage(message) {
    const messageElement = document.createElement('div');
    messageElement.className = 'message user-message';
    
    const content = document.createElement('div');
    content.className = 'message-content';
    content.textContent = message;
    
    const timestamp = document.createElement('div');
    timestamp.className = 'message-timestamp';
    timestamp.textContent = getCurrentTime();
    
    messageElement.appendChild(content);
    messageElement.appendChild(timestamp);
    chatMessages.appendChild(messageElement);
    
    // Scroll to bottom
    chatMessages.scrollTop = chatMessages.scrollHeight;
}

// Add a message from the bot to the chat
function addBotMessage(message) {
    // Split message by newlines to handle multiline responses
    const messages = message.split('\n').filter(m => m.trim() !== '');
    
    messages.forEach((msg, index) => {
        // Add a small delay between multiple messages for better UX
        setTimeout(() => {
            const messageElement = document.createElement('div');
            messageElement.className = 'message bot-message';
            
            const content = document.createElement('div');
            content.className = 'message-content';
            content.textContent = msg;
            
            const timestamp = document.createElement('div');
            timestamp.className = 'message-timestamp';
            timestamp.textContent = getCurrentTime();
            
            messageElement.appendChild(content);
            messageElement.appendChild(timestamp);
            chatMessages.appendChild(messageElement);
            
            // Scroll to bottom
            chatMessages.scrollTop = chatMessages.scrollHeight;
        }, index * 200); // 200ms delay between messages
    });
}

// Show typing indicator
function showTypingIndicator() {
    if (state.isTyping) return;
    
    state.isTyping = true;
    
    const typingElement = document.createElement('div');
    typingElement.id = 'typing-indicator';
    typingElement.className = 'typing-indicator';
    
    // Add three dots for the typing animation
    for (let i = 0; i < 3; i++) {
        const dot = document.createElement('div');
        dot.className = 'typing-dot';
        typingElement.appendChild(dot);
    }
    
    chatMessages.appendChild(typingElement);
    chatMessages.scrollTop = chatMessages.scrollHeight;
}

// Remove typing indicator
function removeTypingIndicator() {
    const typingElement = document.getElementById('typing-indicator');
    if (typingElement) {
        typingElement.remove();
        state.isTyping = false;
    }
}

// Get current time in HH:MM format
function getCurrentTime() {
    const now = new Date();
    return now.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
}

// Initialize the chat when the DOM is fully loaded
document.addEventListener('DOMContentLoaded', initChat);