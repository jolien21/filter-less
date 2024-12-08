#include "helpers.h"
#include<math.h>

void edges(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height ; i++){
    for (int j = 0; j < width; j++){
      // grijs = alle drie de kleuren dezelfde waarde. 
      //  de waarde varieerd per pixel, dus gemiddelde van de drie originele waardes
      //  nemen en dexe waarde returnen naar rood, groen, blauw.
      int gray = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) /3;
      //set de kleuren naar de waarde van grijs.
      image[i][j].rgbtRed = gray;
      image[i][j].rgbtGreen = gray;
      image[i][j].rgbtBlue = gray;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      int SepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
      int SepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
      int SepiaBlue  = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
    
      if (SepiaRed > 255){
        image[i][j].rgbtRed = 255;
      }else{
        image[i][j].rgbtRed = SepiaRed;
      }
      
      if (SepiaGreen > 255){
        image[i][j].rgbtGreen = 255;
      }else{
        image[i][j].rgbtGreen = SepiaGreen;
      }

      if (SepiaBlue > 255){
        image[i][j].rgbtBlue = 255;
      }else{
        image[i][j].rgbtBlue = SepiaBlue;
      }
    }
  }  
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  int temp; 

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width / 2; j++){
      temp = image[i][j].rgbtRed;
      image[i][j].rgbtRed = image[i][width - j].rgbtRed;
      image[i][width - j].rgbtRed = temp;

      temp = image[i][j].rgbtGreen;
      image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
      image[i][width - j].rgbtGreen = temp;
          
      temp = image[i][j].rgbtBlue;
      image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
      image[i][width - j].rgbtBlue = temp;
    }
  }  
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
/* Niet zo goed geschreven code door herhaling

     // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

  for (int i = 0; i < height; i++){  
    for (int j = 0; j < width; j++){
      
      //coordinaten
      int up = i - 1; 
      int down = i + 1;
      int r = j + 1;
      int l = j - 1;
      
      //rijen
      int firstRed, firstGreen, firstBlue; //first row
      int secondRed, secondGreen, secondBlue; //second row
      int thirdRed, thirdGreen, thirdBlue; // third row
      

      //averages red
      int averageR = round((firstRed + secondRed + thirdRed) / 9);
      int average_hoekR = round((firstRed + secondRed) / 4);
      int average_horizontaalR = round((firstRed + secondRed) / 6);
      int average_verticaalR = round((firstRed + secondRed + thirdRed) / 6);
      //average green
      int averageG = round((firstGreen + secondGreen + thirdGreen) / 9);
      int average_hoekG = round((firstGreen + secondGreen) / 4);
      int average_horizontaalG = round((firstGreen + secondGreen) / 6);
      int average_verticaalG = round((firstGreen + secondGreen + thirdGreen) / 6);
      //average blue
      int averageB = round((firstBlue + secondBlue + thirdBlue) / 9);
      int average_hoekB = round((firstBlue + secondBlue) / 4);
      int average_horizontaalB = round((firstBlue + secondBlue) / 6);
      int average_verticaalB = round((firstBlue + secondBlue + thirdBlue) / 6);
      
      if (i == 0 && j == 0){ //hoek links boven
        //red
        firstRed = copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        secondRed = copy[down][j].rgbtRed + copy[down][r].rgbtRed;
        //Green
        firstGreen = copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        secondGreen = copy[down][j].rgbtGreen + copy[down][r].rgbtGreen;
        //Blue
        firstBlue = copy[i][j].rgbtRed + copy[i][r].rgbtBlue;
        secondBlue = copy[down][j].rgbtBlue + copy[down][r].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = average_hoekR;
        image[i][j].rgbtGreen = average_hoekG;
        image[i][j].rgbtBlue = average_hoekB;
      
      }else if(i == 0 && j == width){ //hoek rechts boven
        //red
        firstRed = copy[i][j].rgbtRed + copy[i][l].rgbtRed;
        secondRed = copy[down][j].rgbtRed + copy[down][l].rgbtRed;
        //Green
        firstGreen = copy[i][j].rgbtGreen + copy[i][l].rgbtGreen;
        secondGreen = copy[down][j].rgbtGreen + copy[down][l].rgbtGreen;
        //Blue
        firstBlue = copy[i][j].rgbtBlue + copy[i][l].rgbtBlue;
        secondBlue = copy[down][j].rgbtBlue + copy[down][l].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = average_hoekR;
        image[i][j].rgbtGreen = average_hoekG;
        image[i][j].rgbtBlue = average_hoekB;
      
      }else if(i == height && j == 0){ //hoek links onder
        //Red 
        firstRed = copy[up][j].rgbtRed + copy[up][r].rgbtRed;
        secondRed = copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        //Green
        firstGreen = copy[up][j].rgbtGreen + copy[up][r].rgbtGreen;
        secondGreen = copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        //Blue
        firstBlue = copy[up][j].rgbtBlue + copy[up][r].rgbtBlue;
        secondBlue = copy[i][j].rgbtBlue + copy[i][r].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = average_hoekR;
        image[i][j].rgbtGreen = average_hoekG;
        image[i][j].rgbtBlue = average_hoekB;
      }

      else if(i == height && j == width){ //hoek rechts onder
        //Red
        firstRed = copy[up][l].rgbtRed + copy[up][j].rgbtRed;
        secondRed = copy[i][l].rgbtRed + copy[i][j].rgbtRed;
        //Green
        firstRed = copy[up][l].rgbtGreen + copy[up][j].rgbtGreen;
        secondRed = copy[i][l].rgbtGreen + copy[i][j].rgbtGreen;
        //Blue
        firstBlue = copy[up][l].rgbtBlue + copy[up][j].rgbtBlue;
        secondBlue = copy[i][l].rgbtBlue + copy[i][j].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = average_hoekR;
        image[i][j].rgbtGreen = average_hoekG;
        image[i][j].rgbtBlue = average_hoekB;
      
      }else if(i == 0){ //bovenste rij van de afbeelding
        //Red
        firstRed = copy[i][l].rgbtRed + copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        secondRed = copy[down][l].rgbtRed + copy[down][i].rgbtRed + copy[down][r].rgbtRed;
        //Green
        firstGreen = copy[i][l].rgbtGreen + copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        secondGreen = copy[down][l].rgbtGreen + copy[down][i].rgbtGreen + copy[down][r].rgbtGreen;
        //Blue
        firstBlue = copy[i][l].rgbtBlue + copy[i][j].rgbtBlue + copy[i][r].rgbtBlue;
        secondBlue = copy[down][l].rgbtBlue + copy[down][i].rgbtBlue + copy[down][r].rgbtBlue;
       
        //pixels overzetten
        image[i][j].rgbtRed = average_horizontaalR;
        image[i][j].rgbtGreen = average_horizontaalG;
        image[i][j].rgbtBlue = average_horizontaalB;

      }else if (i == height){ //onderste rij van de afbeelding
        //Red
        firstRed = copy[up][l].rgbtRed + copy[up][j].rgbtRed + copy[up][r].rgbtRed;
        secondRed = copy[i][l].rgbtRed + copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        //Green
        firstGreen = copy[up][l].rgbtGreen + copy[up][j].rgbtGreen + copy[up][r].rgbtGreen;
        secondGreen = copy[i][l].rgbtGreen + copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        //Blue
        firstBlue = copy[up][l].rgbtBlue + copy[up][j].rgbtBlue + copy[up][r].rgbtBlue;
        secondBlue = copy[i][l].rgbtBlue + copy[i][j].rgbtBlue + copy[i][r].rgbtBlue;

        //pixels overzetten
        image[i][j].rgbtRed = average_horizontaalR;
        image[i][j].rgbtGreen = average_horizontaalG;
        image[i][j].rgbtBlue = average_horizontaalB;


      }else if(j == 0){ // linker kolom vn de afbeelding
        //Red
        firstRed = copy[up][j].rgbtRed + copy[up][r].rgbtRed;
        secondRed = copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        thirdRed = copy[down][j].rgbtRed + copy[down][r].rgbtRed;
        //Green
        firstGreen = copy[up][j].rgbtGreen + copy[up][r].rgbtGreen;
        secondGreen = copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        thirdGreen = copy[down][j].rgbtGreen + copy[down][r].rgbtGreen;
        //Blue
        firstBlue = copy[up][j].rgbtBlue + copy[up][r].rgbtBlue;
        secondBlue = copy[i][j].rgbtBlue + copy[i][r].rgbtBlue;
        thirdBlue = copy[down][j].rgbtBlue + copy[down][r].rgbtBlue;
       
        //pixels overzetten
        image[i][j].rgbtRed = average_verticaalR;
        image[i][j].rgbtGreen = average_verticaalG;
        image[i][j].rgbtBlue = average_verticaalB;

      }else if (j == width){ //rechter kolom van de afbeelding
        //Red
        firstRed = copy[up][l].rgbtRed + copy[up][j].rgbtRed;
        secondRed = copy[i][l].rgbtRed + copy[i][j].rgbtRed;
        thirdRed = copy[down][l].rgbtRed + copy[down][j].rgbtRed;
        //Green
        firstGreen = copy[up][l].rgbtGreen + copy[up][j].rgbtGreen;
        secondGreen = copy[i][l].rgbtGreen + copy[i][j].rgbtGreen;
        thirdGreen = copy[down][l].rgbtGreen + copy[down][j].rgbtGreen;
        //Blue
        firstBlue = copy[up][l].rgbtBlue + copy[up][j].rgbtBlue;
        secondBlue = copy[i][l].rgbtBlue + copy[i][j].rgbtBlue;
        thirdBlue = copy[down][l].rgbtBlue + copy[down][j].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = average_verticaalR;
        image[i][j].rgbtGreen = average_verticaalG;
        image[i][j].rgbtBlue = average_verticaalB;

      }else{ //rest van de afbeelding
        //Blue
        firstRed = copy[up][l].rgbtRed + copy[up][r].rgbtRed + copy[up][i].rgbtRed;  
        secondRed = copy[i][l].rgbtRed + copy[i][j].rgbtRed + copy[i][r].rgbtRed;
        thirdRed = copy[down][l].rgbtRed + copy[up][j].rgbtRed + copy[down][r].rgbtRed;
        //Green
        firstGreen = copy[up][l].rgbtGreen + copy[up][r].rgbtGreen + copy[up][i].rgbtGreen;  
        secondGreen = copy[i][l].rgbtGreen + copy[i][j].rgbtGreen + copy[i][r].rgbtGreen;
        thirdGreen = copy[down][l].rgbtGreen + copy[up][j].rgbtGreen + copy[down][r].rgbtGreen;
        //Blue
        firstBlue = copy[up][l].rgbtBlue + copy[up][r].rgbtBlue + copy[up][i].rgbtBlue;  
        secondBlue = copy[i][l].rgbtBlue + copy[i][j].rgbtBlue + copy[i][r].rgbtBlue;
        thirdBlue = copy[down][l].rgbtBlue + copy[up][j].rgbtBlue + copy[down][r].rgbtBlue;
        
        //pixels overzetten
        image[i][j].rgbtRed = averageR;
        image[i][j].rgbtGreen = averageG;
        image[i][j].rgbtBlue = averageB;
      }
    }
  }
return;*/

  // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

  // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise values
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;

        // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }
            // Get average and blur image
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }
                        // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
