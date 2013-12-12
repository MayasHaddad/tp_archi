
#include <stdio.h>
#define mway 4	/* Nombre max de bloc par ensemble*/
#define mnsets 4096	/* Nombre max d'ensembles*/
#define N 64	/* Taille  des matrices et vecteurs*/


FILE *stream, *results;

int am=0, dc=0, BC[mnsets][mway], LRU[mnsets][mway];
int line, taille, way, nsets;
/* nombre d'acces memoire, nombre de defauts de cache, memoire d'etiquettes
 et memoire donnant l'anciennete des blocs*/


int iba (int index)
{
	/* renvoie l'indice du bloc le plus ancien*/
	int j,s, i=0;
	s=LRU[index][0];
for (j=1;j<way;j++)
	if (s>LRU[index][j])
	{	s=LRU[index][j];i=j;}
return (i);
}
	
int cache( unsigned long ad)
{	/* acces cache, gestion des etiquettes et anciennete, renvoie 1 si
	defaut de cache*/
	int index,tag,set,j;
	ad=ad/line;
	tag = ad/nsets;
	index=ad%nsets;
	for (set=0;set<way;set++)
		if (BC[index][set]==tag)
		{LRU[index][set]=am;
		return (0);}
	
		j= iba(index);
		BC[index][j]=tag;
		LRU[index][j]=am;
		return (1);
	
}


void ac(unsigned long z)
{	/* acces cache pour l'adresse z*/
	am++;
	dc+=cache(z);

}

int min (int a, int b)
{
	if (a<b) return a;
	else return b;
}


void main()
{
int i,j,k;
results = fopen( "courbes", "w+" );

double x[N], y[N], s=0;

/** Initialisation des vecteurs**/

for (i=0;i<N;i++)
	{for (j=0;j<N;j++)
		{
		x[i]=i+j;
		y[i]=i-j;
		}
	}	

/*taille = 16*1024;
line = 64;
way= 1;*/

for (taille=8*1024; taille <40000;taille+=taille)
for (line=16;line <100;line+=line)
for (way=1;way<8;way+=way)
{
nsets= taille /(way*line);

/**RAZ des memoires etiquettes et LRU**/
am =0, dc=0;
for (j=0; j<nsets;j++)
	for (k=0;k<way;k++)
	{
			LRU[j][k]=0; BC[j][k]=0;
	}
	
s=0;
for (i=0;i<N;i++)
	
{
			ac((unsigned long) &x[i]);ac((unsigned long) &y[i]);
			s = s + x[i]*y[i];
}
		

fprintf(results,"%d \t %d \t %d \t %d \t %f \t \n",taille,way, line, N,(float)dc/(float)am);
}

}
