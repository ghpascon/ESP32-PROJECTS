import os

import PyInstaller.__main__
from PyInstaller.utils.hooks import collect_all, collect_submodules

# === CONFIGURAÇÕES DO USUÁRIO ===
ENTRY_SCRIPT = "main.py"  # Script principal
APP_NAME = "main"  # Nome do executável final
EXTRA_FOLDERS = ["app"]  # Pastas adicionais para incluir no build

# === Hidden imports adicionais ===
manual_hidden = [
    "uvicorn.config",
    "uvicorn.main",
    "uvicorn.loops.auto",
]

# Inclui todos os submódulos do serial_asyncio manualmente
try:
    serial_asyncio_hidden = collect_submodules("serial_asyncio")
    print(f"[INFO] Found serial_asyncio submodules: {serial_asyncio_hidden}")
except Exception as e:
    print(f"[WARN] Could not collect serial_asyncio submodules: {e}")
    serial_asyncio_hidden = []


# === Funções auxiliares ===
def read_requirements(file_path="requirements.txt"):
    with open(file_path, "r") as f:
        return [
            line.strip().split("==")[0]
            for line in f
            if line.strip() and not line.startswith("#")
        ]


def collect_all_from_packages(packages):
    datas, binaries, hiddenimports = [], [], []
    for pkg in packages:
        try:
            d, b, h = collect_all(pkg)
            datas += d
            binaries += b
            hiddenimports += h
        except Exception as e:
            print(f"[WARN] Falha ao coletar '{pkg}': {e}")
            exit()
    return datas, binaries, hiddenimports


# === Lê pacotes do requirements.txt ===
packages = read_requirements()
datas, binaries, hiddenimports = collect_all_from_packages(packages)

# === Adiciona pastas extras como dados ===
extra_data = [
    f"{folder}{os.sep};{folder}" for folder in EXTRA_FOLDERS if os.path.exists(folder)
]

# === Executa o PyInstaller ===
PyInstaller.__main__.run(
    [ENTRY_SCRIPT, f"--name={APP_NAME}", "--onefile", "--console"]
    + [
        f"--hidden-import={h}"
        for h in hiddenimports + manual_hidden + serial_asyncio_hidden
    ]
    + [f"--add-data={d}" for d in extra_data]
)
