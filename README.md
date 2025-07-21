# MCLXKey-Cpp-Example

A C++ console application demonstrating user authentication using server-side API requests. The project features:

- Console-based login and sign-up menu
- Secure credential handling
- Server communication using cURL
- User information display on successful login
- Error handling for invalid credentials

## Features
- **Login:** Enter username and password to authenticate with the server. Displays user info on success.
- **Sign Up:** Placeholder for future registration functionality.
- **Error Handling:** Shows server error messages (e.g., invalid username).

## Usage
1. Build the project using Visual Studio or your preferred C++ build system.
2. Run the executable. You will see a menu:
   - `1. Login`: Enter your username and password. The app sends a POST request to the server and displays your user info if successful.
   - `2. Sign Up`: Currently not implemented.
   - `0. Exit`: Quit the application.

## Server Communication
- Uses cURL to send POST requests with JSON data.
- Expects server responses in JSON format, e.g.:
  ```json
  {
    "success": true,
    "user": {
      "id": "...",
      "name": "...",
      "username": "...",
      "expireDate": "..."
    }
  }
  ```
- Handles error responses, e.g.:
  ```json
  {
    "success": false,
    "message": "Invalid username"
  }
  ```

## Requirements
- C++17 or later
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- cURL library for HTTP requests

## Setup
1. Clone the repository:
   ```sh
   git clone https://github.com/ostwrafi/MCLXKey-Cpp-Example-.git
   ```
2. Open the project in Visual Studio or your IDE.
3. Build and run the project.

## License
MIT

