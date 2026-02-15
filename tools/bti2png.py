from io import BytesIO
from gclib.bti import BTI
import logging
import argparse

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

parser = argparse.ArgumentParser(description='Convert a BTI to PNG format.')
parser.add_argument('input_bti_path', help='Input path for the BTI file')
parser.add_argument('output_image_path', help='Path to the output PNG image')
args = parser.parse_args()

try:
    bti = BTI(args.input_bti_path)
    image = bti.render()
    image.save(args.output_image_path)
    
    logging.info(f"Successfully converted BTI to PNG at {args.output_image_path}")
except Exception as e:
    logging.error(f"Failed to convert BTI: {e}")
