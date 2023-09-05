from PIL import Image

# Load the image
image_path = "pears.png"
image = Image.open(image_path)

# Resize the image to 32x32
new_size = (20, 20)
resized_image = image.resize(new_size)

# Convert to black and white
bw_image = resized_image.convert("1")

# Generate the bit string
bit_string = ""
for y in range(new_size[1]):
    for x in range(new_size[0]):
        pixel_value = bw_image.getpixel((x, y))
        # Convert pixel value to -1 or 1
        bit = 1 if pixel_value == 0 else -1
        print(str(bit)+",", end = "")
        bit_string += str(bit)

# Print the bit string





