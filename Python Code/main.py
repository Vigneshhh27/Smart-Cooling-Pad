import serial
import time
import subprocess

# === Serial Config ===
PORT = 'COM5'         # Update this to your ESP32 port
BAUD_RATE = 115200
SEND_INTERVAL = 2     # Seconds

# Connect to ESP32
try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    print(f"✅ Connected to {PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"❌ Could not open {PORT}: {e}")
    exit()

# Function to get GPU temperature using nvidia-smi
def get_gpu_temp():
    try:
        output = subprocess.check_output(
            ["nvidia-smi", "--query-gpu=temperature.gpu", "--format=csv,noheader,nounits"],
            encoding='utf-8'
        )
        return float(output.strip())  # e.g., 62.0
    except Exception as e:
        print(f"⚠️ Could not read GPU temp: {e}")
        return 55.0  # fallback value

# Main loop
while True:
    temp = get_gpu_temp()
    try:
        ser.write(f"{temp:.2f}\n".encode())
        print(f"📤 Sent GPU temp: {temp:.2f} °C")
    except Exception as e:
        print(f"❌ Error sending temperature: {e}")
    time.sleep(SEND_INTERVAL)
