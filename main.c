#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#define Do1  (523.2511306)
#define Do11 (1046.502261)
#define Re2  (587.3295358)
#define Re22 (1174.659072)
#define Mi3  (659.2551138)
#define Mi33 (1318.510228)
#define Fa4  (698.4564629)
#define Fa44 (1396.912926)
#define So5  (783.990872)
#define So55 (1567.981744)
#define La6  (880)
#define La66 (1760)
#define Si7  (987.7666025)
#define Si77 (1975.533205)



int main(){
    
 /* The wave header format varible */
    char  riff[4]={'R','I','F','F'};    // Offset 0~3   // ChunkID,      it equals to "RIFF"
    int   filelength;                   // Offset 4~7   // ChunkSize
    char  waveTag[4]={'W','A','V','E'}; // Offset 8~11  // Format,       it is a wav format
    char  fmt[4]={'f','m','t',' '};     // Offset 12~15 // fmt chunck,   subset of RIFF
    int   size=16;                      // Offset 16~19 // SubChunkSize, 16 for PCM
    short formatTag=1;                  // Offset 20~21 // AudioFormat,  1 for PCM
    short channel=2;                    // Offset 22~23 // NumChannel,   2 for Stereo
    int   sampleRate=44100;             // Offset 24~27 // SampleRate
    int   bytePerSec=176400;            // Offset 28~31 // ByteRate,     SampleRate * NumChannels * BitsPerSample/8
    short blockAlign=4;                 // Offset 32~33 // BlockAlign,   NumChannels * BitsPerSample/8
    short bitPerSample=16;              // Offset 34~35 // BitPerSample, 16 for 16 bits
    char  data[4]={'d','a','t','a'};    // Offset 36~39 // data chunck,  subset of PCM
    int   dataSize;                     // Offset 40~43 // SubChunkSize, NumSamples * NumChannels * BitsPerSample/8
    short temp;
    int   count=0;
    int   tempo=21500;                  // a beat every 0.5 seconds


   /* Write the data varible */
     double fs = 44100,Amplitude= 15000,tmp;
     short *x;
     size_t n;
     FILE *fd;
     int z=0;
    // The melody for Little Apple
     float outfreq[]={La6,La6,La6,Si7,Do11,Mi33,Re22,Do11,Si7,La6,Si7,La6,Si7,0,0,0,So5,So5,So5,La6,Si7,Re22,Do11,Si7,La6,La6,So5,La6,0,0,0,0,
                      Do11,Do11,Do11,Do11,Do11,Do11,Do11,La6,Do11,Do11,Do11,Do11,Do11,Do11,Do11,So5,So5,So5,So5,So5,So5,La6,So5,La6,La6,La6,La6,La6,La6,La6,0,0,
                      Do11,Do11,Do11,Do11,Do11,Do11,Do11,La6,Do11,Do11,Do11,Do11,Do11,Do11,Do11,So5,So5,So5,So5,So5,So5,La6,So5,La6,La6,La6,La6,La6,La6,La6,0,0,
                      La6,La6,La6,Si7,Do11,Mi33,Re22,Do11,Si7,La6,Si7,La6,Si7,Si7,0,0,So5,So5,So5,La6,Si7,Re22,Do11,Si7,La6,So5,La6,So5,La6,La6,0,0,
                      La6,La6,La6,Si7,Do11,Mi33,Re22,Do11,Si7,La6,Si7,La6,Si7,Si7,0,0,So5,So5,So5,La6,Si7,Re22,Do11,Si7,La6,So5,La6,So5,La6,La6,0,0,
                      Mi33,Mi33,Do11,Do11,Re22,Re22,La6,La6,Mi33,Re22,Do11,Re22,La6,La6,0,0,Mi33,Mi33,Do11,Do11,Re22,Re22,So55,So55,
                      So55,Mi33,Si7,Si7,Do11,Do11,Do11,Si7,La6,La6,Si7,Do11,Re22,Re22,So5,So5,So5,La66,So55,Mi33,Mi33,Mi33,Mi33,Mi33,Re22,Re22,Re22,Mi33,Mi33,Re22,Mi33,Re22,So55,
                      So55,So55,So55,So55,So55,So55,So55,So55,Mi33,Mi33,Do11,Do11,Re22,Re22,La6,La6,Mi33,Re22,Do11,Re22,La6,La6,0,0,
                      Mi33,Mi33,Do11,Do11,Re22,Re22,Re22,Re22,So55,Mi33,Si7,Si7,Do11,Do11,Do11,Si7,La6,La6,Si7,Do11,Re22,Re22,So5,So5,
                      La66,So55,Mi33,Mi33,Mi33,Mi33,Mi33,Re22,Do11,Do11,Re22,Mi33,Re22,Re22,So5,So5,La6,La6,La6,Do11,La66,La66,0,0};
    /* Storing the melody with a beat every 0.5 seconds */
    x = (short *) malloc(sizeof(short) * tempo * sizeof(outfreq)/4);
     for(z=0; z < sizeof(outfreq)/4-1; z++)
     {
         for( n = 0; n < tempo; n ++ ) {
             if(n > 44100)
             {
                tmp=0;

             }
             else
             {
                tmp = Amplitude * sin(2 * M_PI  * outfreq[z] * n /fs);

             }
             x[n + tempo*z] = (short)floor(((tmp)));
         }
     }
    
    /* Create PCM */
     fd = fopen("LittleApple.pcm", "wb");
     if( !fd )
        exit(1);
     fwrite( x, sizeof(short), tempo * sizeof(outfreq)/4,  fd);
     fclose(fd);




    /* Read the data file and get its data number */
    FILE *fpoint1 = fopen("LittleApple.pcm", "rb");
    while(1)
    {
        fread( &temp, sizeof(short), 1, fpoint1);
        if(feof(fpoint1))
            break;
        count++;
    }
    filelength = 4+(8+16)+(8+count*2);
    dataSize = count*2;
    

    /* Write the wave header */
    FILE *freal=fopen( "Littleapple.wav", "wb");
    
        fwrite( riff, sizeof(char), 4, freal);
        fwrite( &filelength, sizeof(int), 1, freal);
        fwrite( waveTag, sizeof(char), 4, freal);
        fwrite( fmt, sizeof(char), 4, freal);
        fwrite( &size, sizeof(int), 1, freal);
        fwrite( &formatTag, sizeof(short), 1, freal);
        fwrite( &channel, sizeof(short), 1, freal);
        fwrite( &sampleRate, sizeof(int), 1, freal);
        fwrite( &bytePerSec, sizeof(int), 1, freal);
        fwrite( &blockAlign, sizeof(short), 1, freal);
        fwrite( &bitPerSample, sizeof(short), 1, freal);
        fwrite( data, sizeof(char), 4, freal);
        fwrite( &dataSize, sizeof(int), 1, freal);
    printf("wave header was created\n");

    /* Write the data into freal pointer */
    count=0;
    FILE *fpoint2 = fopen( "LittleApple.pcm","rb");
    while(1)
    {
        fread( &temp, sizeof(short), 1, fpoint2);
        fwrite( &temp, sizeof(short), 1, freal);
        if(feof(fpoint2))
            break;
        count++;
    }
    
    return 0;
}
