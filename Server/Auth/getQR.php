<?php
require_once('Application.php');
if (isset($_GET['secretKey']) && isset($_GET['login']) && isset($_GET['site'])) {
    require_once('lib/GoogleAuthenticator.php');
    $ga = new GoogleAuthenticator;
    $app = new Application;
    $app->QR = $ga->getUrl($_GET['login'], $_GET['site'], $_GET['secretKey']);
    $app->Login = $_GET['login'];
    $app->Secret = $_GET['secretKey'];
    $app->Site = $_GET['site'];
    echo json_encode($app);
}
?>