<?php
require_once('Application.php');
if (isset($_GET['secretKey'])) {
    require_once('lib/GoogleAuthenticator.php');
    $ga = new GoogleAuthenticator;
    $app = new Application;
    $app->Secret = $_GET['secretKey'];
    $app->Code = $ga->getCode($_GET['secretKey']);
    echo json_encode($app);
}
?>