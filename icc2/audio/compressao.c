/*******************************************************************************
 |                       USP - Universidade de São Paulo                       |
 |            ICMC - Instituto de Ciências Matemáticas e de Computação         |
 *******************************************************************************
 |                    Bacharelado em Ciências de Computação                    |
 |                                 2021/2                                      |
 |                 SCC0201 - Introdução à Ciências da Computação 2             |
 |                                                                             |
 |             Autor: Victor Lucas de Almeida Fernandes (12675399)             |
 *******************************************************************************
 >                           Compressão de Áudio
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

#define WAV_HEADER_SIZE 44

char *read_str();
unsigned char *read_wav_data(char* fname, int *dataSize);
double complex *DFT(unsigned char *audio, int length);
unsigned char *i_DFT(double complex *coef, int dataSize);
void merge_sort(double complex *array, int start, int end);
void create_compressed(char *fname, unsigned char *audio, int data_size);

int main() {

    // reading data
    char *fname = read_str();
    int amt_significant_coef;
    scanf("%d\n", &amt_significant_coef);
    int data_size;
    unsigned char *wav_data = read_wav_data(fname, &data_size);

    // using wav_data to create a double complex array by using DFT
    double complex *coef_array = DFT(wav_data, data_size);
    // copying the result to an auxiliar array
    double complex *coef_copy = malloc(data_size * sizeof(double complex));
    memcpy(coef_copy, coef_array, data_size * sizeof(double complex));

    // sorting in descending order
    merge_sort(coef_array, 0, data_size - 1);

    // keeping the value of the last position that must be saved
    double limit = cabs(coef_array[amt_significant_coef - 1]);

    // cleaning the values smaller than the limit and counting how many
    // are negative
    int negative_coef_counter = 0;
    for (int i = 0; i < data_size; i++) {
        if (cabs(coef_copy[i]) < limit)
            coef_copy[i] = 0.0;
        if (creal(coef_array[i]) <= 0.0 && cimag(coef_array[i]) <= 0.0) 
            negative_coef_counter++;
    }       
    
    // using the inverse DFT to get wav data from double complex 
    // coefficients and saving it on a file
    unsigned char *audio = i_DFT(coef_copy, data_size);
    create_compressed(fname, audio, data_size);
        
    // printing output        
    printf("%d\r\n", data_size);    
    printf("%d\r\n", negative_coef_counter);  
    for (int i = 0; i < amt_significant_coef - 1; i++) 
        printf("%d\r\n", (int)cabs(coef_array[i]));  
    printf("%d", (int)cabs(coef_array[amt_significant_coef - 1]));  

    // deallocating memory
    free(fname);
    free(wav_data);
    free(coef_array);
    free(coef_copy);
    free(audio);
    return 0;
}

char *read_str() {
    char *str = malloc(sizeof(char));
    int char_counter = 0;
    char c;
    while ((c = getchar()) != '\r') {
        str[char_counter] = c;
        char_counter++;
        str = realloc(str, char_counter + 1);
    }
    getchar();
    str[char_counter] = '\0';
    return str;
}

unsigned char* read_wav_data(char* fname, int *dataSize) {

    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    *dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (*dataSize));
    
    int i = 0;
    while (i < *dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}

double complex *DFT(unsigned char *audio, int length) {

    double complex *coef = calloc(length, sizeof(double complex));
    
    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k] += 
                audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) 
                / 
                (length * 1.0))) * _Complex_I);
        }
    }
    
    return coef;
}

unsigned char *i_DFT(double complex *coef, int dataSize) {

    unsigned char *audio = malloc(sizeof(unsigned char) * (dataSize));
    double complex aux = 0.0;

    int n, k;
    for (n = 0; n < dataSize; n++) {
        for (k = 0; k < dataSize; k++) {
            aux += 
                coef[k] * cexp((2.0 * M_PI * (((k+1) * n * 1.0) 
                / 
                (dataSize * 1.0))) * _Complex_I);
        }
        aux *= (double complex)(1.0 / dataSize);
        audio[n] = creal(aux);
        aux = 0.0;
    }
    
    return audio;
}

void merge_sort(double complex *array, int start, int end) {
    
    if (start >= end) return;

    int center = (int) (start + end) / 2.0;

    merge_sort(array, start, center); 
    merge_sort(array, center + 1, end); 
    
    double complex *aux_array = malloc((end - start + 1) * sizeof(double complex));

    int i = start; 
    int j = center + 1; 
    int k = 0; 

    while (i <= center && j <= end) {
        if (cabs(array[i]) >= cabs(array[j])) {
            aux_array[k] = array[i];
            i++;
        }
        else {
            aux_array[k] = array[j];
            j++;
        }
        k++;
    }

    while (i <= center) {
        aux_array[k] = array[i];
        i++; k++;
    }
    while (j <= end) {
        aux_array[k] = array[j];
        j++; k++;
    }

    for (i = start, k = 0; i <= end; i++, k++) 
        array[i] = aux_array[k];

    free(aux_array);
}

void create_compressed(char *fname, unsigned char *audio, int data_size) {
    FILE *rp = fopen(fname, "rb");
    FILE *wp = fopen("compressed.wav", "wb");
    unsigned char header_wav;
    for (int i = 0; i < WAV_HEADER_SIZE; i++) {
        fread(&header_wav, sizeof(unsigned char), 1, rp);
        fwrite(&header_wav, sizeof(unsigned char), 1, wp);
    }
    for (int i = 0; i < data_size; i++)
        fwrite(&audio[i], sizeof(unsigned char), 1, wp);
    fclose(rp);
    fclose(wp);
} 