import requests
import os
import glob
import json
import platform
import subprocess

CONFIG_PATH = "config.json"

def load_config():
    if not os.path.exists(CONFIG_PATH):
        raise FileNotFoundError(f"Arquivo de configuração '{CONFIG_PATH}' não encontrado.")
    
    with open(CONFIG_PATH, "r") as f:
        config = json.load(f)

    if "ip" not in config or "firmware" not in config:
        raise ValueError("Arquivo de configuração deve conter as chaves 'ip' e 'firmware'.")
    
    return config["ip"], config["firmware"]

def find_bin_file(suffix):
    project_root = os.getcwd()
    bin_dir = os.path.join(project_root, "bin")

    print(f"Procurando arquivo com sufixo '{suffix}' na pasta: {bin_dir}")

    if not os.path.isdir(bin_dir):
        print(f"Erro: Pasta 'bin' não encontrada em '{project_root}'.")
        return None

    bin_files = glob.glob(os.path.join(bin_dir, f"*{suffix}"))
    if bin_files:
        print(f"Arquivo encontrado: {bin_files[0]}")
        return bin_files[0]

    print(f"Nenhum arquivo '{suffix}' encontrado na pasta '{bin_dir}'.")
    return None

def upload_file(file_path, url, file_key="update", label="arquivo"):
    print(f"\nIniciando upload do {label} para: {url}")

    try:
        with open(file_path, 'rb') as f:
            files = {file_key: f}
            response = requests.post(url, files=files, timeout=60)

            if response.status_code == 200:
                print(f"\n--- Upload do {label} concluído com sucesso! ---")
                print(f"Resposta do ESP32: {response.text}")
            else:
                print(f"\n--- Erro no upload do {label}! ---")
                print(f"Status HTTP: {response.status_code}")
                print(f"Resposta do ESP32: {response.text}")
    except requests.exceptions.ConnectionError:
        print(f"\nErro de conexão ao tentar acessar: {url}")
        print("Verifique se o ESP32 está ligado e acessível na rede.")
    except requests.exceptions.Timeout:
        print(f"\nErro: Tempo limite excedido ao enviar para: {url}")
    except Exception as e:
        print(f"\nErro inesperado ao enviar {label}: {e}")

def ping_device(ip):
    print(f"Verificando conectividade com {ip}...")
    param = "-n" if platform.system().lower() == "windows" else "-c"
    command = ["ping", param, "1", ip]
    
    try:
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            print("Dispositivo alcançável ✅")
            return True
        else:
            print("Não foi possível alcançar o dispositivo ❌")
            return False
    except Exception as e:
        print(f"Erro ao executar ping: {e}")
        return False

def main():
    try:
        ip, firmware_mode = load_config()
    except Exception as e:
        print(f"Erro ao carregar configuração: {e}")
        return

    if not ping_device(ip):
        print("Abortando upload devido à falha de conectividade.")
        return

    firmware_url = f"http://{ip}/update_firmware"
    fs_url = f"http://{ip}/update_fs"

    if firmware_mode:
        firmware_path = find_bin_file(".ino.bin")
        if firmware_path:
            upload_file(firmware_path, firmware_url, label="firmware")
        else:
            print("Arquivo de firmware não encontrado. Upload abortado.")
    else:
        fs_path = find_bin_file(".littlefs.bin")
        if fs_path:
            upload_file(fs_path, fs_url, label="sistema de arquivos (LittleFS)")
        else:
            print("Arquivo do sistema de arquivos não encontrado. Upload abortado.")

if __name__ == "__main__":
    main()
