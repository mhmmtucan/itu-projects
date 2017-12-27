// Muhammet Uçan
// 150140707
// Homework 4
// 12.5.2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct person{
    int personID;
    double height;
    double weight;
    double BMI;
};

int main(int argc, char** argv){
    if(argc == 4){
        int n,m,threshold;
        sscanf(argv[1], "%d", &n);
        sscanf(argv[2], "%d", &m);
        sscanf(argv[3], "%d", &threshold);
        
        // read file
        FILE* filePtr = fopen("height_weight.txt", "r");
        int a, b, c, flag=0;
        
        char *id,*height,*weight;
        fscanf(filePtr, "%s %s %s", &id, &height, &weight);
        
        struct person* listPtr = (struct person*) malloc(n * sizeof(struct person));
        
        while(flag != n){
            fscanf(filePtr, "%d %d %d", &a, &b, &c);
            struct person userPerson;
            userPerson.personID = a;
            userPerson.height = b;
            userPerson.weight = c;
            double bmi = (double) c / ((double) b / 100) / ((double) b / 100);
            userPerson.BMI = bmi;
    
            listPtr[flag] = userPerson;
            flag++;
            if(feof(filePtr)){
                break;
            }
        }
        fclose(filePtr);
        
        // sort using bubble sort
        int i,j;
        for(i = 0; i < n; i++){
            for(j = 1; j < n - i; j++){
                if(fabs(listPtr[j-1].BMI - threshold) <= fabs(listPtr[j].BMI - threshold)){
                    struct person temp;
                    temp = listPtr[j-1];
                    listPtr[j-1] = listPtr[j];
                    listPtr[j] = temp;
                }
            }
        }

        // write file
        FILE* filePtr2 = fopen("output.txt", "w");
        fprintf(filePtr2, "Person_id\tHeight(cm)\tWeight(kg)\tBMI\t|BMI-Threshold|\n");
        int k;
        for(k = 0; k < m; k++){
            fprintf(filePtr2, "%9d\t%9.0f\t%9.0f\t%5.2f\t%14.2f\n", listPtr[k].personID, listPtr[k].height, listPtr[k].weight, listPtr[k].BMI, fabs(listPtr[k].BMI - threshold));
        }
        free(listPtr);
    }
    else{
        puts("Enter N & M values correctly");
    }
    
    return 0;
}