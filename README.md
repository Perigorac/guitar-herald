# Guitar Herald

A la 96ème Olympiade de l'an -396, l'épreuve d'hérauts et de trompettes se déroule pour la première fois. À l'âge des courses de chars et de la lutte nue, des athlètes hors du commun s'affrontent sur leur virtuosité. Dans Guitar Herald, armez vous de votre Lyre 8 choeurs et revivez le frisson de cette épreuve mythique en interprétant des musiques cultes comme l'Épitaphe de Sekilos. Il faudra jouer les notes en rythme, mais aussi les accords, les notes liées, et des ornements supplémentaires pour obtenir du score bonus. 
Le record est actuellement détenu par le lyriste grec (?) Mathos. Pourrez vous le battre et prétendre au titre de Champion?

![Screenshot](./CompteRendu/Screenshot.png)
## Regles

GUITAR HERALD se joue au clavier, avec les 8 touches QSDF JKLM représentant les 8 cordes de la lyre. Au fur et à mesure de la musique, des notes défilent sur l'écran : au moment où la note touche la corde horizontale, appuyez sur la touche correspondante pour jouer la note et gagner des points !

Une note non jouée retire 5 points de score, une note bien jouée ajoute 5 points. Si vous avez la maladresse de pincer une corde au mauvais moment, vous perdez 1 point.
Les notes bonus, en rouge, sont plus difficiles à jouer et rapportent au moins 10 points : elles ne retirent pas de points si elles sont manquées.
Les barres de strum descendent sur toutes les cordes et nécessitent donc d'appuyer rapidement sur toutes les touches ! Si cela est réussi, vous gagnez 10 points.

## Manuel d'installation

Sous linux, il suffit de tapper la commande `make` dans le dossier `./game/`. Si vous n'avez pas installé le moteur graphique SFML2, il faut tapper `sudo apt-get install libsfml-dev`. 
Pour lancer le jeu, lancer `GUITAR-HERALD`.

## Explication des développeurs
![Diagramme UML](https://github.com/Perigorac/guitar-herald/blob/main/CompteRendu/UMLv1.2.png?raw=true)

### Résumé des classes

Les **FallingObject** sont, comme leur nom l'indique, une classe abstraite d'objets qui tombent : tout ce qu'on appelle une "note" dans GUITAR HERALD. Ces notes se spécialisent en **StrumLine**, une barre horizontale nécessitant de pincer au moins 6 des cordes, pour des raisons techniques : SFML a du mal à gérer des appuis de plus de 6 touches en même temps. 
Le reste des notes tombent sous la qualification de **RoundPuck**, des objets qui occupent une corde et qui nécessitent un appui sur cette même corde. Ainsi, **NormalPuck** désigne les notes habituelles, **BonusPuck** les palets bonus qui sont de couleur différente et ne font pas perdre de points si ils ne sont pas appuyés.
Enfin, les **LongPucks** sont les notes longues dont le comportement diffère du reste des RoundPuck. Ils nécessitent de laisser appuyée une touche pendant un certain temps : en revanche, suite à des difficultés avec les collisions et les appuis longs dans SFML, ils ne sont malheureusement pas implémentés.

### Synchronisation

Dans un jeu de rythme, la synchronisation entre le jeu et la musique est essentielle. SFML met à notre disposition les Objets `Clock` et `Time`, qui permettent de rendre compte très précisément du temps OS écoulé entre deux évènements. Laisser tourner l'horloge pendant toute la durée d'une chanson n'est pas un problème : les objets `Time` sont un nombre de microsecondes stocké dans un `Int64`, ce qui fait en sorte que notre horloge ne subira pas d'overflow avant des milliers d'années !
Les fichiers de notes ont été méticuleusement écrits à l'aide d'Audacity, un logiciel libre, afin de retranscrire avec le timing le plus précis les notes de la chanson.

Note aux utilisateurs de WSL : il peut arriver, les quelques premières fois où vous lancerez le jeu, que la fenêtre de rendu mette du temps à apparaître, par exemple, si le message `Setting vertical sync not supported` apparaît avant la fenêtre. Dans ce cas, il y aura un décalage entre la musique et les graphismes : relancer l'éxécutable quelques fois règle ce problème.

### Les parties dont nous sommes les plus fiers

De part sa composition graphique attrayante, Guitar Herald réussi à nous plonger dans un autre temps avec une certaine authenticité historique. La chanson pour lyre et voix pré-chargée dans le jeu, nommée l'Épitaphe de Seikilos, est la plus ancienne composition musicale complète conservée par l'homme. C'est d'ailleurs sur la stèle de cet épitaphe que les notes défilent. Les lettres qu'on apperçoit sur les notes sont issues du système de notation de l'époque. 

Ce jeu permet de rajouter simplement de nouvelles pistes en s'inspirant de la première chanson "Sekilos.note" ce qui permet de faire vivre le jeu.

## Sources

Bibliographie :
 * https://en.wikipedia.org/wiki/Herald_and_Trumpet_contest

Musiques :
 * Épitaphe de Seikilos, *Inconnu*, Ier ou IIeme siècle
 * Wretched Shades, Darren Korb, 2020

Polices : 
 * **Metal Lord** de Typodermic Fonts
 * **Pirho Herakles** de PRFonts
 * **Quivira** de Alexander Lange

Sources photographiques : 
 * https://commons.wikimedia.org/wiki/File:Ancient_Greek_theatre_at_Delphi,_Dlf474.jpg
 * https://commons.wikimedia.org/wiki/File:John_Martin_Le_Pandemonium_Louvre.JPG
 * https://www.worldhistory.org/uploads/images/3806.jpg?v=1599364805
 * https://commons.wikimedia.org/wiki/File:Barde_%C3%A0_la_lyre.jpg
