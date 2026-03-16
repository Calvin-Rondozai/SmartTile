# 🚀 Quick Start Guide

Get your SmartTile IoT Alert System up and running in minutes!

## Step 1: Start the Backend Server

```bash
cd backend
pip install -r requirements.txt
python app.py
```

✅ Server should be running on `http://localhost:5000`

## Step 2: Open Web Dashboard

### Option A: Direct File Open
- Open `web/index.html` in your browser
- **Note**: Socket.IO may not work with `file://` protocol

### Option B: Local Server (Recommended)
```bash
cd web
python -m http.server 8000
```
- Navigate to `http://localhost:8000`
- Login with any username/password (demo mode)

## Step 3: Test the System

### Option A: Use Test Script
```bash
cd backend
python test_alert.py
```
- Enter a distance value (e.g., `15`)
- Watch the dashboard flash red and show the alert!

### Option B: Manual API Test
```bash
curl -X POST http://localhost:5000/api/alert \
  -H "Content-Type: application/json" \
  -d '{"type":"Motion Detected","sensor_reading":"Test","distance":15}'
```

## Step 4: Setup ESP32 (Optional)

1. Open `smartTile_updated.ino` in Arduino IDE
2. Update WiFi credentials:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Update server URL (use your computer's IP):
   ```cpp
   const char* serverURL = "http://192.168.1.100:5000/api/alert";
   ```
4. Upload to ESP32
5. Watch alerts appear in real-time!

## 🎯 Testing Checklist

- [ ] Backend server running on port 5000
- [ ] Web dashboard opens and shows login page
- [ ] Can login and see dashboard
- [ ] Connection status shows "Connected"
- [ ] Test alert appears in feed
- [ ] Alert flashes red
- [ ] "Turn Off Buzzer" button works
- [ ] Alert history panel works

## 🔧 Troubleshooting

### "Connection failed" in dashboard
- ✅ Check backend is running: `http://localhost:5000`
- ✅ Check browser console for errors
- ✅ Try refreshing the page

### ESP32 not sending alerts
- ✅ Check Serial Monitor for WiFi connection
- ✅ Verify server URL is correct
- ✅ Ensure backend is running and accessible
- ✅ Check WiFi credentials are correct

## 📱 Finding Your IP Address

### Windows
```bash
ipconfig
```
Look for "IPv4 Address" under your WiFi adapter

### Mac/Linux
```bash
ifconfig | grep "inet "
```
or
```bash
ip addr show
```

## 🎉 You're All Set!

Your SmartTile IoT Alert System is ready to use. Try sending a test alert and watch the magic happen!

---

**Need Help?** Check the main `README.md` for detailed documentation.
