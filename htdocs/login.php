<?php
session_start();

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = "pandas";
    $password = "keras";

    // Check username and password
    if ($_POST["pandas"] == $username && $_POST["keras"] == $password) {
        $_SESSION["loggedin"] = true;
        header("Location: home.php");
        exit;
    } else {
        echo "Invalid username or password.";
    }
}

