/*
 ============================================================================
 Name        : Lab4.c
 Author      : Choma, Theodore, D
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Lab 4
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void arrayops();
double average(int numdata, int* array);
int maximum(int numdata, int* array);


int main(void) {

	arrayops();


	return EXIT_SUCCESS;
}



void arrayops()
{
	int numfile = 0, numdata, maxdata, i;
	char str[15], outstr[25];
	int array[50];
	double outarray[50];
	int selection;
	double factor;
	FILE *fp, *fp2;


	//File opening
	printf("\nWhich file would you like to open? ");
		fflush(stdout);
		scanf("%d", &numfile);
		sprintf(str, "Raw_data_%d.txt", numfile);
	fp = fopen(str, "r");
	if(fp == NULL)
	{
		perror("\n!!!Error opening file!!!\n");
	}



	//data parsing
	fscanf(fp, "%d", &numdata);
	fscanf(fp, "%d", &maxdata);
	for(i = 0; i < numdata; i++)
	{
		fscanf(fp, "%d", &array[i]);
	}
	fclose(fp);



        //!!!!!PART 2!!!!!
        double avg;
        int max;
        
        //Getting stats
        avg = average(numdata, array);
        max = maximum(numdata, array);
        
        //Saving stats
        sprintf(outstr, "Statistics_data_%d.txt", numfile);
        fp2 = fopen(outstr, "w");
        if(fp2 == NULL)
        {
                perror("\n!!!Error opening writing file!!!\n");
        }
        else
        {
                fprintf(fp2, "%lf %d\n", avg, max);
        }
        fclose(fp2);
        
        
        //Centering
        for(i = 0; i < numdata; i++)
        {
                outarray[i] = (double)array[i] - avg;
        }
        
        //Saving Centering
        sprintf(outstr, "Centered_data_%d.txt", numfile);
        fp2 = fopen(outstr, "w");
        if(fp2 == NULL)
        {
                perror("\n!!!Error opening writing file!!!\n");
        }
        else
        {
                fprintf(fp2, "%d %lf\n", numdata, avg);
                for(i = 0; i < numdata; i++)
                {
                        fprintf(fp2, "%lf\n", outarray[i]);
                }
        }
        fclose(fp2);
        
        
        //Normalizing
        for(i = 0; i < numdata; i++)
        {
                outarray[i] = (double)array[i] / (double) max;
        }

        //saving Normal
        sprintf(outstr, "Normalized_data_%d.txt", numfile);
        fp2 = fopen(outstr, "w");
        if(fp2 == NULL)
        {
                perror("\n!!!Error opening writing file!!!\n");
        }
        else
        {
                fprintf(fp2, "%d %d\n", numdata, max);
                for(i = 0; i < numdata; i++)
                {
                        fprintf(fp2, "%lf\n", outarray[i]);
                }
        }
        fclose(fp2);
        
        //!!!!!END OF PART 2!!!!!
        
	//array transformation
	printf("\nWould you like to offset (1) or scale (2) your data? ");
		fflush(stdout);
		scanf("%d", &selection);


	if(selection == 1)
	{
		//offset case
		printf("\nWhat would you like your offset value to be? ");
			fflush(stdout);
			scanf("%lf", &factor);
		for(i = 0; i < numdata; i++)
		{
			outarray[i] = (double)array[i] + factor;
		}

		//saving offset
		sprintf(outstr, "Offset_data_%d.txt", numfile);
		fp2 = fopen(outstr, "w");
		if(fp2 == NULL)
		{
			perror("\n!!!Error opening writing file!!!\n");
		}
		else
		{
			fprintf(fp2, "%d %lf\n", numdata, factor);
			for(i = 0; i < numdata; i++)
			{
				fprintf(fp2, "%lf\n", outarray[i]);
			}
		}
		fclose(fp2);
	}


	else if(selection == 2)
	{
		//scale case
		printf("\nWhat would you like your scale factor to be? ");
			fflush(stdout);
			scanf("%lf", &factor);
		for(i = 0; i < numdata; i++)
		{
			outarray[i] = (double)array[i] * factor;
		}

		//saving scale
		sprintf(outstr, "Scaled_data_%d.txt", numfile);
		fp2 = fopen(outstr, "w");
		if(fp2 == NULL)
		{
			perror("\n!!!Error opening writing file!!!\n");
		}
		else
		{
			fprintf(fp2, "%d %lf\n", numdata, factor);
			for(i = 0; i < numdata; i++)
			{
				fprintf(fp2, "%lf\n", outarray[i]);
			}
		}
		fclose(fp2);
	}

}

double average(int numdata, int* array)
{
    double out = 0;
    int i = 0;
    
    for(i = 0; i < numdata; i++)
    {
        out = out + (double)array[i];
    }
    out = out / (double)numdata;
    
    return out;
    
}

int maximum(int numdata, int* array)
{
    int out = array[0];
    int i = 0;
    for(i = 0; i < numdata; i++)
    {
        if(out < array[i])
            out = array[i];
    }
    
    return out;
    
}
