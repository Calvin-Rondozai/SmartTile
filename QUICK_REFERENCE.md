# ⚡ Quick Reference Card

## 🚀 Start Everything

```bash
# Terminal 1 - Backend
cd backend && python app.py

# Terminal 2 - Web Dashboard  
cd web && python -m http.server 8000

# Terminal 3 - Mobile App
cd mobile && npm start
```

## 🔗 URLs

- **Backend API**: `http://localhost:5000`
- **Web Dashboard**: `http://localhost:8000`
- **Mobile App**: Scan QR code from Expo

## 📝 Configuration

### Web Dashboard
Edit `web/config.js`:
```javascript
SOCKET_URL: 'http://localhost:5000'
```

### Mobile App
Edit `mobile/App.js`:
```javascript
const SOCKET_URL = 'http://YOUR_IP:5000';
```

### ESP32
Edit `smartTile_updated.ino`:
```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
const char* serverURL = "http://YOUR_IP:5000/api/alert";
```

## 🧪 Test Commands

```bash
# Send test alert
cd backend && python test_alert.py

# Test API
curl http://localhost:5000

# Test alert endpoint
curl -X POST http://localhost:5000/api/alert \
  -H "Content-Type: application/json" \
  -d '{"type":"Test","distance":15}'
```

## 🎨 Key Colors

- Primary: `#007ACC` (VS Code blue)
- Alert: `#ff1744` (Red)
- Accent: `#00FF88` (Green), `#00D4FF` (Cyan)
- Background: `#0a0a0a` (Dark)

## 🔌 API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| POST | `/api/alert` | Send alert |
| POST | `/api/buzzer/off` | Turn off buzzer |
| GET | `/api/alerts/history` | Get history |
| GET | `/api/buzzer/status` | Get status |

## 📡 Socket.IO Events

- `new_alert` - New alert received
- `buzzer_off` - Buzzer turned off
- `connection_status` - Connection info
- `alert_history` - Alert history

## 🐛 Common Issues

**Backend won't start:**
```bash
pip install -r requirements.txt
```

**Web dashboard can't connect:**
- Check backend is running
- Verify `config.js` URL

**Mobile app can't connect:**
- Use computer IP, not localhost
- Same WiFi network
- Check firewall

**ESP32 won't connect:**
- Check WiFi credentials
- Verify 2.4GHz network
- Check Serial Monitor

## 📱 Mobile App Features

- ✅ Real-time alerts
- ✅ Voice feedback
- ✅ Vibration
- ✅ Red flash
- ✅ Large controls

## 🌐 Web Dashboard Features

- ✅ Real-time alerts
- ✅ Visual flash
- ✅ Alert history
- ✅ Buzzer control
- ✅ Mute toggle

## 🎯 System Flow

```
ESP32 → HTTP POST → Flask → Socket.IO → Web Dashboard
                                    → Mobile App
```

## 📚 Documentation

- `README.md` - Main docs
- `QUICK_START.md` - Quick setup
- `INSTALLATION.md` - Full installation
- `ARCHITECTURE.md` - System design
- `DESIGN_DOCUMENTATION.md` - Design specs

---

**Keep this handy for quick reference!** 📌
