<?php
require_once("User.php");
function checkData($log, $pass) {
    return preg_match("/^[a-z0-9-_]{2,20}$/i", $log) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass) && filter_var($log, FILTER_VALIDATE_EMAIL) == false;
}

if (isset($_GET['login']) && isset($_GET['password'])) {
    $db = mysqli_connect("localhost", "irval_ftl", "0WH4R6", "irval_ftl");
    $log = $_GET['login'];
    $pass = $_GET['password'];        
    $getname = mysqli_query($db, "SELECT * FROM `FTL` WHERE `Username` = '{$log}'");
    if (!checkData($log, $pass))
        echo 'INCORRECT';
    else if ($getname->num_rows > 0)
        echo 'EXISTS';
    else {
        $rezult = mysqli_query($db, "SELECT COUNT(1) FROM `FTL`");
        $id = mysqli_fetch_array($rezult)[0] + 1;
        $sql = "INSERT INTO `FTL` (`Id`, `Username`, `Email`, `Password`, `SecretKeys`) VALUES ('{$id}', '{$log}', 'null', '{$pass}', 'null')";
        $user = new User();
        $user->Id = $id;
        $user->Username = $_GET['login'];
        $user->Password = $_GET['password'];
        echo mysqli_query($db, $sql) ? 'OK ' . $id : 'ERROR'; 
    }
    mysqli_close($db);
}
?>