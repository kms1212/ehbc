import os
import math
import PIL.Image as Image

FILE_HEADER_SIZE = 512
GLYPH_ADDRESS_TABLE_OFFSET = 512
GLYPH_ADDRESS_TABLE_SIZE = 1024
GLYPH_BITMAP_DESCRIPTORS_OFFSET = 2048
GLYPH_BITMAP_DESCRIPTOR_SIZE = 16

def bitmap_to_imgdata(bitmap, gwidth, gheight):
    imgdata = []
    bytesperline = math.ceil(gwidth / 8)
    for i in range(gheight):
        bitsleft = gwidth - 1
        
        for j in range(bytesperline):
            if bitsleft < 0:
                break
            k = 7
            while k >= 0 and bitsleft >= 0:
                imgdata.append(((bitmap[i * bytesperline + j] >> k) & 1) * 255)
                bitsleft -= 1
                k -= 1

    return imgdata


if __name__ == "__main__":
    print("Glyph ROM Generator")
    filename = input("Enter filename: ")

    if not os.path.exists(filename) or input("File already exists. Overwrite? (y/N) ").lower() == "y":
        print("Generating file...")
        gwidth = int(input("Enter glyph width: "))
        gheight = int(input("Enter glyph height: "))
        hoffset = int(input("Enter header offset: "))
        hlspc = int(input("Enter horizontal spacing: "))
        vlspc = int(input("Enter vertical spacing: "))

        file = open(filename, "wb")

        # Write the file header

        # Glyph name
        file.write("DEFAULT_FONT".encode("ascii"))
        file.write(b"\x00")
        file.seek(16)  # Skip the rest of the name

        # Revision number
        file.write(int(1).to_bytes(2, "big"))

        # Glyph width
        file.write(gwidth.to_bytes(1, "big"))

        # Glyph height
        file.write(gheight.to_bytes(1, "big"))

        # Glyph header offset
        file.write(hoffset.to_bytes(4, "big"))

        # Horizontal spacing
        file.write(hlspc.to_bytes(1, "big"))

        # Vertical spacing
        file.write(vlspc.to_bytes(1, "big"))

        # Calculate the bitmap size
        bitmap_size = math.ceil(math.ceil(gwidth / 8) * gheight / 16) * 16
        
        # Seek to the Glyph Bitmap Descriptors
        file.seek(GLYPH_BITMAP_DESCRIPTORS_OFFSET)

        addr_tbl = []

        # Write the Glyph Bitmap Descriptors
        for i in range(256):
            # Add the address to the address table
            addr_tbl.append(file.tell())

            # Magic number
            file.write(b"\xAA\xBB\xCC")

            # Glyph character
            file.write(i.to_bytes(1, "big"))

            file.seek(4, os.SEEK_CUR)  # Reserved bytes

            # Glyph bitmap size
            file.write(bitmap_size.to_bytes(4, "big"))

            file.write(b"\x00\x00\x00\x00")  # Reserved bytes

            # Blank bitmap
            file.write(b"\x00" * bitmap_size)

            # Seek to the next descriptor
            file.seek(GLYPH_BITMAP_DESCRIPTOR_SIZE + bitmap_size + addr_tbl[i])

        # Seek to the Glyph Address Table
        file.seek(512)

        # Write the Glyph Address Table
        for addr in addr_tbl:
            file.write(addr.to_bytes(4, "big"))

        # Pad the file to the correct size
        if input("Would you like to pad the file to larger size? (y/N) ").lower() == "y":
            size = int(input("Enter size: "))

            # Don't pad if the file is already larger than the bitmap size
            file.seek(0, os.SEEK_END)
            if file.tell() < bitmap_size: 
                print("File is already larger than the bitmap size.")
            else:
                file.seek(size - 1)
                file.write(b"\x00")

        file.close()

    file = open(filename, "rb")

    # Read the file header

    gname = file.read(16).decode("ascii").rstrip("\x00")
    rev = int.from_bytes(file.read(2), "big")
    gwidth = int.from_bytes(file.read(1), "big")
    gheight = int.from_bytes(file.read(1), "big")
    hoffset = int.from_bytes(file.read(4), "big")
    hlspc = int.from_bytes(file.read(1), "big")
    vlspc = int.from_bytes(file.read(1), "big")

    print("Glyph name: " + gname)
    print("Revision: " + str(rev))
    print("Glyph width: " + str(gwidth))
    print("Glyph height: " + str(gheight))
    print("Header offset: " + hex(hoffset))
    print("Horizontal spacing: " + str(hlspc))
    print("Vertical spacing: " + str(vlspc))

    # Seek to the Glyph Address Table
    file.seek(GLYPH_ADDRESS_TABLE_OFFSET)

    # Read the Glyph Address Table
    addr_tbl = []
    for i in range(256):
        addr_tbl.append(int.from_bytes(file.read(4), "big"))

    # Print the Glyph Address Table
    print("Glyph Address Table:")
    column = int(input("Enter number of columns(power of 2, [4]): "))
    
    if column == 0 or column & (column - 1) != 0: 
        column = 4

    print("CHAR    ADDRESS       " * column)

    for j in range(int(256 / column)):
        for i in range(column):
            print("0x" + hex(j * column + i)[2:].upper().zfill(2), end="    ")
            print("0x" + hex(addr_tbl[j * column + i])[2:].upper().zfill(8), end="    ")
        print()

    # Select a glyph to view/modify
    while True:
        print("[0-255] to select a glyph")
        print("[r] to reload the bitmap")
        print("[q] to quit")
        instr = input("Enter a selection: ")
        
        if instr == "q":
            break
        elif instr == "r":
            file.flush()
            file.close()
            file = open(filename, "rb")
        elif str(instr).isnumeric():
            glyphid = int(instr)

            if glyphid >= 0 and glyphid < 256:
                # Seek to the Glyph Bitmap Descriptor
                file.seek(addr_tbl[glyphid])

                # Read the Glyph Bitmap Descriptor
                magic = file.read(3)

                if magic != b"\xAA\xBB\xCC":
                    print("Invalid glyph magic number.")
                    continue

                # Get reserved bytes
                file.seek(5, os.SEEK_CUR)

                # Get bitmap size
                bitmap_size = int.from_bytes(file.read(4), "big")

                file.seek(addr_tbl[glyphid] + GLYPH_BITMAP_DESCRIPTOR_SIZE)

                # Read the Glyph Bitmap
                bitmap = file.read(bitmap_size)

                # Print the Glyph Bitmap
                print("Glyph Bitmap of char " + hex(glyphid) + ":")
                for i in range(16):
                    print("0x" + hex(i)[2:].upper().zfill(2), end=" ")
                print()
                print("-" * 80)

                for i in range(0, bitmap_size, 16):
                    for j in range(16):
                        print("0x" + hex(bitmap[i + j])[2:].upper().zfill(2), end=" ")
                    print()

                # draw the bitmap
                img = Image.new("1", (gwidth, gheight))

                img.putdata(bitmap_to_imgdata(bitmap, gwidth, gheight))
                img.show()

                # Modify the bitmap if desired
                if input("Would you like to modify the bitmap? (y/N) ").lower() == "y":
                    barr = bytearray(bitmap)

                    while True:
                        instr = input("(x y value) ([q] to quit): ")

                        if instr == "q":
                            break
                        else:
                            (x, y, value) = instr.split(" ")
                            x = int(x)
                            y = int(y)
                            value = int(value)
                            
                            bytesperline = math.ceil(gwidth / 8)

                            if value != 0 and value != 1:
                                print("Invalid value.")
                                continue
                            elif x < 0 or x >= gwidth or y < 0 or y >= gheight:
                                print("Invalid coordinates.")
                                continue
                            else:
                                if value == 0:
                                    barr[y * bytesperline + int(x / 8)] &= ~(1 << (7 - x % 8))
                                else:
                                    barr[y * bytesperline + int(x / 8)] |= 1 << (7 - x % 8)

                            for i in range(16):
                                print("0x" + hex(i)[2:].upper().zfill(2), end=" ")
                            print()
                            print("-" * 80)

                            for i in range(0, bitmap_size, 16):
                                for j in range(16):
                                    print("0x" + hex(barr[i + j])[2:].upper().zfill(2), end=" ")
                                print()

                    bitmap = bytes(barr)

                    with open(filename, "r+b") as wf:
                        # Write the bitmap back to the file
                        wf.seek(addr_tbl[glyphid] + GLYPH_BITMAP_DESCRIPTOR_SIZE)
                        wf.write(bitmap)

                    # Redraw the bitmap
                    img.putdata(bitmap_to_imgdata(bitmap, gwidth, gheight))
                    img.show()

    file.close()

