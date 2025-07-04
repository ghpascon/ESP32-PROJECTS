# -*- mode: python ; coding: utf-8 -*-


a = Analysis(
    ['main.py'],
    pathex=[],
    binaries=[],
    datas=[],
    hiddenimports=['requests', 'requests.__version__', 'requests._internal_utils', 'requests.adapters', 'requests.api', 'requests.auth', 'requests.certs', 'requests.compat', 'requests.cookies', 'requests.exceptions', 'requests.help', 'requests.hooks', 'requests.models', 'requests.packages', 'requests.sessions', 'requests.status_codes', 'requests.structures', 'requests.utils', 'uvicorn.config', 'uvicorn.main', 'uvicorn.loops.auto', 'serial_asyncio'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)
pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,
    [],
    name='main',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
