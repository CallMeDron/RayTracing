from PIL import Image
import re
import glob

png_folder = 'D:\Coding\C++\RayTracing\src\images'
output_gif = 'result.gif'

png_files = sorted(
    glob.glob(png_folder + '/output_*.png'),
    key=lambda x: int(re.search(r'output_(\d+)\.png', x).group(1))
)

images = [Image.open(png) for png in png_files]

images[0].save(output_gif,
               save_all=True,
               append_images=images[1:],
               duration=50,     # время между кадрами в миллисекундах
               loop=0,          # 0 - бесконечная цикличность
               optimize=False,  # отключаем оптимизацию
               palette=None)
   
print(f"GIF успешно сохранен как {output_gif}")