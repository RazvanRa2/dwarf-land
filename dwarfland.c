#include <stdio.h>
#include <math.h>

#define MAX 1001 /* numar cu 1 mai mare ca cea mai mare coordonata posibila a unui copac*/
#define PI 3.14159265

/* functia veirifica daca un numar este prim */ 
int checkPrime(int inCheckNr){

    int i, flag=1;
    if (inCheckNr==0 || inCheckNr==1)
        return 0;
    else{

        for(i =2; i*i<=inCheckNr; i++)
            if(inCheckNr%i==0)
                flag=0;
        return flag;
    }

}

/* functia verifica daca un numar este magic */
int checkMagic(int nr1, int nr2, int nr3, int nr4){

	int magic=nr1%10; /*se construieste numarul magic*/
	magic*=10;
	magic+=nr2%10;
	magic*=10;
	magic+=nr3%10;
	magic*=10;
	magic+=nr4%10;
	while(magic>0){ /* se verifica proprietatea unui numar magic cu checkPrime*/
		
		if(checkPrime(magic)==0)
			return 0; /*0 deoarece numarul nu e magic*/
		magic/=10;
	}
	return 1;	/*in cazul in care nu s-a returnat 0, inseamna ca numarul e magic. return 1.*/

}
int main()
{
    int lightX, lightY;
    float lightSourceIntensity;

    int n, treeCount=1;

    int pTreeX, cTreeX, nTreeX;
    int pTreeY, cTreeY, nTreeY;
    float cTreeInt;

    int perfectTreeX=MAX, perfectTreeY=MAX, perfectPosition;
    float perfectIntensity;
    int goodTreeCounter=0;

    int aftPerfX, aftPerfY;
    int befPerfX, befPerfY;
    double triLen1, triLen2, triLen3, angle;
    
    /*citirea datelor de intrrare*/

    scanf("%d %d %f", &lightX, &lightY, &lightSourceIntensity);
    scanf("%d", &n);

    scanf("%d %d", &pTreeX, &pTreeY); n--;
    scanf("%d %d", &cTreeX, &cTreeY); n--;

    while(n>0){

        scanf("%d %d", &nTreeX, &nTreeY);
	
	if(n>1){	
        cTreeInt = (lightX-cTreeX)*(lightX-cTreeX)+(lightY-cTreeY)*(lightY-cTreeY);
        cTreeInt = lightSourceIntensity/cTreeInt; /*calcularea intensitatii conform formulei date*/

        if(checkMagic(cTreeInt, pTreeY, cTreeY, nTreeY)==1){
            if(perfectTreeY>cTreeY){	/*indeplinind cele douca conditii, copacul devine ideal*/

                perfectPosition=treeCount; /*se inlocuiesc datele copacului ideal*/
                perfectIntensity=cTreeInt;

                perfectTreeX=cTreeX;
                perfectTreeY=cTreeY;

                befPerfX=pTreeX;	/*se retin date despre copacul ideal pentru bonus*/
                befPerfY=pTreeY;

                aftPerfX=nTreeX;    
                aftPerfY=nTreeY;

                goodTreeCounter++;

            }
        }

        pTreeX=cTreeX; pTreeY=cTreeY; /*interschimbarea necesara pentru verificarea fiecarui copac*/
        cTreeX=nTreeX; cTreeY=nTreeY;
        }

        treeCount++; n--; /*se numara cati copaci au fost verificati si se scade cati au ramas*/
    }
    if(goodTreeCounter>0){ /*se rezolva bonusul doar daca s-a gasit un copac ideal*/

        triLen1=(perfectTreeX-befPerfX)*(perfectTreeX-befPerfX);
        triLen1+=(perfectTreeY-befPerfY)*(perfectTreeY-befPerfY);
        triLen1=sqrt(triLen1);

        triLen2=(perfectTreeX-aftPerfX)*(perfectTreeX-aftPerfX);
        triLen2+=(perfectTreeY-aftPerfY)*(perfectTreeY-aftPerfY);
        triLen2=sqrt(triLen2);

        triLen3=(aftPerfX-befPerfX)*(aftPerfX-befPerfX);
        triLen3+=(aftPerfY-befPerfY)*(aftPerfY-befPerfY);
        triLen3=sqrt(triLen3);

        angle=pow(triLen2,2)+pow(triLen1,2)-pow(triLen3,2); /*calcul conform teoremei cosinusului*/
        angle=angle/(2*triLen2*triLen1);
        angle=acos(angle);
        angle=(180.0*angle)/PI; /*schimbare din radiani in grade*/
	
	/*printarea datelor cerute*/
        if(angle>90 && angle<180)
            printf("%d %.4f \n%.4lf IT CAN BE EXTENDED\n", perfectPosition, perfectIntensity, angle);
        else
            printf("%d %.4f \n%.4lf IT CAN NOT BE EXTENDED\n", perfectPosition, perfectIntensity, angle);
    }
    else
        printf("There is no place for you in DwarfLand!\n");	
	/*printat doar daca nu s-a gasit copaci ideal*/
    return 0;
}

