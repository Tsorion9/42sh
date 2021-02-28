#!/bin/sh

# Usage: ./norme.sh path-to-norminette
# result: formatted.txt

PATH_TO_NORMINETTE=$1

echo "Checking codestyle"
$PATH_TO_NORMINETTE src/ includes/ libft/ > norme.txt && 
cat norme.txt | grep -v "Not a valid file" >norme1.txt &&
./format.py norme1.txt > formatted.txt &&
rm norme.txt norme1.txt &&
echo "Norme errors in saved in formatted.txt" ||
echo "Something went wrong"
