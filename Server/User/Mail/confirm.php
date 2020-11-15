<?php
function checkData($log, $pass, $email) {
    return preg_match("/^[a-z0-9-_]{2,20}$/i", $log) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass) && filter_var($email, FILTER_VALIDATE_EMAIL) !== false;
}

if (isset($_GET['key'])) {
    $dat = openssl_decrypt(str_replace(' ', '+', $_GET['key']), 'aes256', 'ebb6da4f35d5c1cc51b0a3b66567bcb5');
    $inf = explode(";;;5", $dat);
    $db = mysqli_connect("localhost", "irval_ftl", "0WH4R6", "irval_ftl");
    $data = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Username` = '{$inf[0]}' AND `Password` = '{$inf[1]}'");
    if ($data->num_rows > 0 && checkData($inf[0], $inf[1], $inf[2])) {
        $row = mysqli_fetch_array($data);
        if ($row['Email'] == 'null') {
            mysqli_query($db, "UPDATE `FTL` SET `Email` = '{$inf[2]}' WHERE `Username` = '{$inf[0]}' AND `Password` = '{$inf[1]}'");
            echo 'OK';
        }
        else
            echo "EXISTS";
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>