#include <gluten/Png.h>

//#define PNG_ONLY

#ifdef PNG_ONLY
  #include "lodepng.h"
#else
  //#define STB_IMAGE_IMPLEMENTATION           
  #include "stb_image.h"
#endif

#include <iostream>

namespace Gluten
{
  Png::Png(string path)
  {
    unsigned char* data = NULL;
    powerWidth = 0;
    powerHeight = 0;

#ifdef PNG_ONLY
    if(lodepng_decode32_file(&data, &width, &height, path.c_str()))
    {
      throw Exception("File '" + path + "' failed to load");
    }
#else
    int n = 0;
    int x = 0;
    int y = 0;

    //std::cout << "Loading: " << path << std::endl;

    data = stbi_load(path.c_str(), &x, &y, &n, 4);

    if(!data)
    {
      throw Exception("File '" + path + "' failed to load");
    }

    width = x;
    height = y;
#endif

//////////////////////////////////////////////////////////////////////////////////////

  // Width power block
  if(width > 1)
  {
    powerWidth = 2;
  }
  if(width > 2)
  {
    powerWidth = 4;
  }
  if(width > 4)
  {
    powerWidth = 8;
  }
  if(width > 8)
  {
    powerWidth = 16;
  }
  if(width > 16)
  {
    powerWidth = 32;
  }
  if(width > 32)
  {
    powerWidth = 64;
  }
  if(width > 64)
  {
    powerWidth = 128;
  }
  if(width > 128)
  {
    powerWidth = 256;
  }
  if(width > 256)
  {
    powerWidth = 512;
  }
  if(width > 512)
  {
    powerWidth = 1024;
  }
  if(width > 1024)
  {
    powerWidth = 2048;
  }

  // Height power block
  if(height > 1)
  {
    powerHeight = 2;
  }
  if(height > 2)
  {
    powerHeight = 4;
  }
  if(height > 4)
  {
    powerHeight = 8;
  }
  if(height > 8)
  {
    powerHeight = 16;
  }
  if(height > 16)
  {
    powerHeight = 32;
  }
  if(height > 32)
  {
    powerHeight = 64;
  }
  if(height > 64)
  {
    powerHeight = 128;
  }
  if(height > 128)
  {
    powerHeight = 256;
  }
    if(height > 256)
  {
    powerHeight = 512;
  }
  if(height > 512)
  {
    powerHeight = 1024;
  }
  if(height > 1024)
  {
    powerHeight = 2048;
  }

  powerData.resize(powerWidth*powerHeight*4);

  for(int x = 0; x < powerWidth*powerHeight*4; x++)
  {      
    powerData[x] = 0;
  }

  int amount = 0;
  int offset = 0;

  int t = width * height * 4;
  t-=1;

  unsigned char *tmp = (unsigned char*)malloc(width * height * 4 * sizeof(unsigned char));
  memcpy(tmp, data, width * height * 4 * sizeof(unsigned char));

  for(int x = 0; x < width*height*4; x+=4)
  {
    data[x+3] = tmp[t]; t--;
    data[x+2] = tmp[t]; t--;
    data[x+1] = tmp[t]; t--;
    data[x] = tmp[t]; t--;
  }

  free(tmp);

  for(int x = 0; x < width*height*4; x++)
  {
    powerData[x+offset] = data[x];
    amount++;

    if(amount >= width*4)
    {
      offset+= (powerWidth-width)*4;
      //offset+= (512-width)*4;
      amount = 0;
    }
  }


#ifdef PNG_ONLY
  free(data);
#else
  stbi_image_free(data);
#endif
}

  int Png::getWidth()
  {
    //return width;
  return powerWidth;
    //return 512;
  }

  int Png::getHeight()
  {
    //return height; // 
  return powerHeight;
    //return 512;
  }

  int Png::getOffsetX()
  {
    return powerWidth - width;
  //return 512 - width;
  }

  int Png::getOffsetY()
  {
    return powerHeight - height;
  //return 512 - height;
  }

  unsigned char* Png::getData()
  {
    //return data;
    return &powerData[0];
  }
}
