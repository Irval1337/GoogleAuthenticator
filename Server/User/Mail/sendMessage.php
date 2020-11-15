<?php
function checkData($log, $pass) {
    return (preg_match("/^[a-z0-9-_]{2,20}$/i", $log) || filter_var($log, FILTER_VALIDATE_EMAIL) !== false) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass);
}

if (isset($_GET['login']) && isset($_GET['password']) && isset($_GET['text']) && isset($_GET['theme'])) {
    $db = mysqli_connect("localhost", "login", "password", "database");
    $log = $_GET['login'];
    $pass = $_GET['password'];
    $text = $_GET['text'];
    $theme = $_GET['theme'];
    $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Username` = '{$log}' AND `Password` = '{$pass}'");
    if (filter_var($log, FILTER_VALIDATE_EMAIL) !== false && $data->num_rows <= 0)
        $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Email` = '{$log}' AND `Password` = '{$pass}'");
    if ($data->num_rows > 0 && checkData($log, $pass)) {
        $row = mysqli_fetch_array($data);
        if ($row['Email'] !== 'null') {
            $headers = "From: FTL <noreply@yourhost.site>\r\n";
            try {
                echo mail($row['Email'], $theme, $text, $headers, "-f noreply@yourhost.site") == true ? 'OK' : 'ERROR';
            } catch (Exception $ex) {
                echo 'ERROR';
            }
        } else
            echo "NO EMAIL";
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>