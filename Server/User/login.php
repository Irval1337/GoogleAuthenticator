<?php
require_once("User.php");
function checkData($log, $pass) {
    return (preg_match("/^[a-z0-9-_]{2,20}$/i", $log) || filter_var($log, FILTER_VALIDATE_EMAIL) !== false) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass);
}

if (isset($_GET['login']) && isset($_GET['password'])) {
    $db = mysqli_connect("localhost", "login", "password", "database");
    $log = $_GET['login'];
    $pass = $_GET['password'];
    $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Username` = '{$log}' AND `Password` = '{$pass}'");
    if (filter_var($log, FILTER_VALIDATE_EMAIL) !== false && $data->num_rows <= 0)
        $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Email` = '{$log}' AND `Password` = '{$pass}'");
    if ($data->num_rows > 0 && checkData($log, $pass)) {
        $row = mysqli_fetch_array($data);
        $user = new User();
        $user->Id = $row['Id'];
        $user->Username = $row['Username'];
        $user->Password = $row['Password'];
        $user->Email = $row['Email'];
        $user->Applications = json_decode($row['SecretKeys']);
        echo json_encode($user);
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>