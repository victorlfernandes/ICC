#include <stdio.h>

#define SIZE_IN 10

int highest(int n[SIZE_IN]){
    int current_highest = n[0];
    for (int i=0; i<SIZE_IN; i++){
        if (n[i] > current_highest){
            current_highest = n[i];
        }
    }
    return current_highest;
}

int lower(int n[SIZE_IN]){
    int current_lower = n[0];
    for (int i=0; i<SIZE_IN; i++){
        if (n[i] < current_lower){
            current_lower = n[i];
        }
    }
    return current_lower;
}

double avg(int n[SIZE_IN]){
    double sum = 0;
    for (int i=0; i<SIZE_IN; i++){
        sum += n[i];
    }
    return sum / SIZE_IN;
}

int mode(int n[SIZE_IN]){
    int counter[10] = {};
    for (int i=0; i<SIZE_IN; i++){
        for (int j=i+1; j<SIZE_IN; j++){
            if (n[i] == n[j]){
                counter[i]++;
            }
        }
        counter[i]++;
    }
    int highest_counter = counter[0];
    int mode = n[0];
    for (int i=0; i<SIZE_IN; i++){
        if (counter[i] > highest_counter){
            highest_counter = counter[i];
            mode = n[i];
        }
    }
    return mode;
}

int main(){

    int in[SIZE_IN] = {};
    for (int i=0; i<SIZE_IN; i++){
        scanf(" %d", &in[i]);
    }

    int h = highest(in);
    int l = lower(in);
    double a = avg(in);
    int m = mode(in);

    printf("%d %d %.2lf %d\n", h, l, a, m);

    return 0;
}