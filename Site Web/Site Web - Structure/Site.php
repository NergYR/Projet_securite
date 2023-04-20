
<html>

  <link href="https://fonts.googleapis.com/css?family=Inter&display=swap" rel="stylesheet">
  <script src="/socket.io/socket.io.js"></script>
  <script src="js/script.js"></script>

  <meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate">
  <meta http-equiv="Pragma" content="no-cache">
  <meta http-equiv="Expires" content="0">

    
    <p id="screen"></p>
    <p id="window"></p>
    <p id="page"></p>
  
  <head>
    <meta charset="utf-8">
    <title>Site controle d'accés</title>
    <link rel="stylesheet" href="css/style.css">
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>

  <body>

    
    <!-- Voici notre en‑tête principale utilisée dans toutes les pages
          de notre site web -->
    <header>
    </header>

    <nav>
    </nav>

    <style>
    </style>

    <div class="box">
        <p class="title">Controle d'accés - Liste élève</p>
        <div class="list-container">
        <button class="refresh-button" onclick="location.reload();">Rafraîchir la liste</button>
            <div class="list_font">
                <?php
                // Connexion à la base de données
                $dbhost = 'localhost';
                $dbuser = 'root';
                $dbpass = 'sti2d';
                $dbname = 'test_eleve';
                $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);

                // Vérification des erreurs
                if (!$conn) {
                    die('Impossible de se connecter : ' . mysqli_error());
                }

                // Récupération des données de la table
                $sql = "SELECT id, nom, prenom, heure FROM eleve";
                $result = mysqli_query($conn, $sql);

                if ($result->num_rows > 0) {
                    echo "<ul class='list'>";
                    while ($row = $result->fetch_assoc()) {
                        $heure_format = date('H:i:s', strtotime($row["heure"]));
                        echo "<li class='list_hover'>ID: " . $row["id"] . " - Nom: " . $row["nom"] . " - Prénom: " . $row["prenom"] . " - Heure: " . $heure_format . "</li>";
                    }
                    echo "</ul>";
                } else {
                    echo "Aucun résultat";
                }

                // Fermeture de la connexion à la base de données
                mysqli_close($conn);
                ?>
            </div>
        </div>
    </div>


    <!-- Ici nous mettons le contenu de la page -->
    <main>
      <!-- <span  class="e117_8">gejbd vdssd</span> -->
        
    </main>


    <style>
        /*
          Figma Background for illustrative/preview purposes only.
          You can remove this style tag with no consequence
        */
        body {background: rgba(108.37500303983688, 108.37500303983688, 108.37500303983688, 1); }

        .list_hover:hover {
          background-color: #fff;
          color: #494949;
          cursor: pointer;
        }
    </style>

    <div class="line"></div>

    <!-- Et voici notre pied de page utilisé sur toutes les pages du site -->
    <div class="box2">
      <footer>
        <p>©Copyright 2023 par Aurelien Muller. Tous droits reversés.</p>
      </footer>
    </div>

  </body>
</html>