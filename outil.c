#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compl�ter votre nom ici                                                */
/*   Nom : Montegnies                        Pr�nom : Mathis              */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le r�pertoire stock� en m�moire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compl�ter code ici pour tableau
	

	if (rep->nb_elts < MAX_ENREG)
	{
		rep->tab[rep->nb_elts] = enr;          // enregistre le contact
		rep->nb_elts = rep->nb_elts + 1;   //ajoute un emplacement au tableau pour stocker le contact
		return rep->nb_elts;
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
			//
			// compl�ter code ici pour Liste
			//
			//
			//

	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compl�ter code ici pour tableau
	if (rep->nb_elts >= 1 && indice < rep->nb_elts)		/* s'il y a au moins un element ds le tableau */
	{													/* et que l'indice pointe a l'interieur */
		for (int i = indice; i < rep->nb_elts - 1; i++)
		{
			rep->tab[i] = rep->tab[i + 1];              // on reecrit le tableau en ne mettant pas l'element indice 
		}
		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;			//La supression a ete faite
	}
	else
	{
		printf("Probleme lors de supression");
		modif = false;			// la suppression n'a pas pu se faire
	}
	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("Nom : %s ", enr.nom);
	printf("Prenom : %s ", enr.prenom);
	printf("Telephone : %s", enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// comme fonction affichage_enreg, mais avec pr�sentation align�es des infos
	printf("| Nom : %20s ", enr.nom);
	printf("| Prenom : %20s ", enr.prenom);
	printf("| Telephone : %20s ", enr.tel);
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if (enr1.nom == NULL || enr1.prenom == NULL || enr1.tel == NULL || enr2.nom == NULL || enr2.prenom == NULL || enr2.tel == NULL)
	{
		printf("Probleme dans l'enregistrement");
		return false;
	}
	for (int i = 0; i < MAX_NOM; i++)
	{
		if (tolower(enr1.nom[i]) < tolower(enr2.nom[i]))
		{
			return true;
		}
		if (tolower(enr1.nom[i]) > tolower(enr2.nom[i]))
		{
			return false;
		}
	}
	for (int i = 0; i < MAX_NOM; i++)
	{
		if (tolower(enr1.prenom[i]) < tolower(enr2.prenom[i]))
		{
			return true;
		}
		if (tolower(enr1.prenom[i]) > tolower(enr2.prenom[i]))
		{
			return false;
		}
	}
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	
	if (rep == NULL) {printf("le repertoire est vide");}

	for (int i = 0; i < rep->nb_elts - 1; i++)
	{
		if (est_sup(rep->tab[i], rep->tab[i + 1]) == false)
		{
			Enregistrement tmp = rep->tab[i];
			rep->tab[i] = rep->tab[i + 1];
			rep->tab[i + 1] = tmp;
		}
	}
	


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		

	int s = 0;

#ifdef IMPL_TAB
	if (ind > rep->nb_elts || ind < 0) { return 0; }
	
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);    //on copie nom dans tmp_nom
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);				// le nom est passé en majuscule
	ind_fin = rep->nb_elts;
	while (i < ind_fin)
	{
		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);   //même étape
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		if (tmp_nom == tmp_nom2)      //compare les deux noms
		{
			trouve = true;
			return i;
		}
		else 
		{
			i++;
		}
	}
	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	int size = strlen(s);
	
	for (int i = 0; i < size; i++)
	{
		if (isalnum(s[i]) == false)
		{
			int a = i;
			while (s[a + 1] != '\0') {
				*(s + a) = *(s + a + 1);
				a++;
			}
		}
	}

	return;
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	errno_t err;
	FILE *fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) {   //on vérifie que le fichier est ouvert
		err = ERROR;
		return err;
	}
	for (int i = 0; i < rep->nb_elts; i++) {      //pour tous les éléments du tableau
		fprintf(fic_rep, "%s%c", rep->tab[i].nom, SEPARATEUR);           //on écrit dans le fichier on ecrit les noms prenoms et tel des contacts 
		fprintf(fic_rep, "%s%c", rep->tab[i].prenom, SEPARATEUR);
		fprintf(fic_rep, "%s\n", rep->tab[i].tel);

	}
	if (feof(fic_rep) == true) {
		fclose(fic_rep);			// si la fin du fichier est atteint on le ferme
	}
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */