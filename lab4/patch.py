import os


code = (
    b'\x08\x84\xC0\x74\x72',
    b'\x08\x84\xC0\x75\x72',
)

for entry in os.listdir('.'):
    try:
        if not os.path.isdir(entry):
            continue
        with open(f'{entry}/LabReverse.exe', 'rb+') as file:
            data = file.read()
            c = data.count(code[0])
            if c < 0:
                print(f'{entry}: not found')
            elif c > 1:
                print(f'{entry}: multiple matches')
            else:
                print(f'{entry}: successfully')
                data.replace(code[0], code[1])
                file.seek(0)
                file.write(data)
                file.truncate()
    except Exception as e:
        print(f'{entry}: {e}')
