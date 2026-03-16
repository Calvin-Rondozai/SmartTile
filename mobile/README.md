# SmartTile Orbit – Mobile App

React Native + Expo mobile app for your SmartTile IoT alert system with an **Orbit-style** UI, real-time alerts, history, and settings (dark/light themes).

## Features

- **Orbit-inspired dashboard** (like the screenshots you shared)
  - Animated central “planet” with orbiting dot
  - Connection status pill (Online / Offline)
  - Active alerts + buzzer status cards
  - List of current active alerts
  - Big gradient **Silence buzzer** button
- **History screen**
  - Full list of past alerts (latest at top)
  - Shows time, distance, and sensor for each alert
- **Settings screen**
  - Toggle between **Dark / Light** themes
  - Toggle **Voice alerts** on/off
- **Real-time integration**
  - Connects to your existing Flask-SocketIO backend
  - Uses the same `new_alert`, `buzzer_off`, and `alert_history` events as the web dashboard
- **Voice feedback**
  - Repeats “Alert! Alert! Alert!” until the buzzer is silenced

## Setup

```bash
cd mobile
npm install
```

### Configure backend URL

Edit `App.js` at the top:

```js
const SOCKET_URL = 'http://10.44.166.47:5000'; // your backend host
const API_BASE = SOCKET_URL;
```

If your backend IP/port changes, update this value.

### Run the app

```bash
cd mobile
npm start
```

Then:

- Scan the QR code with **Expo Go** on your phone, or
- Press `a` for Android emulator / `i` for iOS simulator (if configured)

## How it works with your system

### Real-time alerts

- Connects to `SOCKET_URL` with `socket.io-client`
- Listens for:
  - `new_alert` → shows alert on **Alerts** tab and appends to **History**
  - `buzzer_off` → clears active alerts and stops voice feedback
  - `alert_history` → populates **History** on connect

### Buzzer control

- When you press **Silence buzzer** in the app it calls:

```http
POST /api/buzzer/off
```

on your Flask backend (same as the web dashboard).

### Voice alerts

- Uses `expo-speech` to speak “Alert! Alert! Alert!” in a loop
- Runs while:
  - Voice alerts setting is ON
  - Buzzer is active
  - There is at least one active alert
- Stops when:
  - Buzzer is turned off, or
  - Voice alerts setting is turned OFF

## Screens

### Alerts (Orbit dashboard)

- Animated orbit visual in the center
- Connection status (Online/Offline)
- “Active Alerts” and “Buzzer” stat cards
- List of recent active alerts
- Large gradient **Silence buzzer** pill button

### History

- Reverse-chronological list of all alerts
- Each item shows:
  - Type (e.g., Motion Detected)
  - Time
  - Distance and sensor

### Settings

- **Theme:** Dark / Light toggle
- **Voice alerts:** enable / disable

## Notes

- This app is **purely a client**: it doesn’t change backend logic – it reuses your current Flask-SocketIO + ESP32 system.
- The UI is designed to be visually close to the Orbit screens you provided while using your alert concepts instead of subscriptions.

---

You can now use both the web dashboard and this Orbit-style mobile app against the same backend and ESP32 device.

