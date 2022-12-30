
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define true 0
#define false 1

struct product
	{
		char id[10];   // code de produit/no.
		char name[20]; // nome de produit
		int  quantity; // quantité restante de produit. Soustraire de la quantité d'origine la quantité achetée
        int  numSold;  // initialement zéro, quand pas encore d'achat.
		float price;   // prix d'un produit
		int discount;  // remise pour ce produit
		float sales;   // ventes cumulées, ventes totales pour ce produit
	};
	struct product prod[30];//le maximum d'éléments du tableau.
	int Tot_elem = 0;	//cela sera incrémenté s'il y a un nouveau produit
 	FILE *f;	//pour le pointeur de fichier

 	int writefile()
{
    int i;
    f = fopen("inventory.txt", "w");
    if (f == NULL)
        return -1;
    fprintf(f, "%d\n", Tot_elem);
    for (i = 0; i < Tot_elem; ++i) // écrire tous les détails de toutes les fonctions dans le fichier texte.
    {
        // Changed
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].discount);
        fprintf(f, "%f\n", prod[i].sales);
    }
    fclose(f);
    return 0;
}
int readFile()
{
    int n = 0;
    int i;
    f = fopen("inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; ++i)
    {
        fgets(prod[i].id, 10, f);
        prod[i].id[strlen(prod[i].id) - 1] = 0; // supprimer les nouvelles lignes
        fgets(prod[i].name, 20, f);
        prod[i].name[strlen(prod[i].name)-1] = 0; // supprimer les nouvelles lignes
        fscanf(f, "%d", &prod[i].quantity);
        fscanf(f, "%d", &prod[i].numSold);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%d", &prod[i].discount);
        fscanf(f, "%f\n", &prod[i].sales);
    }
    fclose(f);
    return n;
}

void Quantnull(){ // pour le commutateur numéro 7 = appeler tous les identifiants de produit avec une quantité nulle.
		int i;

       Tot_elem= readFile();
         printf("\nProduits avec une quantité nulle: ");
        for (i=0; i<Tot_elem; i++){
		if(prod[i].quantity==0){
    printf("\nNom du produit: %s \nId de produit: %s \nQuantité restante: %d \nNombre de produits vendus: %d \nPrix ​​du produit: %.2f \nRemise du produit: %d %% \nVentes totales: %.2lf\n",prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
		}
     }
writefile();

}
void plus_vendu(){ //pour afficher  la vente la plus élevée
	int maxi,i;
	 maxi=prod[0].numSold; // initialisation au premier élément du tableau
     for(i=0;i<Tot_elem;i++) // la recherche
     {
          if(prod[i].numSold>maxi)
          maxi=prod[i].numSold;
     }
        printf("\nLeproduit le plus vendu est: \n");
   	for(i=0;i<Tot_elem;i++) // recherche.
     {
    if(prod[i].numSold==maxi)//affichage.
    printf("Nom du produit: %s \nId de produit: %s \nQuantité restante: %d \nNombre de produits vendus: %d \nPrix ​​du produit: %.2f \nRemise du produit: %d %% \nVentes totales: %.2lf\n",prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
     }

}

void purchaseprod(){// fonction d'achat d'un produit
	int nbr,i;
    char id[10];
    int z=false;
    Tot_elem=readFile();
	printf("Vendre un article ");
    printf("\nId du produit: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<Tot_elem; i++){
        if (strcmp(id,prod[i].id)==0) 	// si les deux Ids sont identiques.
        {
        	z=true;
        printf("\nObjet trouvé , contenant: \n");// afficher la correspondance
	   	printf("\nNom du produit: %s",prod[i].name);
		printf("\nPrix: %.2lfphp\n\n",prod[i].price);

            printf("Entrez la quantité que vous souhaitez acheter  : ");
            fflush(stdin);
			scanf("%d",&nbr);
            if (nbr>prod[i].quantity){		// si la quantité est inférieure à celle de l'utilisateur
               puts("\nQuantité insuffisante\nVeuillez restocker.\n ");
             break; // break et retour aux choix.
				}

            float tempSales = prod[i].sales;  // ne sera exécuté que si la quantité est supérieure à la quantité sélectionnée par l'utilisateur.
            prod[i].numSold += nbr;
            prod[i].quantity -= nbr;
            prod[i].sales = nbr*(prod[i].price*(prod[i].discount/100.0));
            prod[i].sales += tempSales;
			}

	}
 if(z==false){	//si Id du produit n'est pas disponible.

	printf("Impossible de trouver Id du produit: %s.",id);
}
	writefile();


}
void supprimer_prod(){ //supprimer le produit.
	Tot_elem=readFile();
	char id[10];
	int i,j;
	int z=false;
printf("Entrez l'Id que vous souhaitez supprimer: ");
fflush(stdin);
gets(id);

for(i=0;i<Tot_elem;i++){		//recherche
		z=true;
	if(strcmp(prod[i].id,id)==0){ // si Id trouvé
	for( j=i; j<(Tot_elem-1); j++)	//la suppression
			{
				prod[j]=prod[j+1];
			}
			Tot_elem--;
	}
}
if(z==false){	// Id non trouvé.
	printf("Impossible de trouver l'Id: %s .",id);
}
writefile();
}



void ajout_prod(){	// ajout de produit

  	printf("saisir un nouveau produit\n");
	readFile();
  	    if (Tot_elem>0) {
  	    Tot_elem=readFile();
  		Check_Id(0,Tot_elem); // vérifier si l'Id est déjà utilisé.
		}
	else{
		printf("\nId du produit: ");
		fflush(stdin);
		gets(prod[Tot_elem].id);
		}
		printf("nom du produit: ");gets(prod[Tot_elem].name);
		printf("Quantité du produit: ");scanf("%d",&prod[Tot_elem].quantity);
		printf("Prix ​​du produit: ");scanf("%f",&prod[Tot_elem].price);
		printf("Remise sur l'article: ");scanf("%d",&prod[Tot_elem].discount);
		++Tot_elem; // incrémentation pour la position du produit et le nombre d'éléments dans le tableau.
	writefile(); // enregistrer dans le fichier.
}



int Check_Id(int i, int j)	//vérification de l'Id
{
	Tot_elem=readFile();
    printf("Id du produit: ");
    fflush(stdin);
	gets(prod[Tot_elem].id);
    if (strcmp(prod[i].id,prod[j].id)==0){
        printf("L'Id est déjà pris !");
        return Check_Id(i++,j--);
		}
}


void modifier_prod(){	//Modification du produit
	char id[10];
int test;
int i;
	int choice;
  printf("Modifier un produit!");
  printf("\nSaisissez l'Id du produit que vous souhaitez modifier: ");
	fflush(stdin);
	gets(id);
	test=checkID(id);
    if (test == 0)
 {
  printf("Id %s introuvable.", id);
 }
 else
 {
 		readFile();
  {
	for(i=0;i<Tot_elem;i++){

  if(strcmp(id,prod[i].id)!=0) // id trouvé.
	writefile();
   else
   {
    printf("\n1. modifier l'Id du produit?");
    printf("\n2. modifier nom du produit?");
    printf("\n3. modifier Quantité du produit?");
    printf("\n4. modifier Prix ​​du produit?");
    printf("\n5. modifier Remise du produit?");
    printf("\nEntrez votre choix:");
    fflush(stdin);
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

     printf("Entrez nouvelle Id: ");
 		fflush(stdin);
        gets(prod[i].id);
     break;
    case 2:
     printf("Entrez nouveau nom: ");
    	fflush(stdin);
        gets(prod[i].name);
     break;
    case 3:
     printf("Entrez Quantité: ");
    scanf("%d",&prod[i].quantity);
    break;
    case 4:
     printf("Entrez le nouveau prix: ");
    scanf("%f",&prod[i].price);
     break;
     case 5:
     	 printf("Entrez la nouvelle remise du produit: ");
   scanf("%d",&prod[i].discount);
    default:
     printf("choix invalide");
     break;
    }
   writefile();
   }

   }
  }
  fclose(f);
  f = fopen("Inventory.txt", "r");
 readFile();
 {
   writefile();
  }
  fclose(f);
  printf("DOSSIER MIS À JOUR");
 }
}

int checkID(char id[]){ // vérification si l'Id est disponible
	int i;
Tot_elem=readFile();


 		readFile();
 		for(i=0;i<Tot_elem;i++){

	if(strcmp(id,prod[i].id)!=0){ //si les deux identifiants ne sont pas identiques.

			 fclose(f);
		}
   return 1;		// envoyer une erreur.
  }

 fclose(f);
 return 0; // pas d'erreur.
}


void afficher_prod(){
	int i;

  Tot_elem = readFile();
  if (Tot_elem < 0)
    puts("ne peut pas ouvrir le fichier");
	printf(" \t\t\t\t *****  INVENTORY *****\n");
   printf("------------------------------------------------------------------------------------\n");
   printf("S.N.|    nom     |  ID DU PROD  |  QUANTITÉ | PROD VENDU |  PRIX  | REMISE | VENTES |\n");
   printf("------------------------------------------------------------------------------------\n");

   for (i=0;i<Tot_elem;i++){ // obtenir les détails sur chaque produit.
   printf("%d     %-10s       %-8s     %-5d      %-3d       %-6.2f    %-5d%%    P%.2lf\n",i+1,prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
	}

}




int main (){
	int choice;
	Tot_elem = readFile();
	if(Tot_elem < 0) // il n'y a pas de fichier.
		printf("Impossible de trouver le fichier\n");
do {
	printf("\n");
	printf("\t\t\t  =====================================\n");
	printf("\t\t\t     application de gestion de stock\n");
	printf("\t\t\t  =====================================");

	printf("\n\nPress:");
	printf("\n 1.) Saisir un nouveau produit.");
	printf("\n 2.) Modifier un produit.");
	printf("\n 3.) Supprimer un produit.");
	printf("\n 4.) Afficher tous les produits.");
	printf("\n 5.) Faire un achat.");
	printf("\n 6.) Afficher le produit le plus vendu.");
	printf("\n 7.) Afficher tous les produits avec une quantité nulle");
	printf("\n 8.) Quitter le programme.");
	printf("\nChoix--> ");
	scanf("%d", &choice);
	     switch(choice){
        case 1 :  //ajouter un produit.
                ajout_prod();
                break;
        case 2://Modifier un produit.
		    	modifier_prod();
				break;
        case 3://Supprimer un produit.
        supprimer_prod();
               	 break;
        case 4: //Afficher tous les produits
               afficher_prod();
                break;
       	case 5://Faire un achat.
       	purchaseprod();
		 break;
	   	case  6:
	   		plus_vendu(); //  Afficher le produit le plus vendu.
		 	break;
		case 7:
	Quantnull(); // les produits avec une quantité nulle.
		 	break;
		case 8:
		 	  exit(1);
			   break;
		 default :
                printf("Votre choix est erroné, veuillez réessayer");
            break;
      }
  }while(choice!=8);
  printf("Merci d'utiliser ce programme");
}


