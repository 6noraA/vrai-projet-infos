#!/bin/bash

# Nom du fichier CSV d'entrée


echo "Veuillez entrer le chemin du fichier CSV :"
read chemin_du_fichier


input_csv="$chemin_du_fichier"

# Vérifier si le fichier CSV d'entrée existe
if [ ! -f "$input_csv" ]; then
  echo "Le fichier $input_csv n'existe pas."
  exit 1
fi

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <d1|d2|l>"
  exit 1
fi

# Script de compilation

# Définir le chemin vers les fichiers source et d'en-tête
SRC_DIR="src"
MAIN_FILE="./progc/main.c"
AVL_FILE="./progc/avl.c"
HEADER_FILE="./progc/avl.h"

# Compiler les fichiers source
gcc -o mon_programme $MAIN_FILE $AVL_FILE -I$SRC_DIR -Wall -Wextra -std=c99

# Vérifier si la compilation a réussi
if [ $? -eq 0 ]; then
    echo "Compilation réussie. Vous pouvez exécuter le programme en utilisant './mon_programme <fichier_donnees>'."
else
    echo "Erreur lors de la compilation."
fi

executable="./progc/mon_programme"  # Changez ceci si vous avez un autre nom d'exécutable

# Vérifier si l'exécutable existe
if [ -x "$executable" ]; then
    echo "L'exécutable $executable existe."
else
    echo "L'exécutable $executable n'a pas été trouvé. Veuillez compiler le programme C avant d'exécuter ce script."
    exit 1  # Quitter le script avec un code d'erreur
fi

# Reste du script...



temps_debut=$(date +%s)

case $1 in
  "d1")
    temps_debut_d1=$(date +%s)
    temp_file="temp.txt"
    {
  awk -F';' '$2 == "1" {print}' "$input_csv" > "$temp_file"
  sort -t';' -k6,6 "$temp_file" > "${temp_file}_sorted"
  mv "${temp_file}_sorted" "$temp_file"
}




temps_debut=$(date +%s)
conducteurs_plus_frequents=$(awk -F';' '{print $6}' "$temp_file" | sort | uniq -c | sort -nr | head -n 10)
temps_fin=$(date +%s)
temps_total=$((temps_fin - temps_debut))
# Afficher les 10 conducteurs les plus fréquents avec leur nom de famille
echo "Les 10 conducteurs les plus fréquents dans le fichier $temp_file :"
echo "$conducteurs_plus_frequents" > tmpD1.txt
while read -r line; do
  prenom=$(echo "$line" | awk '{print $2}')
  nom=$(awk -F';' -v p="$prenom" '$6 ~ p {print $7}' "$temp_file" | sort -u)
done <<< "$conducteurs_plus_frequents"

awk '{print $2, $3 ";" ,$1}' tmpD1.txt > tempD1.txt
rm tmpD1.txt
rm temp.txt



gnuplot D1.gnu 
convert -rotate 90 big_test.png bigtest.png
rm big_test.png


    ;;

  "d2")
    echo "Traitement -d2 en cours..."
    awk -F ';' '{total[$6]+=$5} END {for (i in total) print total[i], i}' "$input_csv" | sort -k1nr | head -n 10 > temp.txt
    awk '{print $2, $3 ";", $1}' temp.txt > temps.txt
    rm temp.txt
    echo "Top 10 des distances totales par conducteur sauvegardé dans temps.txt"
    gnuplot graphe2.gnu
    convert -rotate 90 D2.png hD2.png
    rm D2.png
    ;;

  "l")
    echo "Traitement -l en cours..."
    LC_NUMERIC=C awk -F ';' '{distance[$1]+=$5} END {for (i in distance) print i, distance[i]}' "$input_csv" | sort -k2nr,2 | head -n 10 | sort -k1nr,1 > resultatsL.txt

    gnuplot L.gnu
    ;;
   "t")
	echo "traitement -t en cours..."
	temp3="temp.txt"
	if [ $? -eq 0 ]; then
    echo "premier tri en cour..."
    ./"$executable" "$input_csv" > "$temp3"
    echo "c'est presque fini..."
    awk -F ';' '{print $0}' "$temp3" | sort -n -r -t ';' -k3 | head -n 10 > "temp2.txt"
    echo "traitement terminé."
    rm temp.txt
	else
    echo "Erreur lors de la compilation du programme C."
fi
	gnuplot t.gnu
    ;;
  *)
    echo "Option non reconnue. Utilisation : $0 <d1|d2|l>"
    exit 1
    ;;
esac

temps_fin=$(date +%s)
temps_total=$((temps_fin - temps_debut))

echo "Le traitement a été effectué en $temps_total secondes."

# Déplacement des fichiers images générés
mv *.txt temp
mv "image"/*.png "demo/"
mv *.png image

echo "Tous les traitements ont été effectués avec succès."

