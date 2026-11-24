<?php

$PAGES = [
    'index.php' => ['/', '/home'],
    'about.php' => ['/about', '/info'],
    'contact.php' => ['/contact']
];

$PAGES_NAMES = [
    'index.php' => 'Home',
    'about.php' => 'About',
    'contact.php' => 'Contact'
];

if (!isset($_SERVER['REQUEST_URI'])) {
    include 'pages/index.php';
} else {
    $requestUri = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
    $currPage = null; // Defaults to 404 page

    foreach ($PAGES as $page => $routes) {
        if (in_array($requestUri, $routes)) {
            $currPage = $page;
            break;
        }
    }
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <title>MPanel <?php echo $PAGES_NAMES[$currPage] ?? '404 Not Found'; ?></title>
    <style><?php include 'include/styles.css'; ?></style>
    <?php include 'include/head.html'; ?>
</head>
<body>

<?php
include 'include/navbar.html';

if ($currPage !== null) {
        include 'pages/' . $currPage;
} else {
    http_response_code(404);
    include 'pages/404.php';
}

?>
</body>
</html>