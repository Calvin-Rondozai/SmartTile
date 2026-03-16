# 📦 Complete Installation Guide

Step-by-step installation for all components of the SmartTile IoT Alert System.

## Prerequisites

### Required Software
- **Python 3.8+** - [Download](https://www.python.org/downloads/)
- **Node.js 14+** - [Download](https://nodejs.org/)
- **Git** (optional) - [Download](https://git-scm.com/)
- **Arduino IDE** (for ESP32) - [Download](https://www.arduino.cc/en/software)

## Part 1: Backend Setup

### Step 1: Install Python Dependencies

```bash
cd backend
pip install -r requirements.txt
```

**Or use virtual environment (recommended):**
```bash
python -m venv venv
# Windows
venv\Scripts\activate
# Mac/Linux
source venv/bin/activate

pip install -r requirements.txt
```

### Step 2: Test Backend

```bash
python app.py
```

You should see:
```
Starting SmartTile IoT Alert System Server...
Server running on http://localhost:5000
```

✅ Backend is ready!

## Part 2: Web Dashboard Setup

### Step 1: No Installation Required!

The web dashboard uses vanilla JavaScript - no build step needed.

### Step 2: Start Local Server

```bash
cd web
python -m http.server 8000
```

**Or use any HTTP server:**
- **Node.js**: `npx http-server -p 8000`
- **PHP**: `php -S localhost:8000`
- **VS Code**: Use "Live Server" extension

### Step 3: Access Dashboard

Open browser: `http://localhost:8000`

✅ Web dashboard is ready!

## Part 3: ESP32 Setup (Optional)

### Step 1: Install ESP32 Board Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search "ESP32" and install

### Step 2: Install Required Libraries

ESP32 libraries are included, but you may need:
- WiFi (included)
- HTTPClient (included)

### Step 3: Configure ESP32 Code

Edit `smartTile_updated.ino`:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://YOUR_COMPUTER_IP:5000/api/alert";
```

### Step 4: Upload to ESP32

1. Connect ESP32 via USB
2. Select board: **Tools → Board → ESP32 Arduino → Your ESP32 Model**
3. Select port: **Tools → Port → COMx (Windows) or /dev/ttyUSBx (Linux)**
4. Click **Upload**

✅ ESP32 is ready!

## Verification Checklist

### Backend
- [ ] Server starts without errors
- [ ] Accessible at `http://localhost:5000`
- [ ] API responds: `curl http://localhost:5000`

### Web Dashboard
- [ ] Login page loads
- [ ] Can login (any credentials work in demo)
- [ ] Dashboard shows connection status
- [ ] Test alert appears when sent

### Mobile App
- [ ] Expo starts without errors
- [ ] App loads on phone
- [ ] Shows "Connected" status
- [ ] Receives test alerts

### ESP32
- [ ] Connects to WiFi (check Serial Monitor)
- [ ] Sends alerts to backend
- [ ] Backend receives alerts

## Testing the System

### 1. Start All Services

**Terminal 1 - Backend:**
```bash
cd backend
python app.py
```

**Terminal 2 - Web Dashboard:**
```bash
cd web
python -m http.server 8000
```

### 2. Send Test Alert

**Terminal 3 - Test Script:**
```bash
cd backend
python test_alert.py
```

Enter a distance (e.g., `15`)

### 3. Verify

- ✅ Web dashboard flashes red
- ✅ Alert appears in feed
- ✅ "Turn Off Buzzer" button works

## Troubleshooting

### Backend Issues

**Port already in use:**
```bash
# Windows
netstat -ano | findstr :5000
taskkill /PID <PID> /F

# Mac/Linux
lsof -ti:5000 | xargs kill
```

**Module not found:**
```bash
pip install --upgrade -r requirements.txt
```

### Web Dashboard Issues

**CORS errors:**
- Backend CORS is enabled, should work
- Check browser console for errors

**Socket.IO connection failed:**
- Verify backend is running
- Check `config.js` has correct URL

### ESP32 Issues

**WiFi connection fails:**
- Check credentials
- Verify WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
- Check Serial Monitor for errors

**Can't upload:**
- Install USB drivers for ESP32
- Try different USB cable
- Hold BOOT button while uploading

## Next Steps

1. ✅ All components installed
2. ✅ System tested and working
3. 🎯 Customize colors/styles
4. 🎯 Add more features
5. 🎯 Deploy to production

## Support

- Check individual README files
- Review error messages in console
- Verify all prerequisites installed
- Ensure all services running

---

**Installation complete!** 🎉
