# 🏗️ System Architecture

## Overview

SmartTile IoT Alert System uses a client-server architecture with real-time communication via WebSockets.

```
┌─────────────┐
│   ESP32     │  (Hardware Sensor)
│  Ultrasonic │
│   Sensor    │
└──────┬──────┘
       │
       │ HTTP POST
       │ /api/alert
       ▼
┌─────────────────┐
│  Flask Backend  │  (Python)
│  Flask-SocketIO │  Port: 5000
│  REST API       │
└────┬────────────┘
     │
     │ Socket.IO
     │ (WebSocket)
     │
     ▼
┌─────────┐
│   Web   │
│Dashboard│
│(Browser)│
└─────────┘
```

## Component Details

### 1. ESP32 (Hardware Layer)

**Technology**: Arduino C++  
**Communication**: WiFi + HTTP  
**Function**: 
- Reads ultrasonic sensor
- Detects motion (distance < threshold)
- Sends HTTP POST to backend
- Activates buzzer and RGB LED

**Key Files**:
- `smartTile_updated.ino`

**Data Flow**:
```
Sensor Reading → Detection Logic → HTTP POST → Backend
```

### 2. Flask Backend (Server Layer)

**Technology**: Python, Flask, Flask-SocketIO  
**Port**: 5000  
**Function**:
- Receives alerts from ESP32 via REST API
- Stores alert history
- Broadcasts alerts to all connected clients via Socket.IO
- Manages buzzer state
- Provides REST API endpoints

**Key Files**:
- `backend/app.py`
- `backend/requirements.txt`

**API Endpoints**:
- `POST /api/alert` - Receive alert from ESP32
- `POST /api/buzzer/off` - Turn off buzzer
- `GET /api/alerts/history` - Get alert history
- `GET /api/buzzer/status` - Get buzzer status

**Socket.IO Events**:
- `new_alert` - Broadcast new alert
- `buzzer_off` - Broadcast buzzer off
- `connection_status` - Send connection info
- `alert_history` - Send alert history

### 3. Web Dashboard (Client Layer)

**Technology**: Vanilla JavaScript, HTML5, CSS3  
**Communication**: Socket.IO Client  
**Function**:
- Real-time alert display
- User controls (buzzer off, mute)
- Alert history
- Visual feedback (red flash, animations)

**Key Files**:
- `web/index.html` - Login page
- `web/dashboard.html` - Main dashboard
- `web/styles.css` - All styles and animations
- `web/login.js` - Login logic
- `web/dashboard.js` - Dashboard logic

**Features**:
- Glassmorphism UI
- Smooth animations
- Real-time updates
- Responsive design

## Data Flow

### Alert Detection Flow

```
1. ESP32 detects motion
   ↓
2. ESP32 sends HTTP POST to /api/alert
   {
     "type": "Motion Detected",
     "sensor_reading": "Ultrasonic Sensor",
     "distance": 15
   }
   ↓
3. Flask backend receives alert
   ↓
4. Backend stores alert in history
   ↓
5. Backend broadcasts via Socket.IO: emit('new_alert', alert)
   ↓
6. All connected clients receive alert
   ↓
7. Web dashboard: Flash red, add to feed
```

### Buzzer Off Flow

```
1. User clicks "Turn Off Buzzer" button
   ↓
2. Client sends HTTP POST to /api/buzzer/off
   ↓
3. Backend sets buzzer_active = False
   ↓
4. Backend broadcasts: emit('buzzer_off')
   ↓
5. All clients receive event
   ↓
6. Web dashboard: Deactivate button, stop animations
```

## Technology Stack

### Backend
- **Flask** - Web framework
- **Flask-SocketIO** - WebSocket support
- **Flask-CORS** - Cross-origin resource sharing
- **Python 3.8+** - Runtime

### Web Frontend
- **Vanilla JavaScript** - No frameworks
- **Socket.IO Client** - Real-time communication
- **HTML5** - Markup
- **CSS3** - Styling with animations

### Hardware
- **ESP32** - Microcontroller
- **Arduino IDE** - Development environment
- **WiFi** - Network communication
- **HTTPClient** - HTTP requests

## Security Considerations

⚠️ **Current Implementation**: Basic demo authentication  
✅ **Production Recommendations**:
- Implement proper JWT authentication
- Use HTTPS/WSS for encrypted communication
- Add rate limiting to API endpoints
- Validate and sanitize all inputs
- Use environment variables for secrets
- Implement user roles and permissions

## Scalability

### Current Limitations
- Single server instance
- In-memory alert storage
- No database persistence

### Production Enhancements
- Use Redis for Socket.IO scaling
- Database (PostgreSQL/MongoDB) for alert storage
- Load balancer for multiple server instances
- Message queue (RabbitMQ/Kafka) for high throughput
- Caching layer for performance

## Network Requirements

- **Backend**: Accessible on port 5000
- **ESP32**: WiFi connection to same network
- **Web Dashboard**: Browser with WebSocket support
- **Mobile App**: Same network or VPN for testing

## Deployment Options

### Development
- Local machine (localhost)
- All components on same network

### Production
- Backend: Cloud server (AWS, DigitalOcean, etc.)
- Web: Static hosting (Netlify, Vercel, GitHub Pages)
- Mobile: App stores (iOS App Store, Google Play)
- ESP32: Same as development (local network)

---

This architecture provides a solid foundation for a real-time IoT alert system with room for future enhancements!
