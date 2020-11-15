<?php
function checkData($log, $pass, $email) {
    return preg_match("/^[a-z0-9-_]{2,20}$/i", $log) && preg_match("/^[a-z0-9-_]{2,20}$/i", $pass) && filter_var($email, FILTER_VALIDATE_EMAIL) !== false;
}

if (isset($_GET['login']) && isset($_GET['password']) && isset($_GET['email'])) {
    $db = mysqli_connect("localhost", "login", "password", "database");
    $log = $_GET['login'];
    $pass = $_GET['password'];
    $email = $_GET['email'];
    $data = mysqli_query($db, "SELECT * FROM `DB` WHERE `Username` = '{$log}' AND `Password` = '{$pass}'");
    $mails = mysqli_query($db, "SELECT * FROM `DB` WHERE `Email` = '{$email}'");
    if ($data->num_rows > 0 && checkData($log, $pass, $email)) {
        $row = mysqli_fetch_array($data);
        if ($mails->num_rows == 0 && $row['Email'] == 'null') {
            $headers = "From: Email confirmation <noreply@yourhost.site>\r\n";
            try {
                if (mail($email, 'Подтверждение почтового адреса', 'https://yourhost.site/FTL/User/Mail/confirm.php?key=' 
                    . openssl_encrypt($log . ';;;5' . $pass . ';;;5' . $email, 'aes256', 'ebb6da4f35d5c1cc51b0a3b66567bcb5'), $headers, "-f noreply@yourhost.site") == true)
                    echo 'OK';
                else
                    echo 'ERROR';
            } catch (Exception $ex) {
                echo 'ERROR';
            }
        } else
            echo "EXISTS";
    } else
        echo 'INCORRECT';
    mysqli_close($db);
}
?>