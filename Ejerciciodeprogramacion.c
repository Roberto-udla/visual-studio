#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZONAS 5
#define DIAS 30

/* Límites OMS (valores de referencia) */
#define LIM_CO2 400
#define LIM_SO2 20
#define LIM_NO2 40
#define LIM_PM25 25

/* Estructuras */
typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
} Contaminacion;

typedef struct {
    float temperatura;
    float viento;
    float humedad;
} Clima;

typedef struct {
    char nombre[30];
    Contaminacion historial[DIAS];
    Contaminacion actual;
    Clima clima;
} Zona;

/* Prototipos */
void inicializarZonas(Zona zonas[]);
void cargarDatos(Zona zonas[]);
void guardarDatos(Zona zonas[]);
Contaminacion promedioHistorico(Zona *z);
Contaminacion prediccion(Zona *z);
void verificarAlertas(Zona *z, Contaminacion pred);
void generarRecomendaciones(Contaminacion c);
void exportarReporte(Zona zonas[]);

/* Función principal */
int main() {
    int valor = 1;
    srand((valor)time(NULL));
    Zona zonas[ZONAS];
    int i;

    inicializarZonas(zonas);
    cargarDatos(zonas);

    printf("\n===== SISTEMA DE CONTAMINACION DEL AIRE =====\n");

    for (i = 0; i < ZONAS; i++) {
        printf("\nZona: %s\n", zonas[i].nombre);

        Contaminacion prom = promedioHistorico(&zonas[i]);
        Contaminacion pred = prediccion(&zonas[i]);

        printf("Promedio 30 dias - CO2: %.2f | SO2: %.2f | NO2: %.2f | PM2.5: %.2f\n",
               prom.co2, prom.so2, prom.no2, prom.pm25);

        printf("Prediccion 24h - CO2: %.2f | SO2: %.2f | NO2: %.2f | PM2.5: %.2f\n",
               pred.co2, pred.so2, pred.no2, pred.pm25);

        verificarAlertas(&zonas[i], pred);
        generarRecomendaciones(pred);
    }

    guardarDatos(zonas);
    exportarReporte(zonas);

    printf("\nReporte generado exitosamente.\n");
    return 0;
}

/* Inicialización */
void inicializarZonas(Zona zonas[]) {
    char nombres[ZONAS][30] = {
        "Centro",
        "Norte",
        "Sur",
        "Este",
        "Oeste"
    };

    for (int i = 0; i < ZONAS; i++) {
        strcpy(zonas[i].nombre, nombres[i]);

        for (int j = 0; j < DIAS; j++) {
            zonas[i].historial[j].co2 = 350 + rand() % 50;
            zonas[i].historial[j].so2 = 10 + rand() % 10;
            zonas[i].historial[j].no2 = 20 + rand() % 20;
            zonas[i].historial[j].pm25 = 15 + rand() % 15;
        }

        zonas[i].actual = zonas[i].historial[DIAS - 1];
        zonas[i].clima.temperatura = 20 + rand() % 10;
        zonas[i].clima.viento = 1 + rand() % 5;
        zonas[i].clima.humedad = 50 + rand() % 30;
    }
}

/* Cargar datos desde archivo */
void cargarDatos(Zona zonas[]) {
    FILE *f = fopen("datos.txt", "rb");
    if (f != NULL) {
        fread(zonas, sizeof(Zona), ZONAS, f);
        fclose(f);
    }
}

/* Guardar datos */
void guardarDatos(Zona zonas[]) {
    FILE *f = fopen("datos.txt", "wb");
    fwrite(zonas, sizeof(Zona), ZONAS, f);
    fclose(f);
}

/* Promedio histórico */
Contaminacion promedioHistorico(Zona *z) {
    Contaminacion p = {0, 0, 0, 0};

    for (int i = 0; i < DIAS; i++) {
        p.co2 += z->historial[i].co2;
        p.so2 += z->historial[i].so2;
        p.no2 += z->historial[i].no2;
        p.pm25 += z->historial[i].pm25;
    }

    p.co2 /= DIAS;
    p.so2 /= DIAS;
    p.no2 /= DIAS;
    p.pm25 /= DIAS;

    return p;
}

/* Predicción (promedio ponderado últimos 5 días) */
Contaminacion prediccion(Zona *z) {
    int pesos[5] = {1, 2, 3, 4, 5};
    int sumaPesos = 15;
    Contaminacion p = {0, 0, 0, 0};

    for (int i = 0; i < 5; i++) {
        int d = DIAS - 1 - i;
        p.co2 += z->historial[d].co2 * pesos[i];
        p.so2 += z->historial[d].so2 * pesos[i];
        p.no2 += z->historial[d].no2 * pesos[i];
        p.pm25 += z->historial[d].pm25 * pesos[i];
    }

    p.co2 /= sumaPesos;
    p.so2 /= sumaPesos;
    p.no2 /= sumaPesos;
    p.pm25 /= sumaPesos;

    return p;
}

/* Alertas */
void verificarAlertas(Zona *z, Contaminacion p) {
    if (p.co2 > LIM_CO2 || p.so2 > LIM_SO2 || p.no2 > LIM_NO2 || p.pm25 > LIM_PM25) {
        printf(" ALERTA: Contaminacion elevada en %s\n", z->nombre);
    }
}

/* Recomendaciones */
void generarRecomendaciones(Contaminacion c) {
    if (c.no2 > LIM_NO2 || c.co2 > LIM_CO2) {
        printf("Recomendacion: Reducir tráfico vehicular.\n");
    }
    if (c.so2 > LIM_SO2) {
        printf("Recomendacion: Control temporal de industrias.\n");
    }
    if (c.pm25 > LIM_PM25) {
        printf("Recomendacion: Evitar actividades al aire libre.\n");
    }
}

/* Exportar reporte */
void exportarReporte(Zona zonas[]) {
    FILE *f = fopen("reporte.txt", "w");

    for (int i = 0; i < ZONAS; i++) {
        Contaminacion prom = promedioHistorico(&zonas[i]);
        Contaminacion pred = prediccion(&zonas[i]);

        fprintf(f, "Zona: %s\n", zonas[i].nombre);
        fprintf(f, "Promedio 30 días -> CO2: %.2f SO2: %.2f NO2: %.2f PM2.5: %.2f\n",
                prom.co2, prom.so2, prom.no2, prom.pm25);
        fprintf(f, "Prediccion 24h -> CO2: %.2f SO2: %.2f NO2: %.2f PM2.5: %.2f\n\n",
                pred.co2, pred.so2, pred.no2, pred.pm25);
    }

    fclose(f);
}

