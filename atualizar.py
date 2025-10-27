import serial
import time
import os
import re

# Caminho da porta serial do ESP32
porta_esp = '/dev/ttyACM0'
baud_rate = 115200

# Caminho completo do arquivo (usado pelo PHP)
arquivo_txt = '/opt/lampp/htdocs/airh20/nivel.txt'

# Garante que a pasta existe
os.makedirs(os.path.dirname(arquivo_txt), exist_ok=True)

# Conecta na porta serial do ESP32
print(f"Conectando ao ESP32 na porta {porta_esp}...")
ser = serial.Serial(porta_esp, baud_rate, timeout=1)
time.sleep(3)  # espera ESP32 iniciar completamente

print("✅ Conectado! Lendo dados do ESP32...")

while True:
    try:
        linha = ser.readline().decode('utf-8').strip()
        if linha:
            print(f"Recebido: {linha}")  # Mostra o mesmo que o Serial Monitor

            # Pega só o número do nível
            match = re.search(r'(\d+)', linha)
            if match:
                nivel = match.group(1)

                # Escreve no arquivo para o PHP ler
                with open(arquivo_txt, 'w') as f:
                    f.write(nivel)
                    f.flush()
                print(f"🔄 Atualizado nivel.txt -> {nivel}%")

        time.sleep(0.5)
    except Exception as e:
        print("❌ Erro:", e)
        time.sleep(2)
