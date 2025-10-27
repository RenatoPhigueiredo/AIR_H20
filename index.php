<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <title>Medidor de Nível de Água</title>
    <meta http-equiv="refresh" content="3"> 
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background: #eef; }
        #nivel { font-size: 3em; color: #0077cc; }
    </style>
</head>
<body>
    <h1>💧 Medidor de Nível de Água</h1>
    <p>Nível atual:</p>
    <div id="nivel">
        <?php
        $arquivo = "nivel.txt";
        if(file_exists($arquivo)){
            $nivel = file_get_contents($arquivo);
            echo $nivel;
        } else {
            echo "--";
        }
        ?>
    </div>
</body>
</html>
