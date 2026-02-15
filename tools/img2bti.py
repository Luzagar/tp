from gclib.bti import BTI, ImageFormat, PaletteFormat
from gclib.gx_enums import WrapMode, FilterMode
import logging
import argparse

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

parser = argparse.ArgumentParser(description='Convert an image to BTI format.')
parser.add_argument('input_image_path', help='Path to the input JPEG or PNG image')
parser.add_argument('output_bti_path', help='Output path for the BTI file')
args = parser.parse_args()

bti = BTI()

bti.mipmap_count = 1  # Set to 1 for no mipmaps, or higher for mipmaps
bti.wrap_s = WrapMode.ClampToEdge
bti.wrap_t = WrapMode.ClampToEdge
bti.min_filter = FilterMode.Linear
bti.mag_filter = FilterMode.Linear
bti.min_lod = 0
bti.max_lod = 0
bti.lod_bias = 0
bti.alpha_setting = 1  # Enable alpha if needed (depends on image and format)
bti.unknown_3 = 0

# If using a paletted format like C8, set palette properties
bti.image_format = ImageFormat.C8
bti.palette_format = PaletteFormat.RGB5A3
bti.num_colors = 256  # Up to 256 colors for C8

try:
    bti.replace_image_from_path(args.input_image_path)
    bti.save_changes()
    
    with open(args.output_bti_path, "wb") as f:
        bti.data.seek(0)
        f.write(bti.data.read())
    logging.info(f"Successfully created BTI at {args.output_bti_path}")
except Exception as e:
    logging.error(f"Failed to create BTI: {e}")
