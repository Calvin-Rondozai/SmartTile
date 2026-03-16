<<<<<<< HEAD
# SmartTile IoT Alert System

A modern, techy, real-time IoT alert system with a web dashboard. The system receives alerts from an ESP32 via a Flask-SocketIO backend.

## 🎨 Design Features

- **Color Theme**: VS Code blue (#007ACC) primary, white/light gray backgrounds, bright red alerts, neon green/cyan accents
- **Glassmorphism UI**: Modern frosted glass panels with blur effects
- **Smooth Animations**: Alert flashes, button pulses, fade transitions
- **Real-time Updates**: Socket.IO for instant alert broadcasting
- **Voice Feedback**: Mobile app provides voice alerts until buzzer is turned off

## 📁 Project Structure

```
SmartTile/
├── backend/
│   ├── app.py              # Flask-SocketIO server
│   └── requirements.txt    # Python dependencies
├── web/
│   ├── index.html          # Login page
│   ├── dashboard.html      # Main dashboard
│   ├── styles.css          # All styles with animations
│   ├── login.js            # Login logic
│   └── dashboard.js        # Dashboard logic with Socket.IO
├── smartTile.ino           # Original ESP32 code
└── smartTile_updated.ino   # ESP32 code with WiFi & HTTP
```

## 🚀 Setup Instructions

### Backend Setup

1. Navigate to the backend directory:
```bash
cd backend
```

2. Create a virtual environment (recommended):
```bash
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
```

3. Install dependencies:
```bash
pip install -r requirements.txt
```

4. Run the server:
```bash
python app.py
```

The server will start on `http://localhost:5000`

### Web Dashboard Setup

1. Open `web/index.html` in a web browser
2. Or use a local server (recommended):
```bash
cd web
python -m http.server 8000
```
Then navigate to `http://localhost:8000`

**Note**: Update the Socket.IO URL in `dashboard.js` if your backend is on a different host/port.

### ESP32 Setup

1. Open `smartTile_updated.ino` in Arduino IDE
2. Install required libraries:
   - ESP32 Board Support (via Board Manager)
   - WiFi library (included with ESP32)
   - HTTPClient library (included with ESP32)

3. Update WiFi credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

4. Update server URL:
```cpp
const char* serverURL = "http://YOUR_SERVER_IP:5000/api/alert";
```

5. Upload to ESP32

## 🔄 System Flow

1. **ESP32** detects motion via ultrasonic sensor
2. **ESP32** sends HTTP POST to Flask backend
3. **Flask Backend** receives alert and broadcasts via Socket.IO
4. **Web Dashboard** receives alert via Socket.IO, flashes red
5. **User** taps "Turn Off Buzzer" button
6. **Backend** receives request and broadcasts "buzzer_off" event
7. **All clients** update UI and stop alerts/voice feedback

## 🎯 Key Features

### Web Dashboard
- ✅ Modern login page with glassmorphism
- ✅ Real-time alert feed with red flash animations
- ✅ Large circular "Turn Off Buzzer" button with pulse animation
- ✅ Mute toggle for alerts
- ✅ Collapsible alert history panel
- ✅ Connection status indicator
- ✅ Responsive design

### Backend API
- `POST /api/alert` - Receive alerts from ESP32
- `POST /api/buzzer/off` - Turn off buzzer
- `GET /api/alerts/history` - Get alert history
- `GET /api/buzzer/status` - Get buzzer status
- Socket.IO events: `new_alert`, `buzzer_off`, `connection_status`

## 🎨 Design Elements

### Colors
- Primary: `#007ACC` (VS Code blue)
- Alert: `#ff1744` (bright red)
- Accent: `#00FF88` (neon green), `#00D4FF` (cyan)
- Background: Dark gradient (`#0a0a0a` → `#1a1a2e` → `#16213e`)

### Animations
- Alert flash: Red overlay fade
- Button pulse: Scale animation on active state
- Alert slide-in: From left with fade
- Shimmer effect: Glass panels
- Starfield: Animated background stars

### Typography
- Headers: Orbitron (futuristic, techy)
- Body: Rajdhani (modern, clean)

## 🔧 Configuration

### Backend Port
Default: `5000`. Change in `backend/app.py`:
```python
socketio.run(app, host='0.0.0.0', port=5000, debug=True)
```

### Alert Cooldown (ESP32)
Prevent spam alerts. Change in `smartTile_updated.ino`:
```cpp
const unsigned long alertCooldown = 2000; // milliseconds
```

### Detection Distance (ESP32)
Adjust sensitivity. Change in `smartTile_updated.ino`:
```cpp
const int detectionDistance = 20; // centimeters
```

## 🐛 Troubleshooting

### Web Dashboard not connecting
- Check backend is running on port 5000
- Update Socket.IO URL in `dashboard.js` if needed
- Check browser console for errors

### ESP32 not sending alerts
- Verify WiFi credentials
- Check server URL is correct
- Ensure backend is running and accessible
- Check Serial Monitor for connection status

## 📄 License

This project is open source and available for personal and educational use.

## 🎉 Enjoy!

You now have a fully functional, modern IoT alert system with beautiful animations and real-time updates!
=======
# SmartTile
SmartTile is a real‑time IoT alert system built around an ESP32, a Flask‑SocketIO backend, a modern web dashboard, and a React Native (Expo) mobile app. It’s designed for safety/monitoring scenarios (e.g. “Kitchen” motion/pressure alerts), providing instant visual, audio, and push‑notification feedback whenever an event is detected.
>>>>>>> 8af61ba1e2eb22591ce1332d92ebf1432bb80055
