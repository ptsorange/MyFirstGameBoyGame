from PIL import Image

img = Image.open(input())
rgb_img = img.convert('RGB')
width, height = rgb_img.size

tile_data = []

name=input()

if width == 16:
    for i in range(4):
        for y in range(8):
            low_byte = 0
            high_byte = 0
            for x in range(8):
                px, py = x + (i % 2 * 8), y + (i // 2 * 8)
                r, g, b = rgb_img.getpixel((px, py))
                
                brightness = (r + g + b) // 3
                if brightness > 200:
                    color = 0  # White
                elif brightness > 120:
                    color = 1  # Light Gray
                elif brightness > 60:
                    color = 2  # Dark Gray
                else:
                    color = 3  # Black
                if color & 0x01:
                    low_byte |= (1 << (7 - x))
                if color & 0x02:
                    high_byte |= (1 << (7 - x))
            
            tile_data.append(low_byte)
            tile_data.append(high_byte)

print(f"// Image size: {width}x{height}")
print("const unsigned char "+name+"[] = {")
for idx, val in enumerate(tile_data):
    end_char = ",\n" if (idx + 1) % 16 == 0 else ","
    print(f"{hex(val)}", end=end_char)
print("};")