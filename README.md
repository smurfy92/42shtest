<h1>42sh man</h1>

PDF 42sh correction:

tabulation: c’est obligatoire ca peut nous baiser !
--> bash n'en affiche jamais avec le bouton tab ..
--> utilisation d'une combinaison de touches INEDITE ?



hdoc: 
- Testez l'existence et le fonctionnement du heredoc "<<", avec ses options (wtf ???)  et cas particuliers. 
cat << heredoc | cat -e ---> reste bloque dans le pipe

squote:
si plusieurs args en squote a partir du deuxieme args la premiere quote nest pas polish -> ret de check parenthese == 0;
appel check_parentheses(0) pr chaque arg ---> OK;

historic: (Ya pas de segflt)
- fais des truc bizarre si !num en plein milieu d’une cmd ---> normalement corrige avec ca ((i - 1 > 0 && TERM(cmd_line)[i - 1] == ' ') || (i == 0))

separateur ';':
- on fonctionnent pas comme bash, a voir si utile de le modifier

prompt ? Resolu (+ 6 au lieu de +4 a la fin de prompt() --> a checker)
-> bug edition de ligne sur la premiere ligne -> 2char sur la 2eme ligne puis \n

++ Trello: https://trello.com/b/WJXyMpVc/42sh
