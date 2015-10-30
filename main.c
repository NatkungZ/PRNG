// C99 Complementary Multiply With Carry generator
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CMWC working parts
#define CMWC_CYCLE 4096 // as Marsaglia recommends
#define CMWC_C_MAX 809430660 // as Marsaglia recommends
static uint32_t Q[CMWC_CYCLE];
static uint32_t c = 362436; // must be limited with CMWC_C_MAX (we will reinit it with seed)

// Make 32 bit random number (some systems use 16 bit RAND_MAX)
uint32_t rand32(void)
{
    uint32_t result = 0;
    result = rand();
    result <<= 16;
    result |= rand();
    return result;
}

// Init all engine parts with seed
void initCMWC(unsigned int seed)
{
    srand(seed);
    for (int i = 0; i < CMWC_CYCLE; i++) Q[i] = rand32();
    do c = rand32(); while (c >= CMWC_C_MAX);
}

// CMWC engine
uint32_t randCMWC(void)
{
    //uint32 max value is  4,294,967,295
    //uint32 min value is  0
    static uint32_t i = CMWC_CYCLE - 1;
    uint64_t t = 0;
    uint64_t a = 18782; // as Marsaglia recommends
    uint32_t r = 0xfffffffe; // as Marsaglia recommends
    uint32_t x = 0;

    i = (i + 1) & (CMWC_CYCLE - 1);
    t = a * Q[i] + c;
    c = t >> 32;
    x = t + c;
    if (x < c)
    {
        x++;
        c++;
    }

    return Q[i] = r - x;
}

int main()
{
    FILE *f = fopen("file.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    unsigned int seed = time(NULL);
    initCMWC(seed);
    uint32_t min = 4294967295;
    uint32_t max = 0;
    uint32_t rgen = 0;
    int freq[] = {0,0,0,0,0,0,0,0,0,0};
    uint32_t length[] = {0,429496730,858993459,1288490189,1717986918,2147483648,2576980377,3006477107,3435973836,3865470566,4294967295};

    for (int i = 0; i < 1000000000; ++i)
    {   
        rgen = randCMWC();
        if(rgen < min){
            min = rgen;
        }
        if (rgen > max)
        {
            max = rgen;
        }
        
        if (rgen < 429496730)
        {
            freq[0] += 1; 
        }else if (rgen < 858993459)
        {
            freq[1] += 1;
        }else if (rgen < 1288490189)
        {
            freq[2] += 1;
        }else if (rgen < 1717986918)
        {
            freq[3] += 1;
        }else if (rgen < 2147483648)
        {
            freq[4] += 1;
        }else if (rgen < 2576980377)
        {
            freq[5] += 1;
        }else if (rgen < 3006477107)
        {
            freq[6] += 1;
        }else if (rgen < 3435973836)
        {
            freq[7] += 1;
        }else if (rgen < 3865470566)
        {
            freq[8] += 1;
        }else 
        {
            freq[9] += 1;
        }
        //printf("Random CMWC: %u\n", randCMWC());
        //fprintf(f,"%u\n", randCMWC());
    }
    fprintf(f,"min %u\nmax %u\n",min,max );
    for (int i = 0; i < 10; ++i)
    {
        fprintf(f,"Length %u - %u freq is %d\n",length[i],length[i+1] ,freq[i]);
    }
    

}