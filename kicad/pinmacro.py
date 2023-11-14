from decimal import *

DEFAULT_PIN_ELECTRICAL_TYPE = "unspecified"
DEFAULT_GRAPHIC_STYLE = "line"

for i in range(1, 145):
    print(f"""      (pin unspecified line (at 0 -{str(i * 254)[:-2]}.{str(i * 254)[-2:]} 0) (length 2.54)
        (name "" (effects (font (size 1.27 1.27))))
        (number "{i}" (effects (font (size 1.27 1.27))))
      )""")