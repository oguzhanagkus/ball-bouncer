# Gebze Technical University<br/>Computer Engineering Department<br/>CSE396 Computer Engineering Project Course

### Members of Group #11:
- Abdulhakim Emre Artış
- Cihan Can Ayyıldız
- Esra Emirli
- Hamza Yoğurtcuoğlu
- İlkay Can
- Melike Serra Kalyon
- Oğuzhan Agkuş
- Oğuzhan Şentürk
- Sezer Demir
- Selman Özleyen
- Yusuf Can Kan

#### We have 4 applications/modules:
- Server app
- Client app
- Mobile app
- Controller board (STM32F4)

##### Server app includes:
- Image processing (with OpenCV)
  - Detect the ball's coordinates and height from plate
- PID controller
  - Calculates angles for servo motors
- Serial port handler
  - Communicates with the STM32F4 board
  - Send calculates angles for servo motors
- Broadcast server (UDP)
  - Sends data (x,y,z coordinates) to client and mobile applications
- User interface
  - Position of the ball in 2D graphs (for XY and XZ axes)
  - Position of the ball in 3D graph/simulation (XYZ axes)
  - Simulation for the movement of the servo motors and arms (OpenGL)
  - Some control buttons ("Balance", "Draw Circle", "Stop")

##### Client app includes:
- Broadcast listener (UDP)
  - Listen a specific port for incoming data
- User interface
  - Position of the ball in 2D graphs (for XY and XZ axes)
  - Position of the ball in 3D graph/simulation (XYZ axes)

##### Mobile app includes:
- User interface
  - Position of the ball in 2D graphs (for XY and XZ axes)

##### Controller board (STM32F4):
- Serial port handler
  - Listen incoming angles
- Motor driver
  - Move servo motors

#### Notes:
- The server and client/mobile applications should be in same local network
- The server and client applications are compatible with both Linux and Windows because we have developed on QT Platform
- The mobile applications for only Android systems
- The project's video on YouTube:
- The detailed report added to repository
