<?php
function checkData($log, $pass) {
    return (preg_match("/^[a-z0-9-_]{2,20}$/i", $log) || filter_var($log, FILTER_VALIDATE_EMAIL) !== false) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass);
}

if (isset($_GET['login']) && isset($_GET['newPassword'])) {
    $db = mysqli_connect("localhost", "login", "password", "database");
    $log = $_GET['login'];
    $pass = $_GET['newPassword'];
    $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Username` = '{$log}'");
    if (filter_var($log, FILTER_VALIDATE_EMAIL) !== false && $data->num_rows <= 0)
        $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Email` = '{$log}'");
    if ($data->num_rows > 0 && checkData($log, $pass)) {
        $row = mysqli_fetch_array($data);
        if ($row['Email'] !== 'null') {
            $headers = "From: Reset password <noreply@yourhost.site>\r\n";
            try {
                if (mail($row['Email'], 'Восстановление пароля', 'https://yourhost.site/FTL/User/resetPassword.php?key=' 
                    . openssl_encrypt($log . ';;;5' . $row['Email'] . ';;;5' . $_GET['newPassword'], 'aes256', 'ebb6da4f35d5c1cc51b0a3b66567bcb5')
                    , $headers, "-f noreply@yourhost.site") == true)
                    echo 'OK';
                else
                    echo 'ERROR';
            } catch (Exception $ex) {
                echo 'ERROR';
            }
        } else
            echo 'NO EMAIL';
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>