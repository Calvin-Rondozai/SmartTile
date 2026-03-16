# SmartTile IoT - Design Documentation

## 🎨 Visual Design System

### Color Palette

| Color | Hex Code | Usage |
|-------|----------|-------|
| Primary Blue | `#007ACC` | Main buttons, accents, VS Code theme |
| Primary Blue Dark | `#005a9e` | Button hover states |
| Primary Blue Light | `#1a8cd8` | Button gradients |
| Alert Red | `#ff1744` | Alert indicators, flash effects |
| Alert Red Dark | `#d50000` | Alert button active state |
| Accent Green | `#00FF88` | Techy highlights, status indicators |
| Accent Cyan | `#00D4FF` | Secondary accents, distance values |
| Background Dark | `#1e1e1e` | Main background |
| Background Darker | `#151515` | Secondary backgrounds |
| Background Light | `#2d2d2d` | Panel backgrounds |
| Text Primary | `#ffffff` | Main text |
| Text Secondary | `#b0b0b0` | Secondary text |

### Typography

- **Headers**: Orbitron (futuristic, techy, bold)
- **Body**: Rajdhani (modern, clean, readable)
- **Sizes**: Responsive scaling from 0.85rem to 2.5rem

### Glassmorphism Effects

- Background: `rgba(255, 255, 255, 0.05)` with `backdrop-filter: blur(20px)`
- Border: `rgba(255, 255, 255, 0.1)` 1px solid
- Shadow: Multiple layers for depth
- Shimmer: Animated gradient overlay

## 📱 Page Flows

### Web Dashboard Flow

```
┌─────────────┐
│ Login Page  │
│  (index.html)│
└──────┬──────┘
       │
       │ [Submit Credentials]
       │
       ▼
┌─────────────┐
│  Dashboard  │
│(dashboard.html)│
└──────┬──────┘
       │
       ├──► [New Alert Received]
       │    ├── Flash Red Screen
       │    ├── Add to Alert Feed
       │    ├── Update Alert Count
       │    └── Activate Buzzer Button
       │
       ├──► [User Clicks "Turn Off Buzzer"]
       │    ├── Send POST to /api/buzzer/off
       │    ├── Animate Button (scale)
       │    └── Deactivate Buzzer State
       │
       └──► [Toggle Mute]
            └── Stop Alert Visual Effects
```



## 🎬 Animation Specifications

### Alert Flash Animation
- **Trigger**: New alert received
- **Duration**: 500ms
- **Effect**: Red overlay fades in/out
- **CSS**: `flashFade` keyframe (0.8 opacity → 0)

### Button Pulse Animation
- **Trigger**: Buzzer active state
- **Duration**: 2s loop
- **Effect**: Scale 1.0 → 1.1 → 1.0
- **CSS**: `buzzerPulse` keyframe

### Alert Slide-In Animation
- **Trigger**: New alert added to feed
- **Duration**: 500ms
- **Effect**: Slide from left (-20px) with fade
- **CSS**: `alertSlideIn` keyframe

### Button Ripple Effect
- **Trigger**: Button click
- **Duration**: 600ms
- **Effect**: Expanding circle from center
- **CSS**: Width/height transition 0 → 300px

### Shimmer Effect
- **Trigger**: Continuous on glass panels
- **Duration**: 3s loop
- **Effect**: Gradient sweep left to right
- **CSS**: `shimmer` keyframe

## 🎯 Component Specifications

### Login Page (`index.html`)

**Layout**:
- Centered glass panel (max-width: 450px)
- Logo with pulsing ring animation
- Two input fields (username, password)
- Submit button with glow effect

**Interactions**:
- Input focus: Underline animation
- Form submit: Button scale animation
- Error: Shake animation

### Dashboard Page (`dashboard.html`)

**Header**:
- App title with gradient text
- User name display
- Connection status indicator (pulsing dot)
- Logout button

**Alert Feed Section**:
- Glass panel container
- Section header with alert count badge
- Scrollable alert list (max-height: 400px)
- Each alert: Red left border, slide-in animation, shimmer effect

