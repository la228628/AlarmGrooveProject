//Pictocode meteoblue and its corresponding weather icon

#ifndef PICTOCODE_H
#define PICTOCODE_H

struct pictocode
{
    int code;
    const char *description;
};

const struct pictocode pictocodes[] = {
    {1, "Sunny"},
    {2, "Sunny and few clouds"},
    {3, "Partly cloudy"},
    {4, "Overcast"},
    {5, "Fog"},
    {6, "Overcast with rain"},
    {7, "Mixed with showers"},
    {8, "Showers thunderstorms likely"},
    {9, "Overcast with snow "},
    {10, "Mixed with snow showers "},
    {11, "Mostly cloudy with snow and rain"},
    {12, "Overcast with light rain "},
    {13, "Overcast with light snow "},
    {14, "Mostly cloudy with rain  "},
    {15, "Mostly cloudy with snow "},
    {16, "Mostly cloudy with light rain"},
    {17, "Mostly cloudy with light snow "}
    
}; 

const char *getPictocodeDescription(int code)
{
    for (int i = 0; i < sizeof(pictocodes) / sizeof(pictocodes[0]); i++)
    {
        if (pictocodes[i].code == code)
        {
            return pictocodes[i].description;
        }
    }
    return "Unknown";
}


#endif // PICTOCODE_H
