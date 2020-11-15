<?php
require_once("../Auth/Application.php");
function checkData($log, $pass){
    return (preg_match("/^[a-z0-9-_]{2,20}$/i", $log) || filter_var($log, FILTER_VALIDATE_EMAIL) !== false) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass);
}

if (isset($_GET['login']) && isset($_GET['password']) && isset($_GET['secretKey']) && isset($_GET['username']) && isset($_GET['site'])) {
    $db = mysqli_connect("localhost", "irval_ftl", "0WH4R6", "irval_ftl");
    $log = $_GET['login'];
    $pass = $_GET['password'];
    $data = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Username` = '{$log}' AND `Password` = '{$pass}'");
    if (filter_var($log, FILTER_VALIDATE_EMAIL) !== false && $data->num_rows <= 0)
        $data = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Email` = '{$log}' AND `Password` = '{$pass}'");
    if ($data->num_rows > 0 && checkData($log, $pass)) {
        $row = mysqli_fetch_array($data);
        $adding = "null";
        $app = new Application();
        $app->Secret = $_GET['secretKey'];
        $app->Login = $_GET['username'];
        $app->Site = $_GET['site'];
        if ($row['SecretKeys'] !== 'null'){
            $secretKeys = json_decode($row['SecretKeys']);
            $exists = false;
            foreach ($secretKeys as &$key) {
                if ($key->Secret == $app->Secret)
                    $exists = true;
            }
            if ($exists === false)
                array_push($secretKeys, $app);
            $adding = json_encode($secretKeys);
        } else {
            $tmp = array();
            array_push($tmp, $app);
            $adding = json_encode($tmp);
        }
        echo mysqli_query($db, "UPDATE `FTL` SET `SecretKeys` = '{$adding}' WHERE `Username` = '{$log}' OR `Email` = '{$log}'") ? "OK" : "ERROR";
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>