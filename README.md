# Description
Pong de AstralArchitect. Requiert GTK 3 installé.
# Comment jouer
Le principe du jeu est très similaire au pong classique, vous déplacez une pagaie (vous êtes la verte) pour faire rebondir la balle sur l'adversaire alors imbattable.
## Le but du jeu
L'adversaire étant imbattable, le but est donc de faire rebondir la balle le plus de fois possible. Attention, les mouvement de la balle sont semi-aléatoires et accélérés.
## Comptage du score
Le score affiché sur le titre de la fenêtre correspond au nombre de fois que vous avez fait rebondir la balle. Si à la fin de la partie votre score est superieur à votre meilleur score, il sera enregistré dans ./score.bin.
## Fin de la partie
la partie s'arrète lorsque vous avez ratté la balle, c'est-à-dire que la balle est passé derrière vous car vous ne l'avez pas touché.

## Bon amusement

# Comment installer
Lorsque vous clonez le repository depuis github, vous ne téléchrger que le code source. Si vous voulez l'utiliser, il faudra donc le compiler.
Mais vous pouvez aussi utiliser les binaires (ils risquent de ne pas être totalement à jour) et il n'éxiste pas de version pour MacOS:
## binaires
### Windows
[Pong_launcher.exe](https://github.com/AstralArchitect/pong-GTK-binaries/raw/main/Windows/Pong_launcher.exe)
### Linux
[Pong_launcher](https://github.com/AstralArchitect/pong-GTK-binaries/raw/main/Linux/Pong_launcher)
