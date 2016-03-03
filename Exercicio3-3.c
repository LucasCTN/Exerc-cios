#include <stdint.h>
#include <stdio.h>

typedef struct
{
    float temperature;
    uint8_t wind_velocity;
    uint8_t humidity;
}Log_Entry_T;

typedef struct
{
    uint8_t raw_entry[6];
}Packet_T;

void print8bits(uint8_t data)
{
    int8_t i;
    
    for(i = 7; i >= 0; i--)
    printf("%u ", data&(1 << i) ? 1 : 0);//Seleciona bit a bit e imprime apenas esse bit usando o ?
    printf("\n");
}

void print32bits(uint32_t data)
{
    int32_t i;
    
    for(i = 31; i >= 0; i--)
    printf("%u ", data&((int32_t)1 << i) ? 1 : 0);//Seleciona bit a bit e imprime apenas esse bit usando o ?
    printf("\n");
}

void fill_hardcoded (Log_Entry_T* leitura, Packet_T* pacote)
{
    uint32_t temperatura_raw = (*leitura).temperature;
    
    uint32_t primeiro = 1, segundo = 0, terceiro = 0, quarto = 0;
    
    for(uint8_t i = 0; i < 31; i++)
    {
        primeiro = primeiro << 1;
        segundo = segundo << 1;
        terceiro = terceiro << 1;
        quarto = quarto << 1;
        
        if(i < 7)
            primeiro = (primeiro | 1);
        else if(i >= 7 && i < 15)
            segundo = (segundo | 1);
    }
    
    uint32_t parte1 = (primeiro & temperatura_raw);
    uint8_t parte1_8 = parte1 >> 24;
    
    uint32_t parte2 = (segundo & temperatura_raw);
    //uint8_t parte2_8 = parte2 >> 16;
    
    printf("Original: \n");
    print32bits(temperatura_raw);
    printf("Parte2: \n");
    print32bits(segundo);
    
    (*pacote).raw_entry[4] = (*leitura).wind_velocity;
    (*pacote).raw_entry[5] = (*leitura).humidity;
}

void main()
{
    Log_Entry_T leitura;
    leitura.temperature = 429496700.0;
    leitura.wind_velocity = 17;
    leitura.humidity = 5;
    
    Packet_T pacote;
    
    fill_hardcoded(&leitura, &pacote);
    
    printf("%d \n", sizeof(float));
}
