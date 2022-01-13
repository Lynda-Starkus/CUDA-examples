/*Exercice 03 : un programme CUDA C qui permet d'inverser 2 vecteurs de taille N = 100 000, en mobilisant plusieurs threads de blocs différents*/

#include <stdio.h>
#include <stdlib.h>
#define N (2048*2048)
#define THREADS_PER_BLOCK 512

__global__ void kenrnel_add(int* vect1, int* result, int taille){
    int index;

    index = threadIdx.x + blockIdx.x * blockDim.x;

    if(index < taille)
    result[index] = vect1[taille-1-index];
}


int main(){
    // Déclaration des variables 

    int *d_vect1,*d_result;
    int *h_vect1, *h_result;

    //Définit la taille des vecteurs 
    int size = N * sizeof(int);

    //Allocation des varaibels du Host
    h_vect1 = (int*) malloc(size);
    h_result = (int*) malloc(size);

    //Allocation des variabels du  Device
    cudaMalloc((void **) &d_vect1, size);
    cudaMalloc((void **) &d_result, size);

    //Initialisation aléatoires des vecteurs dans le Host
    random_ints(h_vect1, N);

    //Copier les données de la mémoire du Host vers celle du Device 
    cudaMemcpy(d_vect1, h_vect1, size, cudaMemcpyHostToDevice);

    //Lancer le Kernel
    kenrnel_add<<<N/THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(d_vect1, d_vect2, d_result, taille);

    //Copier le résultat du Device vers le Host 
    cudaMemcpy(h_result, d_result, size, cudaMemcpyDeviceToHost);

    //Libération de la mémoire 
    free(h_vect1);  free(h_result);
    cudaFree(d_vect1);  cudaFree(d_result);

    return 0;   
}