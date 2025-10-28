import serial
import time
import os
import re

# 🔹 Caminho da porta COM do ESP32
# Veja no Arduino IDE (em "Ferramentas" > "Porta")
porta_esp = 'COM3'   # altere se necessário, ex: 'COM4', 'COM5', etc.
baud_rate = 115200

# 🔹 Caminho completo do arquivo (usado pelo XAMPP)
arquivo_txt = r'C:\xampp\htdocs\air_h2o\nivel.txt'

# Garante que a pasta exista
os.makedirs(os.path.dirname(arquivo_txt), exist_ok=True)

print(f"Conectando ao ESP32 na porta {porta_esp}...")
try:
    ser = serial.Serial(porta_esp, baud_rate, timeout=1)
except Exception as e:
    print(f"❌ Erro ao abrir a porta {porta_esp}: {e}")
    exit()

time.sleep(3)  # Espera ESP32 iniciar completamente
print("✅ Conectado! Lendo dados do ESP32...")

while True:
    try:
        linha = ser.readline().decode('utf-8', errors='ignore').strip()
        if linha:
            print(f"📥 Recebido: {linha}")

            # Pega só o número do nível
            match = re.search(r'(\d+)', linha)
            if match:
                nivel = match.group(1)

                # Escreve no arquivo TXT
                with open(arquivo_txt, 'w') as f:
                    f.write(nivel)
                    f.flush()

                print(f"💾 Atualizado nivel.txt -> {nivel}%")

        time.sleep(0.5)

    except Exception as e:
        print(f"⚠️ Erro: {e}")
        time.sleep(2)
