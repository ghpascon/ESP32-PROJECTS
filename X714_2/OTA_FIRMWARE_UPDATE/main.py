import requests
import os
import glob

ESP32_IP = "192.168.4.1" # Mantenha o IP do seu ESP32 aqui

UPLOAD_URL = f"http://{ESP32_IP}/update_firmware"

# AUTH_USERNAME = "admin" # Descomente e defina se usa autenticação no ESP32
# AUTH_PASSWORD = "suasenhaota" # Descomente e defina se usa autenticação no ESP32

def find_firmware_path():
    # Obtém o diretório onde o script 'main.py' está sendo executado (G:)
    project_root = os.getcwd()
    
    # Caminho para a pasta 'bin' dentro do diretório raiz do projeto
    bin_dir = os.path.join(project_root, "bin")

    print(f"Procurando arquivo .ino.bin na pasta: {bin_dir}")

    if not os.path.isdir(bin_dir):
        print(f"Erro: Pasta 'bin' não encontrada em '{project_root}'.")
        return None

    # Procura por arquivos que terminam com '.ino.bin' diretamente dentro da pasta 'bin'
    firmware_files = glob.glob(os.path.join(bin_dir, "*.ino.bin"))
    
    if firmware_files:
        # Retorna o primeiro arquivo .ino.bin encontrado
        print(f"Arquivo .ino.bin encontrado: {firmware_files[0]}")
        return firmware_files[0]
    
    print(f"Nenhum arquivo .ino.bin encontrado na pasta '{bin_dir}'.")
    return None

def upload_firmware():
    firmware_path = find_firmware_path()

    if not firmware_path:
        print("Não foi possível encontrar o arquivo de firmware. Abortando o upload.")
        return

    print(f"Tentando enviar firmware para: {UPLOAD_URL}")

    try:
        with open(firmware_path, 'rb') as f:
            files = {'update': f}

            auth_params = None
            # Descomente para usar autenticação:
            # if 'AUTH_USERNAME' in globals() and 'AUTH_PASSWORD' in globals():
            #     auth_params = (AUTH_USERNAME, AUTH_PASSWORD)
            #     print(f"Usando autenticação para o upload: {AUTH_USERNAME}")

            response = requests.post(UPLOAD_URL, files=files, timeout=60)

            if response.status_code == 200:
                print("\n--- Upload Concluído Com Sucesso! ---")
                print(f"Mensagem do ESP32: {response.text}")
                print("O ESP32-S3 deve reiniciar em breve com o novo firmware.")
            else:
                print(f"\n--- Erro no Upload! ---")
                print(f"Status HTTP: {response.status_code}")
                print(f"Mensagem do ESP32: {response.text}")

    except requests.exceptions.ConnectionError:
        print(f"\nErro de Conexão: Não foi possível conectar ao ESP32 no IP {ESP32_IP}.")
        print("Verifique se o ESP32 está ligado, conectado à rede e se o IP está correto.")
        print("Também, verifique se seu computador está na mesma rede que o ESP32.")
    except requests.exceptions.Timeout:
        print(f"\nErro de Tempo Limite: A requisição demorou muito para responder. ({UPLOAD_URL})")
        print("Isso pode acontecer com arquivos grandes ou conexões instáveis.")
    except Exception as e:
        print(f"\nOcorreu um erro inesperado: {e}")

if __name__ == "__main__":
    upload_firmware()