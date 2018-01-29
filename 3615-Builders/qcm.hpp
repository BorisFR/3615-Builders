#ifndef QCM_HPP
#define QCM_HPP

const PROGMEM uint8_t qcmLevel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5};
const PROGMEM uint8_t qcmCategories[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1, 2, 2};
const PROGMEM String qcmQuestions[] = {"Comment se nomme le compositeur de la musique de Star wars ?", "Quel est le titre de l´épisode IV ?", "Qui joue le rôle de Luke Skywalker dans les épisodes IV, V et VI de la Guerre des Etoiles ?", "Qui tient le rôle de la Princesse Leïa ?", "Quel personnage à la fois un acteur pour le tournage des scènes et un autre pour sa voix ?", "Quelle espèce est un gros quadrupède à fourrure ?", "Comment s'appelle l'héroine de Rogue One ?", "De quel couleur sont les vaisseaux de combat de Naboo ?", "De quelle couleur est la lame de Luke lors de son 2ème combat contre Vador ?", "De quelle espèce est Chewbacca ?", "Quel nom donne-t-on au rang d'apprenti Jedi ?", "Quel type de vaisseau utilise les rebelles sur Hoth ?", "Quel type de vaisseau utilise Luke lors de la bataille de Yavin ?", "Quelle technique Sith utilise Dark Vador pour punir ses subordonnés ?", "Qui a dit \"Outini, outini\" ?", "Comment se nomme le droïde dans Rogue One ?", "Comment se nomme le droïde qui détient une partie de la carte où trouver Luke ?", "Quel est le nom du droïde protocolaire accompagnant R2-D2 ?", "A bord de quoi s'enfuient Poe et Finn dans le réveil de la force ?", "Comment s'appelle la mère biologique de la Princesse Leia ?", "Comment se nomme le vaisseau appartenant à Han Solo ?", "Dans quoi atterisse luke, Leïa, Han et Chewbacca lors de leur fuite dans l'étoile noire ?", "En quoi se déguisent Han et Luke pour inflitrer l'étoile noire ?", "Par qui est recueilli Luke après sa naissance ?", "Que fait Kylo Ren au moment où il était censé tuer Rey ?", "Quel est cette fameuse phrase célèbre des Star Wars ?", "Quel est la particularité de C-3PO dans l'épisode IV \"Un nouvel espoir\" ?", "Quel ordre ordonne Palpatine d'éxécuter aux clonetroopers ?", "Quels sont les deux personnages qui figurent dans les 8 films et Rogue One ?", "Qui a donné a R2-D2 les plans de l'Arme absolue du pouvoir de l'Empire, l'Etoile de la Mort ?", "Qui est Dark Vador ?", "Qui est Dark Vador pour Luke ?", "Qui s'est fait cryogéniser dans la carbonite ?", "Qui tue Han Solo ?", "Qui tue le général Grievous ?", "Combien de films Star Wars ont été réalisés par George Lucas ?", "En quelle année a été tourné l'épisode 4 ?", "En quelle année a été tourné l'épisode L'Empire Contre-attaque ?", "En quelle année a été tourné l'épisode Le Retour Du Jedi ?", "En quelle année est sorti le film \"Star Wars : Un nouvel espoir\" ?", "Qui est le réalisateur de l'épisode IV ?", "Warwick \"wicket\" Davis a aussi participé à une autre grande saga au cinéma, laquelle ?", "Qu'est ce que Rogue One ?", "Qu'est ce qui alimente un sabre laser ?", "A quel âge Yoda meurt-il ?", "Combien de sabre laser le général Grievous utilise-t-il pour se battre ?", "Comment s'appelle le chasseur de prime que tue Han solo dans la Catina ?", "Comment se nomme le véhicule qu'utilise Luke pour retrouver R2-D2 sur Tatooine ?", "De quelle cité Lando Cadrissian est-il l'administrateur ?", "Jar Jar Binks a été banni de son peuple car ... ?", "Qu'est ce qu'un Mynock?", "Quel est le métier de Boba Fett ?", "Quel est le nom de code de Luke lors de la bataille de Yavin ?", "Quel est le nom général donné aux soldats de l'Empire Galactique ?", "Quel nom avait donné les rebelles à leur base sur Hoth ?", "Quelle est la principale activité des Jawas ?", "Qui dit à Vador que Leia est sa fille ?", "Combien d'enfants à eu Anakin ?", "Combien d'enfants Padmé met-elle au monde et comment s'appellent-ils ?", "Comment s'appele le fils de Han et Leïa ?", "Dans Star Wars V, qu'apprend Luke en allant voir Yoda ?", "De qui Qui Gon Jinn libére-t-il Anakin ?", "En quoi consiste la mission de Rogue One ?", "Pourquoi Chewbacca ne veut pas sauter dans le trou lors de l'évasion de Leïa ?", "Que propose-t-on à Obiwan lors de sa poursuite contre Zam Wesell dans les bas fonds de Coruscant ?", "Quel défaut a le premier droïde choisit par l'oncle Owen ?", "Quel est le nom du plus connu mais aussi maladroit des Gungans ?", "Quel secret cachent Padmé et Anakin parmi ces propositions ?", "Quelle espèce intelligente habite sur la lune forestière d'Endor ?", "Qui a construit C-3PO ?", "Qui est la Reine de Naboo dans l'Episode I, la Menace fantôme ?", "Qui prononce cette phrase \"C'est un piège !\" / \"It's a trap!\" ?", "Qui tue Jango Fett sur Geonosis ?", "Sur quelle planète habite Yoda ?", "Sur quelle planète Luke part-il en exil ?", "Sur quelle planète Rey et Finn se rencontrent ?", "Sur quelle planète se déroule la bataille finale de Rogue One ?", "Sur Tatooine, comment Obiwan Kenobi se fait-il appeller ?", "Comment Harisson Ford a t il été recruté ?", "Dans quel autres films trouve-t-on des références à Star Wars ?", "Pendant quel film George Lucas a-t-il entendu les termes R2-D2 ?", "Quel acteur au service de sa majesté fait un caméo dans le réveil de la force ?", "Quel acteur français a prêté sa voix à de nombreux personnages à la télé et à C-3PO ?", "Quel acteur interprête Dark Maul ?", "Quel rôle joue Ewan McGregor dans les Episodes I, II et III de la Guerre des Etoiles ?", "Quelle pays a servi de décor pour Tatooine ?", "De quelle espèce est Aayla Secura ?", "Quel est le nom de la bataille après laquelle le traité marquant la fin de l'Empire a été signé ?", "Quel est le point commun entre Yoda, Cookie Monster et Miss Piggy ?", "A quel jeu de cartes, ressemblant au poker, jouents Lando Calrissian et Han Solo ?", "Chewie vient de quelle planète ?", "Combien d'années s'écoulent entre l'épisode I et l'épisode II ?", "Comment s'appelle l'artefact dans lequel les Siths gardent leurs secrets ?", "Comment s'appelle la ville où se trouve la Cantina ?", "Comment s'appelle le copilote de Luke lors de la bataille sur Hoth ?", "Comment se nomme l'aide administrateur de Lando sur Bespin ?", "Comment se nomme l'espèce animale qu'utilise Luke et Han sur Hoth ?", "Comment se nomme la marionettiste qui gére et donne sa voix à Yoda", "Comment se nomme le capitaine qui accompagne Padmé dans la menace fantôme ?", "Comment se nomme le monstre affronté par Luke Skywalker et apprivoisé par Jabba le Hutt ?", "Comment se nomme le monstre qui attaque Luke sur Hoth ?", "Comment se nomme le vaisseau de la princesse Leïa au début de l'épisode IV ?", "Comment se nomme le véhicule des Jawas ?", "Dans quel pays se situe le tournage en extérieur pour Hoth ?", "Quelle est l'habitation de Rey sur Jakku ?", "De quel espèce est l'Amiral Ackbar ?", "De quelle espèce est Sebulba ?", "Laquelle de ces armes est un pistolet ?", "Par qui fut élevée la princesse Leïa ?", "Quel autre personnage que R2-D2, Kenny Baker interprète-t-il ?", "Quel est l'ordre que Sidious donne aux clones pour devoir tuer les Jedis en mission ?", "Quel est le maitre Jedi qui a un sabre violet ?", "Quel est le nom du maître Jedi ayant formé Obi-Wan Kenobi ?", "Quel est le nom du super destroyer que Dark Vador commanda ?", "Qui n'a pas le droit d'entrer dans la Cantina ?", "Sur quelle planète a lieu le début de la Guerre des clones ?", "Sur quelle planète Anakin se rend-il après avoir été converti au côté obscur ?", "Sur quelle planète se situe la forteresse personnelle de Dark Vador ?", "Sur quellle planète Dark Vador fut gravement blessé, l'obligeant à porter une armure ?", "Comment s'appellent les droïdes qui rendent le vaisseau d'Obi-Wan hors service ?", "Parmi les 6 chasseurs de primes engagés par Dark Vador, deux sont des droïdes, lesquels ?", "Que signifie R2-D2 ?", "Quel est le nom du Droïde choisit par l'oncle Owen ?", "A quel âge Padmé a-t-elle été élue Reine de Naboo ?", "A qui le sénateur Organa ordonne d'effacer la mémoire de C-3PO ?", "Cite la réplique culte de Dark Vador.", "Combien de chasseurs de primes sont présent avec Dark Vador ?", "Combien de fois Dark Vador a-t-il affronté son fils ?", "Combien de formes de communication parle C-3PO ?", "Combien de membres Anakin perd-il après son combat avec Obi-Wan ?", "Comment se nomme le gérant du restaurant que va rencontrer Obiwan sur Coruscant ?", "Comment se nomme le grand Moff qui ordonne la destruction d'Aldeeran ?", "Comment se nomme le vice-roi qui impose un blocus à Naboo ?", "Dans L'Episode II, l'attaque des clones, sur quelle planète se trouvent l'armée des clones ?", "Dans l´épisode V, sur quelle planète sont les rebelles ?", "La mère d'Anakin a été enlevée et tuée par qui ?", "Pourquoi Yoda part-il en exil sur Daghoba ?", "Pourquoi, au départ, Yoda ne veut pas enseigner la force à Luke ?", "Quel est le matricule de Finn ?", "Quel était le nom de l'Empereur Palpatine lorqu'il était Maitre Sith ?", "Quel Jedi blessa grièvement Anakin Skywalker ?", "Quel main se fait couper Luke lors de son 1er combat avec Vador ?", "Quelle fut la première mission d'Anakin en tant que seigneur sith ?", "Quelle planète a été effacée des archives du temple Jedi ?", "Qui a dit \"Toujours par deux ils vont, le maître et l'apprenti\" ?", "Qui dit : \"Je fais un avec la force et la force est avec moi\" ?", "Qui pilote le faucon lors de la bataille de l'étoile de la mort dans le Retour du Jedi ?", "Qui transmet la carte à Poe pour retrouver Luke ?", "Qui tue Jabba ?", "Sous quel nom de code sont cachés les plans de l'étoile noire ?", "Sur le cube de chance de Watto, quel couleur sauverait Anakin ?", "Que chercher à faire Finn lorsqu'il rencontre Rose dans les derniers Jedis ?", "Dans quel autre film Julian Glover et Harisson Ford se sont croisés ?", "Quel était le titre de film sous lequel se cachait \"le retour du Jedi\" pendant son tournage ?", "Quelle pays a servi de décor pour Yavin 4 ?", "Qui a joué Greedo en plus de Paul Blake ?", "Qui est le réalisateur de l'épisode VI, le Retour du Jedi en 1983 ?", "Quel rôle a interprêté Jack Purvis ?", "Sur quelle planète vivent les Wookies ?", "Avec quoi ont ils été inspiré pour la forme du Faucon Millenium ?", "Comment a faillit être traduit Luke Skywalker ?", "Comment s'appelle le vaisseau du général Grievous ?", "Comment s'appellent les deux agresseurs de Luke dans la Cantina ?", "Comment se nomme l'arme des Tuskens ?", "Comment se nomme l'Ewok qui subtilise un speederbike dans le retour du jedi ?", "Comment se nomme le chaman Ewok ?", "Comment se nomme le chasseur de prime qui veut tuer Padmé au début de l'attaque des clones ?", "Comment se nomme le maître Jedi de la même espèce que Yoda dans l'épisode I ?", "Comment se nomme le monstre qui attrape Luke dans le compacteur à déchets ?", "De combien de membres est composé le Conseil Jedi ?", "De quelle couleur est l'épaulette du Sandtrooper sergeant ?", "De quelle couleur est l'épaulette du Sandtrooper squad leader ?", "Quel amiral exécute Dark Vador pour incompétence ?", "Quel est le point de commun entre Oola et Bib Fortuna ?", "Quel surnom fut donné à la 501e légion qui accompagna Dark Vador dans ses campagnes ?", "Quelle est la couleur de la portion que Rey mange sur Jakkhu ?", "Quelle est la couleur du lait de Bantha ?", "Quelle est la couleur du lait de Sirène Thala ?", "Qui niche dans la fosse de Carkoon ?", "Sélectionne la couleur du sabre laser de Mace Windu.", "Quelle était la taille de l'acteur Kenny Baker qui jouait dans R2-D2 ?", "Quelles sont les couleurs de R2-M5 ?", "Comment se nomme le droïde qui soigne Luke aprés son combat contre Vador ?", "Quel droïde garde l'entrée du palais de Jabba ?", "A quoi jouent Chewbacca et R2-D2 sur le Faucon Millenium ?", "Comment se nomme l'espion de l'empire sur Mos Eisley ?", "Comment se nomme la mère d'Anakin ?", "Comment se nomme le droide qui accueille Qui Gon Jinn et Obiwan sur le vaisseau de la Fédération ?", "Laquelle de doublures de Padmé se fait tuer au début du second film ?", "Quel est la première planète détruite par l'Etoile noire ?", "Quel général mène l'attaque sur Hoth ?", "Qui dit : \"Je ne suis pas un jedi, mais je connais la force\" ?", "Combien d'Oscar a obtenu Star Wars en 1978 ?", "Comment était nommé le Faucon Millenium dans le script du premier Star Wars ?", "De quel langage est inspiré celui de Nien Nunb ?", "De quel langage est inspiré celui des Jawas ?", "Quel était le nom de code de L'Empire Contre-attaque lors de son tournage ?", "Sur quel son est basé le bruit d'un chasseur TIE ?", "Quelle est le nom Sith du Comte Dooku ?", "Quel est le nom du droide d'interrogation ?", "Si vous aviez une main coupée : à quel droïde demanderiez assistance ?"};
const PROGMEM String qcmAnswers[] = {"John Williams", "Un nouvel espoir", "Mark Hamill", "Carrie Fisher", "Dark Vador", "Bantha", "Jyn Erso", "Jaune", "Verte", "Un wookiee", "Un Padawan", "Snowspeeder", "X-wing", "Étranglement de force", "Un Jawa", "K2SO", "BB-8", "C-3PO", "Chasseur TIE", "Padmé Amidala", "Le Faucon Millenium", "Compacteur à déchets", "Stormtrooper", "Owen Lars", "Il tue Snoke à la place", "Que La force soit avec toi", "Il a une demi jambe argentée", "Ordre 66", "R2-D2 & C-3PO", "Leïa Organa", "Anakin Skywalker", "Son père", "Han Solo", "Kylo ren", "Obi Wan Kenobi", "4", "1977", "1979", "1982", "En 1977", "George Lucas", "Harry potter", "un faux nom de code", "Un cristal", "900 ans", "4", "Greedo", "Landspeeder", "La cité des nuages", "Il est trop maladroit", "Une bestiole", "Chasseur de primes", "Red V", "Des Stormtroopers", "Echo", "Ils capturent et revendent les droïdes", "Luke", "2", "2, Leïa et Luke", "Ben", "A contrôler ses dons de Jedi", "Watto", "Voler les plans de l'Etoile de la mort", "ça pue", "Des bâtons de la mort", "Motivator", "Jar Jar Binks", "Ils sont mariés", "Les Ewoks", "Anakin Skywalker", "Reine Amidala", "Amiral Ackbar", "Mace windu", "Dagobah", "Ach-to", "Jakku", "Scarif", "Ben", "Il donnait la réplique aux candidats du casting", "Indiana Jones", "American Graffiti", "Daniel Craig", "Roger Carel", "Ray park", "Obi-Wan Kenobi", "Tunisie", "Twi'lec", "La bataille de Jakku", "Frank oz", "Au Sabacc", "Kashyyyk", "10 ans", "Holocron", "Mos Eisley", "Dak", "Lobot", "Tauntaun", "Frank Oz", "Panaka", "Rancor", "Wampa", "Tantive IV", "Sandcrawler", "Norvège", "AT-TT", "Mon Calamari", "Dug", "DL-44", "Bail Organa", "Un ewok", "L'ordre 66", "Mace Windu", "Qui-Gon Jinn", "Executor", "Les Droïdes", "Géonosis", "Mustaphar", "Mustaphar", "Mustaphar", "Des vibro-droïdes", "IG-88 et 4-LOM", "Reel 2 Dialog 2", "R5-D4", "14", "Capitaine Antilles", "Non, je suis ton père", "6", "2", "6 millions", "3", "Dexter Jettster", "Tarkin", "Nute Gunray", "Sur Kamino", "Sur Hoth", "Des Tuskens", "Car il a perdu son combat contre Palpatine", "Trop vieux", "FN 2187", "Dark Sidious", "Obi-Wan Kenobi", "Droite", "L'attaque du temple jedi de Coruscant", "Kamino", "Yoda", "Chirrut Îmwe", "Lando Calrissian", "Lor San Tekka", "Princesse Leïa", "Nébuleuse", "Bleue", "Il veut s'enfuir", "Indiana Jones et la dernière croisade", "Blue Harvest", "Guatémala", "Maria De Aragorn", "Richard Marquand", "Gonk", "Kashyyyk", "Un hamburger & une olive", "Luc Courleciel", "La Main invisible", "Ponda Baba et Dr Evazan", "Gaderffii", "Paploo", "Logray", "Zam Wesell", "Yaddle", "Dianoga", "De 12 membres", "Blanche", "Orange", "Ozzel", "Espèce", "Poing de Vador", "Verte", "Bleu", "Vert", "Un sarlacc", "Violet", "112 cm", "Blanc et rouge", "2-1B", "TT-8L", "Dejarik", "Garindan", "Shmi", "TC-14", "Cordé", "Jedha", "Veers", "Maze Kanata", "7", "Le Vaisseau Pirate", "Dialecte Kenyan", "Dialectes Zulu", "Chapitre 2", "Le barissement d'un éléphant", "Dark Tyranus", "IT-0", "2-1B"};
const PROGMEM String qcmFalse1[] = {"James Horner", "La revanche des Sith", "David Prowse", "Sissy Spacek", "C3PO", "Tauntaun", "Kathleen Airso", "Gris", "Bleue", "Un moonkiee", "Un Wampa", "Snowing", "A-wing", "Éclairs de force", "Un Ewok", "K3S3", "R2-D2", "C-1PO", "Bombardier", "Breha Organa", "Le Lady Luck", "Chaufferie", "Officier impérial", "Unkar plutt", "Il élimine les gardes de Snoke puis s'enfuit", "Que La force soit sur toi", "Il a un bras rouge", "Ordre 69", "Chewbacca & Ackbar", "Luke Skywalker", "Luke Skywalker", "Son oncle", "Luke Skywalker", "Hux", "Anakin", "3", "1975", "1978", "1981", "En 1980", "Steven Spielberg", "le seigneur des anneaux", "Un rebelle", "Des piles", "800 ans", "2", "Freddo", "Earthspeeder", "La cité des étoiles", "Il est trop laid", "Un véhicule", "Tueur a gages", "Red leader", "Des Palpatiniers", "Crait", "Ils sont agriculteurs", "Palpatine", "3", "2, Leïa et Lucas", "Kylo", "A piloter un vaisseau", "Unkar plutt", "Tuer Dark Vador", "c'est trop étroit", "Du lait de Bantha", "Utiliy arm", "A'Sharad Hett", "La véritable identité de Palpatine", "Les Nautolans", "Han Solo", "Reine Jamillia", "Mon Mothma ", "Obi wan Kenobi", "Naboo", "Dagobah", "Tatooine", "Jedah", "Ken", "Il a passé le casting face à Kurt Russel", "Star Trek", "THX-1138", "Roger Moore", "Philippe Dumat", "Irvin Keshner", "Anakin Skywalker", "Egypte", "Kaminoen", "La bataille d'Endor", "John Henson", "Au Sarlacc", "Hoth", "8 ans", "Holoprojecteur", "Mos Espa", "Biggs", "Gabot", "Bantha", "John Kermit", "Antilles", "Bubo", "Bantha", "Xwing", "Landcrawler", "Canada", "AT-ST", "Géonosien", "Lasat", "DLT-19", "Padme Amidala", "Un Jawa", "L'ordre 64", "Maître Yoda", "Yoda", "Basilic", "Les Sullustéens", "Kamino", "Geonosis", "Coruscant", "Géonosis", "Des droïdes de combat", "IG-90 et C-21", "Robot 2 Detecteur 2", "R5-J3", "16", "Capitaine Typhoo", "Pas avant que mon mot à dire, j'aurai", "5", "1", "10 millions", "2", "Huggy kyyk", "Ozzel", "Lott Dod", "Sur Dantooine", "Sur Aldérande", "Des Wookies", "Car une prophétie lui dit d'attendre la venue de Luke", "Trop puissant", "THX1138", "Dark Tyranus", "Mace Windu", "Gauche", "L'élimination des leaders séparatistes", "Aldorande", "Mace windu", "Yoda", "Han solo", "Lord San Jakku", "Luke Skywalker", "Trinité", "Rouge", "Il veut réparer quelques choses", "Frantic", "JAK production", "Mexique", "Un animatronic", "Georges Lucas", "R4-P17", "Endor", "Une pizza & un hot dog", "Luke Cielmarche", "Le Black Pearl", "Kabe & Muftak", "Masstue", "Wicket", "Paploo", "Jango Fett", "Yabbo", "Dagoma", "De 10 membres", "Rouge", "Blanche", "Palleon", "Cousins", "Bras droit de Vador", "Marron foncé", "Blanc", "Blanc", "Un Rancor", "Vert", "107 cm", "Blanc et bleu", "R2 Medical", "C-3PX", "Jokari", "Zuckuss", "Beru", "C-5P2", "Sabé", "Aldorande", "Ozzel", "Leia Organa", "3", "YT-1300", "Dialecte Zulu", "Inuit", "Episode 2", "Le rugissement d'un lion", "Dark Sidious", "IG-88", "L8-L9"};
const PROGMEM String qcmFalse2[] = {"James Williams", "L'Empire contre attaque", "Alec Guinness", "Faye Dunaway", "Palpatine", "Dewback", "Yasmine Erco", "Rouge", "Violette", "Un Bookiee", "Un Sarlaac", "Snowair", "Y-wing", "Implosion", "Salacious Crumb", "K1S4", "C-3PO", "C-5PO", "Capsule de sauvetage", "Beru Whitesun", "Le Leviathan", "Vestiaire", "Imperial gunner", "Dr Evazan", "Il refuse et préfère être tué par Rey devant Snoke", "Que La force t'accompagne", "Il a des doigts en moins", "1er Ordre", "Palpatine & Jabba", "Padmé Amidala", "Obi-Wan Kenobi", "Son cousin", "Lando Calrissian", "Capitaine Phasma", "Yoda", "5", "1976", "1980", "1983", "En 1983", "Peter Jackson", "Hunger games", "Le nom d'une opération", "La Force", "1000 ans", "1", "Boba", "Autospeeder", "La cité du ciel", "Il est trop idiot", "Une arme", "Garde de Jabba The Hutt", "Red 7", "Des Empiristes", "Bok", "Ils sont mécaniciens", "Leia", "4", "3, Ayla, Muke et Suke", "Anakin", "A bâtir une maison pour sa famille", "Jabba", "Détruire le champ de protection protégeant la demeure de l'empereur", "c'est trop chaud", "Des sucettes kipik", "Antenne", "Yaddle", "Ils sont témoins du meurtre du précédent chancelier", "Les Voxyns", "Luke Skywalker", "Reine Apailana", "Crix Madine", "Plo Koon", "Onderon", "Bespin", "Jedah", "Endor", "Obi", "George Lucas l'a rencontré dans la rue", "Les Goonies", "Un nouvel espoir", "Timothy Dalton", "Henri Labussière", "Jack Purvis", "Le Capitaine Panaka", "Mexique", "Humain", "La bataille de Yavin", "George Lucas", "Au Barlacc", "Kamino", "19 ans", "Dark Crystal", "Mos tafar", "Jek", "Robot-1", "Wampa", "Steve Gonzo", "Typho", "Mynock", "Tauntaun", "Hammerwing", "Earthcrawler", "Etats unis (Alaska)", "Hutte", "Gungan", "Togruta", "DC-15", "Owen Lars", "Un Ugnaught", "L'ordre 65", "Ki-Adi-Mundi", "Le comte Dooku", "Chimaera", "Les Wookies", "Utapau", "Tatooine", "Naboo", "Hoth", "Des bombo-droïdes", "000 et BT-1", "Rien du tout", "R2-BO", "18", "Capitaine madine", "Luke, je suis ton père", "7", "3", "30 millions", "1", "Freezer ster", "Motti", "Dag Obert", "Sur Onderon", "Sur Ossus", "Des Ewoks", "Car il s'est soustrait de son rang de Jedi", "Trop petit", "TK2187", "Dark Plagueis", "Yoda", "Aucune", "La récupération des plans de l'étoile noire", "Géonosis", "Obiwan Kenobi", "Mace Windu", "Chewbacca", "Tor Jefa", "Chewbacca", "Deathstar", "Verte", "Il veut appeler Rey", "Blade Runner", "Purple Haze", "Venesuela", "Une image de synthèse", "Irvin Kershner", "2-1b", "Kachirho", "Une Apple pie & une glace", "Luc Marcheur", "Le destroyer 3 de la Fédération du commerce", "Figrin d'An & Tedn Dahai", "Picsskens", "Logray", "Warok", "Dengar", "Yoga", "diadora", "De 14 membres", "Noir", "Noir", "Piett", "Amants", "Glaive de Vador", "Beige", "Vert", "Rouge", "Un Varactyle", "Bleu", "98 cm", "Bleu et rouge", "C-R7", "B1", "Daktari", "Bossk", "Mon Mothma", "TX-03", "Saché", "Scarif", "Piett", "Jynn Erso", "0", "Le tas de ferraille", "Indien", "Vietnamien", "Episode V", "Le bruit d'un réacteur", "Dark Plagueis", "ID-10", "WA-7"};

#endif