**Control Panel**:
- Large circular button (300px diameter)
- Gradient background (blue → light blue)
- Active state: Red gradient with pulse
- Mute toggle switch
- Button animations on click

**History Panel**:
- Collapsible section
- Scrollable list (max-height: 450px)
- Timestamped entries
- Fade-in animation for new items

## 🔌 API Endpoints

### REST Endpoints

| Method | Endpoint | Description | Request Body | Response |
|--------|----------|-------------|--------------|----------|
| POST | `/api/alert` | Receive alert from ESP32 | `{type, sensor_reading, distance}` | `{status, alert_id}` |
| POST | `/api/buzzer/off` | Turn off buzzer | None | `{status, buzzer}` |
| GET | `/api/alerts/history` | Get alert history | Query: `?limit=50` | `{alerts: [...]}` |
| GET | `/api/buzzer/status` | Get buzzer status | None | `{buzzer_active: bool}` |

### Socket.IO Events

| Event | Direction | Payload | Description |
|-------|-----------|---------|-------------|
| `connect` | Client → Server | None | Client connects |
| `disconnect` | Client → Server | None | Client disconnects |
| `connection_status` | Server → Client | `{status, buzzer_active}` | Connection confirmation |
| `new_alert` | Server → Client | `{id, type, distance, timestamp}` | New alert broadcast |
| `buzzer_off` | Server → Client | `{timestamp}` | Buzzer turned off |
| `request_history` | Client → Server | None | Request alert history |
| `alert_history` | Server → Client | `{alerts: [...]}` | Alert history response |

## 📐 Responsive Breakpoints

- **Desktop**: Default (grid: 2 columns)
- **Tablet**: 768px and below (grid: 1 column)
- **Mobile**: Optimized for 375px+ width

## 🎨 Visual Mockups Description

### Login Page
- Dark gradient background with animated stars
- Centered glass panel with blur effect
- Logo with pulsing green ring
- Input fields with animated underlines
- Blue gradient button with hover glow

### Dashboard
- Header bar with app name and status
- Full-width alert feed panel
- Two-column layout: Controls | History
- Large circular blue button (prominent)
- Alert items with red left border and flash effect

### Mobile App
- Dark background
- Header with connection status
- Scrollable alert feed
- Large circular button (70% width, centered)
- Toggle switch for mute
- Voice indicator when active

## 🔄 State Management

### Web Dashboard State
- `alerts`: Array of recent alerts
- `buzzerActive`: Boolean
- `isMuted`: Boolean
- `alertHistory`: Array of all alerts
- `connected`: Socket.IO connection status

### Mobile App State
- `alerts`: Array of alerts
- `buzzerActive`: Boolean
- `connected`: Socket.IO connection status
- `isMuted`: Boolean
- Animation refs: `flashAnim`, `pulseAnim`

## 🎯 User Experience Flow

1. **User logs in** → Smooth fade-in animation
2. **Dashboard loads** → Connection indicator shows status
3. **Alert arrives** → 
   - Red flash (web) / Red overlay (mobile)
   - Alert slides into feed
   - Buzzer button activates (pulse animation)
   - Mobile: Vibration + Voice feedback starts
4. **User sees alert** → Clear visual indication
5. **User taps "Turn Off Buzzer"** → 
   - Button animates (scale down/up)
   - Request sent to backend
   - All clients receive "buzzer_off" event
   - Voice stops (mobile)
   - Button deactivates
6. **User can mute** → Toggle stops visual/audio alerts

## 🚀 Performance Considerations

- **Animations**: Use `transform` and `opacity` for GPU acceleration
- **Socket.IO**: Automatic reconnection on disconnect
- **Alert History**: Limited to 50 items by default
- **Mobile Voice**: Stops automatically when buzzer off or muted
- **ESP32**: Cooldown period prevents alert spam (2 seconds)

---

This design system ensures a cohesive, modern, and techy user experience across all platforms!
