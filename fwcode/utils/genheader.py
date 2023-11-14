import os
import re

cwdpath = os.getcwd()

headerpath = input(f"Header path (after {cwdpath}/include/): ")

with open("include/" + headerpath, "w", encoding='utf-8') as file:
    macroname = re.sub(r'\W|^(?=\d)', '_', headerpath.upper())
    macroname = f'__{macroname}__'

    file.write(f"#ifndef {macroname}\n")
    file.write(f"#define {macroname}\n\n\n")
    file.write(f"#endif  // {macroname}\n")

    file.close()
