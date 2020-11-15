<?php
function checkData($log, $pass) {
    return (preg_match("/^[a-z0-9-_]{2,20}$/i", $log) || filter_var($log, FILTER_VALIDATE_EMAIL) !== false) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass);
}

if (isset($_GET['login']) && isset($_GET['password'])) {
    $db = mysqli_connect("localhost", "irval_ftl", "0WH4R6", "irval_ftl");
    $log = $_GET['login'];
    $pass = $_GET['password'];
    $data = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Username` = '{$log}' AND `Password` = '{$pass}'");
    if (filter_var($log, FILTER_VALIDATE_EMAIL) !== false && $data->num_rows <= 0)
        $data = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Email` = '{$log}' AND `Password` = '{$pass}'");
    if ($data->num_rows > 0 && checkData($log, $pass))
        echo mysqli_query($db, "UPDATE `FTL` SET `SecretKeys` = 'null' WHERE `Username` = '{$log}' OR `Email` = '{$log}'") ? "OK" : "ERROR";
    else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>