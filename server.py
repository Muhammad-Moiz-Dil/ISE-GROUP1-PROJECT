from flask import Flask, jsonify, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # This enables CORS for all routes

# Simple test route to check if server is running
@app.route('/test', methods=['GET'])
def test():
    return jsonify({"status": "Server is running!"})

@app.route('/chat', methods=['POST', 'OPTIONS'])
def chat():
    if request.method == 'OPTIONS':
        response = jsonify()
        response.headers.add('Access-Control-Allow-Origin', '*')
        response.headers.add('Access-Control-Allow-Headers', '*')
        response.headers.add('Access-Control-Allow-Methods', 'POST, OPTIONS')
        return response

    try:
        data = request.get_json()
        user_input = data.get('message', '').strip().upper()
        current_state = data.get('state', 'MAIN_MENU')
        
        response = "I didn't understand that. Please try again."
        new_state = current_state

        if current_state == 'MAIN_MENU':
            if user_input in ['A', 'H', 'C', 'S', 'P']:
                if user_input == 'H':
                    new_state = 'HOME_LOAN_AREA'
                    response = "You've selected Home Loan Information."
                else:
                    response = f"You've selected option {user_input}. This feature is coming soon!"
            else:
                response = "Please select a valid option (A, H, C, S, or P)."
        
        elif current_state == 'HOME_LOAN_AREA':
            if user_input in ['1', '2', '3', '4']:
                response = f"Showing home loan information for Area {user_input}."
                new_state = 'MAIN_MENU'
            else:
                response = "Please select a valid area (1, 2, 3, or 4)."

        return jsonify({
            'response': response,
            'newState': new_state
        })

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001, debug=True)