from pathlib import Path


code = (
    b'\x08\x84\xC0\x74\x72',
    b'\x08\x84\xC0\x00\x00',
)


c = {
    '': '\033[0m',
    'r': '\033[31;1m',
    'g': '\033[32;1m',
}

for entry in Path('.').glob('*'):
    try:
        if not entry.is_dir():
            continue
        with open(entry / 'LabReverse.exe', 'rb+') as file:
            data = file.read()
            n = data.count(code[0])
            if n < 1:
                print(f'{entry}: {c["r"]}not found{c[""]}')
            elif n > 1:
                print(f'{entry}: {c["r"]}multiple matches{c[""]}')
            else:
                data = data.replace(code[0], code[1])
                file.seek(0)
                file.write(data)
                file.truncate()
                print(f'{entry}: {c["g"]}successfully{c[""]}')
    except Exception as e:
        print(f'{entry}: {e}')
