# CUDA cheat sheet 

### 1° / Terminoogie utilisée :

architecture hiérarchique : 
> Grids (grilles) ---> Blocks (blocs) ---> Threads (kernels = one CUDA core)

> Host = CPU + DRAM du CPU
> Device = GPU + DRAM du GPU




### 2° / Flux d'un programme CUDA :

##### Etape 01 : Partie du code à exécution séquentielle (Host)
##### Etape 02 : Préparer les paramètres du kernal (grid size, block size)
##### Etape 03 : Allocation de la mémoire sur le Device 
##### Etape 04 : Copier data du Host -> Device
##### Etape 05 : Lancer le kernel 
##### Etape 04 : Copier data du Device -> Host 


### 3° / Déclarations : 

- Les variables (des pointeurs pour facilter le passage par référence)
- La fonction du Kernel 
- Les dimensions du grid et block 


### 4°/ Allocation de la mémoire sur le Device :
    - cudaMalloc(LOCATION, SIZE); //SIZE en octets 
    - cudaFree();
    - cudaMemcpy(destination, source, num_Bytes, direction) /*  destination : pointeur 
                                                                source : pointeur
                                                                num_Bytes : octets
                                                                direction : "cudaMemcpyHostToDevice" ou "cudaMemcpyDeviceToHost"
                                                            */

### 5° / Convention d'appelation des variables :

En général, on distingue les variables du Host et du Device en rajoutant un suffix.
Exemple : int *h_a, *h_b; //variables Host 
          int *d_a, *d_b; //variables Device 

### 6° / Définition de la fonction du kernel :

_ _global_ _ void kernel_function(int* d_out, int* d_in){...}


### 7° / Les indices :
threadIdx.x : retourne l'id du thread
blockIdx.x : retourne l'id du block 

Pour trouver l'indice d'un thread dans une grille qui contient plusieurs blocs il existe la formule :

index = threadIdx.x + blockIdx.x * blockDim.x;

### 8°/ Lancement d'un kernel :
    //configurer les dimensions de blocs et grilles

    dim3 grid_size(x,y);
    dim3 block_size(x,y);

    //launch kernel
    kernel_function<<<grid_size, block_size>>>(args);
