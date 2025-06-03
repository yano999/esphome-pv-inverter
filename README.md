# ESPHome PV Inverter

An ESPHome-based solution for monitoring and controlling photovoltaic inverters via Modbus RTU communication. This project provides comprehensive integration with Home Assistant, enabling real-time monitoring and control of solar power systems.

## 📋 Currently Supported Inverters

- **Deye SG04LP3** (Low Voltage)
- **Deye SG01HP3** (High Voltage)

## 🚀 Features

- **Real-time Monitoring**: Monitor PV production, battery status, grid consumption, and load data
- **Remote Control**: Control inverter work modes, battery charging parameters, and time-of-use settings
- **Home Assistant Integration**: Seamless integration with Home Assistant via ESPHome API
- **Safety Features**: Automatic fallback to safe operating parameters when connection to Home Assistant is lost
- **Modular Design**: Clean, maintainable code structure with separate packages for different system components
- **Multiple Inverter Support**: Supports both low voltage (SG04LP3) and high voltage (SG01HP3) Deye inverters

## 🛠️ Hardware Requirements

- **ESP Development Board** (e.g., ESP32-DevKit V1)
- **RS485 to TTL Converter**
- **PV Inverter** with Modbus RTU support
- **Connecting Cables** (for RS485 communication)

## 🔌 Wiring

Connect your ESP32-DevKit V1 to the inverter's Modbus port:

```
ESP32          RS485 Converter    Inverter
GPIO17 (TX) -> DI/A+           -> A+ (Modbus)
GPIO16 (RX) -> RO/B-           -> B- (Modbus)
3.3V        -> VCC             
GND         -> GND             -> GND (Modbus)
```

**Note**: Some RS485 converters may require a flow control pin. Uncomment and configure the `flow_control_pin` in the main configuration if needed.

## ⚙️ Installation

### 1. Prerequisites

- [ESPHome](https://esphome.io/) installed
- [Home Assistant](https://www.home-assistant.io/) (optional but recommended)
- Basic knowledge of YAML configuration

### 2. Configuration

1. **Create secrets file**:
   Create `secrets.yaml` in your ESPHome configuration directory:
   ```yaml
   wifi_ssid: "YourWiFiSSID"
   wifi_password: "YourWiFiPassword"
   deye_inverter_api_key: "your-32-character-api-key"
   deye_inverter_ota_password: "your-ota-password"
   deye_inverter_fallback_password: "your-fallback-password"
   ```

2. **Adjust configuration**:
   Edit `pv_inverter.yaml` to match your setup:
   - Set the correct Modbus address (`modbus_inverter_address`)
   - Choose the appropriate inverter variant (LV or HV)
   - Configure GPIO pins if different from defaults
   - Adjust safety parameters as needed

### 3. Flash to ESP32

Use ESPHome Builder or 

```bash
esphome run pv_inverter.yaml
```

## 🔧 Configuration Options

### Main Configuration (`pv_inverter.yaml`)

| Parameter | Description | Default |
|-----------|-------------|---------|
| `modbus_inverter_address` | Modbus address of your inverter | `0x01` |
| `safe_mode_delay` | Delay before activating safe mode when disconnected | `600s` |
| `default_maximum_battery_charge_current` | Safe charging current limit | `140A` |
| `default_max_sell_power` | Safe power export limit | `12000W` |
| `default_system_work_mode` | Safe operating mode | `"Zero Export To Load"` |
| `default_solar_sell` | Solar selling state in safe mode | `"on"` |

### Default Hardware Configuration

- **UART Pins**: GPIO17 (TX), GPIO16 (RX)
- **Baud Rate**: 19200
- **Board**: ESP32-DevKit v1 (configurable)

## 🏠 Home Assistant Integration

This project automatically integrates with Home Assistant through the ESPHome API. Once flashed and connected, you'll have access to:

### Sensors
- Solar panel voltage, current, and power
- Battery voltage, current, state of charge, and temperature
- Grid voltage, current, frequency, and power
- Load consumption
- Inverter temperature and status

### Controls
- Work mode selection (Selling First, Zero Export to Load, Zero Export to CT)
- Battery charging parameters
- Time-of-use settings
- Solar selling on/off
- Maximum power limits

### Safety Features
- Automatic transition to safe mode when Home Assistant connection is lost
- Configurable safety parameters
- Connection status monitoring

## 🔒 Safety Features

The system includes several safety mechanisms:

1. **Connection Monitoring**: Continuously monitors connection to Home Assistant
2. **Safe Mode**: Automatically applies safe operating parameters when disconnected
3. **Parameter Validation**: Ensures all settings are within safe operating ranges
4. **Fallback Hotspot**: Creates a WiFi access point for emergency access

## 🐛 Troubleshooting

### Common Issues

1. **No Communication with Inverter**:
   - Check wiring connections
   - Verify Modbus address matches inverter settings
   - Ensure correct baud rate (19200)

2. **WiFi Connection Issues**:
   - Check SSID and password in secrets.yaml
   - Verify WiFi signal strength
   - Use fallback hotspot for emergency access

3. **Home Assistant Integration Problems**:
   - Verify API key is correct
   - Check ESPHome add-on logs
   - Ensure firewall allows ESPHome traffic

### Debug Mode

Enable verbose logging by uncommenting in `pv_inverter.yaml`:
```yaml
logger:
  level: VERBOSE
```

## 📝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [Solarman Stick Logger by David Rapan](https://github.com/davidrapan/ha-solarman) and [pilipphenkel](https://github.com/philipphenkel/esphome-config) for inspirations
- [ESPHome Team](https://esphome.io/) for the excellent home automation platform
- [Home Assistant Community](https://community.home-assistant.io/) for continuous support and inspiration
- Deye inverter users who helped test and improve this integration

## 📞 Support

- **GitHub Issues**: [Report bugs or request features](https://github.com/Lewa-Reka/esphome-pv-inverter/issues)
- **Home Assistant Community**: [ESPHome section](https://community.home-assistant.io/c/esphome/)

---

**⚠️ Disclaimer**: This project is not officially affiliated with Deye. Use at your own risk and ensure compliance with local electrical codes and regulations. Always consult with a qualified electrician for installation and safety verification. 