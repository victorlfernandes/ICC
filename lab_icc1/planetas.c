#include <stdio.h>
#include <string.h>

#define DIA 86400
#define HORA 3600
#define MINUTO 60

#define LLU long long unsigned int

void terra(LLU segundos_planeta, LLU *dias, LLU *horas, LLU *minutos, LLU *segundos){
    if ((segundos_planeta / DIA)  > 0){
        *dias = (segundos_planeta / DIA);
        segundos_planeta = segundos_planeta % DIA;
    }
    if ((segundos_planeta / HORA)  > 0){
        *horas = (segundos_planeta / HORA);
        segundos_planeta = segundos_planeta % HORA;
    }
    if ((segundos_planeta / MINUTO)  > 0){
        *minutos = (segundos_planeta / MINUTO);
        segundos_planeta = segundos_planeta % MINUTO;
    }
    if (segundos_planeta  > 0){
        *segundos = segundos_planeta;
    }
}

void jupiter(LLU segundos_planeta, LLU *dias, LLU *horas, LLU *minutos, LLU *segundos){
    /*
    relacao ente o dia na terra e em jupiter:
    jupiter = terra * ((9/24) + (56/(24*60)))
    ((9/24) + (56/(24*60))) = 9/24 + 56/1440
    = 540/1440 + 56/1440 = 596/1440 = 149/360
    portanto, jupiter = terra * 149/360
    */
    if ((segundos_planeta / (DIA * 149 / 360))  > 0){
        *dias = (segundos_planeta / (DIA * 149 / 360));
        segundos_planeta = (segundos_planeta % (DIA * 149 / 360));
    }
    if ((segundos_planeta / (HORA) > 0)){
        *horas = (segundos_planeta / HORA);
        segundos_planeta = segundos_planeta % HORA;
    }
    if ((segundos_planeta / MINUTO) > 0){
        *minutos = (segundos_planeta / MINUTO);
        segundos_planeta = segundos_planeta % MINUTO;
    }
    if (segundos_planeta > 0){
        *segundos = segundos_planeta;
    }
}

void venus(LLU segundos_planeta, LLU *dias, LLU *horas, LLU *minutos, LLU *segundos){
    if ((segundos_planeta / (DIA * 243))  > 0){
        *dias = (segundos_planeta / (DIA * 243));
        segundos_planeta = segundos_planeta % (DIA * 243);
    }
    if ((segundos_planeta / (HORA) > 0)){
        *horas = (segundos_planeta / HORA);
        segundos_planeta = segundos_planeta % HORA;
    }
    if ((segundos_planeta / MINUTO) > 0){
        *minutos = (segundos_planeta / MINUTO);
        segundos_planeta = segundos_planeta % MINUTO;
    }
    if (segundos_planeta > 0){
        *segundos = segundos_planeta;
    }
}

void mercurio(LLU segundos_planeta, LLU *dias, LLU *horas, LLU *minutos, LLU *segundos){
    /*
    relacao entre o dia na terra e em mercurio
    mercurio = terra * (58 + 16/24)
    58 + 16/24 = 1392/24 + 16/24
    = 1408/24 = 176/3
    portanto, mercurio = terra * 176/3
    */
    if ((segundos_planeta / (DIA * 176 / 3))  > 0){
        *dias = (segundos_planeta / (DIA * 176 / 3));
        segundos_planeta = (segundos_planeta % (DIA * 176 / 3));
    }
    if ((segundos_planeta / (HORA) > 0)){
        *horas = (segundos_planeta / HORA);
        segundos_planeta = segundos_planeta % HORA;
    }
    if ((segundos_planeta / MINUTO) > 0){
        *minutos = (segundos_planeta / MINUTO);
        segundos_planeta = segundos_planeta % MINUTO;
    }
    if (segundos_planeta > 0){
        *segundos = segundos_planeta;
    }
}

int main(){

    LLU dias=0, horas=0, minutos=0, segundos=0;
    LLU segundos_planeta;
    char planeta[9];
    scanf(" %llu %s", &segundos_planeta, planeta);

    if (strcmp(planeta, "Terra") == 0){
        terra(segundos_planeta, &dias, &horas, &minutos, &segundos);
    }
    else if (strcmp(planeta, "Jupiter") == 0){
        jupiter(segundos_planeta, &dias, &horas, &minutos, &segundos);
    }
    else if (strcmp(planeta, "Venus") == 0){
        venus(segundos_planeta, &dias, &horas, &minutos, &segundos);
    }
    else{
        mercurio(segundos_planeta, &dias, &horas, &minutos, &segundos);
    }

    printf("%llu segundos no planeta %s equivalem a:\n", segundos_planeta, planeta);
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", dias, horas, minutos, segundos);
            
    return 0;
}